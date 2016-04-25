/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int op, id;
    scanf("%d", &op);
    
    //--- para limpar o arquivo a cada execução ===//
    FILE *fp = fopen("registros.dat", "w");
    fclose(fp);
    //--------------------------------------------//
    printf("\n\n\t\tSeja Bem-Vindo(a)!\n\n\n");
   
    while(op!=0){ // aceita o cadastro de novos registros até o fim da entrada
        printf("Escolha a opção desejada:\n\n");
        printf("[1]\tAdicionar uma nova série.\n"); // vai ser retirado depois (porque vai ser gerado automaticamente)
        printf("[2]\tMostrar todas as séries cadastradas.\n");
        printf("[3]\tVisualizar uma série específica.\n");
        printf("[0]\tSair.\n\n");
        switch(op){
            case 1:
                addSeries("./data/registros.dat");
                break;
            case 2:
                readFile("./data/registros.dat");
                break;
            case 3:
                printf("\n\nDigite o id da série: \n");
                scanf("%d", &id);
                printf("\n");
                if(!findSeries(id, "registros.dat")){
                    printf("\n\nNão foi encontrada nenhuma série com id igual a %d. \n\n", id);
                }
                break;
        }
        scanf("%d", &op);
    }
    
   
   
   return 0;
}