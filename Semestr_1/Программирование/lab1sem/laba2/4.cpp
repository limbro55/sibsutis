#include<stdio.h>

int main(){
	int k1 = 0, k2 = 0;
	int a,b,c,d,e,f,g,h;
	
	printf("vvedite 4 chisla:");
	scanf("%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h);

	if(a < 0){
		k1+=1;
	} else{
		k2+=1;
	}
	if(b < 0){
		k1+=1;
	}else{
		k2+=1;
	}

	if(c < 0){
		k1+=1;
	}else{
		k2+=1;
	}
	if(d < 0){
		k1+=1;
	}else{
		k2+=1;
	}

	if(e < 0){
		k1+=1;
	}else{
		k2+=1;
	}
	if(f < 0){
		k1+=1;
	}else{
		k2+=1;
	}

	if(g < 0){
		k1+=1;
	}else{
		k2+=1;
	}
	if(h < 0){
		k1+=1;
	}else{
		k2+=1;
	}

printf("+: %d -: %d", k2, k1);

return 0;}
