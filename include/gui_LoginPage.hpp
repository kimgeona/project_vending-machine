#pragma once
#ifndef gui_LoginPage_hpp
#define gui_LoginPage_hpp

// c++17
#include <gtkmm.h>

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
