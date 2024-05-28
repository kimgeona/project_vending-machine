#pragma once
#ifndef gui_functions_hpp
#define gui_functions_hpp

// c++17
#include <gtkmm.h>

// 나의 라이브러리
#include <gui_MainPage.hpp>
#include <gui_LoginPage.hpp>
#include <gui_AdministratorPage.hpp>

// 전역 변수
extern data::DataManagement dm;
extern std::map<std::string, Gtk::Widget*> widget;

namespace gui
{


// 화면 새로 고침
void refresh_MainPage();


}

#endif /* gui_functions_hpp */
