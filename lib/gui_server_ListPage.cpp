#include <gui_server_ListPage.hpp>

namespace gui_server
{

MyListingScrolledWindow::MyListingScrolledWindow()
{
    // MyListingScrolledWindow 설정
    set_expand();
    set_size_request(350, 400);                                         // 최소 크기 설정
    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);    // 스크롤바 방향 설정
    set_child(gd);
    
    // Grid 설정
    gd.set_hexpand();               // 위젯 꽉 채우기
    gd.set_margin(20);              // 내부 여백 설정
    gd.set_row_spacing(15);         // 내부 요소 row spacing
    gd.set_column_spacing(15);      // 내부 요소 col spacing
    gd.set_row_homogeneous();       // 내부 위젯들 행 크기 동일하게
    gd.set_column_homogeneous();    // 내부 위젯들 열 크기 동일하게
    
    // map 컨테이너에 위젯들 저장
    widget["MyListingScrolledWindow::gd"] = &gd;
    
    // 데이터 관리자 파일들 찾아서 불러오기
    update_DataManagement();
    
    // 격자 안에 버튼들 새로 고침
    refresh_ListPage_MyListingScrolledWindow();
}


ListPage::ListPage() :
bt_sales("매출"),
bt_alart("알림"),
bt_info("정보")
{
    // Window 설정
    set_title("자판기 서버");
    set_child(gd);
    
    // Grid 설정
    gd.set_hexpand();               // 위젯 꽉 채우기
    gd.attach(sw, 0, 0, 1, 1);
    gd.attach(bx, 0, 1, 1, 1);
    
    // Box 설정
    bx.set_expand();
    bx.set_orientation(Gtk::Orientation::HORIZONTAL);
    bx.set_margin(20);
    bx.set_spacing(20);
    bx.set_homogeneous();
    bx.append(bt_sales);
    bx.append(bt_alart);
    bx.append(bt_info);
    
    // Button 설정
    bt_sales.set_expand();
    bt_alart.set_expand();
    bt_info.set_expand();
}


}
