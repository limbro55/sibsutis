#include <stdio.h>

int main() {
	int a,b,c,d,max,min;
	printf("vvedite 4 chisla:");
	scanf("%d%d%d%d", &a, &b, &c, &d);

	max = a;
	if (b>max){
	 max = b;
	}
	if (c > max){
	 max = c;
}
	if (d > max){
	max = d;
}

	min = a;
	if (b < min){
	min = b;
}
	if (c < min){
	min = c;
}
	if (d < min){
	min = d;
}

printf("The difference is: %d\n", max - min);

return 0;
}	
