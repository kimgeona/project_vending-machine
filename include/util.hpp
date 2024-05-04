#pragma once
#ifndef util_hpp
#define util_hpp

// c++17
#include <string>
#include <vector>

namespace util
{


// 파이썬 split
std::vector<std::string>    my_split(std::string s1, std::string s2);


// 파이썬 strip
std::string                 my_strip(std::string s1);


}

#endif /* util_hpp */
