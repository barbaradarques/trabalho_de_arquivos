/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

/*
 * Biblioteca do TAD para estrutura de registros.
 * Os campos do struct está definido no arquivo .c e não
 * será acessivel por meio direto, apenas por chamadas das 
 * funções deste TAD.
 */

#ifndef __REGISTRY_H_
#define __REGISTRY_H_

#define MAX_COUNTRY 31 //O pais com maior nome é o República Democrática do Congo [30 letras] + '\0' = [31]
typedef struct REG REG;

//allocation & desallocation
/*
 * As funções create e delete são funções de alocações e 
 * desalocações de struct de registros. 
 *
 * Com o create é
 * retornado um ponteiro para uma struct REG alocado dinamicamente
 * e com seus campos pre-setados com default (NULL para ponteiros,
 * "" para campos strings fixos e -1 para campos numéricos).
 *
 * Com o delete é
 * retornado um valor de status da operação, tendo como parametro
 * ponteiro para o ponteiro da strict de registro alocado dinamica-
 * mente. Nele todos as memoria de ponteiros são desalocados, tra-
 * tando casos de ponteiros nulos.
 */
REG* createRegist (unsigned char ID);
int deleteRegist (REG**);

/*
 * As funções abaixo são todas referente aos set-get de campos
 * dos registros, ou seja, dos valores da struct REG. 
 *
 * Para as funções GET são dadas os ponteiros tipo constantes para 
 * proteger dados contra eventuais tentivas de alteração. 
 *
 * Para os SET são dadas os ponteiros da REG e o valor a ser 
 * inserido neles.
 */

//ID
unsigned char getRegistID (const REG*);

//title
int setRegistTitle (REG*, char*);
char* getRegistTitle (const REG*);

//description
int setRegistDescrip (REG*, char*);
char* getRegistDescrip (const REG*);

//producer
int setRegistProducer (REG*, char*);
char* getRegistProducer (const REG*);

//year
int setRegistYear (REG*, unsigned short int);
unsigned short int getRegistYear (const REG*);

//season
int setRegistSeason (REG*, unsigned char);
unsigned char getRegistSeason (const REG*);

//genre
int setRegistGenre (REG*, char*);
char* getRegistGenre (const REG*);

#endif
