#pragma once
#ifndef network_Socket_hpp
#define network_Socket_hpp

// c++17
#include <thread>
#include <chrono>
#include <mutex>

// 소켓 프로그래밍 관련
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cerrno>


namespace network
{


class Socket
{
    /*
     
     주의 :
     파생된 스레드에서 [복사 생성자]와, [대입 연산자] 사용은 하지 말것.
     해당 함수들은 공유자원 보호 적용이 안됨.
     
     */
    
public:
    // 공유자원 잠금
    std::mutex socket_mtx;
    
    // 소켓 정보
    int info_time_out;
    
    // 소켓 상태
    bool state_sock;
    bool state_sock_addr;
    bool state_sock_len;
    bool state_bind;
    bool state_listen;
    bool state_use;
    
    // 소켓 정보
    int                 sock;       // 소켓
    struct sockaddr_in  sock_addr;  // 소켓 주소 구조체
    socklen_t           sock_len;   // 소켓 길이
    
    // 생성자
    Socket()
    {
        // 소켓 초기화
        sock = -1;
        
        // 소켓 주소 구조체 초기화
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        
        // 소켓 길이 초기화
        sock_len = sizeof(sock_addr);
        
        // 소켓 정보 설정
        info_time_out = -1;
        
        // 소켓 상태 설정
        state_sock = false;
        state_sock_addr = false;
        state_sock_len = false;
        state_bind = false;
        state_listen = false;
        state_use = false;
    }
    Socket(const unsigned long IP, const unsigned short PORT, int time_out=5)
    {
        // 소켓 생성 및 초기화
        while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
        
        // 소켓 블로킹 설정
        if (time_out == 0)
        {
            int count = 0;
            int flags = -1;
            
            try
            {
                // 현재 파일 속성 읽기
                while ((flags = fcntl(sock, F_GETFL, 0)) == -1)
                {
                    if (count++ > 5) throw std::runtime_error("fcntl error 1");
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                count = 0;
                
                // 논블로킹 모드로 변경
                while (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
                {
                    if (count++ > 4) throw std::runtime_error("fcntl error 2");
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                count = 0;
                
                // 소켓 정보 업데이트
                info_time_out = time_out;
            }
            catch (const std::runtime_error& e)
            {
                if      (std::string(e.what())=="fcntl error 1");
                else if (std::string(e.what())=="fcntl error 2")
                {
                    // 소켓 닫기
                    ::close(sock);
                    
                    // 소켓 재생성 및 초기화
                    while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
                }
                else throw;
                
                // 소켓 정보 업데이트
                info_time_out = time_out = 5;
                
                printf("|   network::Socket() : 소켓을 블로킹으로 생성할 수 없어 그냥 생성합니다.");
            }
        }
        
        // 소켓 타임아웃 설정
        if (time_out > 0)
        {
            struct timeval timeout;
            timeout.tv_sec = time_out;
            timeout.tv_usec = 0;
            
            try
            {
                // 소켓 수신 제한 시간 설정
                if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == -1)
                {
                    throw std::runtime_error("setsockopt error 1");
                }
                
                // 소켓 송신 제한 시간 설정
                if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout)) == -1)
                {
                    throw std::runtime_error("setsockopt error 2");
                }
                
                // 소켓 정보 업데이트
                info_time_out = time_out;
            }
            catch (const std::runtime_error& e)
            {
                if (std::string(e.what())=="setsockopt error 1" || std::string(e.what())=="setsockopt error 2")
                {
                    // 소켓 닫기
                    ::close(sock);
                    
                    // 소켓 재생성 및 초기화
                    while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
                }
                else throw;
                
                // 소켓 정보 업데이트
                info_time_out = time_out = -1;
                
                printf("|   network::Socket() : 소켓의 타임아웃을 설정 할 수 없어 그냥 생성합니다.");
            }
        }
        
        // 소켓 주소 구조체 초기화
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        sock_addr.sin_port = htons(PORT);
        
        // 소켓 길이 초기화
        sock_len = sizeof(sock_addr);
        
        // 소켓 상태 설정
        state_sock = true;
        state_sock_addr = true;
        state_sock_len = true;
        state_bind = false;
        state_listen = false;
        state_use = false;
    }
    Socket(const char* IP, const unsigned short PORT, int time_out=5)
    {
        // 소켓 생성 및 초기화
        while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
        
        // 소켓 블로킹 설정
        if (time_out == 0)
        {
            int count = 0;
            int flags = -1;
            
            try
            {
                // 현재 파일 속성 읽기
                while ((flags = fcntl(sock, F_GETFL, 0)) == -1)
                {
                    if (count++ > 5) throw std::runtime_error("fcntl error 1");
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                count = 0;
                
                // 논블로킹 모드로 변경
                while (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
                {
                    if (count++ > 4) throw std::runtime_error("fcntl error 2");
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
                count = 0;
                
                // 소켓 정보 업데이트
                info_time_out = time_out;
            }
            catch (const std::runtime_error& e)
            {
                if      (std::string(e.what())=="fcntl error 1");
                else if (std::string(e.what())=="fcntl error 2")
                {
                    // 소켓 닫기
                    ::close(sock);
                    
                    // 소켓 재생성 및 초기화
                    while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
                }
                else throw;
                
                // 소켓 정보 업데이트
                info_time_out = time_out = 5;
                
                printf("|   network::Socket() : 소켓을 블로킹으로 생성할 수 없어 그냥 생성합니다.");
            }
        }
        
        // 소켓 타임아웃 설정
        if (time_out > 0)
        {
            struct timeval timeout;
            timeout.tv_sec = time_out;
            timeout.tv_usec = 0;
            
            try
            {
                // 소켓 수신 제한 시간 설정
                if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) == -1)
                {
                    throw std::runtime_error("setsockopt error 1");
                }
                
                // 소켓 송신 제한 시간 설정
                if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout)) == -1)
                {
                    throw std::runtime_error("setsockopt error 2");
                }
                
                // 소켓 정보 업데이트
                info_time_out = time_out;
            }
            catch (const std::runtime_error& e)
            {
                if (std::string(e.what())=="setsockopt error 1" || std::string(e.what())=="setsockopt error 2")
                {
                    // 소켓 닫기
                    ::close(sock);
                    
                    // 소켓 재생성 및 초기화
                    while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
                }
                else throw;
                
                // 소켓 정보 업데이트
                info_time_out = time_out = -1;
                
                printf("|   network::Socket() : 소켓의 타임아웃을 설정 할 수 없어 그냥 생성합니다.");
            }
        }
        
        // 소켓 주소 구조체 초기화
        memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        inet_pton(AF_INET6, IP, &sock_addr.sin_addr);
        sock_addr.sin_port = htons(PORT);
        
        // 소켓 길이 초기화
        sock_len = sizeof(sock_addr);
        
        // 소켓 상태 설정
        state_sock = true;
        state_sock_addr = true;
        state_sock_len = true;
        state_bind = false;
        state_listen = false;
        state_use = false;
    }
    
    // 복사 생성자
    Socket(const Socket& other)
    {
        // 공유자원 잠금
        //std::lock_guard<std::mutex> lock(other.socket_mtx);

        // 멤버 변수 복사
        this->sock = other.sock;
        this->sock_addr = other.sock_addr;
        this->sock_len = other.sock_len;
        this->info_time_out = other.info_time_out;
        this->state_sock = other.state_sock;
        this->state_sock_addr = other.state_sock_addr;
        this->state_sock_len = other.state_sock_len;
        this->state_bind = other.state_bind;
        this->state_listen = other.state_listen;
        this->state_use = other.state_use;
    }
    
    // 대입 연산자 함수
    Socket& operator=(const Socket& other)
    {
        if (this != &other) // 자기 자신과의 대입 방지
        {
            // 공유자원 잠금
            //std::lock(this->socket_mtx, other.socket_mtx);
            //std::lock_guard<std::mutex> lock_this(this->socket_mtx, std::adopt_lock);
            //std::lock_guard<std::mutex> lock_other(other.socket_mtx, std::adopt_lock);

            // 멤버 변수 복사
            this->sock = other.sock;
            this->sock_addr = other.sock_addr;
            this->sock_len = other.sock_len;
            this->info_time_out = other.info_time_out;
            this->state_sock = other.state_sock;
            this->state_sock_addr = other.state_sock_addr;
            this->state_sock_len = other.state_sock_len;
            this->state_bind = other.state_bind;
            this->state_listen = other.state_listen;
            this->state_use = other.state_use;
        }
        return *this;
    }
    
    // bind()
    void bind()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && !state_bind && !state_listen && !state_use)
        {
            while (::bind(sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1);
            
            // 소켓 길이 초기화
            sock_len = sizeof(sock_addr);
            
            // 소켓 상태 설정
            state_sock = true;
            state_sock_addr = true;
            state_sock_len = true;
            state_bind = true;
            state_listen = false;
            state_use = false;
        }
        else
        {
            throw std::runtime_error("network::Socket::bind() : 소켓이 bind() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // listen()
    void listen()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && state_bind && !state_listen && !state_use)
        {
            while (::listen(sock, SOMAXCONN) == -1);
            
            // 소켓 길이 초기화
            sock_len = sizeof(sock_addr);
            
            // 소켓 상태 설정
            state_sock = true;
            state_sock_addr = true;
            state_sock_len = true;
            state_bind = true;
            state_listen = true;
            state_use = false;
        }
        else
        {
            throw std::runtime_error("network::Socket::listen() : 소켓이 listen() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // accept()
    Socket accept()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && state_bind && state_listen && !state_use)
        {
            // client 소켓 생성
            Socket new_sock;
            
            // client 소켓 받기
            if (info_time_out >= 0)
            {
                if ((new_sock.sock = ::accept(this->sock, (struct sockaddr*)&new_sock.sock_addr, &new_sock.sock_len)) == -1)
                {
                    // 소켓 상태 설정
                    new_sock.state_sock = false;
                    new_sock.state_sock_addr = false;
                    new_sock.state_sock_len = false;
                    new_sock.state_bind = false;
                    new_sock.state_listen = false;
                    new_sock.state_use = false;
                }
                else
                {
                    // 소켓 상태 설정
                    new_sock.state_sock = true;
                    new_sock.state_sock_addr = true;
                    new_sock.state_sock_len = true;
                    new_sock.state_bind = false;
                    new_sock.state_listen = false;
                    new_sock.state_use = true;
                }
            }
            else
            {
                while ((new_sock.sock = ::accept(this->sock, (struct sockaddr*)&new_sock.sock_addr, &new_sock.sock_len)) == -1);
                
                // 소켓 상태 설정
                new_sock.state_sock = true;
                new_sock.state_sock_addr = true;
                new_sock.state_sock_len = true;
                new_sock.state_bind = false;
                new_sock.state_listen = false;
                new_sock.state_use = true;
            }
            
            // client 소켓 반환
            return new_sock;
        }
        else
        {
            throw std::runtime_error("network::Socket::accept() : 소켓이 accept() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // connect()
    void connect()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && !state_bind && !state_listen && !state_use)
        {
            // 소켓 연결
            if (info_time_out >= 0)
            {
                if (::connect(sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1)
                {
                    // 소켓 상태 설정
                    state_sock = false;
                    state_sock_addr = false;
                    state_sock_len = false;
                    state_bind = false;
                    state_listen = false;
                    state_use = false;
                }
                else
                {
                    // 소켓 상태 설정
                    state_sock = true;
                    state_sock_addr = true;
                    state_sock_len = true;
                    state_bind = false;
                    state_listen = false;
                    state_use = true;
                }
            }
            else
            {
                int count = 0;
                while (true)
                {
                    if (::connect(sock, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1)
                    {
                        // 2초 또는 10초 뒤에 다시 시도
                        if (count++ < 30)   std::this_thread::sleep_for(std::chrono::seconds(2));
                        else                std::this_thread::sleep_for(std::chrono::seconds(10));
                        
                        // 소켓 닫기
                        ::close(sock);
                        
                        // 소켓 생성
                        while ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1);
                    }
                    else break;
                }
                
                // 소켓 길이 초기화
                sock_len = sizeof(sock_addr);
                
                // 소켓 상태 설정
                state_sock = true;
                state_sock_addr = true;
                state_sock_len = true;
                state_bind = false;
                state_listen = false;
                state_use = true;
            }
        }
        else
        {
            throw std::runtime_error("network::Socket::connect() : 소켓이 connect() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // close()
    void close()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock)
        {
            ::close(sock);
            state_sock = false;
        }
    }
    
    // send()
    void send(const std::string str)
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && !state_bind && !state_listen && state_use)
        {
            // 전송할 데이터 크기 계산
            unsigned int size = (unsigned int)strlen(str.c_str());
            
            // 데이터 전송
            while (::send(sock, (char*)&size, sizeof(unsigned int), 0) == -1);    // 크기
            while (::send(sock, str.c_str(), size, 0) == -1);                     // 데이터
        }
        else
        {
            throw std::runtime_error("network::Socket::send() : 소켓이 send() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // recv()
    std::string recv()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr && state_sock_len && !state_bind && !state_listen && state_use)
        {
            // 전송받을 데이터 크기
            unsigned int size = 0;
            
            // 데이터 수신 : 데이터 크기
            while (::recv(sock, (char*)&size, sizeof(unsigned int), MSG_WAITALL) == -1);
            
            // 버퍼 공간 할당
            char* buf = new char[size + 1];
            
            // 데이터 수신 : 자판기 데이터
            while (::recv(sock, (char*)buf, size, MSG_WAITALL) == -1);
            buf[size] = '\0';
            
            // string 객체로 변환
            std::string str(buf);
            
            // 버퍼 공간 메모리 해제
            delete [] buf;
            
            return str;
        }
        else
        {
            throw std::runtime_error("network::Socket::recv() : 소켓이 recv() 할 수 있는 상태가 아닙니다.");
        }
    }
    
    // 소켓 아이피 주소 문자열로 반환
    std::string get_ip()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr)
        {
            char ipv4str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sock_addr.sin_addr, ipv4str, sizeof(ipv4str));
            return std::string(ipv4str);
        }
        else
        {
            throw std::runtime_error("network::Socket::get_ip() : 소켓이 없습니다.");
        }
    }
    
    // 소켓 포트 번호 문자열로 반환
    unsigned short get_port()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        if (state_sock && state_sock_addr)
        {
            return ntohs(sock_addr.sin_port);
        }
        else
        {
            throw std::runtime_error("network::Socket::get_port() : 소켓이 없습니다.");
        }
    }
    
    // 소켓이 현재 recved 상태인지 반환
    bool is_received()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        // 수신 버퍼에 데이터가 있는지 확인
        char buf;
        ssize_t result = ::recv(sock, &buf, 1, MSG_PEEK | MSG_DONTWAIT);
        
        // 읽은 내용이 있으면 true 반환
        return (result > 0);
    }
    
    // 소켓이 현재 connected 상태인지 반환
    bool is_connected()
    {
        // 공유자원 잠금
        std::lock_guard<std::mutex> lock(socket_mtx);
        
        // 임시 소켓 주소 구조체와 임시 소켓 길이
        struct sockaddr_in sock_addr_tmp;
        socklen_t sock_len_tmp = sizeof(sock_addr_tmp);
        
        // 연결된 상대 주소 정보 가져오기
        return getpeername(sock, (struct sockaddr*)&sock_addr_tmp, &sock_len_tmp) == 0;
    }

};


}

#endif /* network_Socket_hpp */
