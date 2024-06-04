#pragma once
#ifndef gui_server_functions_hpp
#define gui_server_functions_hpp

// c++17
#include <gtkmm.h>
#include <filesystem>

// 나의 라이브러리
#include <gui_server_ListPage.hpp>

// 전역 변수
extern std::map<std::string, data::DataManagement> dms;
extern std::map<std::string, Gtk::Widget*>         widget;

namespace gui_server
{


// ======== ListPage ========


// 데이터 관리자 파일들 찾아서 불러오기
void update_DataManagement();

// 격자 안에 버튼들 새로 고침
void refresh_ListPage_MyListingScrolledWindow();


}

#endif /* gui_server_functions_hpp */
