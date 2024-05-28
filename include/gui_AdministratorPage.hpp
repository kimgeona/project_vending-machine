#pragma once
#ifndef gui_AdministratorPage_hpp
#define gui_AdministratorPage_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <gui_functions.hpp>
#include <data.hpp>

// 전역 변수
extern data::DataManagement dm;
extern std::map<std::string, Gtk::Widget*> widget;

namespace gui
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
class MyGridSales       : public Gtk::Grid
{
public:
    MyGridSales();
    
protected:
    MyCheckButton       bt1, bt2;
    Gtk::Frame          fm;
    Gtk::ScrolledWindow sw;
    Gtk::TextView       tv;
    Glib::RefPtr<Gtk::TextBuffer> tb_ptr;
};
class MyGridChanges     : public Gtk::Grid
{
public:
    MyGridChanges();
    
protected:
    MyBox       bx1, bx2, bx3;
    Gtk::Label  lb1, lb2, lb3, lb4, lb5;
    Gtk::Label  lb_total, lb_refundable;
    MyEntry     en1, en2, en3, en4, en5;
    MyEntry     en_total, en_refundable;
    Gtk::Button bt1_p, bt2_p, bt3_p, bt4_p, bt5_p;
    Gtk::Button bt1_m, bt2_m, bt3_m, bt4_m, bt5_m;
    Gtk::Button bt_collect;
    
};
class MyGridInventory   : public Gtk::Grid
{
public:
    MyGridInventory();
    
protected:
    MyBox               bx;
    MyCheckButton       cb1, cb2, cb3, cb4, cb5, cb6;
    Gtk::Label          lb_na;  // 음료 이름
    Gtk::Label          lb_pr;  // 음료 가격
    Gtk::Label          lb_re;  // 음료 갯수
    MyEntry             en_na;
    MyEntry             en_pr;
    MyEntry             en_re;
    Gtk::Button         bt_na;
    Gtk::Button         bt_pr;
    Gtk::Button         bt_re_p, bt_re_m;
};
class MyGridSettings    : public Gtk::Grid
{
public:
    MyGridSettings();
    
protected:
    Gtk::Label  label_id;
    Gtk::Label  label_pw;
    Gtk::Entry  id;
    Gtk::Entry  pw;
    Gtk::Button button_id;
    Gtk::Button button_pw;
};

template <class MyGrid>
class MyFrame           : public Gtk::Frame
{
public:
    MyFrame(Glib::ustring name);
    
protected:
    MyGrid gd;
};

class MyBoxListedFrames : public Gtk::Box
{
public:
    MyBoxListedFrames();
    
protected:
    MyFrame<MyGridSettings>     fm1;    // 계정 설정
    MyFrame<MyGridInventory>    fm2;    // 재고
    MyFrame<MyGridChanges>      fm3;    // 거스름돈
    MyFrame<MyGridSales>        fm4;    // 매출
};

class MyScrolledWindow  : public Gtk::ScrolledWindow
{
public:
    MyScrolledWindow();
    
protected:
    MyBoxListedFrames bx;
};

class AdministratorPage : public Gtk::Window
{
public:
    AdministratorPage();
    
protected:
    MyScrolledWindow sw;
};


}

#endif /* gui_AdministratorPage_hpp */
