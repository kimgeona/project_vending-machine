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
    
    Drink(std::string name="", int price=-1)
    {
        this->name = name;
        this->price = price;
    }
}


}

#endif /* data_Drink_hpp */
