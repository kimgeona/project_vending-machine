// c++17
#include <gtkmm.h>
#include <iostream>

// 나의 라이브러리
#include <gui.hpp>

int main(int argc, char* argv[])
{
    int e1=0, e2=0, e3=0;
    
    // 자판기 어플리케이션 메인 페이지 실행
    auto app_MainPage = Gtk::Application::create("kimgeona.VendingMachine.MainPage");
    e1 = app_MainPage->make_window_and_run<gui::MainPage>(argc, argv);
    
    // 자판기 어플리케이션 로그인 페이지 실행
    auto app_LoginPage = Gtk::Application::create("kimgeona.VendingMachine.LoginPage");
    e2 = app_LoginPage->make_window_and_run<gui::LoginPage>(argc, argv);
    
    return e1 || e2 || e3;
}
