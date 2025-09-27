#include <stdio.h>

void printPositiveNumbers() {
    int num;
    scanf("%d", &num);

    if (num != 0) {
        if (num > 0) {
            printf("%d ", num);
        }
        printPositiveNumbers();
    }
}

int main() {
    printPositiveNumbers();

    return 0;
}
