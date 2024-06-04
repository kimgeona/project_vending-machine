// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>

// 나의 라이브러리
#include <gui_server.hpp>
#include <data.hpp>

// 전역 변수
std::map<std::string, data::DataManagement> dms;
std::map<std::string, Gtk::Widget*>         widget;

int main(int argc, char* argv[])
{
    using namespace std;
    
    // 1. 프로그램 실행
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 실행합니다." << endl;
    auto n = Gtk::Application::create("kimgeona.VendingMachine.server")->make_window_and_run<gui_server::ListPage>(argc, argv);
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 종료합니다." << endl;

    return 0;
}
