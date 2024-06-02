// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>

// 나의 라이브러리
#include <gui.hpp>
#include <data.hpp>

// 전역 변수
data::DataManagement dm;
std::map<std::string, Gtk::Widget*> widget;

int main(int argc, char* argv[])
{
    using namespace std;
    
    // 1. 프로그램 준비
    cout << "Vending-Machine : 프로그램을 준비합니다." << endl;
    cout << "Vending-Machine : 데이터 관리자를 생성합니다." << endl;
    dm = data::DataManagement("test");
    
    // 2. 프로그램 실행
    cout << "Vending-Machine : GUI 어플리케이션을 실행합니다." << endl;
    auto n = Gtk::Application::create("kimgeona.VendingMachine")->make_window_and_run<gui::MainPage>(argc, argv);
    cout << "Vending-Machine : GUI 어플리케이션을 종료합니다." << endl;
    return n;
}
