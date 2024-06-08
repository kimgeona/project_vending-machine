#pragma once
#ifndef network_Pipe_hpp
#define network_Pipe_hpp

// c++17
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <fstream>
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
     Pipe() 클래스를 [복사 생성자] 또는 [대입 연산자]를 이용하여 생성하지 말 것.
     
     */
    
private:
    // 공유자원 잠금
    std::mutex pipe_mtx;
    
    // 쓰레드 벡터
    std::vector<std::thread> threads;
    std::atomic<bool>        threads_exit;
    
    // 파이프 정보
    bool server;    // 타입 : server
    bool client;    // 타입 : client
    
    // 주소 정보
    const char*                     IP = (char*)"127.0.0.1";
    const unsigned short            PORT = 9000;
    
    // 필드 : server
    Socket                          listen_sock;
    std::map<std::string, Socket>   client_sock;
    
    // 필드 : client
    Socket                          server_sock;
    std::string                     name;
    
public:
    // 생성자
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
        
        // 쓰레드 종료 여부 저장
        threads_exit.store(true);
    }
    
    // 소멸자
    ~Pipe()
    {
        // 쓰레드 종료 여부 저장
        threads_exit.store(true);
        
        // 쓰레드 종료 기다리기
        for (auto& thread : threads) if (thread.joinable()) thread.join();
        
        // 쓰레드 제거하기
        threads.clear();
        
        // 소켓들을 해제한다
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            // listen_sock 해제
            listen_sock.close();
            
            // client_sock 해제
            for(auto& pair : client_sock) if (pair.second.is_connected()) pair.second.close();
        }
        if (client && server_sock.is_connected())
        {
            // server_sock 해제
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
            listen_sock = Socket(INADDR_ANY, PORT, 0);
            
            // 소켓 준비
            listen_sock.bind();
            listen_sock.listen();
            
            // 클라이언트와 연결
            while (!threads_exit.load())
            {
                // 클라이언트 소켓 얻기
                Socket sock = listen_sock.accept();
                
                // 클라이언트 소켓 확인
                if (!sock.state_use)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    continue;
                }
                
                // 클라이언트 이름 얻기
                std::string name = sock.recv();
                
                // 클라이언트 파일 얻기
                {
                    using namespace std;
                    using namespace std::filesystem;
                    
                    // 파일 이름 생성
                    std::string file_name = name + "_data.txt";
                    std::string file_name2 = name + "_log.txt";
                    
                    // 파일 데이터 받기
                    std::string file_data = sock.recv();
                    std::string file_data2 = sock.recv();
                    
                    // 기존 파일 제거
                    if (exists(path(file_name))) remove(path(file_name));
                    if (exists(path(file_name2))) remove(path(file_name2));
                    
                    // 파일 데이터 저장
                    std::ofstream fout(file_name), fout2(file_name2);
                    if (!fout | !fout2)
                    {
                        throw std::runtime_error("network::Pipe::thread_connect() : 파일("+ name +")을 열 수 없습니다.");
                    }
                    fout << file_data;
                    fout2 << file_data2;
                    if (!fout | !fout2)
                    {
                        throw std::runtime_error("network::Pipe::thread_connect() : 파일("+ name +")을 쓰는중 오류가 발생했습니다.");
                    }
                    fout.close();
                    fout2.close();
                    if (!fout | !fout2)
                    {
                        throw std::runtime_error("network::Pipe::thread_connect() : 파일("+ name +")을 닫는중 오류가 발생했습니다.");
                    }
                }
                
                // 클라이언트 소켓 저장
                {
                    // 공유자원 잠금
                    std::lock_guard<std::mutex> lock(pipe_mtx);
                    
                    // 기존 소켓이 있다면 지우기
                    if (client_sock.find(name)!=client_sock.end())
                    {
                        // 상태 출력
                        printf("|  network::Pipe : 클라이언트(%s:%u)와 연결이 해제 되었습니다.\n", client_sock[name].get_ip().c_str(), client_sock[name].get_port());
                        
                        // 소켓 닫기
                        client_sock[name].close();
                    }
                    
                    // 소켓 저장
                    client_sock[name] = sock;
                }
                
                // 상태 출력
                printf("|  network::Pipe : 클라이언트(%s:%u)와 연결되었습니다.\n", sock.get_ip().c_str(), sock.get_port());
            }
        }
        
        // 클라이언트
        if (client)
        {
            while (!threads_exit.load())
            {
                // 소켓 생성
                Socket sock = Socket(IP, PORT);
                
                // 서버와 연결
                sock.connect();
                
                // 클라이언트 소켓 확인
                if (!sock.state_use)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    continue;
                }
                
                // 서버에 이름 전송
                sock.send(name);
                
                // 서버에 파일 전송
                {
                    // 파일 불러오기
                    std::ifstream fin(name + "_data.txt"), fin2(name + "_log.txt");
                    if (!fin || !fin2)
                    {
                        throw std::runtime_error("network::Pipe::thread_connect() : 파일("+ name +")을 열 수 없습니다.");
                    }
                    std::ostringstream oss, oss2;
                    oss << fin.rdbuf();
                    oss2 << fin2.rdbuf();
                    
                    // 파일 데이터 추출
                    std::string data = oss.str();
                    std::string data2 = oss2.str();
                    
                    // 파일 데이터 전송
                    sock.send(data);
                    sock.send(data2);
                    
                    // 파일 닫기
                    fin.close();
                    fin2.close();
                    if (!fin | !fin2)
                    {
                        throw std::runtime_error("network::Pipe::thread_connect() : 파일("+ name +")을 닫는중 오류가 발생했습니다.");
                    }
                }
                
                // 화면 새로 고침 명령어 전송
                sock.send("refresh");
                
                // 클라이언트 소켓 저장
                {
                    // 공유자원 잠금
                    std::lock_guard<std::mutex> lock(pipe_mtx);
                    
                    // 소켓 저장
                    server_sock = sock;
                }
                
                // 상태 출력
                printf("|  network::Pipe : 서버(%s:%u)와 연결되었습니다.\n", server_sock.get_ip().c_str(), server_sock.get_port());
                
                // 서버와 연결 확인
                while (true)
                {
                    {
                        // 공유자원 잠금
                        std::lock_guard<std::mutex> lock(pipe_mtx);
                        
                        // 서버와 연결 확인
                        if (threads_exit.load() || !server_sock.is_connected())
                        {
                            // 상태 출력
                            printf("|  network::Pipe : 서버(%s:%u)와 연결이 해제 되었습니다.\n", server_sock.get_ip().c_str(), server_sock.get_port());
                            
                            // 서버와 연결이 끊기면
                            server_sock.close();
                            
                            // 서버와 연결 확인 반복문 종료
                            break;
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }
        }
        printf("|  network::Pipe::thread_connect : 종료\n");
    }
    
    // 클라이언트-서버 연결 확인 함수
    void thread_connect_check()
    {
        if (server) while (!threads_exit.load())
        {
            // 클라이언트 이름과, 클라이언트 소켓
            bool        find = false;
            std::string name = "";
            Socket      sock;
            
            {
                // 공유자원 잠금
                std::lock_guard<std::mutex> lock(pipe_mtx);
                
                // 연결이 끊긴 소켓 확인
                for(auto& pair : client_sock)
                {
                    if (!pair.second.is_connected())
                    {
                        name = pair.first;
                        sock = pair.second;
                        find = true;
                        break;
                    }
                }
                
                if (find)
                {
                    // 상태 출력
                    printf("|  network::Pipe : 클라이언트(%s:%u)와 연결이 해제 되었습니다.\n", sock.get_ip().c_str(), sock.get_port());
                    
                    // 소켓 닫기
                    sock.close();
                    
                    // 제거
                    client_sock.erase(name);
                }
            }
            
            // 0.1초 마다 확인
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        if (server) printf("|  network::Pipe::thread_connect_check : 종료\n");
    }
    
    // 소켓 수신 확인 함수
    void thread_recv_alart(const Glib::Dispatcher& dispatcher)
    {
        while (!threads_exit.load())
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
                // 공유자원 잠금
                std::lock_guard<std::mutex> lock(pipe_mtx);
                
                // 서버와 연결되어 있고, 소켓 버퍼에 내용이 들어 있다면 emit()
                if (server_sock.is_connected() && server_sock.is_received()) dispatcher.emit();
                continue;
            }
        }
        printf("|  network::Pipe::thread_recv_alart : 종료\n");
    }
    
public:
    // 클라이언트-서버 연결 함수
    void start()
    {
        // 쓰레드 종료 여부 저장
        threads_exit.store(false);
        
        // 클라이언트-서버 연결 쓰레드 시작
        threads.emplace_back(&Pipe::thread_connect, this);
        
        // 클라이언트-서버 연결 확인 쓰레드 시작
        threads.emplace_back(&Pipe::thread_connect_check, this);
    }
    
    // 수신 알림 연결 함수
    void alert(const Glib::Dispatcher& dispatcher)
    {
        // 쓰레드 종료 여부 저장
        threads_exit.store(false);
        
        // 소켓 수신 알림 쓰레드 시작
        threads.emplace_back(&Pipe::thread_recv_alart, this, std::ref(dispatcher));
    }
    
    // 클라이언트-서버 연결 종료 함수
    void end()
    {
        // 쓰레드 종료 여부 저장
        threads_exit.store(true);
        
        // 쓰레드 종료 기다리기
        for (auto& thread : threads) if (thread.joinable()) thread.join();
        
        // 쓰레드 제거하기
        threads.clear();
        
        // 소켓들을 해제한다
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            // listen_sock 해제
            listen_sock.close();
            
            // client_sock 해제
            for(auto& pair : client_sock) if (pair.second.is_connected()) pair.second.close();
        }
        if (client && server_sock.is_connected())
        {
            // server_sock 해제
            server_sock.close();
        }
    }
    
    
public:
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
    
    // server 전용 : 어떤 클라이언트가 데이터를 보냈는지 확인
    std::string check_who_send_it()
    {
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            // 클라이언트 이름
            std::string client_name = "";
            
            // 어떤 클라이언트에서 들어왔는지 확인
            for (auto& pair : client_sock)
            {
                // 서버와 연결되어 있고, 소켓 버퍼에 내용이 들어 있다면 emit()
                if (pair.second.is_connected() && pair.second.is_received()) client_name = pair.first;
            }
            
            // 클라이언트 이름 반환
            return client_name;
        }
        else
        {
            throw std::runtime_error("network::Pipe::check_who_send_it() : 서버만 사용 가능합니다.");
        }
    }
    
    // server 전용 : 클라이언트 연결 확인
    bool is_connected(std::string client_name)
    {
        if (server)
        {
            // 공유자원 잠금
            std::lock_guard<std::mutex> lock(pipe_mtx);
            
            // 해당 클라이언트가 존재하는지 확인
            if (client_sock.find(client_name)==client_sock.end()) return false;
            
            // 클라이언트 연결 확인
            return client_sock[client_name].is_connected();
        }
        else
        {
            throw std::runtime_error("network::Pipe::is_connected() : 서버만 사용 가능합니다.");
        }
    }
    
public:
    // client 전용 : 서버 연결 확인
    bool is_connected()
    {
        if (client)
        {
            return server_sock.is_connected();
        }
        else
        {
            throw std::runtime_error("network::Pipe::is_connected() : 클라이언트만 사용 가능합니다.");
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
    
public:
    // IP 주소 얻기
    std::string get_ip(const std::string client_name="")
    {
        if (server) return client_sock[client_name].get_ip();
        if (client) return server_sock.get_ip();
    }
    
    // PORT 번호 얻기
    std::string get_port(const std::string client_name="")
    {
        if (server) return std::to_string(client_sock[client_name].get_port());
        if (client) return std::to_string(server_sock.get_port());
    }
};


}

#endif /* network_Pipe_hpp */
