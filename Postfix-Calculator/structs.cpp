#include "structs.h"

template <typename T>
void stack<T>::push(const T& value) {
    node<T>* newnode = new node<T>;
    newnode->val = value;
    newnode->point = head;
    head = newnode;
    if (tail == nullptr) {
        tail = newnode;
    }
}

template <typename T>
stack<T>::~stack() {
    while (head != nullptr) {
        node<T>* temp = head;
        head = head->point;
        delete temp;
    }
}

template <typename T>
T stack<T>::pop() {
    T poppedValue = head->val;
    node<T>* temp = head;
    head = head->point;
    delete temp;
    return poppedValue;
}

template <typename T>
void stack<T>::print() {
    node<T>* tbp = head;
    if (tbp != nullptr) {
        std::cout << tbp->val << " ";
        while (tbp->point != nullptr) {
            tbp = tbp->point;
            std::cout << tbp->val << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void queue<T>::push(const T& value) {
    if (head == nullptr) {
        node<T>* newnode = new node<T>;
        newnode->val = value;
        head = newnode;
        tail = newnode;
    }
    else {
        node<T>* newnode = new node<T>;
        newnode->val = value;
        head->point = newnode;
        head = newnode;
    }
}

template <typename T>
T queue<T>::pop() {
    T poppedValue = tail->val;
    node<T>* temp = tail;
    tail = tail->point;
    delete temp;
    return poppedValue;
}

template <typename T>
void queue<T>::print() {
    node<T>* tbp = tail;
    std::cout << tbp->val << " ";
    while (tbp->point != nullptr) {
        tbp = tbp->point;
        std::cout << tbp->val << " ";
    }
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
    if (this != &other) {
        while (tail != nullptr) {
            node<T>* temp = tail;
            tail = tail->point;
            delete temp;
        }
        node<T>* current = other.tail;
        while (current != nullptr) {
            push(current->val);
            current = current->point;
        }
    }
    return *this;
}

template struct stack<int>;
template struct stack<double>;
template struct stack<char>;
template struct queue<int>;
template struct queue<double>;
template struct queue<char>;
