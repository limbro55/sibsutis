#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>



int F(const void* a,const void* b)
{
	return strcmp(*(char**)a,*(char**)b);
}

int main()
{
	int n = 0, i = 0, j = 0, dlina = 0;
	char str[80], *temp;
	char *slovo;
	char ** words = (char**)malloc(sizeof(char*));
	FILE *pf, *ps;
	
	
	pf = fopen("input.txt","r");  
	
	while (fgets(str, sizeof(str), pf))
	{
		temp = strtok(str, " ");
		while (!(temp == NULL))
		{
			words = (char **)realloc(words,(n + 1)* sizeof(char *));
			
			dlina = strlen(temp);
			words[n] = (char *)malloc((dlina + 1)*sizeof(char));
			
			strcpy(words[n], temp);
			
			n++;
			temp = strtok(NULL," ");
		}
	}
	fclose(pf);
	
	
	
	ps = fopen("output.txt","w");
	
	qsort(words,n,sizeof(char*),F);
	
	for (i = 0; i < n; i++) 
	{
        fprintf(ps, "%s\n", words[i]);
        free(words[i]);
	}

	free(words);
	
	fclose(ps);
	return 0;
}