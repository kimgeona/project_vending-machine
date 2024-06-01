#include <gui_AdministratorPage.hpp>

namespace gui
{


MyGridSales::MyGridSales()
{
    // MyGridSales 설정
    set_hexpand();              // 위젯 꽉 채우기
    set_margin(15);             // 내부 여백 설정
    set_row_spacing(10);        // 내부 요소 row spacing
    set_column_spacing(10);     // 내부 요소 col spacing
    set_row_homogeneous();      // 내부 위젯들 행 크기 동일하게
    set_column_homogeneous();   // 내부 위젯들 열 크기 동일하게
    
    // MyGridSales 설정 : child 등록
    attach(cb1, 0, 0, 1, 1);
    attach(cb2, 1, 0, 1, 1);
    attach(fm, 0, 1, 2, 7);
    
    // CheckButton 설정
    cb1.set_label("일별");
    cb2.set_label("월별");
    cb2.set_group(cb1);
    
    // Frame 설정
    fm.set_hexpand();
    fm.set_child(sw);
    
    // ScrolledWindow 설정
    sw.set_hexpand();
    sw.set_margin(5);
    sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    sw.set_child(lb);
    
    // Label 설정
    lb.set_text("-- 여기에 매출이 표시됩니다.");
    lb.set_margin(10);
    lb.set_expand();
    lb.set_xalign(0.0);
    lb.set_yalign(0.0);
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridSales::cb1"] = &cb1;
    widget["MyGridSales::cb2"] = &cb2;
    widget["MyGridSales::lb"] = &lb;
    
    // signal 연결
    cb1.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridSales));
    cb2.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridSales));
}
MyGridChanges::MyGridChanges()
{
    // MyGridChanges 설정
    set_hexpand();              // 위젯 꽉 채우기
    set_margin(15);             // 내부 여백 설정
    set_row_spacing(10);        // 내부 요소 row spacing
    set_column_spacing(10);     // 내부 요소 col spacing
    //set_row_homogeneous();      // 내부 위젯들 행 크기 동일하게
    //set_column_homogeneous();   // 내부 위젯들 열 크기 동일하게
    
    // MyGridChanges 설정 : child 등록
    attach(lb[0], 0, 0, 1, 1);
    attach(lb[1], 0, 1, 1, 1);
    attach(lb[2], 0, 2, 1, 1);
    attach(lb[3], 0, 3, 1, 1);
    attach(lb[4], 0, 4, 1, 1);
    attach(sb[0], 1, 0, 4, 1);
    attach(sb[1], 1, 1, 4, 1);
    attach(sb[2], 1, 2, 4, 1);
    attach(sb[3], 1, 3, 4, 1);
    attach(sb[4], 1, 4, 4, 1);
    attach(bt[0], 5, 0, 1, 1);
    attach(bt[1], 5, 1, 1, 1);
    attach(bt[2], 5, 2, 1, 1);
    attach(bt[3], 5, 3, 1, 1);
    attach(bt[4], 5, 4, 1, 1);
    attach(lb_total, 0, 5, 1, 1);
    attach(lb_total_v, 1, 5, 5, 1);
    attach(lb_refundable, 0, 6, 1, 1);
    attach(lb_refundable_v, 1, 6, 4, 1);
    attach(bt_collect, 5, 6, 1, 1);
    
    // Label 설정
    lb[0].set_label("₩   10 : ");
    lb[1].set_label("₩   50 : ");
    lb[2].set_label("₩  100 : ");
    lb[3].set_label("₩  500 : ");
    lb[4].set_label("₩ 1000 : ");
    lb[0].set_xalign(1.0);
    lb[1].set_xalign(1.0);
    lb[2].set_xalign(1.0);
    lb[3].set_xalign(1.0);
    lb[4].set_xalign(1.0);
    lb_total.set_label("전체 잔액 : ");
    lb_total.set_xalign(1.0);
    lb_total_v.set_label(dm.get_balance());
    lb_total_v.set_xalign(0.0);
    lb_refundable.set_label("수금 가능 금액 : ");
    lb_refundable.set_xalign(1.0);
    lb_refundable_v.set_label(dm.get_collectable_changes());
    lb_refundable_v.set_xalign(0.0);
    
    // Adjustment 생성
    ad[0] = Gtk::Adjustment::create(std::stod(dm.get_coin_num(0)), 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[1] = Gtk::Adjustment::create(std::stod(dm.get_coin_num(1)), 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[2] = Gtk::Adjustment::create(std::stod(dm.get_coin_num(2)), 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[3] = Gtk::Adjustment::create(std::stod(dm.get_coin_num(3)), 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[4] = Gtk::Adjustment::create(std::stod(dm.get_coin_num(4)), 0.0, 100.0, 1.0, 0.0, 0.0);
    
    // SpiinButton 설정
    sb[0].set_adjustment(ad[0]);
    sb[1].set_adjustment(ad[1]);
    sb[2].set_adjustment(ad[2]);
    sb[3].set_adjustment(ad[3]);
    sb[4].set_adjustment(ad[4]);
    sb[0].set_digits(0); // 허용 가능한 소수점 범위 설정
    sb[1].set_digits(0);
    sb[2].set_digits(0);
    sb[3].set_digits(0);
    sb[4].set_digits(0);
    sb[0].set_expand();
    sb[1].set_expand();
    sb[2].set_expand();
    sb[3].set_expand();
    sb[4].set_expand();
    
    // button 설정
    bt[0].set_label("수정");
    bt[1].set_label("수정");
    bt[2].set_label("수정");
    bt[3].set_label("수정");
    bt[4].set_label("수정");
    bt_collect.set_label("수금하기");
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridChanges::sb[0]"] = &sb[0];
    widget["MyGridChanges::sb[1]"] = &sb[1];
    widget["MyGridChanges::sb[2]"] = &sb[2];
    widget["MyGridChanges::sb[3]"] = &sb[3];
    widget["MyGridChanges::sb[4]"] = &sb[4];
    widget["MyGridChanges::lb_total_v"] = &lb_total_v;
    widget["MyGridChanges::lb_refundable_v"] = &lb_refundable_v;
    
    // signal 연결
    bt[0].signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_coin_num), 0));
    bt[0].signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt[0].signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt[1].signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_coin_num), 1));
    bt[1].signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt[1].signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt[2].signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_coin_num), 2));
    bt[2].signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt[2].signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt[3].signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_coin_num), 3));
    bt[3].signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt[3].signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt[4].signal_clicked().connect(sigc::bind(sigc::ptr_fun(edit_coin_num), 4));
    bt[4].signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt[4].signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    bt_collect.signal_clicked().connect(sigc::mem_fun(dm, &data::DataManagement::collect_changes));
    bt_collect.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridChanges));
    bt_collect.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
}
MyGridInventory::MyGridInventory()
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
    attach(lb_re, 0, 3, 2, 1);
    attach(en_na, 2, 1, 8, 1);
    attach(en_pr, 2, 2, 8, 1);
    attach(sb_re, 2, 3, 8, 1);
    attach(bt_na, 10, 1, 2, 1);
    attach(bt_pr, 10, 2, 2, 1);
    attach(bt_re, 10, 3, 2, 1);
    
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
    lb_re.set_label("갯수 : ");
    
    // Entry 설정
    en_na.set_placeholder_text("음료 이름");
    en_pr.set_placeholder_text("음료 가격");
    
    // Adjustment 생성
    ad_re = Gtk::Adjustment::create(5.0, 0.0, 10.0, 1.0, 0.0, 0.0);
    
    // SpiinButton 설정
    sb_re.set_adjustment(ad_re);
    sb_re.set_digits(0);            // 허용 가능한 소수점 범위 설정
    
    // Button 설정
    bt_na.set_label("수정");
    bt_pr.set_label("수정");
    bt_re.set_label("수정");
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridInventory::cb1"] = &cb1;
    widget["MyGridInventory::cb2"] = &cb2;
    widget["MyGridInventory::cb3"] = &cb3;
    widget["MyGridInventory::cb4"] = &cb4;
    widget["MyGridInventory::cb5"] = &cb5;
    widget["MyGridInventory::cb6"] = &cb6;
    widget["MyGridInventory::en_na"] = &en_na;
    widget["MyGridInventory::en_pr"] = &en_pr;
    widget["MyGridInventory::sb_re"] = &sb_re;
    widget["MyGridInventory::bt_na"] = &bt_na;
    widget["MyGridInventory::bt_pr"] = &bt_pr;
    widget["MyGridInventory::bt_re"] = &bt_re;
    
    // 화면 새로 고침
    refresh_AdministratorPage_MyGridInventory();
    
    // signal 연결
    cb1.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    cb2.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    cb3.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    cb4.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    cb5.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    cb6.signal_toggled().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    
    bt_na.signal_clicked().connect(sigc::ptr_fun(edit_drink_name));
    bt_na.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory_name));
    bt_na.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    
    bt_pr.signal_clicked().connect(sigc::ptr_fun(edit_drink_price));
    bt_pr.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory_price));
    bt_pr.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
    
    bt_re.signal_clicked().connect(sigc::ptr_fun(edit_drink_num));
    bt_re.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridInventory));
    bt_re.signal_clicked().connect(sigc::ptr_fun(refresh_MainPage));
}
MyGridSettings::MyGridSettings()
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
    elb_id.set_placeholder_text(dm.get_id());
    elb_id.set_max_length(50);
    elb_id.set_hexpand(true);
    
    // Entry : pw 설정
    elb_pw.set_placeholder_text(dm.get_pw());
    elb_pw.set_max_length(50);
    elb_pw.set_hexpand(true);
    
    // Button 설정
    bt_id.set_label("변경");
    bt_pw.set_label("변경");
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridSettings::elb_id"] = &elb_id;
    widget["MyGridSettings::elb_pw"] = &elb_pw;
    widget["MyGridSettings::bt_id"] = &bt_id;
    widget["MyGridSettings::bt_pw"] = &bt_pw;
    
    // signal 연결
    bt_id.signal_clicked().connect(sigc::ptr_fun(edit_id));
    bt_id.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridSidebar_id));
    bt_pw.signal_clicked().connect(sigc::ptr_fun(edit_pw));
    bt_pw.signal_clicked().connect(sigc::ptr_fun(refresh_AdministratorPage_MyGridSidebar_pw));
}


template <class MyGrid>
MyFrame<MyGrid>::MyFrame()
{
    // MyFrame 설정
    set_hexpand();
    
    // child 등록
    set_child(gd);
}


AdministratorPage::AdministratorPage() :
lb1("계정 설정"),
lb2("\n음료 정보 및 재고"),
lb3("\n거스름돈"),
lb4("\n매출")
{
    // Window 설정
    set_title("관리자 메뉴");
    set_default_size(470, 600);
    set_size_request(470, 300);     // 윈도우 최소 크기 설정
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
    bx.append(lb3);
    bx.append(fm3);
    bx.append(lb4);
    bx.append(fm4);
    
    // Label 설정
    lb1.set_xalign(0.0);
    lb2.set_xalign(0.0);
    lb3.set_xalign(0.0);
    lb4.set_xalign(0.0);
    
    lb1.set_justify(Gtk::Justification::LEFT);
    lb2.set_justify(Gtk::Justification::LEFT);
    lb3.set_justify(Gtk::Justification::LEFT);
    lb4.set_justify(Gtk::Justification::LEFT);
}


}
