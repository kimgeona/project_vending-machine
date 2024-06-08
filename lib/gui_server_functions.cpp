#include <gui_server_functions.hpp>

namespace gui_server
{


// ======== network ========

// 자판기 파일 받기
void recv_vm_data(std::string name)
{
    using namespace std::filesystem;
    
    // 자판기 데이터 파일 이름 받기
    std::string file_name;
    std::string file_name2;
    
    // 자판기 데이터 받기
    std::string file_data;
    std::string file_data2;
    
    try
    {
        // 자판기 데이터 파일 이름 받기
        file_name = pipe_to_client.recv(name);
        file_name2 = pipe_to_client.recv(name);
        
        // 자판기 데이터 받기
        file_data = pipe_to_client.recv(name);
        file_data2 = pipe_to_client.recv(name);
    }
    catch (const std::exception& e)
    {
        printf("|  연결 상황이 좋지 않아 파일 수신을 건너뜁니다.\n");
        return;
    }
    
    // 기존 파일 제거
    if (exists(path(file_name))) remove(path(file_name));
    if (exists(path(file_name2))) remove(path(file_name2));
    
    // 자판기 파일 저장
    std::ofstream fout(file_name), fout2(file_name2);
    if (!fout | !fout2)
    {
        throw std::runtime_error("gui_server::recv_vm_data() : 자판기("+ name +") 데이터 파일을 열 수 없습니다.");
    }
    fout << file_data;
    fout2 << file_data2;
    if (!fout | !fout2)
    {
        throw std::runtime_error("gui_server::recv_vm_data() : 자판기("+ name +") 데이터 파일을 쓰는중 오류가 발생했습니다.");
    }
    fout.close();
    fout2.close();
    if (!fout | !fout2)
    {
        throw std::runtime_error("gui_server::recv_vm_data() : 자판기("+ name +") 데이터 파일을 닫는중 오류가 발생했습니다.");
    }
}

// 소켓 확인하고 작업 실행
void check_socket()
{
    // 클라이언트 이름 구하기
    std::string client_name = pipe_to_client.check_who_send_it();
    
    // 실행 동작 구하기
    std::string command = pipe_to_client.recv(client_name);
    
    // 파일 수신
    if (command == "file")
    {
        recv_vm_data(client_name);
    }
    
    // 화면 새로 고침
    if (command == "refresh")
    {
        update_DataManagement();
        refresh_ListPage_MyListingScrolledWindow();
    }
    
    // 콘솔 출력
    if (command == "print")
    {
        printf("|  --> %s\n", pipe_to_client.recv(client_name).c_str());
    }
}

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
    }
    
    // 새로운 버튼 생성
    for (auto& pair : dms)
    {
        // key 값 생성
        std::string id = "MyListingScrolledWindow::bt[" + std::to_string(r) + "][" + std::to_string(c) + "]";
        
        // 버튼 레이블 생성
        std::string s = "";
        
        // 클라이언트와 연결 확인 후 버튼 레이블 생성
        if (pipe_to_client.is_connected(pair.second.name) && pair.second.state == "on")
        {
            s += "\nName : " + pair.second.name + "\n\n";                              // 이름
            s += "IP   : " + pipe_to_client.get_ip(pair.second.name) + "\n";    // 아이피주소
            s += "Port : " + pipe_to_client.get_port(pair.second.name) + "\n";  // 포트번호
        }
        else
        {
            s += "\nName : " + pair.second.name + "\n\n";
            s += "⸝⸝• ̫•⸝⸝\n";
            s += "오프라인\n";
        }
        
        // 버튼 생성, 저장
        widget[id] = Gtk::make_managed<Gtk::Button>(s.c_str());
        
        // 버튼 설정
        dynamic_cast<Gtk::Button*>(widget[id])->set_expand();
        
        // 버튼 설정
        if (pipe_to_client.is_connected(pair.second.name) && pair.second.state == "on")
        {
            dynamic_cast<Gtk::Button*>(widget[id])->set_sensitive(true);
        }
        else
        {
            dynamic_cast<Gtk::Button*>(widget[id])->set_sensitive(false);
        }
        
        
        // 버튼 이벤트 연결
        dynamic_cast<Gtk::Button*>(widget[id])->signal_clicked().connect(sigc::bind(sigc::ptr_fun(open_AdministratorPage), pair.second.name));
        
        // 버튼 배치하기
        dynamic_cast<Gtk::Grid*>(widget["MyListingScrolledWindow::gd"])->attach(*dynamic_cast<Gtk::Button*>(widget[id]), c, r);
        
        // 버튼과 관련된 AdministratorPage창이 존재하면 내용 업데이트
        if (widget.find(pair.second.name+"::AdministratorPage") != widget.end())
        {
            refresh_AdministratorPage_MyGridSidebar(pair.second.name);
            refresh_AdministratorPage_MyGridInventory(pair.second.name);
        }
        
        // 버튼 갯수 업데이트
        if (c<1)    c++;
        else        c--, r++;
    }
}

// 관리자 페이지 열기
void open_AdministratorPage(std::string name)
{
    // 이미 존재하는 페이지인지 확인
    if (widget.find(name+"::AdministratorPage") == widget.end())
    {
        // AdministratorPage 생성
        widget[name+"::AdministratorPage"] = Gtk::make_managed<gui_server::AdministratorPage>(name);
        
        // AdministratorPage 열기
        dynamic_cast<Gtk::Window*>(widget[name+"::AdministratorPage"])->show();
    }
    else
    {
        // AdministratorPage 열기
        dynamic_cast<Gtk::Window*>(widget[name+"::AdministratorPage"])->present();
    }
}

// ======== AdministratorPage ========

// 화면 새로 고침
void refresh_AdministratorPage_MyGridSidebar(std::string name)
{
    refresh_AdministratorPage_MyGridSidebar_id(name);
    refresh_AdministratorPage_MyGridSidebar_pw(name);
}
void refresh_AdministratorPage_MyGridSidebar_id(std::string name)
{
    // 아이디 엔트리 새로 고침
    dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_id"])->set_placeholder_text(dms[name].get_id());
    dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_id"])->set_text("");
    
    // 엔트리 활성 비활성 여부
    if (dms[name].state == "on")
    {
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_id"])->set_sensitive(true);
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridSettings::bt_id"])->set_sensitive(true);
    }
    else
    {
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_id"])->set_sensitive(false);
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridSettings::bt_id"])->set_sensitive(false);
    }
}
void refresh_AdministratorPage_MyGridSidebar_pw(std::string name)
{
    // 비밀번호 엔트리 새로 고침
    dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_pw"])->set_placeholder_text(dms[name].get_pw());
    dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_pw"])->set_text("");
    
    // 엔트리 활성 비활성 여부
    if (dms[name].state == "on")
    {
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_pw"])->set_sensitive(true);
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridSettings::bt_pw"])->set_sensitive(true);
    }
    else
    {
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_pw"])->set_sensitive(false);
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridSettings::bt_pw"])->set_sensitive(false);
    }
}

// 아이디 수정
void edit_id(std::string name)
{
    // 입력된 아이디 구하기
    std::string id = dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_id"])->get_text();
    
    // 데이터 확인
    if (id == "") return;
    
    // 클라이언트에게 수정 요청
    pipe_to_client.send(name, "edit");
    pipe_to_client.send(name, "id");
    pipe_to_client.send(name, id);
}

// 비밀번호 수정
void edit_pw(std::string name)
{
    // 입력된 아이디 구하기
    std::string pw = dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridSettings::elb_pw"])->get_text();
    
    // 데이터 확인
    if (pw == "") return;
    
    // 클라이언트에게 수정 요청
    pipe_to_client.send(name, "edit");
    pipe_to_client.send(name, "pw");
    pipe_to_client.send(name, pw);
}

// 라디오 버튼 활성화 확인
int get_MyGridInventory_radio_button_state(std::string name)
{
    // 활성화된 라디오 버튼 종류 알아내기
    int active;
    if      (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb1"])->get_active()) active = 0;
    else if (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb2"])->get_active()) active = 1;
    else if (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb3"])->get_active()) active = 2;
    else if (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb4"])->get_active()) active = 3;
    else if (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb5"])->get_active()) active = 4;
    else if (dynamic_cast<Gtk::CheckButton*>(widget[name + "::MyGridInventory::cb6"])->get_active()) active = 5;
    else active = -1;
    
    // 활성화된 라디오 버튼 종류 반환
    return active;
}

// 화면 새로 고침
void refresh_AdministratorPage_MyGridInventory(std::string name)
{
    refresh_AdministratorPage_MyGridInventory_name(name);
    refresh_AdministratorPage_MyGridInventory_price(name);
}
void refresh_AdministratorPage_MyGridInventory_name(std::string name)
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridInventory_radio_button_state(name);
    
    // 활성화된 라디오 버튼 종류에 따라 다르게 창 새로 고침
    if (active == -1)
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_placeholder_text("음료 이름");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_na"])->set_sensitive(false);
    }
    else if (dms[name].state == "off")
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_placeholder_text(dms[name].get_drink_name(active));
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_na"])->set_sensitive(false);
    }
    else
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_placeholder_text(dms[name].get_drink_name(active));
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_text("");
        
        // 재고 여부에 따라 활성 비활성
        if (dms[name].get_drink_name(active)=="재고 소진")
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_sensitive(false);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_na"])->set_sensitive(false);
        }
        else
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->set_sensitive(true);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_na"])->set_sensitive(true);
        }
    }
}
void refresh_AdministratorPage_MyGridInventory_price(std::string name)
{
    // 활성화된 라디오 버튼 확인
    int active = get_MyGridInventory_radio_button_state(name);
    
    // 활성화된 라디오 버튼 종류에 따라 다르게 창 새로 고침
    if (active == -1)
    {
        // 음료 가격 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_placeholder_text("음료 가격");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_pr"])->set_sensitive(false);
    }
    else if (dms[name].state == "off")
    {
        // 음료 이름 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_placeholder_text(dms[name].get_drink_price(active));
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_text("");
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_sensitive(false);
        
        // 버튼들 새로고침
        dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_pr"])->set_sensitive(false);
    }
    else
    {
        // 음료 가격 엔트리 새로 고침
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_placeholder_text(dms[name].get_drink_price(active));
        dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_text("");
        
        // 재고 여부에 따라 활성 비활성
        if (dms[name].get_drink_price(active)=="----")
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_sensitive(false);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_pr"])->set_sensitive(false);
        }
        else
        {
            // 음료 이름 엔트리 새로 고침
            dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->set_sensitive(true);
            
            // 버튼들 새로고침
            dynamic_cast<Gtk::Button*>(widget[name + "::MyGridInventory::bt_pr"])->set_sensitive(true);
        }
    }
}

// 음료 이름 수정
void edit_drink_name(std::string name)
{
    // 선택된 라디오 버튼 구하기
    int b = get_MyGridInventory_radio_button_state(name);
    
    // 입력된 음료 이름 구하기
    std::string drink_name = dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_na"])->get_text();
    
    // 데이터 확인
    if (drink_name == "") return;
    
    // 클라이언트에게 수정 요청
    pipe_to_client.send(name, "edit");
    pipe_to_client.send(name, "drink_name");
    pipe_to_client.send(name, drink_name);
    pipe_to_client.send(name, std::to_string(b));
}

// 음료 가격 수정
void edit_drink_price(std::string name)
{
    // 선택된 라디오 버튼 구하기
    int b = get_MyGridInventory_radio_button_state(name);
    
    // 입력된 음료 가격 구하기
    int drink_price = std::stoi(dynamic_cast<Gtk::Entry*>(widget[name + "::MyGridInventory::en_pr"])->get_text());
    
    // 데이터 확인
    if (drink_price < 0)  return;
    
    // 클라이언트에게 수정 요청
    pipe_to_client.send(name, "edit");
    pipe_to_client.send(name, "drink_price");
    pipe_to_client.send(name, std::to_string(drink_price));
    pipe_to_client.send(name, std::to_string(b));
}


}
