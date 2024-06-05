#pragma once
#ifndef network_client_hpp
#define network_client_hpp

// c++17
//#include <iostream>

// 소켓 프로그래밍 관련
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cerrno>

// 나의 라이브러리
#include <gui_client.hpp>

// 전역 변수
extern data::DataManagement                    dm;
extern std::map<std::string, Gtk::Widget*>     widget;
extern std::map<std::string, Glib::Dispatcher> dispatchers;

namespace network
{


// Dispatcher 준비
void make_dispatchers();

// 소켓 통신 시작
void Networking();


}

#endif /* network_client_hpp */
