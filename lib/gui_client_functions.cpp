#include <gui_client_functions.hpp>

namespace gui_client
{

// ======== MainPage ========

// 화면 새로 고침
void refresh_MainPage()
{
    // 음료 버튼 새로 고침
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt1"])->lb1.set_label(dm.get_drink_name(0));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt1"])->lb2.set_label(dm.get_drink_price(0));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt2"])->lb1.set_label(dm.get_drink_name(1));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt2"])->lb2.set_label(dm.get_drink_price(1));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt3"])->lb1.set_label(dm.get_drink_name(2));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt3"])->lb2.set_label(dm.get_drink_price(2));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt4"])->lb1.set_label(dm.get_drink_name(3));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt4"])->lb2.set_label(dm.get_drink_price(3));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt5"])->lb1.set_label(dm.get_drink_name(4));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt5"])->lb2.set_label(dm.get_drink_price(4));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt6"])->lb1.set_label(dm.get_drink_name(5));
    dynamic_cast<MyButtonMenu*>(widget["MyGridMenu::bt6"])->lb2.set_label(dm.get_drink_price(5));
    
    // 음료수 출구 새로 고침
    dynamic_cast<Gtk::Button*>(widget["MyGridReturnTray::bt1"])->set_label(dm.get_out_drink());
    
    // 거스름돈 출구 새로 고침
    dynamic_cast<Gtk::Button*>(widget["MyGridReturnTray::bt2"])->set_label(dm.get_out_coin());
    
    // 상태 메시지 새로 고침
    dynamic_cast<Gtk::Button*>(widget["MyGridSidebar::bt1"])->set_label(dm.get_status_message());
    
    // 선택한 음료 정보 새로 고침
    dynamic_cast<MyButtonMenu*>(widget["MyGridSidebar::bt2"])->lb2.set_label(dm.get_selected_drink());
    
    // 투입된 금액 정보 새로 고침
    dynamic_cast<MyButtonMenu*>(widget["MyGridSidebar::bt3"])->lb2.set_label(dm.get_inserted_coins());
}

// 로그인 페이지 열기
void show_login_page()
{
    // 버튼들 비활성화
    
    // LoginPage 생성
    widget["LoginPage"] = Gtk::make_managed<gui_client::LoginPage>();
    
    // LoginPage 열기
    dynamic_cast<Gtk::Window*>(widget["LoginPage"])->show();
}

// ======== LoginPage ========

// 로그인
void login()
{
    // 아이디와 비밀번호 가져오기
    std::string id = dynamic_cast<Gtk::Entry*>(widget["MyGridLogin::id"])->get_text();
    std::string pw = dynamic_cast<Gtk::Entry*>(widget["MyGridLogin::pw"])->get_text();
    
    // 로그인 진행
    if (id != dm.get_id())
    {
        dynamic_cast<Gtk::Button*>(widget["MyGridLogin::message"])->set_label("아이디를 다시 확인하여 주세요.");
        return;
    }
    if (pw != dm.get_pw())
    {
        dynamic_cast<Gtk::Button*>(widget["MyGridLogin::message"])->set_label("비밀번호를 다시 확인하여 주세요.");
        return;
    }
    
    // 로그인 성공
    dynamic_cast<Gtk::Button*>(widget["MyGridLogin::message"])->set_label("로그인 성공.");
    
    // 이미 존재하는 페이지인지 확인
    if (widget.find("AdministratorPage") == widget.end())
    {
        // AdministratorPage 생성
        widget["AdministratorPage"] = Gtk::make_managed<gui_client::AdministratorPage>();
        
        // AdministratorPage 열기
        dynamic_cast<Gtk::Window*>(widget["AdministratorPage"])->show();
    }
    else
    {
        // AdministratorPage 열기
        dynamic_cast<Gtk::Window*>(widget["AdministratorPage"])->present();
    }
    
    // LoginPage 닫기
    dynamic_cast<Gtk::Window*>(widget["LoginPage"])->destroy();
}

// ======== AdministratorPage ========

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSidebar()
{
    refresh_AdministratorPage_MyGridSidebar_id();
    refresh_AdministratorPage_MyGridSidebar_pw();
}
void refresh_AdministratorPage_MyGridSidebar_id()
{
    // 아이디 엔트리 새로 고침
    dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_id"])->set_placeholder_text(dm.get_id());
    dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_id"])->set_text("");
}
void refresh_AdministratorPage_MyGridSidebar_pw()
{
    // 비밀번호 엔트리 새로 고침
    dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_pw"])->set_placeholder_text(dm.get_pw());
    dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_pw"])->set_text("");
}

// 라디오 버튼 활성화 확인
int get_MyGridInventory_radio_button_state()
{
    // 활성화된 라디오 버튼 종류 알아내기
    int active;
    if      (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb1"])->get_active()) active = 0;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb2"])->get_active()) active = 1;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb3"])->get_active()) active = 2;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb4"])->get_active()) active = 3;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb5"])->get_active()) active = 4;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridInventory::cb6"])->get_active()) active = 5;
    else                                                                                    active = -1;
    
    // 활성화된 라디오 버튼 종류 반환
    return active;
}

// 화면 새로 고침
void refresh_AdministratorPage_MyGridInventory()
{
    refresh_AdministratorPage_MyGridInventory_name();
    refresh_AdministratorPage_MyGridInventory_price();
    refresh_AdministratorPage_MyGridInventory_num();
}
void refresh_AdministratorPage_MyGridInventory_name()
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridInventory_radio_button_state();
    
    // 활성화된 라디오 버튼 종류에 따라 다르게 창 새로 고침
    if (active == -1)
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_placeholder_text("음료 이름");
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_na"])->set_sensitive(false);
    }
    else
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_placeholder_text(dm.get_drink_name(active));
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_text("");
        
        // 재고 여부에 따라 활성 비활성
        if (dm.get_drink_name(active)=="재고 소진")
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_sensitive(false);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_na"])->set_sensitive(false);
        }
        else
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->set_sensitive(true);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_na"])->set_sensitive(true);
        }
    }
}
void refresh_AdministratorPage_MyGridInventory_price()
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridInventory_radio_button_state();
    
    // 활성화된 라디오 버튼 종류에 따라 다르게 창 새로 고침
    if (active == -1)
    {
        // 음료 가격 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_placeholder_text("음료 가격");
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_pr"])->set_sensitive(false);
    }
    else
    {
        // 음료 가격 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_placeholder_text(dm.get_drink_price(active));
        dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_text("");
        
        // 재고 여부에 따라 활성 비활성
        if (dm.get_drink_price(active)=="----")
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_sensitive(false);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_pr"])->set_sensitive(false);
        }
        else
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->set_sensitive(true);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_pr"])->set_sensitive(true);
        }
    }
}
void refresh_AdministratorPage_MyGridInventory_num()
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridInventory_radio_button_state();
    
    // 활성화된 라디오 버튼 종류에 따라 다르게 창 새로 고침
    if (active == -1)
    {
        // 음료 갯수 스핀버튼 새로 고침
        dynamic_cast<Gtk::SpinButton*>(widget["MyGridInventory::sb_re"])->set_value(0.0);
        dynamic_cast<Gtk::SpinButton*>(widget["MyGridInventory::sb_re"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_re"])->set_sensitive(false);
    }
    else
    {
        // 음료 갯수 스핀버튼 새로 고침
        dynamic_cast<Gtk::SpinButton*>(widget["MyGridInventory::sb_re"])->set_value(std::stod(dm.get_drink_num(active)));
        dynamic_cast<Gtk::SpinButton*>(widget["MyGridInventory::sb_re"])->set_sensitive(true);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget["MyGridInventory::bt_re"])->set_sensitive(true);
    }
}

// 아이디 수정
void edit_id()
{
    // 입력된 아이디 구하기
    std::string id = dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_id"])->get_text();
    
    // 기존 아이디 변경
    if (id != "") dm.set_id(id);
}

// 비밀번호 수정
void edit_pw()
{
    // 입력된 아이디 구하기
    std::string pw = dynamic_cast<Gtk::Entry*>(widget["MyGridSettings::elb_pw"])->get_text();
    
    // 기존 아이디 변경
    if (pw != "") dm.set_pw(pw);
}

// 음료 이름 수정
void edit_drink_name()
{
    // 선택된 라디오 버튼 구하기
    int b = get_MyGridInventory_radio_button_state();
    
    // 입력된 음료 이름 구하기
    std::string name = dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_na"])->get_text();
    
    // 기존 음료 이름 변경
    if (name != "") dm.set_drink_name(b, name);
}

// 음료 가격 수정
void edit_drink_price()
{
    // 선택된 라디오 버튼 구하기
    int b = get_MyGridInventory_radio_button_state();
    
    // 입력된 음료 가격 구하기
    int price = std::stoi(dynamic_cast<Gtk::Entry*>(widget["MyGridInventory::en_pr"])->get_text());
    
    // 기존 음료 가격 변경
    if (price >= 0) dm.set_drink_price(b, price);
}

// 음료 갯수 수정
void edit_drink_num()
{
    // 선택된 라디오 버튼 구하기
    int b = get_MyGridInventory_radio_button_state();
    
    // 입력된 음료 갯수 구하기
    int v = dynamic_cast<Gtk::SpinButton*>(widget["MyGridInventory::sb_re"])->get_value();
    
    // 기존 음료 갯수 구하기
    int n = std::stoi(dm.get_drink_num(b));
    
    // 입력한 갯수가 기존 갯수보다 많을 떄
    if (v > n) for (int i=n; i<v; i++)
    {
        std::string name = dm.get_drink_name(b);
        std::string price = dm.get_drink_price(b);
        
        if (name == "재고 소진") dm.push_drink(b, data::Drink("이름 없는 음료", 0));
        else                   dm.push_drink(b, data::Drink(name, std::stoi(price)));
    }
    
    // 입력한 갯수가 기존 갯수보다 적을 때
    if (v < n) for (int i=n; i>v; i--) dm.pop_drink(b);
}

// 화면 새로 고침
void refresh_AdministratorPage_MyGridChanges()
{
    // 거스름돈 갯수 새로 고침
    dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb[0]"])->set_value(std::stod(dm.get_coin_num(0)));
    dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb[1]"])->set_value(std::stod(dm.get_coin_num(1)));
    dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb[2]"])->set_value(std::stod(dm.get_coin_num(2)));
    dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb[3]"])->set_value(std::stod(dm.get_coin_num(3)));
    dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb[4]"])->set_value(std::stod(dm.get_coin_num(4)));
    
    // 전체 잔액 새로 고침
    dynamic_cast<Gtk::Label*>(widget["MyGridChanges::lb_total_v"])->set_text(dm.get_balance());
    
    // 수금 가능 금액 새로 고침
    dynamic_cast<Gtk::Label*>(widget["MyGridChanges::lb_refundable_v"])->set_text(dm.get_collectable_changes());
}

// 동전 갯수 서정
void edit_coin_num(int slot_number)
{
    // 입력된 동전 갯수 구하기
    int v = dynamic_cast<Gtk::SpinButton*>(widget["MyGridChanges::sb["+std::to_string(slot_number)+"]"])->get_value();
    
    // 기존 음료 갯수 구하기
    int n = std::stoi(dm.get_coin_num(slot_number));
    
    // 입력한 갯수가 기존 갯수보다 많을 때
    if (v > n) for (int i=n; i<v; i++) switch (slot_number)
    {
        case 0: dm.push_coin(slot_number, data::Coin(10, 2024));   break;
        case 1: dm.push_coin(slot_number, data::Coin(50, 2024));   break;
        case 2: dm.push_coin(slot_number, data::Coin(100, 2024));  break;
        case 3: dm.push_coin(slot_number, data::Coin(500, 2024));  break;
        case 4: dm.push_coin(slot_number, data::Coin(1000, 2024)); break;
    }
    
    // 입력한 갯수가 기존 갯수보다 적을 때
    if (v < n) for (int i=n; i>v; i--) dm.pop_coin(slot_number);
}

// 라디오 버튼 활성화 확인
int get_MyGridSales_radio_button_state()
{
    // 활성화된 라디오 버튼 종류 알아내기
    int active;
    if      (dynamic_cast<Gtk::CheckButton*>(widget["MyGridSales::cb1"])->get_active()) active = 0;
    else if (dynamic_cast<Gtk::CheckButton*>(widget["MyGridSales::cb2"])->get_active()) active = 1;
    else                                                                                active = -1;
    
    // 활성화된 라디오 버튼 종류 반환
    return active;
}

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSales()
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridSales_radio_button_state();
    
    // 활성화된 라디오 버튼 종류에 따라 레이블 내용 새로고침.
    switch (active) {
        case -1:
            dynamic_cast<Gtk::Label*>(widget["MyGridSales::lb"])->set_text("-- 여기에 매출이 표시됩니다."); 
            break;
        case 0:
            dynamic_cast<Gtk::Label*>(widget["MyGridSales::lb"])->set_text(dm.get_sales_day());
            break;
        case 1:
            dynamic_cast<Gtk::Label*>(widget["MyGridSales::lb"])->set_text(dm.get_sales_month()); 
            break;
    }
}


}
