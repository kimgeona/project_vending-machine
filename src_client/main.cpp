// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>
#include <thread>

// 나의 라이브러리
#include <data.hpp>
#include <network.hpp>
#include <gui_client.hpp>

// 프로그램 버전
#define VM_VERSION (std::to_string(VM_VERSION_MAJOR) + "."+ std::to_string(VM_VERSION_MINOR) + "." + std::to_string(VM_VERSION_PATCH))

// 전역 변수
data::DataManagement                    dm;
std::map<std::string, Gtk::Widget*>     widget;

// 통신 모듈
network::Pipe       pipe_to_server("client", "name");
Glib::Dispatcher    dispatcher;

int main(int argc, char* argv[])
{
    // 1. 자판기 이름 입력받기
    std::string vm_name = "";
    std::cout << "|  ⸝⸝• ̫•⸝⸝"                                          << std::endl;
    std::cout << "|"                                                << std::endl;
    std::cout << "|  Vending-Machine client(" << VM_VERSION << ")"  << std::endl;
    std::cout << "|-"                                               << std::endl;
    while (true)
    {
        std::cout << "|  자판기 이름 입력 : ";
        std::cin >> vm_name;
        std::cout << "|" << std::endl << "|" << std::endl;
        
        // 2. 사용중이지 않은 자판기인지 확인하고 불러오기
        dm = data::DataManagement(vm_name);
        if (dm.state == "off")
        {
            dm.state = "on";
            dm.save();
            break;
        }
        std::cout << "|  이미 실행중인 자판기 입니다." << std::endl;
    }
    
    // 3. 서버와 연결
    pipe_to_server.change_name(vm_name);
    pipe_to_server.start();
    
    // 4. 프로그램 실행
    std::cout << "|-\n|  GUI 어플리케이션을 실행합니다.\n|-\n";
    auto n = Gtk::Application::create("kimgeona.VendingMachine.client")->make_window_and_run<gui_client::MainPage>(argc, argv);
    std::cout << "|-\n|  GUI 어플리케이션을 종료합니다.\n|-\n";
    
    // 5. 프로그램 종료
    pipe_to_server.end();
    
    return n;
}
