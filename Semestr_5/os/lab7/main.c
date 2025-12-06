#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    Node* list = NULL;
    
    printf("Создание списка...\n");
    for (int i = 1; i <= 5; i++) {
        append_node(&list, i );
    }
    
    printf("Исходный список: ");
    print_list(list);
    
    printf("Длина списка: %d\n", list_length(list));
    
    printf("Разворот списка...\n");
    list = reverse_list(list);
    
    printf("Развернутый список: ");
    print_list(list);
    
    printf("Освобождение памяти...\n");
    free_list(list);
    
    return 0;
}