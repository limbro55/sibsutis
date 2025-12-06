#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Добавляем конструктор и деструктор для отслеживания загрузки/выгрузки
__attribute__((constructor))
void library_loaded() {
    printf("liblist.so: Library loaded into process %d\n", getpid());
}

__attribute__((destructor)) 
void library_unloaded() {
    printf("liblist.so: Library unloaded from process %d\n", getpid());
}

Node* create_node(int data) {
    printf("liblist.so: Creating node with data %d\n", data);
    Node* new_node = (Node*)malloc(sizeof(Node));
    
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    printf("liblist.so: Appending node with data %d\n", data);
    Node* new_node = create_node(data);
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void print_list(Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", head->data);
    print_list(head->next);
}

void free_list(Node* head) {
    if (head == NULL) return;
    printf("liblist.so: Freeing node with data %d\n", head->data);
    free_list(head->next);
    free(head);
}

int list_length(Node* head) {
    if (head == NULL) return 0;
    return 1 + list_length(head->next);
}

Node* reverse_list(Node* head) {
    printf("liblist.so: Reversing list\n");
    if (head == NULL || head->next == NULL) return head;
    
    Node* rest = reverse_list(head->next);
    head->next->next = head;
    head->next = NULL;
    
    return rest;
}