#pragma once
#ifndef algo_Stack_hpp
#define algo_Stack_hpp

// c++17
#include <initializer_list>

namespace algo
{


template <class T>
class Stack
{
private:
    // 자료구조
    T* data;
    int pre, total_capacity;
    
public:
    // 생성자
    Stack();
    Stack(const Stack& other);                              // 복사 생성자
    Stack(const std::initializer_list<T>& element_list);    // 복사 생성자
    
    // 소멸자
    virtual ~Stack();
    
    // 함수
    void    push(const T& element);     // 요소 삽입
    T       pop(void);                  // 요소 추출
    int     size(void);                 // 요소 전체 갯수
    int     capacity(void);             // 스택 용량
    bool    empty(void);                // 스택 비어있는지 확인
    bool    full(void);                 // 스택 찼는지 확인
    void    clear(void);                // 스택 초기화
    
    // 연산자 함수
    Stack&  operator=(const Stack& other);                             // 복사 연산자
    Stack&  operator=(const std::initializer_list<T>& element_list);   // 복사 연산자
};


// 생성자
template <class T> Stack<T>::Stack()
{
    pre = -1;
    total_capacity = 2;
    data = new T[total_capacity];
}
template <class T> Stack<T>::Stack(const Stack& other)
{
    // 스택 정보 복사
    pre = other.pre;
    total_capacity = other.total_capacity;
    
    // 데이터 공간 확보
    data = new T[total_capacity];
    
    // 데이터 복사
    for (int i=0; i<total_capacity; i++) data[i] = other.data[i];
}
template <class T> Stack<T>::Stack(const std::initializer_list<T>& element_list)
{
    // {} 인 경우
    if (element_list.size() < 1)
    {
        // 기본 생성자와 동일
        pre = -1;
        total_capacity = 2;
        data = new T[total_capacity];
    }
    
    // {...} 인 경우
    else
    {
        // element_list 크기 만큼 스택 생성
        pre = -1;
        total_capacity = (int)element_list.size();
        data = new T[total_capacity];
        
        // 데이터 복사
        for (auto& element : element_list) data[++pre] = element;
    }
}

// 소멸자
template <class T> Stack<T>::~Stack()
{
    delete [] data;
}

// 함수
template <class T> void    Stack<T>::push(const T& element)
{
    // 가득찼는지 확인
    if (full())
    {
        // 새로운 저장공간 할당
        T* tmp = new T[total_capacity*2];
        
        // 기존 데이터 복사
        for (int i=0; i<total_capacity; i++) tmp[i] = data[i];
        
        // 기존 공간 반환
        delete [] data;
        
        // 데이터 업데이트
        total_capacity = total_capacity * 2;
        data = tmp;
    }
    
    // 맨 뒤에 요소 저장
    data[++pre] = element;
}
template <class T> T       Stack<T>::pop(void)
{
    // 비어있는지 확인
    if (empty())
    {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    
    // 맨 뒤에 요소 하나 반환
    return data[pre--];
}
template <class T> int     Stack<T>::size(void)
{
    if (pre<0)  return 0;
    else        return pre + 1;
}
template <class T> int     Stack<T>::capacity(void)
{
    return total_capacity;
}
template <class T> bool    Stack<T>::empty(void)
{
    if (pre<0)  return true;
    else        return false;
}
template <class T> bool    Stack<T>::full(void)
{
    if (size() == capacity())   return true;
    else                        return false;
}
template <class T> void    Stack<T>::clear(void)
{
    // 기본 생성자 값으로 초기화
    pre = -1;
    total_capacity = 2;
    delete [] data;
    data = new T[total_capacity];
}

// 연산자 함수
template <class T> Stack<T>&  Stack<T>::operator=(const Stack& other)
{
    // 스택 정보 복사
    pre = other.pre;
    total_capacity = other.total_capacity;
    
    // 데이터 공간 확보
    delete [] data;
    data = new T[total_capacity];
    
    // 데이터 복사
    for (int i=0; i<total_capacity; i++) data[i] = other.data[i];
    
    return *this;
}
template <class T> Stack<T>&  Stack<T>::operator=(const std::initializer_list<T>& element_list)
{
    // {} 내용물이 없는 경우
    if (element_list.size() < 1)
    {
        // 기본 생성자와 동일
        pre = -1;
        total_capacity = 2;
        delete [] data;
        data = new T[total_capacity];
    }
    
    // {} 내용물이 있는 경우
    else
    {
        // element_list 크기 만큼 스택 생성
        pre = -1;
        total_capacity = (int)element_list.size();
        delete [] data;
        data = new T[total_capacity];
        
        // 데이터 복사
        for (auto& element : element_list) data[++pre] = element;
    }
    
    return *this;
}


}

#endif /* algo_Stack_hpp */
