#include <gui_functions.hpp>

namespace gui
{


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


}
