#pragma once
#ifndef gui_server_ListPage_hpp
#define gui_server_ListPage_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <data.hpp>
#include <gui_server_functions.hpp>

// 전역 변수
extern std::map<std::string, data::DataManagement>  dms;
extern std::map<std::string, Gtk::Widget*>          widget;

namespace gui_server
{


class MyListingScrolledWindow : public Gtk::ScrolledWindow
{
public:
    MyListingScrolledWindow();
    
protected:
    Gtk::Grid gd;   // 격자
};

class ListPage : public Gtk::Window
{
public:
    ListPage();
    
protected:
    Gtk::Grid               gd; // 격자
    MyListingScrolledWindow sw; // 스크롤 윈도우
    Gtk::Box                bx; // 박스
    
    Gtk::Button bt_sales;   // 매출 버튼
    Gtk::Button bt_alart;   // 알림 버튼
    Gtk::Button bt_info;    // 정보 확인 버튼
};


}

#endif /* gui_server_ListPage_hpp */
