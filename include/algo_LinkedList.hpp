#pragma once
#ifndef algo_LinkedList_hpp
#define algo_LinkedList_hpp

// c++17
#include <initializer_list>
#include <iostream>

namespace algo
{


template <typename T>
class Node
{
public:
    T data;
    Node* front;
    Node* back;
    
    Node(const T& data, Node* front, Node* back) : data(data), front(front), back(back) {}
    
    // 정렬을 위한 비교(<, >, ==) 연산자 작성을 해야함
};


template <class T>
class LinkedList
{
private:
    // 자료구조
    Node<T>* data;
    
public:
    // 생성자
    LinkedList();
    LinkedList(const LinkedList& other);                        // 복사 생성자
    LinkedList(const std::initializer_list<T>& element_list);   // 초기화 리스트 생성자
    
    // 소멸자
    virtual ~LinkedList();
    
    // 함수
    void    push(const T& element, int n);  // 요소 삽입
    void    push_front(const T& element);   // 요소 맨 앞 삽입
    void    push_back(const T& element);    // 요소 맨 뒤 삽입
    T       pop(int n);                     // 요소 추출
    T       pop_front(void);                // 요소 맨 앞 추출
    T       pop_back(void);                 // 요소 맨 뒤 추출
    int     size(void);                     // 요소 전체 갯수
    bool    empty(void);                    // 연결 리스트 비어있는지 확인
    void    clear(void);                    // 연결 리스트 초기화
    
    // 연산자 함수
    LinkedList&  operator=(const LinkedList& other);                        // 복사 연산자
    LinkedList&  operator=(const std::initializer_list<T>& element_list);   // 초기화 리스트 연산자
    
    void print_element()
    {
        using namespace std;
        
        cout << "==>";
        
        Node<T>* pre = data;
        
        while (pre)
        {
            cout << " " << pre->data;
            pre = pre->back;
        }
        cout << endl;
    }
};


// 생성자
template <class T> LinkedList<T>::LinkedList()
{
    // 기본 포인터 초기화
    data = nullptr;
}
template <class T> LinkedList<T>::LinkedList(const LinkedList& other)
{
    // 기본 포인터 초기화
    data = nullptr;
    
    // 시작 노드
    Node<T>* pre = other.data;
    
    // 데이터 복사
    while (pre)
    {
        push_back(pre->data);
        pre = pre->back;
    }
}
template <class T> LinkedList<T>::LinkedList(const std::initializer_list<T>& element_list)
{
    // {} 내용물이 없는 경우
    if (element_list.size() < 1)
    {
        // 기본 포인터 초기화
        data = nullptr;
    }
    
    // {} 내용물이 있는 경우
    else
    {
        // 기본 포인터 초기화
        data = nullptr;
        
        // 데이터 복사
        for (auto& element : element_list) push_back(element);
    }
}

// 소멸자
template <class T> LinkedList<T>::~LinkedList()
{
    clear();
}

// 함수
template <class T> void    LinkedList<T>::push(const T& element, int n)
{
    // 삽입 위치 확인
    if (n > size() && n < 0)
    {
        throw std::out_of_range("LinkedList<>::push(): out of LinkedList index");
    }
    
    // 변수
    int         count       = n;        // 노드 카운트 갯수
    Node<T>*    pre         = data;     // 현재 노드
    Node<T>*    pre_front   = nullptr;  // 앞 노드
    Node<T>*    node        = nullptr;  // 삽입할 노드
    
    // 노드 n개 만큼 건너뛰기
    while(count > 0)
    {
        // 앞 노드
        pre_front = pre;
        
        // 현재 노드
        pre = pre->back;
        
        // count 감소
        count--;
    }
    
    // 노드 생성
    node = new Node(element, pre_front, pre);
    
    // 기존 노드 수정 : front
    if (pre_front != nullptr)
    {
        pre_front->back = node;
    }
    else data = node;
    
    // 기존 노드 수정 : pre
    if (pre != nullptr)
    {
        pre->front = node;
    }
}
template <class T> void    LinkedList<T>::push_front(const T& element)
{
    push(element, 0);
}
template <class T> void    LinkedList<T>::push_back(const T& element)
{
    push(element, size());
}
template <class T> T       LinkedList<T>::pop(int n)
{
    // 추출 위치 확인
    if (n >= size() && n < 0)
    {
        throw std::out_of_range("LinkedList<>::pop(): out of LinkedList index");
    }
    
    // 변수
    int         count       = n;            // 노드 카운트 갯수
    Node<T>*    pre         = data;         // 현재 노드
    Node<T>*    pre_front   = nullptr;      // 앞 노드
    Node<T>*    pre_back    = data->back;   // 뒤 노드
    
    // 노드 n개 만큼 건너뛰기
    while(count > 0)
    {
        // 앞 노드
        pre_front = pre;
        
        // 현재 노드
        pre = pre->back;
        
        // 뒤 노드
        pre_back = pre->back;
        
        // count 감소
        count--;
    }
    
    // 기존 노드 수정 : front
    if (pre_front != nullptr)
    {
        pre_front->back = pre_back;
    }
    else data = pre_back;
    
    // 기존 노드 수정 : back
    if (pre_back != nullptr)
    {
        pre_back->front = pre_front;
    }
    
    // 데이터 추출
    T tmp = pre->data;
    
    // 기존 노드 해제 : pre
    if (pre != nullptr)
    {
        delete pre;
    }
    
    return tmp;
}
template <class T> T       LinkedList<T>::pop_front(void)
{
    return pop(0);
}
template <class T> T       LinkedList<T>::pop_back(void)
{
    return pop(size()-1);
}
template <class T> int     LinkedList<T>::size(void)
{
    // 노드 갯수
    int count = 0;
    
    // 노드 시작 포인터
    Node<T>* pre = data;
    
    // 노드 갯수 세기
    while (pre)
    {
        count++;
        pre = pre->back;
    }
    
    return count;
}
template <class T> bool    LinkedList<T>::empty(void)
{
    if (data == NULL)   return true;
    else                return false;
}
template <class T> void    LinkedList<T>::clear(void)
{
    if (data == nullptr) return;
    
    // 노드 시작지점
    Node<T>* pre = data;
    
    // 맨 끝 노드로 이동
    while (pre->back) pre = pre->back;
    
    // 노드 메모리 반환
    while (pre)
    {
        Node<T>* tmp = pre->front;
        delete pre;
        pre = tmp;
    }
    
    // data 초기화
    data = nullptr;
}

// 연산자 함수
template <class T> LinkedList<T>&  LinkedList<T>::operator=(const LinkedList& other)
{
    // 기존 데이터 초기화
    clear();
    
    // 기본 포인터 초기화
    data = nullptr;
    
    // 시작 노드
    Node<T>* pre = other.data;
    
    // 데이터 복사
    while (pre)
    {
        push_back(pre->data);
        pre = pre->back;
    }
    
    return *this;
}
template <class T> LinkedList<T>&  LinkedList<T>::operator=(const std::initializer_list<T>& element_list)
{
    // 기존 데이터 초기화
    clear();
    
    // {} 내용물이 없는 경우
    if (element_list.size() < 1)
    {
        // 기본 포인터 초기화
        data = nullptr;
    }
    
    // {} 내용물이 있는 경우
    else
    {
        // 기본 포인터 초기화
        data = nullptr;
        
        // 데이터 복사
        for (auto& element : element_list) push_back(element);
    }
    
    return *this;
}


}

#endif /* algo_LinkedList_hpp */
