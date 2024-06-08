// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <thread>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_server.hpp>

// 전역 변수
std::map<std::string, data::DataManagement> dms;
std::map<std::string, Gtk::Widget*>         widget;

// 통신 모듈
network::Pipe       pipe_to_client("server");
Glib::Dispatcher    dispatcher;

int main(int argc, char* argv[])
{
    using namespace std;
    
    // 1. 클라이언트와 연결
    pipe_to_client.start();
    
    // 2. 프로그램 실행
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 실행합니다." << endl;
    auto n = Gtk::Application::create("kimgeona.VendingMachine.server")->make_window_and_run<gui_server::ListPage>(argc, argv);
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 종료합니다." << endl;
    
    // 3. 프로그램 종료
    pipe_to_client.end();
    
    return n;
}
