#include <data_DataManagement.hpp>

namespace data
{


DataManagement::DataManagement(std::string backup_dir)
{
    using namespace std;
    using namespace std::filesystem;
    
    // 자판기 데이터 경로 저장
    dir = path(backup_dir);
    
    // 경로 확인
    if (exists(dir) && is_regular_file(dir))
    {
        cout << "|  data::DataManagement : 자판기 데이터를 불러옵니다." << endl;
        
        // 데이터 불러오기
        load();
    }
    else {
        cout << "|  data::DataManagement : 자판기를 새로 생성합니다." << endl;
        
        // 사용자 계정 생성
        ID = "admin";
        PW = "admin";
        
        // 음료 생성
        for (int i=0; i<10; i++) drinks[0].push_back(Drink("물", 450));
        for (int i=0; i<10; i++) drinks[1].push_back(Drink("커피", 500));
        for (int i=0; i<10; i++) drinks[2].push_back(Drink("이온음료", 550));
        for (int i=0; i<10; i++) drinks[3].push_back(Drink("고급커피", 700));
        for (int i=0; i<10; i++) drinks[4].push_back(Drink("탄산음료", 750));
        for (int i=0; i<10; i++) drinks[5].push_back(Drink("특화음료", 800));
        
        // 잔돈 생성
        for (int i=0; i<10; i++) coins[0].push(Coin(10, 2024));
        for (int i=0; i<10; i++) coins[1].push(Coin(50, 2024));
        for (int i=0; i<10; i++) coins[2].push(Coin(100, 2024));
        for (int i=0; i<10; i++) coins[3].push(Coin(500, 2024));
        for (int i=0; i<10; i++) coins[4].push(Coin(1000, 2024));
        
        // 데이터 저장
        save();
    }
    cout << "|  data::DataManagement : 완료." << endl;
}

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
            
            drinks[stoi(type[1])].push_back(Drink(data[0], stoi(data[1])));
            
            continue;
        }
        
        // 잔돈 정보 읽기
        if (words[0].find("coin")==0)
        {
            vector<string> type = util::my_split(words[0], "-");
            vector<string> data = util::my_split(words[1], "-");
            
            coins[stoi(type[1])].push(Coin(stoi(data[0]), stoi(data[1])));
            
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
        for (int j=0; j<drinks[i].size(); j++)
            fout << "drink-" << i << "-" << j << "=" << drinks[i][j].name << "-" << drinks[i][j].price << endl;
    fout << endl;
    
    // 잔돈 정보 저장
    for (int i=0; i<5; i++)
        for (int j=0; j<coins[i].size(); j++)
            fout << "coin-" << i << "-" << j << "=" << coins[i][j].amount << "-" << coins[i][j].banknote << endl;
    fout << endl;
    
    // 파일 스트림 닫기
    fout.close();
}


}
