#include <stdio.h>
#include <string.h>
int main()
{
    char text[100];
    char* words[100];
    char* temp;
    int kol_vo = 0;
    printf("vvedite text:");
    fgets(text,100,stdin);
    
    int len=strlen(text);
    if(text[len-1] == '\n'){
        text[len-1]== '\0';
    }

    char *token = strtok(text, ",");
    while (!(token == NULL)){
        words[kol_vo]=token;
        kol_vo++;
        token = strtok(NULL,",\n");
    }
    for (int i = 0; i < kol_vo; i++){
        for (int j = 0; j < kol_vo; j++){
            if (strcmp(words[j],words[i]) > 0){
                temp = words[i];
                words[i]= words[j];
                words[j]=temp;
            }
        }
    }
    
    
    printf("spisok po Familiyam:\n ");
    for (int i = 0; i < kol_vo; i++){
        printf("%s ",words[i]);
    }
  
    return 0;
}