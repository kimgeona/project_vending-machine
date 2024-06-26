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
public:
    // 데이터 관리자 타입
    std::string name;   // 이름
    std::string state;  // 상태 : "on", "off"
    
private:
    // 자판기 데이터 경로
    std::filesystem::path   dir_data;       // 데이터 저장 주소
    std::filesystem::path   dir_log;        // 로그 기록 저장 주소
    
    // 사용자 계정
    std::string             ID;             // 계정 ID
    std::string             PW;             // 계정 PW
    
    // 재고
    algo::LinkedList<Drink> slot_drink[6];  // 자판기 음료
    algo::Stack<Coin>       slot_coin[5];   // 자판기 거스름돈
    
    // 버퍼
    algo::Queue<Drink>      buf_out_drink;  // 음료 출구
    algo::Queue<Coin>       buf_out_coin;   // 거스름돈 출구
    algo::Queue<Coin>       buf_in_coin;    // 동전 입구
    
    // 구매 관련 변수
    int selected_drink;         // 선택된 음료 번호
    int inserted_coins;         // 투입된 금액
    int inserted_paper_count;   // 투입된 지폐 갯수
    
    // 자판기 상태 관련 변수
    std::string status_message; // 자판기 상태 메시지

public:
    // 생성자
    DataManagement();
    DataManagement(std::string);
    
    // 데이터 관련
    void load();    // 데이터 불러오기
    void reload();  // 데이터 다시 불러오기
    void save();    // 데이터 저장
    
    // 정보 얻기
    std::string get_dir_data();
    std::string get_dir_log();
    
    // 정보 수정
    void set_id(std::string id);    // 아이디 설정
    void set_pw(std::string pw);    // 비밀번호 설정
    void set_drink_name(int slot_number, std::string name);     // 음료수 이름 변경
    void set_drink_price(int slot_number, int price);           // 음료수 가격 변경
    
    // 재고 관리
    void push_drink(int slot_number, Drink drink);  // 음료 채우기
    void push_coin(int slot_number, Coin coin);     // 동전 채우기
    void pop_drink(int slot_number);                // 음료 빼기
    void pop_coin(int slot_number);                 // 동전 빼기
    void collect_changes();                         // 잔돈 수금
    
    // 구매 관련
    void select_drink(int slot_number);     // 1. 음료 선택 (한번 더 누르면 취소)
    void insert_coin(const Coin& coin);     // 2. 금액 투입
    void purchase();                        // 3. 구입 & 거스름돈 반환
    void return_coin();                     // *. 투입된 금액 반환
    void take_drinks();                     // 반환된 음료 가져가기
    void take_coins();                      // 반환된 거스름돈 가져가기
    
private:
    // 구매 관련 : private
    uint64_t    calculate_change(uint64_t amount);  // *. 거스름돈 계산
    void        return_change(uint64_t changes);    // *. 거스름돈 반환
    
public:
    // 자판기 상태 출력
    void print_status();
    
    // 데이터 수정
    std::string modify_id(std::string);     // 관리자 이름 변경
    std::string modify_pw(std::string);     // 관리자 비밀번호 변경
    std::string modify_drink_name(int slot_number, std::string name);   // 음료 이름 변경
    std::string modify_drink_price(int slot_number, int price);         // 음료 가격 변경
    
    // 자판기 정보 불러오기 : MainPage
    std::string get_status_message();               // 자판기 상태 메시지 가져오기
    std::string get_drink_name(int slot_number);    // 음료 이름 가져오기
    std::string get_drink_price(int slot_number);   // 음료 가격 가져오기
    std::string get_selected_drink();               // 선택된 음료 이름 가져오기
    std::string get_inserted_coins();               // 투입된 금액 가져오기
    std::string get_out_drink();                    // 음료수 출구에서 가져오기
    std::string get_out_coin();                     // 거스름돈 출구에서 가져오기
    
    // 자판기 정보 불러오기 : LoginPage
    std::string get_id();                           // 사용자 id 가져오기
    std::string get_pw();                           // 사용자 pw 가져오기
    
    // 자판기 정보 불러오기 : AdministratorPage
    std::string get_drink_num(int slot_number);     // 보관중인 음료 갯수 구하기
    std::string get_coin_num(int slot_number);      // 보관중인 잔돈 갯수 구하기
    std::string get_balance();                      // 전체 잔액 구하기
    std::string get_collectable_changes();          // 수금 가능한 잔돈 구하기
    std::string get_sales_day();                    // 일별 매출 계산
    std::string get_sales_month();                  // 월별 매출 계산
};


}

#endif /* data_DataManagement_hpp */
