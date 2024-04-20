#pragma once
#ifndef data_DataManagement_hpp
#define data_DataManagement_h

// c++17
#include <string>
#include <chorono>

// 나의 라이브러리
#include <data_Drink.hpp>
#include <data_Cash.hpp>
#include <algo.hpp>

namespace data
{


class DataManagement
{
public:
    // 서버
    // 연결된 서버 정보
    
    // 상태
    // 현재 날짜 변수
    // 현재 시간 변수
    // -> 서버 동기화에 쓰임
    
    // 자판기 계정
    std::string ID;
    std::string PW;
    
    // 자판기 음료 재고
    algo::LinkedList<Drink> drink_1;
    algo::LinkedList<Drink> drink_2;
    algo::LinkedList<Drink> drink_3;
    algo::LinkedList<Drink> drink_4;
    algo::LinkedList<Drink> drink_5;
    algo::LinkedList<Drink> drink_6;
    
    // 자판기 거스름돈 재고
    algo::Stack<Cash> cash_10;
    algo::Stack<Cash> cash_50;
    algo::Stack<Cash> cash_100;
    algo::Stack<Cash> cash_500;
    algo::Stack<Cash> cash_1000;
    
    // 자판기 음료 출구
    algo::Queue<Drink> vm_out_drinks;
    
    // 자판기 거스름돈 출구
    algo::Queue<Coin> vm_out_coins;
}


}

#endif /* data_DataManagement_hpp */
