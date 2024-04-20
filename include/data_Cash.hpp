#pragma once
#ifndef data_Cash_hpp
#define data_Cash_hpp

namespace data
{


class Cash
{
public:
    int amount;     // 금액
    int banknote;   // 발행년도
    
    Cash(int amount=-1, int banknote=-1)
    {
        this->amount = amount;
        this->banknote = banknote;
    }
}


}

#endif /* data_Cash_hpp */
