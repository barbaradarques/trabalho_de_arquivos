/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */


/*
 * Biblioteca responsável por fazer a leitura do arquivo de registros. *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_DELIMITER '|' // delimitador de campo
#define REG_DELIMITER   '#' // delimitador de registro
#define NUM_FIELDS      7   // número de campos
#define TRUE            1
#define FALSE           0

int findSeries(int val, char* filename); // encontra e imprime os dados de uma série dado seu ID
void readFile(char* filename); // lê e imprime os dados de todas as séries cadastradas
char* readStringField(FILE* fp); // auxilia na leitura de campos de tamanho variável
void printDescription(char* desc); // auxilia a impressão do campo descrição