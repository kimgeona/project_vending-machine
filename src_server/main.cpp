// c++17
#include <gtkmm.h>
#include <iostream>
#include <map>

// 나의 라이브러리
#include <gui.hpp>
#include <data.hpp>

// 전역 변수
std::map<std::string, data::DataManagement> dms;
std::map<std::string, Gtk::Widget*>         widget;

int main(int argc, char* argv[])
{
    using namespace std;
    
    // 1. 현존하는 자판기 조사
    
    cout << "Vending-Machine-server : 자판기 파일들을 조사합니다." << endl;
    // 현재 자판기들 종류(파일) 조사
    cout << "Vending-Machine-server : 자판기 파일들을 업데이트 합니다." << endl;
    // 각 자판기 클라이언트 들로부터 파일 받기
    cout << "Vending-Machine-server : 데이터 관리자를 생성합니다." << endl;
    // 각각의 자판기 데이터 관리자를 생성하여 map<string, DataManagement> 컨테이너에 보관하기
    
    // 2. 프로그램 실행
    
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 실행합니다." << endl;
    // 서버 응용프로그램 실행 시키기
    //auto n = Gtk::Application::create("kimgeona.VendingMachine.server")->make_window_and_run<gui::MainPage>(argc, argv);
    cout << "Vending-Machine-server : GUI-server 어플리케이션을 종료합니다." << endl;

    return 0;
}
