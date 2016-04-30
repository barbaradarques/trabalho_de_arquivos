/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

/*
 * TAD para estrutura de registros
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "registry.h"

struct REG {
    unsigned char ID;
    unsigned short int YEAR;
    unsigned char SEASON;
    char* TITLE;
    char* DESCRIP;
    char* PRODUC;
    char* GENRE;
};

/**
 * >>> Função irá alocar memoria para uma estrutura de registro, 
 * atribuir Nulo aos campos de strings variáveis, setar valores
 * de inicialização para os campos numéricos e os campos string de 
 * tamanho fixo.
 *
 *  PARAMETROS:
 *      unsigned char ID - id do novo registro
 *          OBSERVAÇÃO: o ID deveria ser gerado pelo programa, mas
 *          pela PROPOSTA do projeto em que a importação aleatoria
 *          deve ser seguida da não ordenação sequer pelo campo
 *          primeirio, então a solução foi a atribuição do ID
 *          por parametro externo. Pois caso contrário, o ID
 *          seria um valor continuo gerado por esta função,
 *          não permitindo valores duplicados (do ID)
 *          a cada nova importação ou inclusão de novos registros.
 *
 *  RETORNO:
 *      REG* regist - ponteiro para a estrutura de registro alocado
 *
 */
REG* createRegist (unsigned char ID){

    REG* regist = (REG*) malloc(sizeof(REG));
    if(regist != NULL && ID >=0){
        regist->ID = ID;
        regist->TITLE = NULL;
        regist->DESCRIP = NULL;
        regist->PRODUC = NULL;
        regist->YEAR = 0;
        regist->SEASON = 0;
        regist->GENRE = NULL;

        ID++;
        return regist;
    }
    return NULL;
}

/**
 * Função irá desalocar os campos alocados dinamicamente e
 * desalocar a própria estrutura do registro, atribuindo nulo ao
 * ponteiro.
 *
 * PARAMETROS:
 *  REG** regist - ponteiro de ponteiro para estruct de registro
 *
 * RETORNO:
 *  int  - valor simbólico de resultado da operação
 */
int deleteRegist (REG** reg){
    if(reg != NULL && *reg != NULL){
        REG* regist = *reg;

        if(regist->TITLE != NULL)
            free(regist->TITLE);
        
        if(regist->DESCRIP != NULL)
            free(regist->DESCRIP);

        if(regist->PRODUC != NULL)
            free(regist->PRODUC);

        if(regist->GENRE != NULL)
            free(regist->GENRE);

        free(regist);
        *reg = NULL;

        return 0;
    }
    return -1;
}

/**
 * As funções abaixo são de Set-Get dos atributos da struct,
 * devendo tratar se os ponteiros da struct são nulos.
 *
 * Para os Sets além da struct são dadas os valores para os
 * campos de registros, cabendo tratar se são nulo ou inválidos
 * para o tipo de campo, e assim retornando um valor do status
 * da operação, sendo -1 para falha e 0 para sucesso.
 * >>> OBS.: Para os campos de tamanho variável é essencial que
 * os ponteiro apontem para região de memória alocado dinamica-
 * mente, uma vez que a função irá gravar o endereço para o
 * ponteiro da Struct REG.
 *
 * Para os Gets o ponteiro para a struct deve ser do tipo const
 * para não haver alteração do valor do campo. Eles irão retornar
 * o valor do campo caso o registro seja válido caso contrário
 * irá retornar um valor indicativo de falha (-1 para campos 
 * numéricos e NULL para campos de ponteiros). É necessario cautela
 * no uso do ponteiro de retorno dos campo tipo string, uma vez
 * que o retorno não é do tipo const, assim sendo possível alterar
 * seu conteúdo (recurso necessário para futura função de altera-
 * ções).
 */

unsigned char getRegistID (const REG* regist){
    if(regist != NULL){
        return regist->ID;
    }
    return -1;
}

//TITLE
/*o ponteiro para campo TITLE não deve ser Nulo e deve ser 
 * maior que 0.
 * A string deve ter sido alocado dinamicamente.
 */
int setRegistTitle (REG* regist, char* title){
    if(regist != NULL && title != NULL && strlen(title) > 0){
        regist->TITLE = title;
        return 0;
    }
    return -1;
}

char* getRegistTitle (const REG* regist){
    if(regist != NULL){
        return regist->TITLE;
    }
    return NULL;
}

//DESCRIPTION
/*
 * o ponteiro para campo DESCRIP não deve ser Nulo e deve ser maior que 0.
 * A string deve ter sido alocado dinamicamente.
 */
int setRegistDescrip (REG* regist, char* descrip){
    if(regist != NULL && descrip != NULL && strlen(descrip) > 0){
        regist->DESCRIP = descrip;
        return 0;
    }
    return -1;
}

char* getRegistDescrip(const REG* regist){
    if(regist != NULL){
        return regist->DESCRIP;
    }
    return NULL;
}

//PRODUCER
/*
 * O ponteiro para campo PRODUCER não deve ser Nulo e deve ser maior
 * que 0.
 * A string deve ter sido alocado dinamicamente.
 */
int setRegistProducer (REG* regist, char* producer){
    if(regist != NULL && producer != NULL && strlen(producer) > 0){
        regist->PRODUC = producer;
        return 0;
    }
    return -1;
}

char* getRegistProducer (const REG* regist){
    if(regist != NULL){
        return regist->PRODUC;
    }
    return NULL;
}

//YEAR
/*
 * O valor para o campo YEAR não deve ser menor que 1900.
 */
int setRegistYear(REG* regist, unsigned short int year){
    if(regist != NULL && year > 1900){
        regist->YEAR = year;
        return 0;
    }
    return -1;
}

unsigned short int getRegistYear (const REG* regist){
    if(regist != NULL){
        return regist->YEAR;
    }
    return -1;
}

//SEASON
/**
 * O valor para campo SEASON não deve ser menor que 1, mas
 * isso é garantido pela tipo unsigned.
 */
int setRegistSeason (REG* regist, unsigned char season){
    if(regist != NULL && season > 0){
        regist->SEASON = season;
        return 0;
    }
    return -1;
}

unsigned char getRegistSeason (const REG* regist){
    if(regist != NULL){
        return regist->SEASON;
    }
    return -1;
}

//GENRE
/**
 * O ponteiro para campo GENRE não deve ser nulo e
 * a sua string deve ser maior que 0.
 * A memoria apontada pelo parametro char* DEVE ser alocado
 * dinamicamente, pois apenas o endereço será copiado ao 
 * struct.
 */
int setRegistGenre (REG* regist, char* genre){
    if(regist != NULL && genre != NULL && strlen(genre) > 0){
        regist->GENRE = genre;
        return 0;
    }
    return -1;
}

char* getRegistGenre (const REG* regist){
    if(regist != NULL){
        return regist->GENRE;   
    }
    return NULL;
}
