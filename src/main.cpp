// c++17
#include <gtkmm.h>
#include <iostream>

// 나의 라이브러리
#include <gui.hpp>

int main(int argc, char* argv[])
{
    // 자판기 어플리케이션 실행
    auto app = Gtk::Application::create("kimgeona.VendingMachine");
    return app->make_window_and_run<gui::MainPage>(argc, argv);
}
