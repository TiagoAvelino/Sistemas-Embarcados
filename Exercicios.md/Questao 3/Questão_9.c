#include <stdio.h>
int main (int argc, char *argv[]){

int conta=0;

for (int i = 1; i < argc; ++i)
	{
		conta = Num_Caracs(argv[i]);
		printf("string: %s / Numeros de caracteres: %d \n", argv[i], conta);		
	}

return 0;
}
