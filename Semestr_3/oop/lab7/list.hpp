#pragma once

#include <iostream>

template <typename T>
class List {
protected:
    struct Node {
        T data;
        Node* next;
        Node(T new_data) : data(new_data), next(nullptr) {};
    };

    Node* head;

public:
    List() : head(nullptr) {};
    ~List()
    {
        clear();
    }

    void clear()
    {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool is_empty()
    {
        return head == nullptr;
    }

    int size()
    {
        if (is_empty()) {
            return 0;
        }
        int result = 0;
        for (Node* ptr = head; ptr; ptr = ptr->next) {
            result++;
        }
        return result;
    }

    void pop()
    {
        if (is_empty()) {
            throw std::out_of_range("Пустой список!");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void output()
    {
        if (is_empty()) {
            throw std::out_of_range("Пустой список!");
        }
        for (Node* ptr = head; ptr; ptr = ptr->next) {
            std::cout << ptr->data << " ";
        }
        std::cout << std::endl;
    }

    virtual void push(T new_data) = 0;
};
