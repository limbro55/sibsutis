#include <stdio.h>
#include <math.h>
int main()
{
    int N,x,z;
    float S=1;
    int y=1;
    
    printf("write N and X :");
    scanf("%d %d",&N,&x);
    
    for (z=1;z<=N;z++){
        
        y*=z;
        
        S+=(pow((x),z))/y;
        
    }
    
    
    
    printf("%.2f",S);
    return 0;
}
