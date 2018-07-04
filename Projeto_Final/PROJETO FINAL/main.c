/* Display Rasp
	VCC VCC
	GND GND SCE GND RST GPIO 4 DC GPIO 14 MOSI GPIO 10 CLK GPIO 11 LED GPIO 15 
	gcc main.c -lnokia5110 -larmbianio -lpthread -lm
	*/

#define DC 8
#define RST 7
#define LED 10
#define n_prod 10

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
char prod_lista[13], quant_lista[3];
char precoR[4], precoC[3];
char codigo[14];
int quantidade = 1;
int linha = 0;
int nao = 0;
int numero_prod = 0;
float total=0;

void ler_lista(int a){
	FILE* fp=0;
	if((fp = fopen("lista.txt", "r")) == NULL){
		printf("Impossivel ler a lista.\n");
		exit(1);
	}
	fseek(fp, (15*a), SEEK_SET);
	fscanf(fp, "%s", prod_lista);
	fscanf(fp, "%s", quant_lista);
	//printf("prod:%s quat: %s\n", prod_lista, quant_lista);
	fclose(fp);
}

void guardar_lista(){
	FILE* fp=0;
	if((fp = fopen("lista.txt", "a")) == NULL){
		printf("Impossivel guardar na lista.\n");
		exit(1);
	}
	fprintf(fp,"%s ", produto);
	fprintf(fp,"%d\n", quantidade);
	fclose(fp);
}

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
	printf("verificando \n");
	int fp=0, valor;
	char cod[14], prod[13];
	if((fp = open("base.txt", O_RDONLY)) < -1){
		printf("Impossivel ler arquivo.\n");
		exit(1);
	}
	for(int i=0; i<=n_prod; i++){
		read(fp, cod, 14);
		cod[13] ='\0';
		read(fp, prod, 13);
		prod[12] ='\0';
		read(fp, precoR, 4);
		precoR[3] ='\0';
		read(fp, precoC, 3);
		precoC[2] ='\0';
		if(i == n_prod){
			nao = 1;
			break;
		}
		if(strcmp(cod, codigo)==0){
			nao = 0;
			strcpy(produto,prod);
			close(fp);
			numero_prod++;
			printf("achou alguma coisa");
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
			char pr[6];
			sprintf(pr,"%.2f", total);
			nokiaWriteString(7, 3, pr , FONT_SMALL);
			nokiaWriteString(2, 5, "ADICIONAR ", FONT_SMALL);
			usleep(500000);
			break;
		case 2://Tela Adicionar
			nokiaFill(0);
			nokiaWriteString(3, 1, "Aproxime ", FONT_SMALL);
			nokiaWriteString(6, 2, "o ", FONT_SMALL);
			nokiaWriteString(4, 3, "Codigo ", FONT_SMALL);
			AIOWriteGPIO(15, 1);
			system("python /home/pi/Desktop/Projeto_Final/barcode.py");
			AIOWriteGPIO(15, 0);
			ler_codigo();
			verificar_codigo();
			if(nao == 1){
				nokiaFill(0);
				nokiaWriteString(5, 1, "Nao ", FONT_SMALL);
				nokiaWriteString(2, 3, "Cadastrado ", FONT_SMALL);
				sleep(3);
				tela = 1;
			}
			else tela=3;
			break;
		case 3://Quantidade de produto
			nokiaFill(0);
			nokiaWriteString(0, 0, "Quantidade: ", FONT_SMALL);
			char quant[3];
			sprintf(quant, "%d", quantidade);
			nokiaWriteString(12, 0, quant, FONT_SMALL);
			nokiaWriteString(1, 2, produto, FONT_SMALL);
			nokiaWriteString(0, 5, "+ ", FONT_SMALL);
			nokiaWriteString(2, 5, "CONFIRMAR ", FONT_SMALL);
			nokiaWriteString(12, 5, "- ", FONT_SMALL);
			usleep(500000);
			break;
		case 4://Lista
			nokiaFill(0);
			nokiaWriteString(4, 0, "Lista ", FONT_SMALL);
			nokiaWriteString(5, 5, "FIM ", FONT_SMALL);
			printf("%d\n", linha); 
			if(numero_prod < 4){
				for(i=0; i<numero_prod; i++){
					ler_lista(i);
					nokiaWriteString(0, i+1, quant_lista, FONT_SMALL);
					nokiaWriteString(2, i+1, prod_lista, FONT_SMALL);			
				}
			}
			else{
				for(i=linha; i < linha+4; i++){
					ler_lista(i);
					nokiaWriteString(0, i-linha+1, quant_lista, FONT_SMALL);
					nokiaWriteString(2, i-linha+1, prod_lista, FONT_SMALL);			
				}
			}
			usleep(500000);	
			break;
		case 5://Finalizar
			nokiaFill(0);
			nokiaWriteString(4, 1, "Deseja ", FONT_SMALL);
			nokiaWriteString(3, 2, "finalizar? ", FONT_SMALL);
			nokiaWriteString(1, 5, "NAO ", FONT_SMALL);
			nokiaWriteString(9, 5, "SIM ", FONT_SMALL);
			usleep(500000);	
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
				if(AIOReadGPIO(3)==0)
				{
					printf("pino 3\n");
					if(tela==0);
					else if(tela==1) tela = 0;
					else if(tela==2);
					else if(tela==3){
						quantidade++;
						usleep(500000);
					}
					else if(tela==4){
						tela = 1;
						usleep(500000);
					}
					else if(tela==5){
						tela = 4;
						usleep(500000);
					}
				}
				break;
			case 5:
				if(AIOReadGPIO(5)==0)
					{
						printf("pino 5\n");
						if(tela==0){
							tela = 1;
							sleep(1);
						}
						else if(tela==1){
							tela = 2;
							usleep(500000);
						}
						else if(tela==2);
						else if(tela==3){
							total += (float)quantidade*(float)atoi(precoR);
							total += ((float)quantidade*(float)atoi(precoC)/100);
							printf("%.2f\n %d\n", total, quantidade);
							guardar_lista();
							quantidade = 1;
							tela = 1;
							usleep(500000);
						}
						else if(tela==4){
							tela = 5;
							usleep(500000);	
						}
						else if(tela==5);
					}
					break;
			case 29:
				if(AIOReadGPIO(29)==0)
				{
					printf("pino 29\n");
					if(tela==0);
					else if(tela==1)tela = 4;
					else if(tela==2);
					else if(tela==3){
						if(quantidade>1){
							quantidade--;
							usleep(500000);
						}
					}
					else if(tela==4);
					else if(tela==5){
						system("sudo rm lista.txt");
						linha = 0;
						numero_prod = 0;
						total = 0;
						sprintf(produto, "            ");
						tela = 0;
						usleep(500000);
					}
				}
				break;
			case 26:
				if(AIOReadGPIO(26)==0)
				{
					printf("pino 26\n");
					if(tela==0);
					else if(tela==1);
					else if(tela==2);
					else if(tela==3);
					else if(tela==4){
						linha++;
						usleep(500000);
					}
					else if(tela==5);
				}

				break;
			case 31:
			if(AIOReadGPIO(31)==0)
				{
					printf("pino 13\n");
					if(tela==0);
					else if(tela==1);
					else if(tela==2);
					else if(tela==3);
					else if(tela==4){
						if(linha>0) linha--;
						usleep(500000);
					}
					else if(tela==5);
				}
			
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
	pthread_t atualizar_tela, botao1, botao2, botao3, botao4, botao5;

	// SPI Channel, D/C, RESET, LED
	rc = nokiaInit(0, DC, RST, LED);
	if (rc != 0)
	{
		printf("Problem initializing nokia5110 library\n");
		return 0;
	}
	
	AIOAddGPIO(15, GPIO_OUT);
	pthread_create(&botao1, NULL, aguardar_botao, 3);
	pthread_create(&botao2, NULL, aguardar_botao, 5);
	pthread_create(&botao3, NULL, aguardar_botao, 29);
	pthread_create(&botao4, NULL, aguardar_botao, 31);
	pthread_create(&botao5, NULL, aguardar_botao, 26);
	pthread_create(&atualizar_tela, NULL, tela_atual, NULL);
	
	sleep(10000);
	
	nokiaShutdown();
	pthread_cancel(&atualizar_tela);
	pthread_cancel(&botao1);
	pthread_cancel(&botao2);
	pthread_cancel(&botao3);
	pthread_cancel(&botao4);
	pthread_cancel(&botao5);

   return 0;
} /* main() */
