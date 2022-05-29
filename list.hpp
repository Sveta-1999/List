#include "list.h"

template<typename T>
stl::List<T>::List(int num)
{
    m_head = new Node();
    Node* tmp = m_head;
    for(int i{}; i < num - 1; ++i) 
    {
        tmp->m_next = new Node();
        tmp->m_next->m_prev = tmp;
        tmp = tmp->m_next;
    }
    m_begin = m_head;
    tmp->m_next = new Node();
    tmp->m_next->m_prev = tmp;
    m_end = tmp->m_next;
}

template<typename T>
stl::List<T>::List(int num, T value) {
    m_head = new Node(value);
    Node* tmp = m_head;
    for(int i = 0; i < num - 1; ++i) {
        tmp->m_next = new Node(value);
        tmp->m_next->m_prev = tmp;
        tmp = tmp->m_next;
    }
    m_begin = m_head;
    tmp->m_next = new Node();
    tmp->m_next->m_prev = tmp;
    m_end = tmp->m_next;
}

template<typename T>
stl::List<T>::List(const List<T>& oth) {
    Node* tmp = oth._head;
    m_head = new Node(tmp->m_value);
    Node* tmp1 = m_head;
    while(tmp->m_next != nullptr) 
    {
        tmp = tmp->m_next;
        tmp1->m_next = new Node(tmp->m_value);
        tmp->m_next->m_prev = tmp;
        tmp1 = tmp1->m_next;
    }
    m_begin = m_head;
    m_end = tmp1;
}

template<typename T>
stl::List<T>::List(List<T>&& other) {
    m_head = other.m_head;
    m_begin = other.m_begin;
    m_end = other.m_end;
    other.m_head = nullptr;
    other.m_begin = nullptr;
    other.m_end = nullptr;
}

template<typename T>
void stl::List<T>::clear() 
{
    if(m_head != nullptr) 
    {
        Node* tmp = m_head->m_next;
        delete m_head;
        m_head = nullptr;
        while(tmp->m_next != nullptr) 
        {
            m_head = tmp;
            tmp = tmp->m_next;
            delete m_head;
            m_head = nullptr;
        }
    }
    m_begin = nullptr;
    m_end = nullptr;
}

template<typename T>
stl::List<T>::~List()
{
    clear();
}

template<typename T>
bool stl::List<T>::empty()
{
    if(m_begin == m_end)
    {
        return true;
    }
    return false;
}

template<typename T>
size_t stl::List<T>::size() 
{
    if(empty()) 
    {
        return 0;
    }
    int size = 0;
    Node* tmp = m_begin;
    while(++tmp != m_end) 
    {
        ++size;
    }
    return size;
}

template<typename T>
bool stl::List<T>::operator==(const List<T>& list1)
{
    auto it = m_begin;
    auto iter = list1.begin();
    while(it != m_end) 
    {
        if(*it != *iter) 
        {
            return false;
        }
        ++it;
        ++iter;
    }
    return true;
}

template<typename T>
bool stl::List<T>::operator!=(const List<T>& list1) 
{
    return !(*this == list1);
}

template<typename T>
bool stl::List<T>::operator<(const List<T>& rhs) 
{
    return std::lexicographical_compare(m_begin, m_end, rhs.m_begin, rhs.m_end);
}

template<typename T>
bool stl::List<T>::operator<=(const List<T>& list1) 
{
    return !(list1 > *this);
}

template<typename T>
bool stl::List<T>::operator>=(const List<T>& list1) 
{
    return !(list1 < *this);
}

template<typename T>
stl::List<T>& stl::List<T>::operator=(const List<T>& rhs)
{
    if(this == &rhs) 
    {
        return *this;
    }
    clear();
    m_head = new Node(rhs.m_head->m_value);
    Node* tmp = rhs.m_head;
    Node* tmp1 = m_head;
    while(tmp->m_next != nullptr) 
    {
        tmp = tmp->m_next;
        tmp1->m_next = new Node(tmp->m_value);
        tmp->_next->_prev = tmp;
        tmp1 = tmp1->m_next;
    }
    m_begin = m_head;
    m_end = tmp1;
    return *this;
}

template<typename T>
stl::List<T>& stl::List<T>::operator=(List<T>&& rhs) 
{
    m_head = rhs.m_head;
    m_begin = rhs.m_begin;
    m_end = rhs.m_end;
    rhs.m_head = nullptr;
    rhs.m_begin = nullptr;
    rhs.m_end = nullptr;
    return *this;
}


template<typename T>
template<typename U>
stl::List<T>& stl::List<T>::operator=(const stl::List<U>& rhs) 
{
    clear();
    auto it = rhs.begin();
    m_head = new Node(*it);
    Node* tmp = m_head;
    while(++it != rhs.end()) 
    {
        tmp->m_next = new Node(*it);
        tmp->m_next->m_prev = tmp;
        tmp = tmp->m_next;
    }
    m_begin = m_head;
    tmp->m_next = new Node();
    tmp->m_next->m_prev = tmp;
    m_end = tmp->m_next;
    return *this;
}

template<typename T>
void stl::List<T>::assign(int n, const T& value) 
{
    clear();
    m_head = new Node(value);
    Node* tmp = m_head;
    for(int i = 0; i < n - 1; ++i) 
    {
        tmp->m_next = new Node(value);
        tmp->m_next->m_prev = tmp;
        tmp = tmp->m_next;
    }
    m_begin = m_head;
    tmp->m_next = new Node();
    tmp->m_next->m_prev = tmp;
    m_end = tmp->m_next;
}

template<typename T>
template<typename Iter>
void stl::List<T>::assign(Iter begin, Iter end) 
{
    clear();
    m_head = new Node(*begin);
    Node* tmp = m_head;
    ++begin;
    while(begin != end) 
    {
        tmp->m_next = new Node(*begin);
        tmp->m_next->m_prev = tmp;
        tmp = tmp->m_next;
        ++begin;
    }
    m_begin = m_head;
    tmp->m_next = new Node();
    tmp->m_next->m_prev = tmp;
    m_end = tmp->m_next;
}

template<typename T>
void stl::List<T>::swap(stl::List<T>& list1) 
{
    Node* tmp = m_head;
    m_head = list1.m_head;
    list1.m_head = tmp;
    Iterator iter = m_begin;
    m_begin = list1.m_begin;
    list1.m_begin = iter;
    iter = m_end;
    m_end = list1.m_end;
    list1.m_end = iter;
}

        
template<typename T>    
void stl::List<T>::push_back(const T& value) 
{
    if(empty()) 
    {
        m_head = new Node(value);
        m_head->_next = new Node();
        m_begin = m_head;
        m_end = m_head->m_next;
    } 
    else 
    {
        Node* tmp = m_end.getIter();
        tmp->m_value = value;
        tmp->m_next = new Node();
        tmp->m_next->m_prev = tmp;
        m_end = tmp->m_next;
    }
}

template<typename T>
void stl::List<T>::pop_back() 
{
    if(!empty())
    {
        Node* tmp = m_end.getIter()->m_prev;
        delete m_end.getIter();
        tmp->m_value = {};
        tmp->m_next = nullptr;
        m_end = tmp;
    }
}

template<typename T>
void stl::List<T>::push_front(const T& value)
{
    if(empty()) 
    {
        m_head = new Node(value);
        m_head->m_next = new Node();
        m_begin = m_head;
        m_end = m_head->m_next;
    } 
    else 
    {
        m_head->m_prev = new Node(value);
        Node* tmp = m_head;
        m_head = m_head->m_prev;
        m_head->m_next = tmp;
        m_begin = m_head;
    }
}

template<typename T>
void stl::List<T>::pop_front() 
{
    if(!empty()) 
    {
        Node* tmp = m_head;
        m_head = m_head->m_next;
        m_begin = m_head;
        m_head->m_prev = nullptr;
        tmp->m_value = {};
        delete tmp;
    }
}