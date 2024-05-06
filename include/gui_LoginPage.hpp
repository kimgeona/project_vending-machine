#pragma once
#ifndef gui_LoginPage_hpp
#define gui_LoginPage_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <data.hpp>

// 전역 변수
extern data::DataManagement dm;

namespace gui
{


class MyGridLogin         : public Gtk::Grid
{
public:
    MyGridLogin();
    
protected:
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

#endif /* gui_LoginPage_hpp */
