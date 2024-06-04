#pragma once
#ifndef gui_client_LoginPage_hpp
#define gui_client_LoginPage_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <data.hpp>
#include <gui_client_functions.hpp>

// 전역 변수
extern data::DataManagement dm;
extern std::map<std::string, Gtk::Widget*> widget;

namespace gui_client
{


class MyGridLogin         : public Gtk::Grid
{
public:
    MyGridLogin();
    
protected:
    Gtk::Button message;
    Gtk::Button bt;
    Gtk::Entry  id;
    Gtk::Entry  pw;
};


class LoginPage : public Gtk::Window
{
public:
    LoginPage();
    
protected:
    MyGridLogin gd;
};


}

#endif /* gui_client_LoginPage_hpp */
