#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
void append_node(Node** head, int data);
void print_list(Node* head);
void free_list(Node* head);
int list_length(Node* head);
Node* reverse_list(Node* head);

#endif