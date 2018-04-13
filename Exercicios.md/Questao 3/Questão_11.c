#include <stdio.h>
int main (int argc, char *argv[]){

int conta=0;

for (int i = 0; i < argc; ++i)
	{
		conta += Num_Caracs(argv[i]);
		printf (" %s \n", argv[i]);
	}
printf ("Numero de caracteres: %d /n",conta);
return 0;
}
