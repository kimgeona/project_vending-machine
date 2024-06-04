#pragma once
#ifndef gui_server_AdministratorPage_hpp
#define gui_server_AdministratorPage_hpp

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


// 개인 설정 클래스
class MyBox : public Gtk::Box
{
public:
    MyBox()
    {
        set_orientation(Gtk::Orientation::HORIZONTAL);
        set_hexpand();
    }
};
class MyEntry : public Gtk::Entry
{
public:
    MyEntry()
    {
        set_max_length(50);
        set_hexpand(true);
    }
};
class MyCheckButton : public Gtk::CheckButton
{
public:
    MyCheckButton()
    {
        set_hexpand();
    }
};



// UI 클래스
class MyGridInventory   : public Gtk::Grid
{
public:
    MyGridInventory(std::string name);
    std::string name;   // 자판기 이름
    
protected:
    MyBox               bx;
    MyCheckButton       cb1, cb2, cb3, cb4, cb5, cb6;
    
    Gtk::Label          lb_na;  // 음료 이름
    Gtk::Label          lb_pr;  // 음료 가격
    MyEntry             en_na;
    MyEntry             en_pr;
    Gtk::Button         bt_na;
    Gtk::Button         bt_pr;
};
class MyGridSettings    : public Gtk::Grid
{
public:
    MyGridSettings(std::string name);
    std::string name;   // 자판기 이름
    
protected:
    Gtk::Label      lb_id;
    Gtk::Label      lb_pw;
    Gtk::Entry      elb_id;
    Gtk::Entry      elb_pw;
    Gtk::Button     bt_id;
    Gtk::Button     bt_pw;
};

template <class MyGrid>
class MyFrame           : public Gtk::Frame
{
public:
    MyFrame(std::string name);
    std::string name;   // 자판기 이름
    
protected:
    MyGrid gd;
};

class AdministratorPage : public Gtk::Window
{
public:
    AdministratorPage(std::string name);
    std::string name;   // 자판기 이름
    
protected:
    Gtk::ScrolledWindow sw;             // 스크롤 윈도우
    Gtk::Box bx;                        // 박스
    
    Gtk::Label lb1;
    Gtk::Label lb2;
    
    MyFrame<MyGridSettings>     fm1;    // 계정 설정
    MyFrame<MyGridInventory>    fm2;    // 재고
};


}

#endif /* gui_server_AdministratorPage_hpp */
