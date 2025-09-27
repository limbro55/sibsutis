#include<stdio.h>
#include<math.h>

int main(){
	int a,b;
	
	printf("Vvedite number");
	scanf("%d",&a);
	
	if (a>=-9&& a<=9){
		if (a<0){
			printf("minus ");
		}
		b = abs(a);
		if (b==1){
			printf(" odin");
			
		}
		if (b==2){
			printf("dva");
		}
		if (b==3){
			printf("tri");
		}
		if (b==4){
			printf("chetiri");
		}
		if (b==5){
			printf("five");
		}
		if (b==6){
			printf("six");
		}
		if (b==7){
			printf("seven");
		}
		if (b==8){
			printf("vosem");
		}
		if (b==9){
			printf("dev`at`");
		}
	}
	return 0;
}
