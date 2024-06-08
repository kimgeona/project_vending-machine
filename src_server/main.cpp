// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <thread>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_server.hpp>

// 프로그램 버전
#define VM_VERSION (std::to_string(VM_VERSION_MAJOR) + "."+ std::to_string(VM_VERSION_MINOR) + "." + std::to_string(VM_VERSION_PATCH))

// 전역 변수
std::map<std::string, data::DataManagement> dms;
std::map<std::string, Gtk::Widget*>         widget;

// 통신 모듈
network::Pipe       pipe_to_client("server");
Glib::Dispatcher    dispatcher;

int main(int argc, char* argv[])
{
    using namespace std;
    
    // 1. 기본 내용 출력
    std::cout << "|  ⸝⸝• ̫•⸝⸝"                                          << std::endl;
    std::cout << "|"                                                << std::endl;
    std::cout << "|  Vending-Machine server(" << VM_VERSION << ")"  << std::endl;
    std::cout << "|-"                                               << std::endl;
    
    // 2. 클라이언트와 연결
    pipe_to_client.start();
    
    // 2. 프로그램 실행
    std::cout << "|-\n|  GUI 어플리케이션을 실행합니다.\n|-\n";
    auto n = Gtk::Application::create("kimgeona.VendingMachine.server")->make_window_and_run<gui_server::ListPage>(argc, argv);
    std::cout << "|-\n|  GUI 어플리케이션을 종료합니다.\n|-\n";
    
    // 3. 프로그램 종료
    pipe_to_client.end();
    
    return n;
}
