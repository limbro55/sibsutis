#include<stdio.h>
#include <locale.h>

int main(){
	setlocale(LC_ALL, "Rus");
	
	int a;
	
	printf("Введите месяц");
	scanf("%d",&a);
	
	switch(a){
		case 1: case 2: case 3:
			printf("1 квартал\n");
			break;
		case 4: case 5: case 6:
			printf("2 квартал\n");
			break;
		case 7: case 8: case 9:
			printf("3 квартал\n");
			
		case 10: case 11: case 12:
			printf("4 квартал\n");
			break;
		
	}
	switch(a){
		case 12: case 1: case 2:
			printf("Зима\n");
			break;
		case 3: case 4: case 5:
			printf("Весна\n");
			break;
		case 6: case 7: case 8:
			printf("Лето\n");
			break;
		case 9: case 10: case 11:
			printf("Осень\n");
			break;
	}
	return 0;
}
