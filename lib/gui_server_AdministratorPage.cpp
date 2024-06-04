#include <gui_server_AdministratorPage.hpp>

namespace gui_server
{


MyGridInventory::MyGridInventory(std::string name)
{
    // MyGridInventory 설정
    set_hexpand();              // 위젯 꽉 채우기
    set_margin(15);             // 내부 여백 설정
    set_row_spacing(10);        // 내부 요소 row spacing
    set_column_spacing(10);     // 내부 요소 col spacing
    set_row_homogeneous();      // 내부 위젯들 행 크기 동일하게
    set_column_homogeneous();   // 내부 위젯들 열 크기 동일하게
    
    // MyGridInventory 설정 : child 등록
    attach(bx, 0, 0, 12, 1);
    attach(lb_na, 0, 1, 2, 1);
    attach(lb_pr, 0, 2, 2, 1);
    attach(en_na, 2, 1, 8, 1);
    attach(en_pr, 2, 2, 8, 1);
    attach(bt_na, 10, 1, 2, 1);
    attach(bt_pr, 10, 2, 2, 1);
    
    // Box 설정
    bx.append(cb1);
    bx.append(cb2);
    bx.append(cb3);
    bx.append(cb4);
    bx.append(cb5);
    bx.append(cb6);
    
    // Checkbutton 설정
    cb1.set_label("음료 1");
    cb2.set_label("음료 2");
    cb3.set_label("음료 3");
    cb4.set_label("음료 4");
    cb5.set_label("음료 5");
    cb6.set_label("음료 6");
    cb2.set_group(cb1);
    cb3.set_group(cb1);
    cb4.set_group(cb1);
    cb5.set_group(cb1);
    cb6.set_group(cb1);
    
    // Label 설정
    lb_na.set_label("이름 : ");
    lb_pr.set_label("가격 : ");
    
    // Entry 설정
    en_na.set_placeholder_text("음료 이름");
    en_pr.set_placeholder_text("음료 가격");
    
    // Button 설정
    bt_na.set_label("수정");
    bt_pr.set_label("수정");
    
    // map 컨테이너에 위젯들 저장
    widget[name + "::MyGridInventory::cb1"] = &cb1;
    widget[name + "::MyGridInventory::cb2"] = &cb2;
    widget[name + "::MyGridInventory::cb3"] = &cb3;
    widget[name + "::MyGridInventory::cb4"] = &cb4;
    widget[name + "::MyGridInventory::cb5"] = &cb5;
    widget[name + "::MyGridInventory::cb6"] = &cb6;
    widget[name + "::MyGridInventory::en_na"] = &en_na;
    widget[name + "::MyGridInventory::en_pr"] = &en_pr;
    widget[name + "::MyGridInventory::bt_na"] = &bt_na;
    widget[name + "::MyGridInventory::bt_pr"] = &bt_pr;
    
    // 화면 새로 고침
    refresh_AdministratorPage_MyGridInventory(name);
    
    // signal 연결
    cb1.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    cb2.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    cb3.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    cb4.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    cb5.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    cb6.signal_toggled().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory), name));
    
    bt_na.signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_drink_name), name));
    bt_na.signal_clicked().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory_name), name));
    
    bt_pr.signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_drink_price), name));
    bt_pr.signal_clicked().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory_price), name));
    
    // DataManagement 이름 저장
    this->name = name;
}
MyGridSettings::MyGridSettings(std::string name)
{
    // MyGridSettings 설정
    set_hexpand();              // 위젯 꽉 채우기
    set_margin(15);             // 내부 여백 설정
    set_row_spacing(10);        // 내부 요소 row spacing
    set_column_spacing(10);     // 내부 요소 col spacing
    set_row_homogeneous();      // 내부 위젯들 행 크기 동일하게
    set_column_homogeneous();   // 내부 위젯들 열 크기 동일하게
    
    
    // MyGridSettings 설정 : child 등록
    attach(lb_id, 0, 0, 1, 1);
    attach(lb_pw, 0, 1, 1, 1);
    attach(elb_id, 1, 0, 4, 1);
    attach(elb_pw, 1, 1, 4, 1);
    attach(bt_id, 5, 0, 1, 1);
    attach(bt_pw, 5, 1, 1, 1);
    
    
    // Label 설정
    lb_id.set_label("ID :");    // 레이블 텍스트 설정
    lb_id.set_xalign(0.5);      // 텍스트 가운데 정렬
    lb_pw.set_label("PW :");
    lb_pw.set_xalign(0.5);
    
    // Entry : id 설정
    elb_id.set_placeholder_text(dms[name].get_id());
    elb_id.set_max_length(50);
    elb_id.set_hexpand(true);
    
    // Entry : pw 설정
    elb_pw.set_placeholder_text(dms[name].get_pw());
    elb_pw.set_max_length(50);
    elb_pw.set_hexpand(true);
    
    // Button 설정
    bt_id.set_label("변경");
    bt_pw.set_label("변경");
    
    // map 컨테이너에 위젯들 저장
    widget[name + "::MyGridSettings::elb_id"] = &elb_id;
    widget[name + "::MyGridSettings::elb_pw"] = &elb_pw;
    widget[name + "::MyGridSettings::bt_id"] = &bt_id;
    widget[name + "::MyGridSettings::bt_pw"] = &bt_pw;
    
    // signal 연결
    bt_id.signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_id), name));
    bt_id.signal_clicked().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridSidebar_id), name));
    bt_pw.signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_pw), name));
    bt_pw.signal_clicked().connect(sigc::bind(sigc::ptr_fun(refresh_AdministratorPage_MyGridSidebar_pw), name));
    
    // DataManagement 이름 저장
    this->name = name;
}


template <class MyGrid>
MyFrame<MyGrid>::MyFrame(std::string name) :
gd(name)
{
    // MyFrame 설정
    set_hexpand();
    
    // child 등록
    set_child(gd);
    
    // DataManagement 이름 저장
    this->name = name;
}


AdministratorPage::AdministratorPage(std::string name) :
fm1(name),
fm2(name),
lb1("계정 설정"),
lb2("\n음료 정보 및 재고")
{
    // Window 설정
    set_title(name + " : 관리자 메뉴");
    set_default_size(470, 400);
    set_size_request(470, 400);     // 윈도우 최소 크기 설정
    set_child(sw);
    
    // ScrolledWindow 설정
    sw.set_expand();
    sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS); // 스크롤바 설정
    sw.set_child(bx);
    
    // Box 설정
    bx.set_expand();
    bx.set_orientation(Gtk::Orientation::VERTICAL);    // 포함되는 위젯들 나열 방향 설정
    bx.set_margin(20);
    bx.set_spacing(15);
    bx.append(lb1);
    bx.append(fm1);
    bx.append(lb2);
    bx.append(fm2);
    
    // Label 설정
    lb1.set_xalign(0.0);
    lb2.set_xalign(0.0);
    lb1.set_justify(Gtk::Justification::LEFT);
    lb2.set_justify(Gtk::Justification::LEFT);
    
    // DataManagement 이름 저장
    this->name = name;
}


}
