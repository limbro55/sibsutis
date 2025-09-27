#include<stdio.h>

int main(){
	int a;
	
	printf("Vvedite god");
	scanf("%d",&a);
	
	switch(a){
		case 2008: case 2020: case 2032:
			printf("god krisi");
			break;
		 case 2009: case 2021: case 2033:
		 	printf("god korovi");
		 	break;
		case 2010: case 2022: case 2034:
			printf("god tigra");
			break;
		case 2011: case 2023: case 2035:
			printf("god zaitsa");
			break;
		case 2012: case 2024: case 2036:
			printf("god drakona");
			break;
		case 2013: case 2025: case 2037:
			printf("god zmei");
			break;
		case 2014: case 2026: case 2038:
			printf("god loshadi");
			break;
		case 2015: case 2027: case 2039:
			printf("god baran");
			break;
		case 2016: case 2028: case 2040:
			printf("god obez`ana");
			break;
		case 2017: case 2029: case 2041:
			printf("god petux");
			break;
		case 2018: case 2030: case 2042:
			printf("god sobaka");
			break;
		case 2019: case 2031: case 2043:
			printf("dog svin`a");
			break;
		default:
			printf("mi ne poschitali");
			break;
	return 0;
	}
}
