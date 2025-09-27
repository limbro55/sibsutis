#pragma once

#include "list.hpp"

template <typename T>
class Stack : public List<T> {
public:
    Stack() : List<T>() {};

    Stack(Stack& cp)
    {
        for (typename List<T>::Node* ptr = cp.head; ptr; ptr = ptr->next) {
            this->push(ptr->data);
        }
    }

    Stack& operator=(Stack& cp)
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
        ptr->next = this->head;
        this->head = ptr;
    }
};
