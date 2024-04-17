#include <gui_LoginPage.hpp>

namespace gui
{


MyGridLogin::MyGridLogin()
{
    // MyGridLogin 설정
    set_halign(Gtk::Align::CENTER);     // MyGridLogin 좌*우 위치 설정
    set_valign(Gtk::Align::CENTER);     // MyGridLogin 상*하 위치 설정
    set_margin(25);                     // 내부 여백 설정
    set_row_spacing(5);                 // 내부 요소 row spacing
    set_column_spacing(5);              // 내부 요소 col spacing
    
    // entry : id 설정
    id.set_placeholder_text("사용자 이름");
    id.set_max_length(50);
    id.set_hexpand(true);
    
    // entry : pw 설정
    pw.set_placeholder_text("비밀번호");
    pw.set_visibility(false);   // 입력된 비밀번호 가리기
    pw.set_max_length(50);
    pw.set_hexpand(true);
    
    // button 설정
    bt.set_label("로그인");
    
    // child 위젯 등록
    attach(id, 0, 0, 3, 1);
    attach(pw, 0, 1, 3, 1);
    attach(bt, 3, 0, 2, 2);
}

LoginPage::LoginPage()
{
    // window 설정
    set_title("Login Page");        // 윈도우 이름 설정
    set_default_size(300, 150);     // 윈도우 크기 설정
    set_resizable(false);           // 윈도우 크기 고정
    //set_size_request(300, 150);     // 윈도우 최소 크기 설정
    
    // child 위젯 등록
    set_child(gd);
}


}
