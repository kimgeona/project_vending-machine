#include <data_DataManagement.hpp>

namespace data
{


// 생성자
DataManagement::DataManagement()
{
    using namespace std;
    using namespace std::filesystem;
    
    name = "";
    state = "";
    dir_data = path("");
    dir_log = path("");
    ID = "";
    PW = "";
    selected_drink = -1;
    inserted_coins = -1;
    inserted_paper_count = -1;
    
    // 상태 관련 메시지 설정
    status_message = "out of service.";
}
DataManagement::DataManagement(std::string name)
{
    using namespace std;
    using namespace std::filesystem;
    
    // 데이터 관리자 타입 저장
    this->name = name;
    
    // 자판기 데이터 경로 저장
    dir_data = path(name + "_data.txt");
    dir_log = path(name + "_log.txt");
    
    // 자판기 데이터 불러오기
    if (exists(dir_data) && is_regular_file(dir_data))
    {
        // 자판기 데이터 존재
        //cout << "|  data::DataManagement : 자판기("+ name +") 데이터를 불러옵니다." << endl;
        
        // 자판기 데이터에 핵심 데이터가 없을 것을 대비한 기본값 설정
        state   = "off";
        ID      = "admin";
        PW      = "admin";
        
        // 데이터 불러오기
        load();
    }
    else
    {
        // 자판기 데이터가 없다면
        cout << "|  data::DataManagement : 자판기("+ name +")를 새로 생성합니다." << endl;
        
        // 데이터 관리자 타입 저장
        this->state = "off";
        
        // 사용자 계정 생성
        ID = "admin";
        PW = "admin";
        
        // 음료 생성
        for (int i=0; i<10; i++) slot_drink[0].push_back(Drink("물", 450));
        for (int i=0; i<10; i++) slot_drink[1].push_back(Drink("커피", 500));
        for (int i=0; i<10; i++) slot_drink[2].push_back(Drink("이온음료", 550));
        for (int i=0; i<10; i++) slot_drink[3].push_back(Drink("고급커피", 700));
        for (int i=0; i<10; i++) slot_drink[4].push_back(Drink("탄산음료", 750));
        for (int i=0; i<10; i++) slot_drink[5].push_back(Drink("특화음료", 800));
        
        // 잔돈 생성
        for (int i=0; i<10; i++) slot_coin[0].push(Coin(10, 2024));
        for (int i=0; i<10; i++) slot_coin[1].push(Coin(50, 2024));
        for (int i=0; i<10; i++) slot_coin[2].push(Coin(100, 2024));
        for (int i=0; i<10; i++) slot_coin[3].push(Coin(500, 2024));
        for (int i=0; i<10; i++) slot_coin[4].push(Coin(1000, 2024));
        
        // 데이터 저장
        save();
    }
    
    // 자판기 로그 파일 생성하기
    if (exists(dir_log) && is_regular_file(dir_log))
    {
        // 자판기 로그 존재
        //cout << "|  data::DataManagement : 자판기("+ name +") 로그를 불러옵니다." << endl;
    }
    else
    {
        // 자판기 데이터가 없다면
        //cout << "|  data::DataManagement : 자판기("+ name +") 로그를 생성합니다." << endl;
        
        // 로그 파일 생성
        ofstream(dir_log.string()).close();
    }
    
    // 구매 관련 변수 초기화
    selected_drink = -1;
    inserted_coins = 0;
    inserted_paper_count = 0;
    
    // 상태 관련 메시지 설정
    status_message = "구매하실 음료수를 선택하세요.";
    
    //cout << "|  data::DataManagement : 자판기("+ name +") 데이터를 불러왔습니다." << endl;
}

// 데이터 관련
void DataManagement::load()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 변수 생성
    string buf;
    
    // 파일 열기
    ifstream fin(dir_data.string());
    if (!fin)
    {
        throw std::runtime_error("data::DataManagement::load() : 자판기("+ name +") 데이터 파일을 열 수 없습니다.");
    }
    
    while (getline(fin, buf))   // 엔터 제거해서 받음
    {
        // 읽어들인 문자열 전처리
        buf = util::my_strip(buf);                          // 좌우 공백 제거
        vector<string> words = util::my_split(buf, "=");    // "="을 기준으로 split
        
        // 전처리된 문자열이 없으면 건너뛰기
        if (words.empty()) continue;
        
        // 자판기 상태 정보 읽기
        if (words[0]=="state")
        {
            state = words[1];
            continue;
        }
        
        // 사용자 계정 정보 읽기
        if (words[0]=="ID")
        {
            ID = words[1];
            continue;
        }
        if (words[0]=="PW")
        {
            PW = words[1];
            continue;
        }
        
        // 음료 정보 읽기
        if (words[0].find("drink")==0)
        {
            vector<string> type = util::my_split(words[0], "-");
            vector<string> data = util::my_split(words[1], "-");
            
            slot_drink[stoi(type[1])].push_back(Drink(data[0], stoi(data[1])));
            
            continue;
        }
        
        // 잔돈 정보 읽기
        if (words[0].find("coin")==0)
        {
            vector<string> type = util::my_split(words[0], "-");
            vector<string> data = util::my_split(words[1], "-");
            
            slot_coin[stoi(type[1])].push(Coin(stoi(data[0]), stoi(data[1])));
            
            continue;
        }
    }
    
    // 파일 스트림 닫기
    fin.close();
    
    // 읽어들인 파일 저장
    save();
}
void DataManagement::reload()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 변수 생성
    string buf;
    
    // 파일 열기
    ifstream fin(dir_data.string());
    if (!fin)
    {
        throw std::runtime_error("data::DataManagement::load() : 자판기("+ name +") 데이터 파일을 열 수 없습니다.");
    }
    
    while (getline(fin, buf))   // 엔터 제거해서 받음
    {
        // 읽어들인 문자열 전처리
        buf = util::my_strip(buf);                          // 좌우 공백 제거
        vector<string> words = util::my_split(buf, "=");    // "="을 기준으로 split
        
        // 전처리된 문자열이 없으면 건너뛰기
        if (words.empty()) continue;
        
        // 사용자 계정 정보 읽기
        if (words[0]=="ID")
        {
            ID = words[1];
            continue;
        }
        if (words[0]=="PW")
        {
            PW = words[1];
            continue;
        }
        
        // 음료 슬롯 초기화
        for (int i=0; i<6; i++) slot_drink[i].clear();
        
        // 음료 정보 읽기
        if (words[0].find("drink")==0)
        {
            vector<string> type = util::my_split(words[0], "-");
            vector<string> data = util::my_split(words[1], "-");
            
            slot_drink[stoi(type[1])].push_back(Drink(data[0], stoi(data[1])));
            
            continue;
        }
        
        // 잔돈 슬롯 초기화
        for (int i=0; i<6; i++) slot_coin[i].clear();
        
        // 잔돈 정보 읽기
        if (words[0].find("coin")==0)
        {
            vector<string> type = util::my_split(words[0], "-");
            vector<string> data = util::my_split(words[1], "-");
            
            slot_coin[stoi(type[1])].push(Coin(stoi(data[0]), stoi(data[1])));
            
            continue;
        }
    }
    
    // 파일 스트림 닫기
    fin.close();
}
void DataManagement::save()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 기존에 존재하던 백업 파일 삭제
    if (exists(dir_data) && is_regular_file(dir_data)) remove(dir_data);
    
    // 파일 생성
    ofstream fout(dir_data.string());
    
    // 현재 자판기 상태 저장
    fout << "state=" << state << endl << endl;
    
    // 사용자 계정 정보 저장
    fout << "ID=" << ID << endl;
    fout << "PW=" << PW << endl << endl;
    
    // 음료 정보 저장
    for (int i=0; i<6; i++)
        for (int j=0; j<slot_drink[i].size(); j++)
        {
            fout << "drink-" << i << "-" << j;
            fout << "=";
            fout << slot_drink[i][j].name << "-" << std::to_string(slot_drink[i][j].price) << endl;
        }
    fout << endl;
    
    // 잔돈 정보 저장
    for (int i=0; i<5; i++)
        for (int j=0; j<slot_coin[i].size(); j++)
        {
            fout << "coin-" << i << "-" << j;
            fout << "=";
            fout << std::to_string(slot_coin[i][j].amount) << "-" << std::to_string(slot_coin[i][j].banknote) << endl;
        }
    fout << endl;
    
    // 파일 스트림 닫기
    fout.close();
}

// 정보 관련
std::string DataManagement::get_dir_data()
{
    return dir_data.string();
}
std::string DataManagement::get_dir_log()
{
    return dir_log.string();
}

// 정보 수정
void DataManagement::set_id(std::string id)
{
    // 아이디 변경
    if (id != "") this->ID = id;
    
    // 변경 정보 저장
    save();
}
void DataManagement::set_pw(std::string pw)
{
    // 비밀번호 변경
    if (pw != "") this->PW = pw;
    
    // 변경 정보 저장
    save();
}
void DataManagement::set_drink_name(int slot_number, std::string name)
{
    // 음료수 이름 변경
    if (name != "") for (int i=0; i<slot_drink[slot_number].size(); i++)
    {
        // 음료수 빼기
        Drink drink = slot_drink[slot_number].pop_front();
        
        // 음료수 이름 수정
        drink.name = name;
        
        // 음료수 집어넣기
        slot_drink[slot_number].push_back(drink);
    }
    
    // 변경 정보 저장
    save();
}
void DataManagement::set_drink_price(int slot_number, int price)
{
    // 음료수 가격 변경
    if (price >= 0) for (int i=0; i<slot_drink[slot_number].size(); i++)
    {
        // 음료수 빼기
        Drink drink = slot_drink[slot_number].pop_front();
    
        // 음료수 이름 수정
        drink.price = price;
        
        // 음료수 집어넣기
        slot_drink[slot_number].push_back(drink);
    }
    
    // 변경 정보 저장
    save();
}

// 재고 관리
void DataManagement::push_drink(int slot_number, Drink drink)
{
    // 음료 추가
    slot_drink[slot_number].push_back(drink);
    
    // 변경 정보 저장
    save();
}
void DataManagement::push_coin(int slot_number, Coin coin)
{
    // 거스름돈 추가
    slot_coin[slot_number].push(coin);
    
    // 변경 정보 저장
    save();
}
void DataManagement::pop_drink(int slot_number)
{
    if (slot_drink[slot_number].size() > 0)
    {
        // 음료 제거(반환)
        buf_out_drink.push(slot_drink[slot_number].pop_front());
        
        // 변경 정보 저장
        save();
    }
    else
    {
        std::cout << "|  data::DataManagement : 더 이상 빼낼 음료수가 없습니다." << std::endl;
    }
}
void DataManagement::pop_coin(int slot_number)
{
    if (slot_coin[slot_number].size() > 0)
    {
        // 거스름돈 제거(반환)
        buf_out_coin.push(slot_coin[slot_number].pop());
        
        // 변경 정보 저장
        save();
    }
    else
    {
        std::cout << "|  data::DataManagement : 더 이상 빼낼 동전이 없습니다." << std::endl;
    }
}
void DataManagement::collect_changes()
{
    // 수금 가능 금액 만큼 잔돈 수금
    for (int slot=0; slot<5; slot++)                        // 5개의 coin 슬롯에서
        if (slot_coin[slot].size() > 10)                    // 해당 슬롯의 코인 갯수가 10개가 넘는다면
            while (slot_coin[slot].size() > 10)             // 해당 슬롯의 코인 갯수가 10개 이상일때
                buf_out_coin.push(slot_coin[slot].pop());   // 계속해서 코인을 제거(반환)한다.
    
    // 변경 정보 저장
    save();
}

// 구매 관련
void    DataManagement::select_drink(int slot_number)
{
    // 음료수 선택
    if (slot_drink[slot_number].size()==0)  selected_drink = -1;            // 재고 소진인 음료를 선택하는 경우
    else if (selected_drink == -1)          selected_drink = slot_number;   // 처음 선택하는 경우
    else if (selected_drink == slot_number) selected_drink = -1;            // 선택 했던 음료수를 취소하는 경우
    else                                    selected_drink = slot_number;   // 이미 다른 음료수가 선택되어 있는경우
    
    // 상태 관련 메시지 설정
    if (selected_drink == -1)   status_message = "구매하실 음료수를 선택하세요.";
    else                        status_message = "금액을 투입하여 주세요.";
}
void    DataManagement::insert_coin(const Coin& coin)
{
    // 전체 7,000원 상한선
    if ((inserted_coins + coin.amount) > 7000)
    {
        std::cout << "|  data::DataManagement : 입력 받는 금액은 7,000원을 넘을 수 없습니다." << std::endl;
        status_message = "입력 받는 금액은 7,000원을 넘을 수 없습니다.";
        buf_out_coin.push(coin);
        return;
    }
    
    // 지폐는 5장 상한선
    if (coin.amount == 1000 && inserted_paper_count >= 5)
    {
        std::cout << "|  data::DataManagement : 입력 받는 지폐의 갯수는 5장을 넘을 수 없습니다." << std::endl;
        status_message = "입력 받는 지폐의 갯수는 5장을 넘을 수 없습니다.";
        buf_out_coin.push(coin);
        return;
    }
    
    // 돈 입력 받기
    switch (coin.amount)
    {
        case 1000:
            inserted_paper_count += 1;      // 투입 된 지폐 갯수 증가
        case 10:
        case 50:
        case 100:
        case 500:
            inserted_coins += coin.amount;  // 투입 된 금액 증가
            status_message = "금액이 입력 되었습니다.";
            buf_in_coin.push(coin);
            break;
            
        default:
            std::cout << "|  data::DataManagement : 잘못된 금액 입력입니다." << std::endl;
            status_message = "잘못된 금액 입력입니다.";
            buf_out_coin.push(coin);
            return;
    }
}
void    DataManagement::purchase()
{
    // 0. 선택한 음료가 있는지 확인
    if (selected_drink == -1)
    {
        std::cout << "|  data::DataManagement : 구입 하시려는 음료수를 먼저 선택하여 주세요." << std::endl;
        status_message = "음료수를 먼저 선택하여 주세요.";
        return;
    }
    
    // 0. 음료수 남아 있는지 확인
    if (slot_drink[selected_drink].size() < 1)
    {
        std::cout << "|  data::DataManagement : 구입 하시려는 음료수의 재고가 없습니다." << std::endl;
        status_message = "구입 하시려는 음료수의 재고가 없습니다.";
        return;
    }
    
    // 0. 입력된 금액 충분한지 확인
    if (inserted_coins < slot_drink[selected_drink][0].price)
    {
        std::cout << "|  data::DataManagement : 입력하신 금액이 부족합니다." << std::endl;
        status_message = "입력하신 금액이 부족합니다.";
        return;
    }
    
    // 1. 거스름돈 계산
    uint64_t changes = calculate_change(inserted_coins - slot_drink[selected_drink][0].price);
    
    // 0. 거스름돈 반환 가능한지 확인
    if (changes == -1)
    {
        return_coin();
        std::cout << "|  data::DataManagement : 거슬러 드릴 돈이 부족합니다. 금액을 다시 맞게 투입하여 주세요." << std::endl;
        status_message = "거스름돈 부족. 금액을 맞게 투입하세요.";
        return;
    }
    
    // 2. 음료 반환
    buf_out_drink.push(slot_drink[selected_drink].pop_front());
    
    // 3. 거스름돈 반환
    return_change(changes);
    
    // 4. 투입된 금액 저장
    while (buf_in_coin.size())
    {
        // 입력된 coin 1개 pop
        Coin coin = buf_in_coin.pop();
        
        // coin 종류 별로 저장
        switch (coin.amount)
        {
            case 10:    slot_coin[0].push(coin); break;
            case 50:    slot_coin[1].push(coin); break;
            case 100:   slot_coin[2].push(coin); break;
            case 500:   slot_coin[3].push(coin); break;
            case 1000:  slot_coin[4].push(coin); break;
        }
    }
    
    // 5. 구매 관련 변수 수정
    selected_drink = -1;
    inserted_coins = 0;
    inserted_paper_count = 0;
    
    // 6. 재고가 변경됨에 따라 데이터 저장
    save();
    
    // 7. 상태 메시지 초기 설정
    status_message = "구매하실 음료수를 선택하세요.";
}
void    DataManagement::return_coin()
{
    // 구매 관련 변수 초기화
    inserted_coins = 0;
    inserted_paper_count = 0;
    
    // 거스름돈 반환
    while (buf_in_coin.size())
        buf_out_coin.push(buf_in_coin.pop());   // coin 입력 버퍼 -> coin 출력 버퍼
    
    // 상태 관련 메시지 설정
    if (selected_drink == -1)   status_message = "구매하실 음료수를 선택하세요.";
    else                        status_message = "금액을 투입하여 주세요.";
}
void    DataManagement::take_drinks()
{
    // 동전 반환 버퍼 비우기
    while (buf_out_drink.size()) buf_out_drink.pop();
}
void    DataManagement::take_coins()
{
    // 거스름돈 반환 버퍼 비우기
    while (buf_out_coin.size()) buf_out_coin.pop();
}


// 구매 관련 : private
uint64_t    DataManagement::calculate_change(uint64_t amount)
{
    // 잔돈 플래그
    uint64_t changes = 0x0;
    
    // 거스름할 동전 종류
    uint64_t money[5] = {10, 50, 100, 500, 1000};
    
    // 거스름할 동전 갯수
    uint64_t count[5] = {0};
    
    // 거스름돈 계산
    for (int i=4; i>=0; i--)
    {
        // 거슬러줄 동전 갯수 구하기
        count[i] = amount / money[i];
        
        // 남은 동전 수에 맞추기
        while (count[i] > slot_coin[i].size()) count[i]--;
        
        // 남은 가격 계산
        amount = amount - (money[i] * count[i]);
    }
    
    // 거스름돈 정보 플래그에 저장
    for (int i=0; i<5; i++)
    {
        // 동전 갯수 플래그에 저장
        changes = changes | count[i];
        changes = changes << 8;
    }
    changes = changes >> 8;
    
    // 거스름돈 정보 플래그 반환
    if (amount > 0) return -1;      // 거스름이 완벽히 되지 않았을때
    else            return changes; // 거스름이 다 되었을때
}
void        DataManagement::return_change(uint64_t changes)
{
    // 잔돈 갯수 추출
    int count[5] = {
        (int)((changes >> 32) & 0xffff),
        (int)((changes >> 24) & 0xff),
        (int)((changes >> 16) & 0xff),
        (int)((changes >> 8)  & 0xff),
        (int)((changes >> 0)  & 0xff),
    };
    
    // 잔돈 반환 하기 (나중에 멀티스레드로 변경하기)
    for (int i=0; i<5; i++)
        for (int n=0; n<count[i]; n++)
            buf_out_coin.push(slot_coin[i].pop());
}

// 자판기 상태 출력
void DataManagement::print_status()
{
    using namespace std;
    
    cout << "|==== 자판기 상태 출력." << endl;
    cout << "|  ID : " << ID << endl;
    cout << "|  PW : " << PW << endl;
    cout << "|" << endl;
    
    cout << "|  동전 입구 : ";
    for (int i=0; i<buf_in_coin.size(); i++)
    {
        cout << "(" << buf_in_coin[i].amount << "-" << buf_in_coin[i].banknote << ") ";
    }
    cout << endl;
    
    cout << "|  음료 출구 : ";
    for (int i=0; i<buf_out_drink.size(); i++)
    {
        cout << "(" << buf_out_drink[i].name << "-" << buf_out_drink[i].price << ") ";
    }
    cout << endl;
    
    cout << "|  동전 출구 : ";
    for (int i=0; i<buf_out_coin.size(); i++)
    {
        cout << "(" << buf_out_coin[i].amount << "-" << buf_out_coin[i].banknote << ") ";
    }
    cout << endl;
    cout << "|" << endl;
    
    cout << "|  선택된 음료 : " << selected_drink << endl;
    cout << "|  투입된 금액 : " << inserted_coins << endl;
    cout << "|  투입된 지폐 갯수 : " << inserted_paper_count << endl;
    cout << "|" << endl;
    
    for (int j=0; j<6; j++)
    {
        cout << "|  SLOT_DRINK_" << j << " : ";
        for (int i=0; i<slot_drink[j].size(); i++)
        {
            cout << "(" << slot_drink[j][i].name << "-" << slot_drink[j][i].price << ") ";
        }
        cout << endl;
    }
    cout << "|" << endl;
    
    for (int j=0; j<5; j++)
    {
        cout << "|  SLOT_COIN_" << j << " : ";
        for (int i=0; i<slot_coin[j].size(); i++)
        {
            cout << "(" << slot_coin[j][i].amount << "-" << slot_coin[j][i].banknote << ") ";
        }
        cout << endl;
    }
    
    cout << "|===" << endl;
}



// 자판기 정보 불러오기 : MainPage
std::string DataManagement::get_status_message()
{
    return status_message;
}
std::string DataManagement::get_drink_name(int slot_number)
{
    if (slot_drink[slot_number].size() > 0) return slot_drink[slot_number][0].name;
    else                                    return "재고 소진";
}
std::string DataManagement::get_drink_price(int slot_number)
{
    if (slot_drink[slot_number].size() > 0) return std::to_string(slot_drink[slot_number][0].price);
    else                                    return "----";
}
std::string DataManagement::get_selected_drink()
{
    if (selected_drink == -1)   return "";
    else                        return slot_drink[selected_drink][0].name;
}
std::string DataManagement::get_inserted_coins()
{
    return std::to_string(inserted_coins);
}
std::string DataManagement::get_out_drink()
{
    // 음료수 버퍼 비어있을 경우
    if (buf_out_drink.empty()) return "음료수 출구";
    
    // 음료수 버퍼 내용 출력
    std::string s = "";
    for (int i=0; i<buf_out_drink.size(); i++) s += buf_out_drink[i].name + "\n";
    if (!s.empty()) s.erase(s.end()-1); // 마지막 문자 "_" 제거
    return s;
}
std::string DataManagement::get_out_coin()
{
    // 거스름돈 버퍼 비어있을 경우
    if (buf_out_coin.empty()) return "거스름돈 출구";
    
    // 거스름돈 버퍼 내용 출력
    int cs[6] = {0};
    for (int i=0; i<buf_out_coin.size(); i++)
    {
        switch (buf_out_coin[i].amount)
        {
            case 10:    cs[0]++; break;
            case 50:    cs[1]++; break;
            case 100:   cs[2]++; break;
            case 500:   cs[3]++; break;
            case 1000:  cs[4]++; break;
            default:    cs[5]++; break;
        }
    }
    std::string s = "";
    for (int i=0; i<6; i++) if (cs[i])
    {
        switch (i)
        {
            case 0: s += "10원 x " + std::to_string(cs[i]) + "\n"; break;
            case 1: s += "50원 x " + std::to_string(cs[i]) + "\n"; break;
            case 2: s += "100원 x " + std::to_string(cs[i]) + "\n"; break;
            case 3: s += "500원 x " + std::to_string(cs[i]) + "\n"; break;
            case 4: s += "1000원 x " + std::to_string(cs[i]) + "\n"; break;
            case 5: s += "이상한 동전 x " + std::to_string(cs[i]) + "\n"; break;
        }
    }
    if (!s.empty()) s.erase(s.end()-1); // 마지막 문자 "_" 제거
    return s;
}

// 자판기 정보 불러오기 : LoginPage
std::string DataManagement::get_id()
{
    return ID;
}
std::string DataManagement::get_pw()
{
    return PW;
}

// 자판기 정보 불러오기 : AdministratorPage
std::string DataManagement::get_drink_num(int slot_number)
{
    return std::to_string(slot_drink[slot_number].size());
}
std::string DataManagement::get_coin_num(int slot_number)
{
    return std::to_string(slot_coin[slot_number].size());
}
std::string DataManagement::get_balance()
{
    // 전체 잔액 계산
    int balance = 0;
    balance += 10 * slot_coin[0].size();
    balance += 50 * slot_coin[1].size();
    balance += 100 * slot_coin[2].size();
    balance += 500 * slot_coin[3].size();
    balance += 1000 * slot_coin[4].size();
    
    // 계산된 전체 잔액 반환
    return std::to_string(balance);
}
std::string DataManagement::get_collectable_changes()
{
    // 수금 가능 금액 계산
    int sum = 0;
    if (slot_coin[0].size() > 10) sum += 10   * (slot_coin[0].size() - 10);
    if (slot_coin[1].size() > 10) sum += 50   * (slot_coin[1].size() - 10);
    if (slot_coin[2].size() > 10) sum += 100  * (slot_coin[2].size() - 10);
    if (slot_coin[3].size() > 10) sum += 500  * (slot_coin[3].size() - 10);
    if (slot_coin[4].size() > 10) sum += 1000 * (slot_coin[4].size() - 10);
    
    // 계산된 수금 가능 금액 반환
    return std::to_string(sum);
}
std::string DataManagement::get_sales_day()
{
    return "-- 일별 매출 계산입니다.";
}
std::string DataManagement::get_sales_month()
{
    return "-- 월별 매추 계산입니다.";
}


}
