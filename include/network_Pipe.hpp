#pragma once
#ifndef network_Pipe_hpp
#define network_Pipe_hpp

// c++17
#include <map>
#include <thread>
#include <chrono>
#include <mutex>
#include <gtkmm.h>

// 나의 라이브러리
#include <network_Socket.hpp>

namespace network
{

class Pipe
{
    /*
     
     주의 :
     Pipe() 클래스는 프로세스 하나당 1개만 생성할 것.
     Pipe("server")는 모든 프로세스를 통틀어서 1개만 생성할 것.
     
     */
    
private:
    // 공유자원 잠금
    std::mutex pipe_mtx;
    
    // 파이프 정보
    bool server;            // 타입 : server
    bool client;            // 타입 : client
    
    // 주소 정보
    const char*          IP = (char*)"127.0.0.1";
    const unsigned short PORT = 9000;
    
    // 필드 : server
    Socket                          listen_sock;
    std::map<std::string, Socket>   client_sock;
    
    // 필드 : client
    Socket                          server_sock;
    std::string                     name;
    
public:
    Pipe(std::string type, std::string name="client_name")
    {
        // 변수들 초기화
        if (type == "server")
        {
            this->server = true;
            this->client = false;
            this->name   = "server";
        }
        else if (type == "client")
        {
            this->server = false;
            this->client = true;
            this->name   = name;
        }
        else throw std::runtime_error("network::Pipe() : 잘못된 생성자 인자 값입니다.");
        
        // 클라이언트와 서버간 연결 쓰레드 시작
        std::thread(&Pipe::thread_connect, this).detach();
    }
    ~Pipe()
    {
        // 소켓 해제 하기
        if (server)
        {
            listen_sock.close();
            for (auto& pair : client_sock) pair.second.close();
        }
        if (client)
        {
            server_sock.close();
        }
    }
    
private:
    // 클라이언트-서버 연결 함수
    void thread_connect()
    {
        // 서버
        if (server)
        {
            // 소켓 생성
            listen_sock = Socket(INADDR_ANY, PORT);
            
            // 소켓 준비
            listen_sock.bind();
            listen_sock.listen();
            
            // 클라이언트와 연결
            while (true)
            {
                
                // 클라이언트 소켓 얻기
                Socket client = listen_sock.accept();
                
                // 클라이언트 이름 얻기
                std::string name = client.recv();
                
                {
                    // 공유자원 잠금
                    std::lock_guard<std::mutex> lock(pipe_mtx);
                    
                    // 클라이언트 소켓 저장
                    client_sock[name] = client;
                }
                
                // 상태 출력
                printf("|  network::Pipe : 클라이언트(%s:%u)와 연결되었습니다.\n", client.get_ip().c_str(), client.get_port());
            }
        }
        // 클라이언트
        else
        {
            while (true)
            {
                // 소켓 생성
                server_sock = Socket(IP, PORT);
                
                // 서버와 연결
                server_sock.connect();
                
                // 서버에 이름 전송
                server_sock.send(name);
                
                // 상태 출력
                printf("|  network::Pipe : 서버(%s:%u)와 연결되었습니다.\n", server_sock.get_ip().c_str(), server_sock.get_port());
                
                // 서버와 연결 확인
                while (server_sock.is_connected())
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                
                // 서버와 연결이 끊기면
                server_sock.close();
            }
        }
    }
    
    // 소켓 수신 확인 함수
    void thread_recv_alart(const Glib::Dispatcher& dispatcher)
    {
        while (true)
        {
            // 0.1초 마다 확인
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // 소켓 수신 확인 : server
            if (server)
            {
                // 공유자원 잠금
                std::lock_guard<std::mutex> lock(pipe_mtx);
                
                for(auto& pair : client_sock)
                {
                    // 서버와 연결되어 있고, 소켓 버퍼에 내용이 들어 있다면 emit()
                    if (pair.second.is_connected() && pair.second.is_received()) dispatcher.emit();
                }
                continue;
            }
            
            // 소켓 수신 확인 : client
            if (client)
            {
                // 서버와 연결되어 있고, 소켓 버퍼에 내용이 들어 있다면 emit()
                if (server_sock.is_connected() && server_sock.is_received()) dispatcher.emit();
                continue;
            }
        }
    }
    
public:
    // 수신 알림 연결 함수
    void set_alert(const Glib::Dispatcher& dispatcher)
    {
        // 소켓 수신 알림 쓰레드 시작
        std::thread([&](){thread_recv_alart(dispatcher);}).detach();
    }
    
    // server 전용 : 전송
    void send(const std::string client_name, const std::string str)
    {
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            client_sock[client_name].send(str);
        }
        else
        {
            throw std::runtime_error("network::Pipe::send() : 서버만 사용 가능합니다.");
        }
    }
    
    // server 전용 : 수신
    std::string recv(const std::string client_name)
    {
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            return client_sock[client_name].recv();
        }
        else
        {
            throw std::runtime_error("network::Pipe::recv() : 서버만 사용 가능합니다.");
        }
    }
    
    // client 전용 : 전송
    void send(const std::string str)
    {
        if (client)
        {
            server_sock.send(str);
        }
        else
        {
            throw std::runtime_error("network::Pipe::send() : 클라이언트만 사용 가능합니다.");
        }
    }
    
    // client 전용 : 수신
    std::string recv()
    {
        if (client)
        {
            return server_sock.recv();
        }
        else
        {
            throw std::runtime_error("network::Pipe::recv() : 클라이언트만 사용 가능합니다.");
        }
    }
};


}

#endif /* network_Pipe_hpp */
