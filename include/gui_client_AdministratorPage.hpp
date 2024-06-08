#pragma once
#ifndef gui_client_AdministratorPage_hpp
#define gui_client_AdministratorPage_hpp

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
    MyCheckButton       cb1, cb2;
    Gtk::Frame          fm;
    Gtk::ScrolledWindow sw;
    Gtk::Label          lb;
};
class MyGridChanges     : public Gtk::Grid
{
public:
    MyGridChanges();
    
protected:
    Gtk::Label                      lb[5];
    Glib::RefPtr<Gtk::Adjustment>   ad[5];
    Gtk::SpinButton                 sb[5];
    Gtk::Button                     bt[5];
    
    Gtk::Label  lb_total, lb_refundable;
    Gtk::Label  lb_total_v, lb_refundable_v;
    Gtk::Button bt_collect;
};
class MyGridInventory   : public Gtk::Grid
{
public:
    MyGridInventory();
    
protected:
    MyBox               bx;
    MyCheckButton       cb1, cb2, cb3, cb4, cb5, cb6;
    Glib::RefPtr<Gtk::Adjustment> ad_re;
    
    Gtk::Label          lb_na;  // 음료 이름
    Gtk::Label          lb_pr;  // 음료 가격
    Gtk::Label          lb_re;  // 음료 갯수
    MyEntry             en_na;
    MyEntry             en_pr;
    Gtk::SpinButton     sb_re;
    Gtk::Button         bt_na;
    Gtk::Button         bt_pr;
    Gtk::Button         bt_re;
};
class MyGridSettings    : public Gtk::Grid
{
public:
    MyGridSettings();
    
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
    MyFrame();
    
protected:
    MyGrid gd;
};

class AdministratorPage : public Gtk::Window
{
public:
    AdministratorPage();
    ~AdministratorPage();
    
protected:
    Gtk::ScrolledWindow sw;             // 스크롤 윈도우
    Gtk::Box bx;                        // 박스
    
    Gtk::Label lb1;
    Gtk::Label lb2;
    Gtk::Label lb3;
    Gtk::Label lb4;
    
    MyFrame<MyGridSettings>     fm1;    // 계정 설정
    MyFrame<MyGridInventory>    fm2;    // 재고
    MyFrame<MyGridChanges>      fm3;    // 거스름돈
    MyFrame<MyGridSales>        fm4;    // 매출
};


}

#endif /* gui_client_AdministratorPage_hpp */
