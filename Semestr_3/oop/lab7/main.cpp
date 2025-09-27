#include "queue.hpp"
#include"list.hpp"
#include "stack.hpp"

int main()
{
    system("chcp 65001 > nul");

    Stack<int> stack;
    for (int i = 1; i <= 10; i++) {
        stack.push(i);
    }
    std::cout << "Стек: ";
    stack.output();
    std::cout << "Размер стека: " << stack.size() << std::endl;
    stack.pop();
    std::cout << "Изменённый стек: ";
    stack.output();
    std::cout << "Размер изменённого стека: " << stack.size() << std::endl;
    stack.clear();
    if (stack.is_empty()) {
        std::cout << "Стек очищен" << std::endl;
    }

    Queue<int> queue;
    for (int i = 1; i <= 10; i++) {
        queue.push(i);
    }
    std::cout << "Очередь: ";
    queue.output();
    std::cout << "Размер очереди: " << queue.size() << std::endl;
    queue.pop();
    std::cout << "Изменённая очередь: ";
    queue.output();
    std::cout << "Размер изменённой очереди: " << queue.size() << std::endl;
    queue.clear();
    if (queue.is_empty()) {
        std::cout << "Очередь очищена" << std::endl;
    }
    Queue<int> queue1;
    for (int i = 1; i <= 10; i++) {
        queue1.push(i);
    }
    queue1.output();
    Queue<int> queue2 = queue1;
    queue2.output();
    queue1.output();

    return 0;
}
