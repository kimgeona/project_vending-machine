// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <thread>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_client.hpp>

// 전역 변수
data::DataManagement                    dm;
std::map<std::string, Gtk::Widget*>     widget;

// 통신 모듈
network::Pipe       pipe_to_server("client", "test");
Glib::Dispatcher    dispatcher;

int main(int argc, char* argv[])
{
    // 1. 프로그램 준비
    std::cout << "Vending-Machine : 데이터 관리자를 생성합니다." << std::endl;
    dm = data::DataManagement("test");
    dm.state = "on";
    dm.save();
    
    // 2. 서버와 연결
    pipe_to_server.start();
    
    // 3. 프로그램 실행
    std::cout << "Vending-Machine : GUI 어플리케이션을 실행합니다." << std::endl;
    auto n = Gtk::Application::create("kimgeona.VendingMachine.client")->make_window_and_run<gui_client::MainPage>(argc, argv);
    std::cout << "Vending-Machine : GUI 어플리케이션을 종료합니다." << std::endl;
    
    // 4. 프로그램 종료
    pipe_to_server.end();
    
    return n;
}
