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
    
    // checkbutton 설정
    bt1.set_label("일별");
    bt2.set_label("월별");
    bt2.set_group(bt1);
    
    // frame 설정
    fm.set_hexpand();
    fm.set_child(sw);
    
    // scroll window 설정
    sw.set_hexpand();
    sw.set_margin(5);
    sw.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    sw.set_child(tv);
    
    // text buffer 설정
    tb_ptr = Gtk::TextBuffer::create();
    tb_ptr->set_text("--여기에 매출이 표시됩니다.");
    
    // text view 설정
    tv.set_buffer(tb_ptr);
    
    // child 등록
    attach(bt1, 0, 0, 1, 1);
    attach(bt2, 1, 0, 1, 1);
    attach(fm, 0, 1, 2, 7);
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
    lb_total_v.set_label("전체 잔액 합산 표시");
    lb_total_v.set_xalign(0.0);
    lb_refundable.set_label("수금 가능 금액 : ");
    lb_refundable.set_xalign(1.0);
    lb_refundable_v.set_label("수금 가능 잔액 표시");
    lb_refundable_v.set_xalign(0.0);
    
    // Adjustment 생성
    ad[0] = Gtk::Adjustment::create(10.0, 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[1] = Gtk::Adjustment::create(10.0, 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[2] = Gtk::Adjustment::create(10.0, 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[3] = Gtk::Adjustment::create(10.0, 0.0, 100.0, 1.0, 0.0, 0.0);
    ad[4] = Gtk::Adjustment::create(10.0, 0.0, 100.0, 1.0, 0.0, 0.0);
    
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
    
    // child 등록 : 잔액
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
    
    // child 등록 : 전체 잔액
    attach(lb_total, 0, 5, 1, 1);
    attach(lb_total_v, 1, 5, 5, 1);
    
    // child 등록 : 수금
    attach(lb_refundable, 0, 6, 1, 1);
    attach(lb_refundable_v, 1, 6, 4, 1);
    attach(bt_collect, 5, 6, 1, 1);
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
    elb_id.set_placeholder_text("사용자 이름");
    elb_id.set_max_length(50);
    elb_id.set_hexpand(true);
    
    // Entry : pw 설정
    elb_pw.set_placeholder_text("비밀번호");
    elb_pw.set_max_length(50);
    elb_pw.set_hexpand(true);
    
    // Button 설정
    bt_id.set_label("변경");
    bt_pw.set_label("변경");
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
