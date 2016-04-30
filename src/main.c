/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "registry.h"
#include "generator.h"

int main(){
    
    // Geração do arquivo binário de registros
    
    FILE* series = fopen("./data/series.txt", "r"); // abre arquivo de texto auxiliar
    FILE* db = fopen("./data/db_series.bin", "wb"); // abre um novo arquivo binário de registros

    if(series != NULL && db != NULL){ // caso os arquivos tenham sido abertos com sucesso
        int i;
        for(i = 0; i < MAX_REG; i++){
            int pos = randomPosition();  // sorteia uma posição de leitura dentro do arquivo de texto
            REG* regist = readToImport (series, pos); // guarda o registro lido na posição acima
            importOneRegist (db, regist); // salva o registro lido no arquivo de dados
            deleteRegist(&regist); // libera o REG* alocado
        }
        fclose(series);
        fclose(db);
    } else {
        printf("erro ao abrir arquivo: series(%d) db (%d)\n",  
            series == NULL, db == NULL);
            return -1;
    }
    
    // Início da interação com o usuário
    
    int op, id;
    printf("\n\n\t\tSeja Bem-Vindo(a)!\n\n\n");
    
    do {
        // menu
        printf("Escolha a opção desejada:\n\n");
        printf("[1]\tMostrar todas as séries cadastradas.\n");
        printf("[2]\tVisualizar uma série específica.\n");
        printf("[0]\tSair.\n\n");
        scanf("%d", &op);
        
        switch(op){
            case 1:
                readFile("./data/db_series.bin");
                break;
            case 2:
                printf("\n\nDigite o ID da série desejada: \n");
                scanf("%d", &id);
                printf("\n");
                if(!findSeries(id, "./data/db_series.bin")){
                    printf("\n\nNão foi encontrada nenhuma série com ID igual a %d. \n\n", id);
                }
                break;
        }
    } while(op!=0); 
    
    printf("\n\n=============================================================\n");
    printf("\t\t     SESSÃO ENCERRADA\n");
    printf("=============================================================\n");
   
   return 0;
}