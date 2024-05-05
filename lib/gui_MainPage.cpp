#include <gui_MainPage.hpp>

namespace gui
{


MyButtonMenu::MyButtonMenu(Glib::ustring name, Glib::ustring price) :
box(Gtk::Orientation::VERTICAL),
labelName(name),
labelPrice(price)
{
    // MyButtonMenu 설정
    set_expand();
    set_child(box);
    
    // box 설정
    box.append(labelName);
    box.append(labelPrice);
    
    // label 설정
    labelName.set_expand();
    labelPrice.set_expand();
}

MyGridMenu::MyGridMenu() :
bt1("물", "450"),
bt2("커피", "500"),
bt3("이온음료", "550"),
bt4("고급커피", "700"),
bt5("탄산음료", "750"),
bt6("특화음료", "800")
{
    // MyGridMenu 설정
    set_expand();
    set_margin(25);
    set_margin_bottom(15);
    set_margin_end(15);
    set_row_spacing(25);
    set_column_spacing(25);
    
    // child 위젯 붙이기
    attach(bt1, 0, 0);
    attach(bt2, 1, 0);
    attach(bt3, 2, 0);
    attach(bt4, 0, 1);
    attach(bt5, 1, 1);
    attach(bt6, 2, 1);
}

MyGridReturnTray::MyGridReturnTray() :
bt1("음료수 나옴"),
bt2("거스름돈 나옴")
{
    // MyGridReturnTray 설정
    set_expand();
    set_margin(25);
    set_margin_top(15);
    set_margin_end(15);
    set_row_spacing(25);
    set_column_spacing(25);
    
    // Button 설정
    bt1.set_expand();
    bt2.set_expand();
    
    // child 위젯 붙이기
    attach(bt1, 0, 0);
    attach(bt2, 1, 0);
}

MyGridPurchase::MyGridPurchase() :
bt1("10"),
bt2("50"),
bt3("100"),
bt4("500"),
bt5("1000"),
bt6("반환")
{
    // MyGridPurchase 설정
    set_expand();
    set_row_spacing(15);
    set_column_spacing(15);
    
    // Button 설정
    bt1.set_expand();
    bt2.set_expand();
    bt3.set_expand();
    bt4.set_expand();
    bt5.set_expand();
    bt6.set_expand();
    
    // child 위젯 붙이기
    attach(bt1, 0, 0);
    attach(bt2, 1, 0);
    attach(bt3, 0, 1);
    attach(bt4, 1, 1);
    attach(bt5, 0, 2);
    attach(bt6, 1, 2);
}

MyGridSidebar::MyGridSidebar() :
bt1("상태 메시지"),
bt2("투입된 금액"),
bt3("구매"),
bt4("관리자")
{
    // MyGridSidebar 설정
    set_expand();
    set_margin(25);
    set_margin_start(15);
    set_row_spacing(15);
    set_column_spacing(15);
    
    // Button 설정
    bt1.set_expand();
    bt2.set_expand();
    bt3.set_expand();
    //bt4.set_expand();
    bt1.set_sensitive(false);
    bt2.set_sensitive(false);
    
    // child 위젯 붙이기
    attach(bt1, 0, 0, 2, 1);
    attach(bt2, 0, 1, 2, 3);
    attach(gd, 0, 4, 2, 3);
    attach(bt3, 0, 9, 1, 1);
    attach(bt4, 1, 9, 1, 1);
}

MyGridAll::MyGridAll()
{
    // MyGridAll 설정
    set_expand();
    
    // child 위젯 붙이기
    attach(gd1, 0, 0, 5, 5);
    attach(gd2, 0, 5, 5, 2);
    attach(gd3, 5, 0, 2, 7);
}

MyFrameCenter::MyFrameCenter(double rate) :
Gtk::AspectFrame(Gtk::Align::CENTER, Gtk::Align::CENTER, rate, false)
{
    // MyFrameCenter 설정
    set_margin(15);
    
    // grid 설정
    gd.set_expand();
    
    // child 위젯 붙이기
    set_child(fm);
    fm.set_child(gd);
}

MainPage::MainPage() :
fm(9.0/5.0)
{
    // window 설정
    set_title("Vending Machine");   // 윈도우 이름 설정
    set_default_size(900, 500);     // 윈도우 크기 설정
    set_size_request(900, 500);     // 윈도우 최소 크기 설정
    
    // child 위젯 등록
    set_child(fm);
}

void MyButtonMenu::set_name_and_price(Glib::ustring name, Glib::ustring price)
{
    labelName.set_text(name);
    labelPrice.set_text(price);
}


}
