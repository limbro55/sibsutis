#include <stdio.h>
#include <string.h>
int main()
{
    char text[1000];
    char* words[1000];
    int kol_vo[1000];
    int slova = 0;
    
    printf("Vvedite text:");
    fgets(text,100,stdin);
    
    char* token = strtok(text,",");
    
    while (token != NULL){
        int flag = 0;
        for (int i = 0; i < slova;i++){
            if (strcmp(words[i],token)== 0){kol_vo[i]++; flag=1; break;} 
        }
        if (flag==0) {words[slova] = token; kol_vo[slova] = 1; slova++;}
        token = strtok(NULL,",");
        
        
    }
    printf("kol-vo povtoreniy slova:\n");
    for (int i = 0; i < slova; i++) { 
        if (i==slova-1){break;}
        printf("%s: %d\n", words[i], kol_vo[i]);
    }
    
    return 0;
}