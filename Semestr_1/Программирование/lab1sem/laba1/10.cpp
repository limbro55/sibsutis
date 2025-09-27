#include<stdio.h>

#include<math.h>

int main(){
    int min, gig, s, sh;
    s = 200;
    printf("min and gig in mouth");
    scanf("%d%d",&min, &gig);
    if (min>50 && gig >25){
    	sh = s+(min-50)+(gig-25)*25;
	}
    else if (min>50){
        sh = s + (min-50);
        
		}
	else if (gig>25){
		sh = s+ (gig-25)*25;
	}
	else if (min<50 && gig<25){
		sh=s;
	}
    printf("sh=%d",sh);

    return 0;
}