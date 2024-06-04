#include <gui_client_LoginPage.hpp>

namespace gui_client
{


MyGridLogin::MyGridLogin()
{
    // MyGridLogin 설정
    set_halign(Gtk::Align::CENTER);     // MyGridLogin 좌*우 위치 설정
    set_valign(Gtk::Align::CENTER);     // MyGridLogin 상*하 위치 설정
    set_margin(25);                     // 내부 여백 설정
    set_row_spacing(5);                 // 내부 요소 row spacing
    set_column_spacing(5);              // 내부 요소 col spacing
    set_row_homogeneous();
    set_column_homogeneous();
    
    // entry : id 설정
    id.set_placeholder_text("아이디");
    id.set_max_length(50);
    id.set_hexpand(true);
    
    // entry : pw 설정
    pw.set_placeholder_text("비밀번호");
    pw.set_visibility(false);   // 입력된 비밀번호 가리기
    pw.set_max_length(50);
    pw.set_hexpand(true);
    
    // button 설정
    bt.set_label("로그인");
    
    // button 설정
    message.set_label("아이디와 비밀번호를 입력하세요.");
    message.set_sensitive(false);
    message.set_margin_bottom(5);
    
    // child 위젯 등록
    attach(message, 0, 0, 7, 1);
    attach(id, 0, 1, 5, 1);
    attach(pw, 0, 2, 5, 1);
    attach(bt, 5, 1, 2, 2);
    
    // map 컨테이너에 위젯들 저장
    widget["MyGridLogin::message"] = &message;
    widget["MyGridLogin::bt"] = &bt;
    widget["MyGridLogin::id"] = &id;
    widget["MyGridLogin::pw"] = &pw;
    
    // signal 연결
    bt.signal_clicked().connect(sigc::ptr_fun(login));
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
