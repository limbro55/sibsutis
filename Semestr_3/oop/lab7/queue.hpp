#pragma once

#include "list.hpp"

template <typename T>
class Queue : public List<T> {
    
private:
    typename List<T>::Node* tail;

public:
    Queue() : List<T>()
    {
        tail = this->head;
    };

    Queue(Queue& cp)
    {
        for (typename List<T>::Node* ptr = cp.head; ptr; ptr = ptr->next) {
            this->push(ptr->data);
        }
    }

    Queue& operator=(Queue& cp)
    {
        if (this != &cp) {
            this->clear();
            for (typename List<T>::Node* ptr = cp.head; ptr; ptr = ptr->next) {
                this->push(ptr->data);
            }
        }
        return *this;
    }

    void push(T new_data) override
    {
        typename List<T>::Node* ptr = new typename List<T>::Node(new_data);
        if (this->head) {
            tail->next = ptr;
        } else {
            this->head = ptr;
        }
        tail = ptr;
    }
};
