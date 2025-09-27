#include <stdio.h>

void decimalToBinary(int n) {
    if (n == 0) {
        return;
    }

    decimalToBinary(n / 2);
    printf("%d", n % 2);
}

int main() {
    int decimalNum;
    printf("Write number : ");
    scanf("%d", &decimalNum);

    printf("Number %d bin: ", decimalNum);
    if (decimalNum == 0) {
        printf("0");
    } else {
        decimalToBinary(decimalNum);
    }
    printf("\n");

    return 0;
}
