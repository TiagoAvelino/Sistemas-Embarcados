/* Display Rasp
	VCC VCC
	GND GND SCE GND RST GPIO 4 DC GPIO 14 MOSI GPIO 10 CLK GPIO 11 LED GPIO 15 
	gcc main.c -lnokia5110 -larmbianio -lpthread -lm
	*/

#define DC 8
#define RST 7
#define LED 10

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <nokia5110.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <armbianio.h>
 
int tela = 0;
char produto[13];
char codigo[14];
int total=0;

void ler_codigo(){
	FILE* fp=0;
	if((fp = fopen("codigo.txt", "r")) == NULL){
		printf("Impossivel ler arquivo.\n");
		exit(1);
	}
	fscanf(fp, "%s", codigo);
	codigo[13] = '\0';
	printf("%s", codigo);
	fclose(fp);
	system("rm codigo.txt");
	printf("leu\n");
}

void verificar_codigo(){
	printf("acho cod");
	int fp=0, valor;
	char cod[14], prod[13], preco[3];
	if((fp = open("base.txt", O_RDONLY)) < -1){
		printf("Impossivel ler arquivo.\n");
		exit(1);
	}
	for(int i=0; i<5; i++){
		read(fp, cod, 14);
		cod[13] ='\0';
		read(fp, prod, 13);
		prod[12] ='\0';
		read(fp, preco, 3);
		preco[2] = '\0';
		valor = atoi(preco);
		printf("%d \n", valor);
		printf("%s %s\n", cod, prod);
		if(strcmp(cod, codigo)==0 || i==4){
			strcpy(produto,prod);
			total += valor;
			close(fp);
			break;
		}
	}
	close(fp);
}

void* tela_atual(void){
	while(1){
		time_t current_time;
		int i;
		char* time_c;
		char dia[3],mes[3],ano[5] = {"2018 "}, hora[6];
		//char produto_atual[13];
		char cod[2];
		switch (tela){
		case 0://Tela Inicial
			current_time = time(NULL);
			time_c = ctime(&current_time);
			for(i=0; i<=5; i++) hora[i] = time_c[i+11];
			hora[5] = ' ';
			for(i=0; i<=2; i++) dia[i] = time_c[i+8];
			for(i=0; i<=2; i++) mes[i] = time_c[i+4];
			nokiaFill(0);
			nokiaWriteString(2, 1, dia, FONT_SMALL);
			nokiaWriteString(5, 1, mes, FONT_SMALL);
			nokiaWriteString(9, 1, ano, FONT_SMALL);
			nokiaWriteString(5, 2, hora, FONT_SMALL);
			nokiaWriteString(4, 5, "INICIAR ", FONT_SMALL);
			usleep(500000);
			break;
		case 1://Tela Principal
			nokiaFill(0);
			nokiaWriteString(0, 0, "Ultimo Produto", FONT_SMALL);
			nokiaWriteString(1, 1, produto, FONT_SMALL);
			nokiaWriteString(0, 3, "Total", FONT_SMALL);
			char pr[3];
			sprintf(pr,"%d", total);
			nokiaWriteString(10, 3, pr , FONT_SMALL);
			nokiaWriteString(2, 5, "ADICIONAR ", FONT_SMALL);
			usleep(500000);
			break;
		case 2://Tela Adicionar
			nokiaFill(0);
			nokiaWriteString(0, 3, "Aprox. o cod.", FONT_SMALL);
			system("python /home/pi/Desktop/Embarcados/Projeto_Final/qrcode3.py");
			ler_codigo();
			printf("aaaa");
			verificar_codigo();
			printf("bbbb");
			nokiaFill(0);
			nokiaWriteString(0, 1, "Item Adicionad", FONT_SMALL);
			nokiaWriteString(1, 3, produto, FONT_SMALL);
			printf("%s", produto);
			sleep(4);
			tela = 1;
			break;
		default:
			printf("Erro ao atualizar Tela \n");
		}
	}
	return NULL;
}

void* aguardar_botao(int b){
	while(1){
		AIOAddGPIO(b, GPIO_IN);
		switch (b){
			case 3:
				if(AIOReadGPIO(3)==0) tela = 1;
				break;
			case 5:
				if(AIOReadGPIO(5)==0) tela = 0;
				break;
			case 29:
				if(AIOReadGPIO(29)==0) tela = 2;
				break;
			default:
				printf("Erro aguardando oos botões \n");
		}
	usleep(100);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int rc;
	produto[12] = ' ';
	pthread_t atualizar_tela, botao1, botao2, botao3;

	// SPI Channel, D/C, RESET, LED
	rc = nokiaInit(0, DC, RST, LED);
	if (rc != 0)
	{
		printf("Problem initializing nokia5110 library\n");
		return 0;
	}
	
	pthread_create(&botao1, NULL, aguardar_botao, 3);
	pthread_create(&botao2, NULL, aguardar_botao, 5);
	pthread_create(&botao3, NULL, aguardar_botao, 29);
	pthread_create(&atualizar_tela, NULL, tela_atual, NULL);
	
	sleep(100);
	
	nokiaShutdown();
	pthread_cancel(&atualizar_tela);
	pthread_cancel(&botao1);
	pthread_cancel(&botao2);
	pthread_cancel(&botao3);

   return 0;
} /* main() */
