#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    char pr[10];

    fgets(str, 100, stdin);
    fgets(pr,10,stdin);

    char *t = strtok(str, " ");
    while(t!=NULL){
        if(strncmp(t,pr,(sizeof(pr)%sizeof(0)))==0){
            puts(t);
        }
        t = strtok(NULL," ");
    }
    return 0;
}