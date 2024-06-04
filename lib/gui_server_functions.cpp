#include <gui_server_functions.hpp>

namespace gui_server
{


// ======== ListPage ========

// 데이터 관리자 파일들 찾아서 불러오기
void update_DataManagement()
{
    using namespace std;
    using namespace std::filesystem;
    
    // dms 초기화
    dms = std::map<std::string, data::DataManagement>();
    
    // DataManagement 파일 조사
    for (auto& p : directory_iterator(path(".")))
    {
        // 데이터 관리자 파일이 아니면 건너뛰기
        if (p.path().filename().string().find("_data.txt") == std::string::npos) continue;
        
        // 이름 구하기
        string name = p.path().filename().string();
        name.erase(name.length()-9, 9);
        
        // DataManagement()를 생성하여 dms에 추가
        dms[name] = data::DataManagement(name);
    }
}

// 격자 안에 버튼들 새로 고침
void refresh_ListPage_MyListingScrolledWindow()
{
    // 버튼 갯수 정보
    static int r=0, c=0;
    
    // 기존에 존재하는 버튼 제거
    while (r | c)
    {
        // 버튼 갯수 업데이트
        if (c>0)    c--;
        else        c++, r--;
        
        // key 값 생성
        std::string id = "MyListingScrolledWindow::bt[" + std::to_string(r) + "][" + std::to_string(c) + "]";
        
        // grid에 부착했던 기존 버튼 제거
        dynamic_cast<Gtk::Grid*>(widget["MyListingScrolledWindow::gd"])->remove(*dynamic_cast<Gtk::Button*>(widget[id]));
        
        // 기존 버튼 메모리 해제
        delete dynamic_cast<Gtk::Button*>(widget[id]);
    }
    
    // 새로운 버튼 생성
    for (auto& pair : dms)
    {
        // key 값 생성
        std::string id = "MyListingScrolledWindow::bt[" + std::to_string(r) + "][" + std::to_string(c) + "]";
        
        // 버튼 레이블 생성
        std::string s = "";
        s += "\nName : " + pair.second.name + "\n\n";   // 이름
        s += "IP   : (나중에)\n";                 // 아이피
        s += "Port : (나중에)\n";                 // 포트번호
        s += "Update : 5분전\n";
        
        // 버튼 생성, 저장
        widget[id] = new Gtk::Button(s);
        
        // 버튼 설정
        dynamic_cast<Gtk::Button*>(widget[id])->set_expand();
        
        // 버튼 배치하기
        dynamic_cast<Gtk::Grid*>(widget["MyListingScrolledWindow::gd"])->attach(*dynamic_cast<Gtk::Button*>(widget[id]), c, r);
        
        // 버튼 갯수 업데이트
        if (c<1)    c++;
        else        c--, r++;
    }
}


}
