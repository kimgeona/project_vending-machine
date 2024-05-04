#pragma once
#ifndef data_Coin_hpp
#define data_Coin_hpp

namespace data
{


class Coin
{
public:
    int amount;     // 금액
    int banknote;   // 발행년도
    
    Coin()
    {
        this->amount = -1;
        this->banknote = -1;
    }
    Coin(int amount, int banknote)
    {
        this->amount = amount;
        this->banknote = banknote;
    }
    
    // 정렬을 위한 비교(<, >, ==) 연산자 작성을 해야함
};


}

#endif /* data_Coin_hpp */
