#pragma once
#ifndef gui_server_functions_hpp
#define gui_server_functions_hpp

// c++17
#include <gtkmm.h>
#include <filesystem>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_server_ListPage.hpp>
#include <gui_server_AdministratorPage.hpp>

// 전역 변수
extern std::map<std::string, data::DataManagement> dms;
extern std::map<std::string, Gtk::Widget*>         widget;

// 통신 모듈
extern network::Pipe       pipe_to_client;
extern Glib::Dispatcher    dispatcher;

namespace gui_server
{


// ======== network ========

// 자판기 파일 받기
void recv_vm_data();

// 소켓 확인하고 작업 실행
void check_socket();

// ======== ListPage ========

// 데이터 관리자 파일들 찾아서 불러오기
void update_DataManagement();

// 격자 안에 버튼들 새로 고침
void refresh_ListPage_MyListingScrolledWindow();

// 관리자 페이지 열기
void open_AdministratorPage(std::string name);

// ======== AdministratorPage ========

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSidebar(std::string name);
void refresh_AdministratorPage_MyGridSidebar_id(std::string name);
void refresh_AdministratorPage_MyGridSidebar_pw(std::string name);

// 아이디 수정
void edit_id(std::string name);

// 비밀번호 수정
void edit_pw(std::string name);

// 라디오 버튼 활성화 확인
int get_MyGridInventory_radio_button_state(std::string name);

// 화면 새로 고침
void refresh_AdministratorPage_MyGridInventory(std::string name);
void refresh_AdministratorPage_MyGridInventory_name(std::string name);
void refresh_AdministratorPage_MyGridInventory_price(std::string name);

// 음료 이름 수정
void edit_drink_name(std::string name);

// 음료 가격 수정
void edit_drink_price(std::string name);


}

#endif /* gui_server_functions_hpp */
