#include <gui_AdministratorPage.hpp>

namespace gui
{


MyGridSales::MyGridSales()
{
    // MyGridSales 설정
    set_hexpand();
    set_margin(15);          // 내부 여백 설정
    set_row_spacing(10);     // 내부 요소 row spacing
    set_column_spacing(10);  // 내부 요소 col spacing
    
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
    attach(fm, 0, 1, 2, 20);
}
MyGridChanges::MyGridChanges()
{
    // MyGridChanges 설정
    set_hexpand();
    set_margin(15);          // 내부 여백 설정
    set_row_spacing(10);     // 내부 요소 row spacing
    set_column_spacing(10);  // 내부 요소 col spacing
    
    // label 설정
    lb1.set_label("₩   10 : ");
    lb2.set_label("₩   50 : ");
    lb3.set_label("₩  100 : ");
    lb4.set_label("₩  500 : ");
    lb5.set_label("₩ 1000 : ");
    lb_total.set_label("전체 잔액 : ");
    lb_refundable.set_label("수금 가능 금액 : ");
    
    // entry 설정
    en1.set_placeholder_text("잔액 표시");
    en2.set_placeholder_text("잔액 표시");
    en3.set_placeholder_text("잔액 표시");
    en4.set_placeholder_text("잔액 표시");
    en5.set_placeholder_text("잔액 표시");
    en_total.set_placeholder_text("전체 잔액 합산 표시");
    en_refundable.set_placeholder_text("수금 가능 잔액 표시");
    
    // button 설정
    bt1_p.set_label("+");
    bt2_p.set_label("+");
    bt3_p.set_label("+");
    bt4_p.set_label("+");
    bt5_p.set_label("+");
    bt1_m.set_label("-");
    bt2_m.set_label("-");
    bt3_m.set_label("-");
    bt4_m.set_label("-");
    bt5_m.set_label("-");
    bt_collect.set_label("수금하기");
    
    // child 등록 : 잔액
    attach(lb1, 0, 0, 2, 1);
    attach(lb2, 0, 1, 2, 1);
    attach(lb3, 0, 2, 2, 1);
    attach(lb4, 0, 3, 2, 1);
    attach(lb5, 0, 4, 2, 1);
    attach(en1, 2, 0, 8, 1);
    attach(en2, 2, 1, 8, 1);
    attach(en3, 2, 2, 8, 1);
    attach(en4, 2, 3, 8, 1);
    attach(en5, 2, 4, 8, 1);
    attach(bt1_m, 10, 0, 1, 1);
    attach(bt2_m, 10, 1, 1, 1);
    attach(bt3_m, 10, 2, 1, 1);
    attach(bt4_m, 10, 3, 1, 1);
    attach(bt5_m, 10, 4, 1, 1);
    attach(bt1_p, 11, 0, 1, 1);
    attach(bt2_p, 11, 1, 1, 1);
    attach(bt3_p, 11, 2, 1, 1);
    attach(bt4_p, 11, 3, 1, 1);
    attach(bt5_p, 11, 4, 1, 1);
    
    // child 등록 : 전체 잔액
    attach(lb_total, 0, 5, 2, 1);
    attach(en_total, 2, 5, 10, 1);
    
    // child 등록 : 수금
    attach(lb_refundable, 0, 6, 2, 1);
    attach(en_refundable, 2, 6, 8, 1);
    attach(bt_collect, 10, 6, 2, 1);
}
MyGridInventory::MyGridInventory()
{
    // MyGridInventory 설정
    set_hexpand();
    set_margin(15);          // 내부 여백 설정
    set_row_spacing(10);     // 내부 요소 row spacing
    set_column_spacing(10);  // 내부 요소 col spacing
    
    // box 설정
    bx.append(cb1);
    bx.append(cb2);
    bx.append(cb3);
    bx.append(cb4);
    bx.append(cb5);
    bx.append(cb6);
    
    // checkbutton 설정
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
    
    // label 설정
    lb_na.set_label("이름 : ");
    lb_pr.set_label("가격 : ");
    lb_re.set_label("갯수 : ");
    
    // entry 설정
    en_na.set_placeholder_text("음료 이름");
    en_pr.set_placeholder_text("음료 가격");
    en_re.set_placeholder_text("음료 갯수");
    
    // button 설정
    bt_na.set_label("수정");
    bt_pr.set_label("수정");
    bt_re_p.set_label("+");
    bt_re_m.set_label("-");
    
    // child 등록
    attach(bx, 0, 0, 12, 1);
    attach(lb_na, 0, 1, 2, 1);
    attach(lb_pr, 0, 2, 2, 1);
    attach(lb_re, 0, 3, 2, 1);
    attach(en_na, 2, 1, 8, 1);
    attach(en_pr, 2, 2, 8, 1);
    attach(en_re, 2, 3, 8, 1);
    attach(bt_na, 10, 1, 2, 1);
    attach(bt_pr, 10, 2, 2, 1);
    attach(bt_re_m, 10, 3, 1, 1);
    attach(bt_re_p, 11, 3, 1, 1);
}
MyGridSettings::MyGridSettings()
{
    // MyGridSettings 설정
    set_hexpand();
    set_margin(15);          // 내부 여백 설정
    set_row_spacing(10);     // 내부 요소 row spacing
    set_column_spacing(10);  // 내부 요소 col spacing
    
    
    // label 설정
    label_id.set_label("ID : ");
    label_pw.set_label("PW : ");
    
    // entry : id 설정
    id.set_placeholder_text("사용자 이름");
    id.set_max_length(50);
    id.set_hexpand(true);
    
    // entry : pw 설정
    pw.set_placeholder_text("비밀번호");
    pw.set_max_length(50);
    pw.set_hexpand(true);
    
    // button 설정
    button_id.set_label("변경");
    button_pw.set_label("변경");
    
    // child 등록
    attach(label_id, 0, 0, 1, 1);
    attach(label_pw, 0, 1, 1, 1);
    attach(id, 1, 0, 4, 1);
    attach(pw, 1, 1, 4, 1);
    attach(button_id, 5, 0, 1, 1);
    attach(button_pw, 5, 1, 1, 1);
}


template <class MyGrid>
MyFrame<MyGrid>::MyFrame(Glib::ustring name)
{
    // MyFrame 설정
    set_hexpand();
    set_label(name);                        // 레이블 설정
    set_label_align(Gtk::Align::CENTER);    // 레이블 위치 설정
    
    // child 등록
    set_child(gd);
}

MyBoxListedFrames::MyBoxListedFrames() :
fm1("계정 설정"),
fm2("음료 정보 및 재고"),
fm3("거스름돈"),
fm4("매출")
{
    // MyBoxListedFrames 설정
    set_expand();
    set_orientation(Gtk::Orientation::VERTICAL);    // 포함되는 위젯들 나열 방향 설정
    set_margin(20);
    set_spacing(15);                                // 포함되는 위젯들 사이 공간 설정
    
    // child 등록
    append(fm1);
    append(fm2);
    append(fm3);
    append(fm4);
}

MyScrolledWindow::MyScrolledWindow()
{
    // MyScrolledWindow 설정
    set_expand();
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);    // 스크롤바 설정
    
    // child 등록
    set_child(bx);
}

AdministratorPage::AdministratorPage()
{
    // window 설정
    set_title("관리자 메뉴");
    set_default_size(450, 600);
    set_size_request(450, 300);     // 윈도우 최소 크기 설정
    
    // child 등록
    set_child(sw);
}


}
