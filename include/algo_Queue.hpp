#pragma once
#ifndef algo_Queue_hpp
#define algo_Queue_hpp

// c++17
#include <initializer_list>

namespace algo
{


template <class T>
class Queue
{
private:
    // 자료구조
    T* data;
    int pre_out, pre_in, total_capacity;
    
public:
    // 생성자
    Queue();
    Queue(const Queue& other);                              // 복사 생성자
    Queue(const std::initializer_list<T>& element_list);    // 복사 생성자
    
    // 소멸자
    virtual ~Queue();
    
    // 함수
    void    push(const T& element);     // 요소 삽입
    T       pop(void);                  // 요소 추출
    int     size(void);                 // 요소 전체 갯수
    int     capacity(void);             // 큐 용량
    bool    empty(void);                // 큐 비어있는지 확인
    bool    full(void);                 // 큐 찼는지 확인
    void    clear(void);                // 큐 초기화
    int     crop_to_range(int n);       // 큐 범위에 맞게 자르기
    
    // 연산자 함수
    Queue&  operator=(const Queue& other);                             // 복사 연산자
    Queue&  operator=(const std::initializer_list<T>& element_list);   // 복사 연산자
};


// 생성자
template <class T> Queue<T>::Queue()
{
    pre_in = 0;
    pre_out = -1;
    total_capacity = 2;
    data = new T[total_capacity];
}
template <class T> Queue<T>::Queue(const Queue& other)
{
    // 큐 정보 복사
    pre_in = other.pre_in;
    pre_out = other.pre_out;
    total_capacity = other.total_capacity;
    
    // 데이터 공간 확보
    data = new T[total_capacity];
    
    // 데이터 복사
    for (int i=0; i<total_capacity; i++) data[i] = other.data[i];
}
template <class T> Queue<T>::Queue(const std::initializer_list<T>& element_list)
{
    // {} 내용물이 없는 경우
    if (element_list.size() < 1)
    {
        // 기본 생성자와 동일
        pre_in = 0;
        pre_out = -1;
        total_capacity = 2;
        data = new T[total_capacity];
    }
    
    // {} 내용물이 있는 경우
    else
    {
        // element_list 크기 만큼 스택 생성
        pre_in = 0;
        pre_out = 0;
        total_capacity = (int)element_list.size();
        data = new T[total_capacity];
        
        // 데이터 복사
        for (auto& element : element_list) data[pre_in++] = element;
        pre_in = 0;
    }
    
    return *this;
}

// 소멸자
template <class T> Queue<T>::~Queue()
{
    delete [] data;
}

// 함수
template <class T> void    Queue<T>::push(const T& element)
{
    // 가득찼는지 확인
    if (full())
    {
        // 새로운 저장공간 할당
        T* tmp = new T[total_capacity*2];
        
        // 기존 데이터 복사
        for (int i=0; i<capacity(); i++) tmp[i] = data[i];
        
        // 기존 공간 반환
        delete [] data;
        
        // 기존 데이터 위치 이동
        for (int i=pre_in-1; i>=0; i--) tmp[i+total_capacity] = tmp[i];
        
        
        // 데이터 업데이트
        total_capacity = total_capacity * 2;
        pre_in = crop_to_range(pre_in + total_capacity / 2);
        data = tmp;
    }
    
    // 비어있는지 확인
    if (empty())
    {
        // 현재 pre_in 위치로 pre_out 위치시키기
        pre_out = pre_in;
    }
    
    // pre_in 번째 요소에 저장
    data[pre_in] = element;
    
    // pre_in 다음 위치로 이동
    pre_in = crop_to_range(pre_in + 1);
}
template <class T> T       Queue<T>::pop(void)
{
    // 비어있는지 확인
    if (empty())
    {
        throw std::out_of_range("Queue<>::pop(): empty queue");
    }
    
    // pre_out 번째 요소 반환
    T tmp = data[pre_out];
    
    // pre_out 다음 위치로 이동
    pre_out = crop_to_range(pre_out + 1);
    
    // pre_out 위치 확인
    if (pre_out==pre_in) pre_out = -1;
    
    return tmp;
}
template <class T> int     Queue<T>::size(void)
{
    if      (empty())   return 0;
    else if (full())    return capacity();
    else
    {
        int tmp1 = pre_out + capacity();
        int tmp2 = pre_in + capacity();
        return abs(tmp2 - tmp1);
    }
}
template <class T> int     Queue<T>::capacity(void)
{
    return total_capacity;
}
template <class T> bool    Queue<T>::empty(void)
{
    if (pre_out == -1)  return true;
    else                return false;
}
template <class T> bool    Queue<T>::full(void)
{
    if (pre_in == pre_out)  return true;
    else                    return false;
}
template <class T> void    Queue<T>::clear(void)
{
    // 기본 생성자 값으로 초기화
    pre_in = 0;
    pre_out = -1;
    total_capacity = 2;
    delete [] data;
    data = new T[total_capacity];
}
template <class T> int     Queue<T>::crop_to_range(int n)
{
    return (n + total_capacity) % total_capacity;
}

// 연산자 함수
template <class T> Queue<T>&  Queue<T>::operator=(const Queue& other)
{
    // 큐 정보 복사
    pre_in = other.pre_in;
    pre_out = other.pre_out;
    total_capacity = other.total_capacity;
    
    // 데이터 공간 확보
    delete [] data;
    data = new T[total_capacity];
    
    // 데이터 복사
    for (int i=0; i<total_capacity; i++) data[i] = other.data[i];
    
    return *this;
}
template <class T> Queue<T>&  Queue<T>::operator=(const std::initializer_list<T>& element_list)
{
    // {} 내용물이 없는 경우
    if (element_list.size() < 1)
    {
        // 기본 생성자와 동일
        pre_in = 0;
        pre_out = -1;
        total_capacity = 2;
        delete [] data;
        data = new T[total_capacity];
    }
    
    // {} 내용물이 있는 경우
    else
    {
        // element_list 크기 만큼 스택 생성
        pre_in = 0;
        pre_out = 0;
        total_capacity = (int)element_list.size();
        delete [] data;
        data = new T[total_capacity];
        
        // 데이터 복사
        for (auto& element : element_list) data[pre_in++] = element;
        pre_in = 0;
    }
    
    return *this;
}


}

#endif /* algo_Queue_hpp */
