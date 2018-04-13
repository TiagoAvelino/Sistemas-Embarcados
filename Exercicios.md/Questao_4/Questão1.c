#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *pf;
    char nome[9]= "Ola mundo" ;
    if((pf = fopen("arquivo.txt", "wb")) == NULL) /* Abre arquivo binario para escrita */
    {
        printf("Erro na abertura do arquivo");
        exit(1);
    }
    fwrite(nome, sizeof(char), 9,pf);
    fclose(pf);
    return(0);
}	
