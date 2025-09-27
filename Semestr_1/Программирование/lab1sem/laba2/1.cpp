#include <stdio.h>

int main() {
	int num1, num2, num3, num4, num5, num6;

	printf("vvedite 6 chisla ");
	scanf("%d %d %d %d %d %d", &num1, &num2, &num3, &num4, &num5, &num6);

	int sum = num1 + num2 + num3 + num4 + num5 + num6;
	int product = num1 * num2 * num3 * num4 * num5 * num6;

	if (sum < product){
    printf("summa men`she na%d\n", product - sum);
	}else if (sum > product){
    printf("summa bolshe na %d\n", sum - product);
	}
return 0;
}
