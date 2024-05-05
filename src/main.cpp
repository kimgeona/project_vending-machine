// c++17
#include <gtkmm.h>
#include <iostream>

// 나의 라이브러리
#include <gui.hpp>
#include <data.hpp>


void preparation();                 // 프로그램 준비
void run(int argc, char* argv[]);   // 프로그램 시작
void test();                        // 테스트


int main(int argc, char* argv[])
{
    // 1. 프로그램 준비
    preparation();
    
    // 2. 프로그램 시작
    run(argc, argv);
    
    // 0. 테스트
    //test();
    
    return 0;
}


void preparation()
{
    using namespace std;
    cout << "Vending-Machine : 프로그램을 준비합니다." << endl;
}


void run(int argc, char* argv[])
{
    using namespace std;
    cout << "Vending-Machine : GUI 어플리케이션을 실행합니다." << endl;
    
    auto app_MainPage = Gtk::Application::create("kimgeona.VendingMachine.MainPage");
    auto app_LoginPage = Gtk::Application::create("kimgeona.VendingMachine.LoginPage");
    auto app_AdministratorPage = Gtk::Application::create("kimgeona.VendingMachine.AdministratorPage");
    
    app_MainPage->make_window_and_run<gui::MainPage>(argc, argv)    ||
    app_LoginPage->make_window_and_run<gui::LoginPage>(argc, argv)  ||
    app_AdministratorPage->make_window_and_run<gui::AdministratorPage>(argc, argv);
    
    cout << "Vending-Machine : 프로그램을 종료합니다." << endl;
}


void test()
{
    using namespace std;
    cout << "Test : 데이터 관리자를 실행합니다." << endl;
    
    data::DataManagement dm("test.txt");
}
