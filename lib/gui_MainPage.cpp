#include <gui_MainPage.hpp>

namespace gui
{


MyButtonMenu::MyButtonMenu(Glib::ustring label1, Glib::ustring label2) :
box(Gtk::Orientation::VERTICAL),
lb1(label1),
lb2(label2)
{
    // MyButtonMenu 설정
    set_expand();
    set_child(box);
    
    // box 설정
    box.append(lb1);
    box.append(lb2);
    
    // label 설정
    lb1.set_expand();
    lb2.set_expand();
}

MyGridMenu::MyGridMenu() :
bt1(dm.get_drink_name(0), dm.get_drink_price(0)),
bt2(dm.get_drink_name(1), dm.get_drink_price(1)),
bt3(dm.get_drink_name(2), dm.get_drink_price(2)),
bt4(dm.get_drink_name(3), dm.get_drink_price(3)),
bt5(dm.get_drink_name(4), dm.get_drink_price(4)),
bt6(dm.get_drink_name(5), dm.get_drink_price(5))
{
    // MyGridMenu 설정
    set_expand();
    set_margin(25);
    set_margin_bottom(15);
    set_margin_end(15);
    set_row_spacing(25);
    set_column_spacing(25);
    set_row_homogeneous(true);
    set_column_homogeneous(true);
    set_size_request(400, 300);
    
    // child 위젯 붙이기
    attach(bt1, 0, 0);
    attach(bt2, 1, 0);
    attach(bt3, 2, 0);
    attach(bt4, 0, 1);
    attach(bt5, 1, 1);
    attach(bt6, 2, 1);
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridMenu::bt1"] = &bt1;
    widget["MyGridMenu::bt2"] = &bt2;
    widget["MyGridMenu::bt3"] = &bt3;
    widget["MyGridMenu::bt4"] = &bt4;
    widget["MyGridMenu::bt5"] = &bt5;
    widget["MyGridMenu::bt6"] = &bt6;
    
    // signal 연결
    bt1.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 0));
    bt1.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt2.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 1));
    bt2.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt3.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 2));
    bt3.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt4.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 3));
    bt4.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt5.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 4));
    bt5.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt6.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::select_drink), 5));
    bt6.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
}

MyGridReturnTray::MyGridReturnTray() :
bt1(dm.get_out_drink()),
bt2(dm.get_out_coin())
{
    // MyGridReturnTray 설정
    set_expand();
    set_margin(25);
    set_margin_top(15);
    set_margin_end(15);
    set_row_spacing(25);
    set_column_spacing(25);
    set_row_homogeneous(true);
    set_column_homogeneous(true);
    set_size_request(400, 100);
    
    // Button 설정
    bt1.set_expand();
    bt2.set_expand();
    
    // child 위젯 붙이기
    attach(bt1, 0, 0);
    attach(bt2, 1, 0);
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridReturnTray::bt1"] = &bt1;
    widget["MyGridReturnTray::bt2"] = &bt2;
    
    // signal 연결
    bt1.signal_clicked().connect(sigc::mem_fun(dm, &data::DataManagement::take_drinks));
    bt1.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt2.signal_clicked().connect(sigc::mem_fun(dm, &data::DataManagement::take_coins));
    bt2.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
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
    set_row_homogeneous(true);
    set_column_homogeneous(true);
    
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
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridPurchase::bt1"] = &bt1;
    widget["MyGridPurchase::bt2"] = &bt2;
    widget["MyGridPurchase::bt3"] = &bt3;
    widget["MyGridPurchase::bt4"] = &bt4;
    widget["MyGridPurchase::bt5"] = &bt5;
    widget["MyGridPurchase::bt6"] = &bt6;
    
    // signal 연결
    bt1.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::insert_coin), data::Coin(10, 2024)));
    bt1.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt2.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::insert_coin), data::Coin(50, 2024)));
    bt2.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt3.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::insert_coin), data::Coin(100, 2024)));
    bt3.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt4.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::insert_coin), data::Coin(500, 2024)));
    bt4.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt5.signal_clicked().connect(sigc::bind(sigc::mem_fun(dm, &data::DataManagement::insert_coin), data::Coin(1000, 2024)));
    bt5.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt6.signal_clicked().connect(sigc::mem_fun(dm, &data::DataManagement::return_coin));
    bt6.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
}

MyGridSidebar::MyGridSidebar() :
bt1(dm.get_status_message()),
bt2("선택한 음료", dm.get_selected_drink()),
bt3("투입된 금액", dm.get_inserted_coins()),
bt4("구매"),
bt5("관리자")
{
    // MyGridSidebar 설정
    set_expand();
    set_margin(25);
    set_margin_start(15);
    set_row_spacing(15);
    set_column_spacing(15);
    set_row_homogeneous(true);
    set_column_homogeneous(true);
    set_size_request(300, 430);
    
    // Button 설정
    bt1.set_expand();
    bt2.set_expand();
    bt3.set_expand();
    bt4.set_expand();
    bt5.set_expand();
    bt1.set_sensitive(false);
    bt2.set_sensitive(false);
    bt3.set_sensitive(false);
    
    // child 위젯 붙이기
    attach(bt1, 0, 0, 2, 1);
    attach(bt2, 0, 1, 1, 2);
    attach(bt3, 1, 1, 1, 2);
    attach(gd, 0, 3, 2, 3);
    attach(bt4, 0, 8, 1, 1);
    attach(bt5, 1, 8, 1, 1);
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridSidebar::bt1"] = &bt1;
    widget["MyGridSidebar::bt2"] = &bt2;
    widget["MyGridSidebar::bt3"] = &bt3;
    widget["MyGridSidebar::bt4"] = &bt4;
    widget["MyGridSidebar::bt5"] = &bt5;
    
    // signal 연결
    bt4.signal_clicked().connect(sigc::mem_fun(dm, &data::DataManagement::purchase));
    bt4.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt5.signal_clicked().connect(sigc::ptr_fun(show_login_page));
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
fm(860.0/510.0)
{
    // window 설정
    set_title("Vending Machine");   // 윈도우 이름 설정
    set_default_size(860, 510);     // 윈도우 크기 설정
    set_size_request(860, 510);     // 윈도우 최소 크기 설정
    
    // child 위젯 등록
    set_child(fm);
}


}
