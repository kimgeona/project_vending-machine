#pragma once
#ifndef gui_client_functions_hpp
#define gui_client_functions_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_client_MainPage.hpp>
#include <gui_client_LoginPage.hpp>
#include <gui_client_AdministratorPage.hpp>

// 전역 변수
extern data::DataManagement dm;
extern std::map<std::string, Gtk::Widget*> widget;

// 통신 모듈
extern network::Pipe       pipe_to_server;
extern Glib::Dispatcher    dispatcher;

namespace gui_client
{


// ======== network ========

// 자판기 파일 보내기
void send_vm_data();

// 소켓 확인하고 작업 실행
void check_socket();

// ======== MainPage ========

// 화면 새로 고침
void refresh_MainPage();

// 로그인 페이지 열기
void show_login_page();

// 음료 구입
void purchase();

// ======== LoginPage ========

// 로그인
void login();

// ======== AdministratorPage ========

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSidebar();
void refresh_AdministratorPage_MyGridSidebar_id();
void refresh_AdministratorPage_MyGridSidebar_pw();

// 라디오 버튼 활성화 확인
int get_MyGridInventory_radio_button_state();

// 화면 새로 고침
void refresh_AdministratorPage_MyGridInventory();
void refresh_AdministratorPage_MyGridInventory_name();
void refresh_AdministratorPage_MyGridInventory_price();
void refresh_AdministratorPage_MyGridInventory_num();

// 아이디 수정
void edit_id();

// 비밀번호 수정
void edit_pw();

// 음료 이름 수정
void edit_drink_name();

// 음료 가격 수정
void edit_drink_price();

// 음료 갯수 수정
void edit_drink_num();

// 화면 새로 고침
void refresh_AdministratorPage_MyGridChanges();

// 동전 갯수 서정
void edit_coin_num(int slot_number);

// 라디오 버튼 활성화 확인
int get_MyGridSales_radio_button_state();

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSales();


}

#endif /* gui_client_functions_hpp */
