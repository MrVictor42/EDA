#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define NUMERO_SORTEIO 25

int *sorteiaTesteTreino() {

    srand(time(NULL));
    int *numero_sorteado = (int *)malloc(50*sizeof(int));

    int x = 1, y = 0, z = 0;
    numero_sorteado[0] = rand() % 50 + 1;
    
    do {
    	
    	numero_sorteado[x] = rand() % 50  + 1;
        y = 0;
        while(y < x) {
            
            if(numero_sorteado[y] == numero_sorteado[x]) {
                --x;
                break;
            }
            ++y;
        }
        ++x;
    } 
    while(x < 50);
    
    return numero_sorteado;
}

int salvaArquivos(int *array, int testeOuTreino, int gramaOuAsfalto){
    
    char nome[20];
    char diretorio[256];
    char linha[256];
    int i = 0;
    int tipo;

    if(testeOuTreino == 0 && gramaOuAsfalto == 0){
       
        strcpy(nome,"ArquivosTeste/teste_grass.txt");
        strcpy(diretorio,"DataSet/grass/grass_");
        tipo = 0;
    }
    else if (testeOuTreino == 0 && gramaOuAsfalto == 1){
       
        strcpy(nome,"ArquivosTeste/teste_asphalt.txt");
        strcpy(diretorio,"DataSet/asphalt/asphalt_");
        tipo = 1;
    }
    else if (testeOuTreino == 1 && gramaOuAsfalto == 0){
       
        strcpy(nome,"ArquivosTeste/treino_grass.txt");
        strcpy(diretorio,"DataSet/grass/grass_");
        tipo = 2;
    }
    else if (testeOuTreino == 1 && gramaOuAsfalto == 1){
       
        strcpy(nome,"ArquivosTeste/treino_asphalt.txt");
        strcpy(diretorio,"DataSet/asphalt/asphalt_");
        tipo = 3;
    }
    else{
       
        printf("ERRO");
    }
    printf("Criando: %s \n", nome);

    FILE *arquivo = NULL;
    arquivo = fopen(nome, "wt");

    int aux, aux2;
    char temp[MAX];

    for(i = 0; i < NUMERO_SORTEIO; i++){
         if(array[i]<10){
            aux = sprintf(temp, "%s0%d.txt\n", diretorio, array[i]);
            fprintf(arquivo,"%s" ,temp);
         }else if(array[i]>=10){
            aux = sprintf(temp, "%s%d.txt\n", diretorio, array[i]);
            fprintf(arquivo, "%s", temp);
        }
    }
    fclose(arquivo);
    return tipo;
}

int main () {

	int qtde_linhas_asfalto = 0;
	int qtde_colunas_asfalto = 1;
	int qtde_linhas_grama = 0;
	int qtde_colunas_grama = 1;
	int aux  = 0;
	char caractere;
	FILE *file;

	char arquivo_asfalto [] = "DataSet/asphalt/asphalt_01.txt";
	char arquivo_grama [] = "DataSet/grass/grass_01.txt";

	file = fopen(arquivo_asfalto, "r");

  	if(file==NULL){
	    
	    printf("Falha!\n");
	} else {

		while((caractere = fgetc(file)) != EOF) {
			
			if(caractere == '\n') {
				
				qtde_linhas_asfalto ++;
			} else if(qtde_linhas_asfalto == 0 && caractere == ';'){

				qtde_colunas_asfalto ++;
			}
		}
	}

	fclose(file);

	file = fopen(arquivo_asfalto, "r");

  	if(file==NULL){
	    
	    printf("Falha!\n");
	} else {

		while((caractere = fgetc(file)) != EOF) {
			
			if(caractere == '\n') {
				
				qtde_linhas_grama ++;
			} else if(qtde_linhas_grama == 0 && caractere == ';'){

				qtde_colunas_grama ++;
			}
		}
	}

	fclose(file);

	int * ordemImagensAsfalto;
    int * ordemImagensGrama;

    ordemImagensAsfalto = sorteiaTesteTreino();
    sleep(1);
    ordemImagensGrama = sorteiaTesteTreino(); 

    int asfaltoTreino[NUMERO_SORTEIO];
    int asfaltoTeste[NUMERO_SORTEIO];
    int gramaTreino[NUMERO_SORTEIO];
    int gramaTeste[NUMERO_SORTEIO];

    printf("Sorteando arquivos de Treino... \n");
    for(aux = 0; aux < NUMERO_SORTEIO; aux ++){
     
        asfaltoTreino[aux] = *(ordemImagensAsfalto + aux);
        gramaTreino[aux] = *(ordemImagensGrama + aux);
    }

    sleep(1);

    printf("Sorteando arquivos de Teste...\n");
    for(; aux < MAX; aux ++){
     
        asfaltoTeste[aux - NUMERO_SORTEIO] = *(ordemImagensAsfalto + aux);
        gramaTeste[aux - NUMERO_SORTEIO] = *(ordemImagensGrama + aux);
    }

    sleep(1);
    printf("Criando arquivos...\n");

    sleep(1);
    int listaArquivosTesteGrama = salvaArquivos(gramaTeste, 0, 0);

    sleep(1);
    int listaArquivosTesteAsfalto = salvaArquivos(asfaltoTeste, 0, 1);

    sleep(1);
    int listaArquivosTreinoGrama = salvaArquivos(gramaTreino, 1, 0);

    sleep(1);
    int listaArquivosTreinoAsfalto = salvaArquivos(asfaltoTreino, 1, 1);
}