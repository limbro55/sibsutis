#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int i,s_chet = 0,s_nechet = 0;
    int mas[16];
    
    for(i=0;i<16;i++){
        scanf("%1d",&mas[i]);
    }
    
    for (i=1 ; i<16 ; i+=2){
        s_chet+=mas[i];
        
    } 
    for (i=0 ; i<16 ; i+=2){
        if (mas[i]*2>9) {s_nechet+=(mas[i]*2 - 9);} else s_nechet+=(mas[i]*2); 
        
    }
    if ((s_nechet + s_chet) % 10 == 0 ){
        printf("correct");
    } else{
        printf("not correct");
    }

    return 0;
} 