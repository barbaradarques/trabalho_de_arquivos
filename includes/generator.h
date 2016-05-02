/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

/*
 *  Biblioteca para funções de geração de banco de registros a partir
 *  de um arquivo com reportório de series.
 */

#ifndef __GENERATOR_H_
#define __GENERATOR_H_

#include "registry.h"

#define MAX_REG 1000 //numero maximo de registro para importação
#define MARGIN '\n' //delimitador para parser de importação para cada unidade
#define BORDER '\n' //delimitador para parser de importação para atributos
#define REG_DELI '#' //delimitador de registro
#define FIELD_DELI '|' //delimitador de campos de registro

//função irá importar todas as series do arquivo apontado por series
//e escrever em forma de registro no arquivo de dados db.
int import(FILE* series, FILE* db);
int randomPosition ();
char* readFieldToImport (FILE* pfile, const char border);
REG* readToImport (FILE* pfile, const int position);
void* addFieldMem (void* dest, const void* from, unsigned int* size, unsigned int n);
int importOneRegist (FILE *pfile, const REG* regist);

#endif
