#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <iterator>

namespace stl {
template<typename T>
class List {
private:
    struct Node 
	{
		Node(): m_value{0}, m_next{nullptr}, m_prev{nullptr}{}
		Node(const Node& other): m_next{other.m_next},m_prev{other.m_prev}, m_value{other.m_value}{}
		Node(T val, Node* next = nullptr, Node* prev1 = nullptr): m_value{val}, m_next{next}, m_prev{prev1}{}
		Node& operator=(const Node& other)
		{
			if( this == &other){return *this;}
			m_next = other.m_next;
			m_value = other.m_value;
			return *this;
		}
		Node& operator*(){return *this;}

        T m_value;
		Node* m_next;
        Node* m_prev;
	};
public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        Iterator() : m_iter{nullptr} {}
        Iterator(Node* Iter) : m_iter{Iter} {}
        Iterator(const Iterator& other) : m_iter{other.m_iter} {}
    public:
        Iterator& operator++() { m_iter = m_iter->m_next; return *this; }
        Iterator& operator--() { m_iter = m_iter->m_prev; return *this; }
        Iterator operator++(int) { Iterator tmp(*this); m_iter = m_iter->m_next; return tmp; }
        Iterator operator--(int) { Iterator tmp(*this); m_iter = m_iter->m_prev; return tmp; }
        T& operator*() { return m_iter->_value; }
        T* operator->() { return &(m_iter->_value); }
        Node* getIter() const { return m_iter; }
        Iterator& operator=(const Iterator& other) { m_iter = other.m_iter; return *this; }
        Iterator& operator=(Node* Iter) { m_iter = Iter; return *this; }
        bool operator==(const Iterator& rhs) { return (m_iter == rhs.m_iter); }
        bool operator!=(const Iterator& rhs) { return (m_iter != rhs.m_iter); }
    private:
            Node* m_iter;
    };
public:
    Iterator begin() const { return m_begin; }
    Iterator end() const { return m_end; }

public:
    List(): m_head{nullptr}{};  
    List(int num); 
    List(int num, T value);
    List(const List<T>&);
	List(List<T>&&); 
	~List(); 

public:
//Nonmodifying Operations 
    size_t size();  
    bool empty();  
    bool operator==(const List<T>& list1);  
    bool operator!=(const List<T>& list1);  
    bool operator<(const List<T>& list1);   
    bool operator>(const List<T>& list1);  
    bool operator<=(const List<T>& list1);  
    bool operator>=(const List<T>& list1);  

//Assignment Operations
    List<T>& operator=(const List<T>& );  
	List<T>& operator=(List<T>&&);  
    template<typename U>
    List<T>& operator=(const List<U>& rhs);
    void assign(int, const T&);  
    template<typename Iter>
    void assign(Iter begin, Iter end);  
    void swap(List<T>& right);  

//Insert and Remove Operations
    void push_back(const T& value); 
    void pop_back();  
    void push_front(const T& value); 
    void pop_front();  
    /*Iterator insert(Iterator index, const T& value); 
    Iterator insert(Iterator index, size_t n, T& value);
    Iterator insert(Iterator index, Iterator begin, Iterator end);
    Iterator erase(Iterator index);
    Iterator erase(Iterator begin, Iterator end);
    void remove(T value);
    //remove?????
    void resize(size_t num);
    void resize(size_t num, T elem);*/
    void clear();  

private:
    Node* m_head;
    Iterator m_begin;
    Iterator m_end;
};   //class List

};   //namespace 

#endif //LIST_H_