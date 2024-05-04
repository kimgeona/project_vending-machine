#pragma once
#ifndef data_Drink_hpp
#define data_Drink_hpp

// c++17
#include <string>

namespace data
{


class Drink
{
public:
    std::string name;   // 음료 이름
    int         price;  // 음료 가격
    
    Drink()
    {
        this->name = "";
        this->price = -1;
    }
    Drink(std::string name, int price)
    {
        this->name = name;
        this->price = price;
    }
    
    // 정렬을 위한 비교(<, >, ==) 연산자 작성을 해야함
};


}

#endif /* data_Drink_hpp */
