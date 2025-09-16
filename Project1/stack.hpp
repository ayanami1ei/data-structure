#pragma once
#include"list.hpp"
#include<string>
#include<stdexcept>
using namespace std;

template<class T>
class stack {
private:
    node<T>* head; // Õ»¶¥Ö¸Õë
	node<T>* tail; // Õ»µ×Ö¸Õë
    int len;

public:
    stack();

    ~stack();

    template<class U>
    friend istream& operator>>(istream& in, stack<U>& a);

    void push(T x);

    T pop();

    T top() const;

    bool empty() const;

    T size() const;

    void sort(int s, int e, T(*fp)(T, T) = [](T a, T b) {
        return a < b;
        });

	stack<T> operator=(stack<T>& a);
};



template<class T>
stack<T>::stack()
{
    head = nullptr;
    tail = head;
    len = 0;
}

template<class T>
stack<T>::~stack() {
    while (!empty())
        pop();
}

template<class T>
istream& operator>>(istream& in, stack<T>& a)
{
#if 0
    int n;
    in >> n;
    T val;
    for (int i = 0; i < n; ++i) {
        in >> val;
        a.push(val);
    }

    node<T>* p = a.head;
    while (p->next != nullptr)
        p = p->next;
    a.tail = p;

    return in;
#endif

#if 1
    string str;
    in >> str;

    for (int i = str.size() - 1; i >= 0; --i)
        a.push(str[i]);
    node<T>* p = a.head;
    while (p->next != nullptr)
        p = p->next;
    a.tail = p;

    return in;
#endif
}

template<class T>
void stack<T>::push(T x) {
    if (len == 0)
    {
        head = new node<T>(x);
        tail = head;
        ++len;
        return;
    }
    node<T>* a = new node<T>(x);
    a->next = head;
    head->prior = a;
    head = a;
    ++len;
}

template<class T>
T stack<T>::pop() {
    if (empty()) {
        cout << "Õ»¿Õ£¬ÎÞ·¨pop" << endl;
        throw runtime_error("empty");
    }

    if (len==1)
    {
        T val = head->Val();
        delete head;
        head = nullptr;
        tail = head;
        len = 0;
        return val;
	}
    node<T>* tmp = head;
    head = head->next;
    head->prior = nullptr;

    T val = tmp->Val();

    delete tmp;
    --len;

    return val;
}

template<class T>
T stack<T>::top() const {
    if (empty()) {
        //cout << "Õ»¿Õ£¬Ã»ÓÐÕ»¶¥ÔªËØ" << endl;
        throw runtime_error("");
    }
    return head->Val();
}

template<class T>
bool stack<T>::empty() const {
    return head == nullptr;
}

template<class T>
T stack<T>::size() const {
    return len;
}

template<class T>
void stack<T>::sort(int s, int e, T(*fp)(T, T))
{
    if (e - s <= 1)
        return;

    int i = s, j = e;
    T mid;
    node<T>* p = head, pi = head, pj = head;
    int l = len;

    for (int k = 0; k < i; ++k)
        pi = pi->next;
    for (int k = 0; k < j; ++k)
        pj = pj->next;

    while (l >= len / 2)
    {
        p = p->next;
    }
    mid = p->Val();

    while (i <= j)
    {
        while (fp(pi->Val(), mid))
        {
            pi = pi->next;
            ++i;
        }
        while (fp(mid, pj->Val()))
        {
            pj = pj->prior;
            --j;
        }

        if (i <= j)
        {
            T tmp = pi->Val();
            pi->val = pj->Val();
            pj->val = tmp;
            pi = pi->next;
            pj = pj->prior;
            ++i;
            --j;
        }
    }
    sort(s, i, fp);
    sort(i, e, fp);
}

template<class T>
stack<T> stack<T>::operator=(stack<T>& a)
{
    if (this == &a)
        return *this;
    while (!empty())
        pop();
    node<T>* p = a.tail;
    while (p)
    {
        push(p->Val());
        p = p->prior;
    }
    return *this;
}
