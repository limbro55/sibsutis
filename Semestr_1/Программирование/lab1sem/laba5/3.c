#include<stdio.h>
#include<math.h>

int check(int n) {
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int main(){

    int item = 2;
    int n;
    printf("Write N");
    scanf("%d",&n);

    while(n>=item){
        if(check(item)){
            printf("%i\n",item);
        }
        item+=1;
    }
    return 0;

}