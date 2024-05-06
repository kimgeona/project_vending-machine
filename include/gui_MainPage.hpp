#pragma once
#ifndef gui_MainPage_hpp
#define gui_MainPage_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <data.hpp>

// 전역 변수
extern data::DataManagement dm;

namespace gui
{


class MyButtonMenu      : public Gtk::Button
{
public:
    MyButtonMenu(Glib::ustring label1, Glib::ustring label2);
    void set_label(Glib::ustring label1, Glib::ustring label2);
    
protected:
    Gtk::Box    box;
    Gtk::Label  lb1;
    Gtk::Label  lb2;
};


class MyGridMenu        : public Gtk::Grid
{
public:
    MyGridMenu();
    
protected:
    MyButtonMenu bt1;
    MyButtonMenu bt2;
    MyButtonMenu bt3;
    MyButtonMenu bt4;
    MyButtonMenu bt5;
    MyButtonMenu bt6;
};
class MyGridReturnTray  : public Gtk::Grid
{
public:
    MyGridReturnTray();
    
protected:
    Gtk::Button bt1;
    Gtk::Button bt2;
};
class MyGridPurchase    : public Gtk::Grid
{
public:
    MyGridPurchase();
    
protected:
    Gtk::Button bt1;
    Gtk::Button bt2;
    Gtk::Button bt3;
    Gtk::Button bt4;
    Gtk::Button bt5;
    Gtk::Button bt6;
};
class MyGridSidebar     : public Gtk::Grid
{
public:
    MyGridSidebar();
    
protected:
    Gtk::Button bt1;
    MyButtonMenu bt2;
    MyButtonMenu bt3;
    Gtk::Button bt4;
    Gtk::Button bt5;
    MyGridPurchase gd;
};
class MyGridAll         : public Gtk::Grid
{
public:
    MyGridAll();
    
protected:
    MyGridMenu          gd1;
    MyGridReturnTray    gd2;
    MyGridSidebar       gd3;
};


class MyFrameCenter     : public Gtk::AspectFrame
{
public:
    MyFrameCenter(double rate);
    
protected:
    Gtk::Frame  fm;
    MyGridAll   gd;
};


class MainPage          : public Gtk::Window
{
public:
    MainPage();
    
protected:
    MyFrameCenter fm;
};


}

#endif /* gui_MainPage_hpp */
