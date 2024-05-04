#pragma once
#ifndef data_DataManagement_hpp
#define data_DataManagement_hpp

// c++17
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

// 나의 라이브러리
#include <data_Drink.hpp>
#include <data_Coin.hpp>
#include <algo.hpp>
#include <util.hpp>

namespace data
{


class DataManagement
{
private:
    // 자판기 데이터 경로
    std::filesystem::path dir;
    
    // 사용자 계정
    std::string             ID;             // 계정 ID
    std::string             PW;             // 계정 PW
    
    // 재고
    algo::LinkedList<Drink> drinks[6];      // 자판기 음료
    algo::Stack<Coin>       coins[5];       // 자판기 거스름돈
    
    // 버퍼
    algo::Queue<Drink>      vm_out_drinks;  // 음료 출구
    algo::Queue<Coin>       vm_out_coins;   // 거스름돈 출구
    algo::Queue<Coin>       vm_in_coins;    // 동전 입구
    
    // 데이터 불러오기 및 저장
    void load();
    void save();
    
public:
    // 생성자
    DataManagement();
    DataManagement(std::string);
    
    // MainPage
    void select_drink(int n);               // 음료 선택
    void select_cash(int n);                // 금액 입력
    void take_drink(void);                  // 음료 가져가기
    void take_change(void);                 // 거스름돈 가져가기
    void purchase(void);                    // 구매
    void open_administrator_page(void);     // 관리자 메뉴 열기
    
    // LoginPage
    bool login(std::string id, std::string pw); // 로그인
    
    // AdministratorPage
    std::string modify_id(std::string);                     // 사용자 이름 변경
    std::string modify_pw(std::string);                     // 비밀번호 변경
    std::string modify_drink_name(int n, std::string);      // 음료 이름 변경
    std::string modify_drink_price(int n, std::string);     // 음료 가격 수정
    std::string modify_drink_stock(int n, std::string);     // 음료 갯수 변경
    std::string modify_cash_changes(int n, std::string);    // 잔돈 갯수 변경
    void        collect_changes(void);                      // 잔돈 수금
};


}

#endif /* data_DataManagement_hpp */
