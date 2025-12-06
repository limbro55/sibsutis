#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct Node Node;

typedef Node* (*create_node_func)(int);
typedef void (*append_node_func)(Node**, int);
typedef void (*print_list_func)(Node*);
typedef void (*free_list_func)(Node*);
typedef int (*list_length_func)(Node*);
typedef Node* (*reverse_list_func)(Node*);

void print_maps(pid_t pid) {
    char maps_path[256];
    sprintf(maps_path, "/proc/%d/maps", pid);
    
    printf("\n=== Memory Map (PID: %d) ===\n", pid);
    FILE *maps = fopen(maps_path, "r");
    if (maps) {
        char line[1024];
        while (fgets(line, sizeof(line), maps)) {
            if (strstr(line, "liblist.so") || strstr(line, "liblist")) {
                printf("%s", line);
            }
        }
        fclose(maps);
    }
    printf("=== End of Memory Map ===\n\n");
}

int main() {
    pid_t pid = getpid();
    printf("Process PID: %d\n", pid);
    
    // печатаем карту памяти до загрузки
    printf("Before library loading:\n");
    print_maps(pid);
    
    printf("Press Enter to load library...");
    getchar();
    
    // динамическая загрузка
    void *handle = dlopen("./liblist.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }
    
    printf("Library loaded successfully!\n");
    
    printf("After library loading:\n");
    print_maps(pid);
    
    create_node_func create_node = (create_node_func)dlsym(handle, "create_node");
    append_node_func append_node = (append_node_func)dlsym(handle, "append_node");
    print_list_func print_list = (print_list_func)dlsym(handle, "print_list");
    free_list_func free_list = (free_list_func)dlsym(handle, "free_list");
    list_length_func list_length = (list_length_func)dlsym(handle, "list_length");
    reverse_list_func reverse_list = (reverse_list_func)dlsym(handle, "reverse_list");
    
    // Проверяем что все функции загружены
    if (!create_node || !append_node || !print_list || !free_list || 
        !list_length || !reverse_list) {
        fprintf(stderr, "Error loading functions: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }
    
    printf("All functions loaded successfully!\n");
    
    printf("Press Enter to use library functions...");
    getchar();
    
    Node* list = NULL;
    
    printf("Creating list...\n");
    for (int i = 1; i <= 5; i++) {
        append_node(&list, i * 10);
    }
    
    printf("Original list: ");
    print_list(list);
    
    printf("List length: %d\n", list_length(list));
    
    printf("Reversing list...\n");
    list = reverse_list(list);
    
    printf("Reversed list: ");
    print_list(list);
    
    printf("Press Enter to free memory and unload library...");
    getchar();
    
    free_list(list);
    
    printf("Memory freed!\n");
    
    printf("Press Enter to unload library...");
    getchar();
    
    dlclose(handle);
    
    printf("Library unloaded!\n");
    
    printf("After library unloading:\n");
    print_maps(pid);
    
    return 0;
}