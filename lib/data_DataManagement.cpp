#include <data_DataManagement.hpp>

namespace data
{


// 생성자
DataManagement::DataManagement()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 자판기 데이터 경로
    dir = path("");
    ID = "";
    PW = "";
    selected_drink = -1;
    inserted_coins = -1;
    inserted_paper_count = -1;
    
    // 상태 관련 메시지 설정
    status_message = "out of service.";
}
DataManagement::DataManagement(std::string backup_dir)
{
    using namespace std;
    using namespace std::filesystem;
    
    // 자판기 데이터 경로 저장
    dir = path(backup_dir);
    
    // 자판기 데이터 불러오기
    if (exists(dir) && is_regular_file(dir))
    {
        // 자판기 데이터 존재
        cout << "|  data::DataManagement : 자판기 데이터를 불러옵니다." << endl;
        
        // 데이터 불러오기
        load();
    }
    else
    {
        // 자판기 데이터가 없다면
        cout << "|  data::DataManagement : 자판기를 새로 생성합니다." << endl;
        
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
    
    // 구매 관련 변수 초기화
    selected_drink = -1;
    inserted_coins = 0;
    inserted_paper_count = 0;
    
    // 상태 관련 메시지 설정
    status_message = "구매하실 음료수를 선택하세요.";
    
    cout << "|  data::DataManagement : 완료." << endl;
}

// 데이터 관련
void DataManagement::load()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 변수 생성
    string buf;
    
    // 파일 열기
    ifstream fin(dir.string());
    if (!fin)
    {
        throw std::runtime_error("data::DataManagement::load() : 자판기 데이터 파일을 열 수 없습니다.");
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
void DataManagement::save()
{
    using namespace std;
    using namespace std::filesystem;
    
    // 기존에 존재하던 백업 파일 삭제
    if (exists(dir) && is_regular_file(dir)) remove(dir);
    
    // 파일 생성
    ofstream fout(dir.string());
    
    // 사용자 계정 정보 저장
    fout << "ID=" << ID << endl;
    fout << "PW=" << PW << endl << endl;
    
    // 음료 정보 저장
    for (int i=0; i<6; i++)
        for (int j=0; j<slot_drink[i].size(); j++)
        {
            fout << "drink-" << i << "-" << j;
            fout << "=";
            fout << slot_drink[i][j].name << "-" << slot_drink[i][j].price << endl;
        }
    fout << endl;
    
    // 잔돈 정보 저장
    for (int i=0; i<5; i++)
        for (int j=0; j<slot_coin[i].size(); j++)
        {
            fout << "coin-" << i << "-" << j;
            fout << "=";
            fout << slot_coin[i][j].amount << "-" << slot_coin[i][j].banknote << endl;
        }
    fout << endl;
    
    // 파일 스트림 닫기
    fout.close();
}

// 재고 관리
void DataManagement::push_drink(int slot_number, Drink& drink)
{
    slot_drink[slot_number].push_back(drink);
}
void DataManagement::push_coin(int slot_number, Coin& coin)
{
    slot_coin[slot_number].push(coin);
}
void DataManagement::pop_drink(int slot_number)
{
    if (slot_drink[slot_number].size() > 0)
    {
        buf_out_drink.push(slot_drink[slot_number].pop_front());
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
        buf_out_coin.push(slot_coin[slot_number].pop());
    }
    else
    {
        std::cout << "|  data::DataManagement : 더 이상 빼낼 동전이 없습니다." << std::endl;
    }
}

// 구매 관련
void    DataManagement::select_drink(int slot_number)
{
    if (slot_drink[slot_number].size()==0)  selected_drink = -1;            // 재고 소진인 음료를 선택하는 경우
    else if (selected_drink == -1)          selected_drink = slot_number;   // 처음 선택하는 경우
    else if (selected_drink == slot_number) selected_drink = -1;            // 선택 했던 음료수를 취소하는 경우
    else                                    selected_drink = slot_number;   // 이미 다른 음료수가 선택되어 있는경우
}
void    DataManagement::insert_coin(const Coin& coin)
{
    // 전체 7,000원 상한선
    if ((inserted_coins + coin.amount) > 7000)
    {
        std::cout << "|  data::DataManagement : 입력 받는 금액은 7,000원을 넘을 수 없습니다." << std::endl;
        buf_out_coin.push(coin);
        return;
    }
    
    // 지폐는 5장 상한선
    if (coin.amount == 1000 && inserted_paper_count >= 5)
    {
        std::cout << "|  data::DataManagement : 입력 받는 지폐의 갯수는 5장을 넘을 수 없습니다." << std::endl;
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
            buf_in_coin.push(coin);
            break;
            
        default:
            std::cout << "|  data::DataManagement : 잘못된 금액 입력입니다." << std::endl;
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
        return;
    }
    
    // 0. 음료수 남아 있는지 확인
    if (slot_drink[selected_drink].size() < 1)
    {
        std::cout << "|  data::DataManagement : 구입 하시려는 음료수의 재고가 없습니다." << std::endl;
        return;
    }
    
    // 0. 입력된 금액 충분한지 확인
    if (inserted_coins < slot_drink[selected_drink][0].price)
    {
        std::cout << "|  data::DataManagement : 입력하신 금액이 부족합니다." << std::endl;
        return;
    }
    
    // 1. 거스름돈 계산
    uint64_t changes = calculate_change(inserted_coins - slot_drink[selected_drink][0].price);
    
    // 0. 거스름돈 반환 가능한지 확인
    if (changes == -1)
    {
        std::cout << "|  data::DataManagement : 거슬러드릴 돈이 부족합니다. 금액을 맞게 투입하여 주세요." << std::endl;
        return_coin();
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
    //save();
}
void    DataManagement::return_coin()
{
    // 구매 관련 변수 초기화
    inserted_coins = 0;
    inserted_paper_count = 0;
    
    // 거스름돈 반환
    while (buf_in_coin.size())
        buf_out_coin.push(buf_in_coin.pop());   // coin 입력 버퍼 -> coin 출력 버퍼
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



// 자판기 정보 불러오기
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

}
