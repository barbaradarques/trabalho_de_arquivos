/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_DELIMITER '|'
#define REG_DELIMITER   '#'
#define NUM_FIELDS      7
#define TRUE            1
#define FALSE           0

char* readStringField(FILE* fp);
int findSeries(int val, char* filename);
void readFile(char* filename);
int addSeries();
