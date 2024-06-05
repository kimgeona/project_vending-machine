// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <thread>

// 나의 라이브러리
#include <data.hpp>
#include <network_client.hpp>
#include <gui_client.hpp>

// 전역 변수
data::DataManagement                    dm;
std::map<std::string, Gtk::Widget*>     widget;
std::map<std::string, Glib::Dispatcher> dispatchers;

int main(int argc, char* argv[])
{
    // 1. 프로그램 준비
    std::cout << "Vending-Machine : 데이터 관리자를 생성합니다." << std::endl;
    dm = data::DataManagement("test");
    dm.state = "on";
    dm.save();
    
    // 2. 소켓 통신 시작하기
    network::make_dispatchers();
    std::thread(network::Networking).detach();
    
    // 3. 프로그램 실행
    std::cout << "Vending-Machine : GUI 어플리케이션을 실행합니다." << std::endl;
    auto n = Gtk::Application::create("kimgeona.VendingMachine.client")->make_window_and_run<gui_client::MainPage>(argc, argv);
    std::cout << "Vending-Machine : GUI 어플리케이션을 종료합니다." << std::endl;
    
    // 4. 프로그램 종료
    dm.state = "off";
    dm.save();
    
    return n;
}
