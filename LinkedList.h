//
// Created by jon on 10/17/18.
//

#ifndef RESEARCH_LINKEDLIST_H
#define RESEARCH_LINKEDLIST_H
#include <cstddef>

using namespace std;

template<class EltType>
class Node
{
public:
    Node(void);
    EltType data;
    Node<EltType> *next;
};


template<class EltType>
class LinkedList {
private:
    Node<EltType> *head;
    Node<EltType> *iteratorCurr;
    int iteratorPosn = 0;
public:
    LinkedList();
    void add(EltType data);
    void set(int i, EltType data);
    void iterator();
    EltType next();
    EltType get(int i);
    int Size;
};

template<class EltType>
Node<EltType>::Node(void) {}


template<class EltType>
LinkedList<EltType>::LinkedList(void) {head=nullptr;Size=0;};


template<class EltType>
void LinkedList<EltType>::add(EltType value)
{
    Node<EltType> *tmp = new Node<EltType>();
    tmp->data = value;
    tmp->next = head;
    head = tmp;
    Size++;
}

template<class EltType>
EltType LinkedList<EltType>::get(int i)
{
    Node<EltType> *curr = head;
    for (int j=1; j<i; j++)
        curr = curr->next;
    return curr->data;
}

template<class EltType>
void LinkedList<EltType>::set(int i, EltType d)
{
    Node<EltType> *curr = head;
    for (int j=1; j<i; j++)
        curr = curr->next;
    curr->data = d;
}

template<class EltType>
void LinkedList<EltType>::iterator()
{
    iteratorCurr = head;
    iteratorPosn = 1;
}

template<class EltType>
EltType LinkedList<EltType>::next()
{
    if (!iteratorPosn)
        throw "Iterator not initialized";
    if (iteratorPosn > Size)
        throw "Nullptr Exception";
    EltType temp = iteratorCurr->data;
    iteratorCurr = iteratorCurr->next;
    iteratorPosn++;
    return temp;
}


#endif //RESEARCH_LINKEDLIST_H
