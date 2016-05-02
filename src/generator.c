/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

/*
 *  Funções para geração de banco de registros aleatórios
 * a partir de um arquivo com reportório de séries.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "registry.h"
#include "generator.h"

/**
 * A função faz uso de um vetor estatico com MAX_REG posições,
 * onde randomicamente será eleito uma posição dela e retornado
 * como uma posição sorteada. Caso a posição já foi aleita, 
 * segundo o valor deste proprio vetor, então a proxima posição
 * válida será retornado. Chegada ao fim do vetor, a proxima 
 * posição será o começo do vetor. Desta forma, com o vetor
 * estático, a cada chamada da função aos posições anteriormente
 * eleitas serão lembradas.
 *
 * Para que o vetor seja setado na primeira vez, uma variavel
 * estatica será usada para lembrar se esta função já foi chamada
 * alguma vez, sendo apenas na primeira que todas as posições 
 * do vetor serão setadas para 0, dado uma semente para a função
 * randomica e mudada o valor esta variável estatica, para não
 * executar esta rotina novamente.
 */
int randomPosition (){
    static char lock = 0;
    static unsigned char positions[MAX_REG]; //MAX_REG definido no arquivo .h
    int i;

    //rotina para geração de vetor de posições na primeira chamada
    if(lock == 0){
        for(i = 0; i < MAX_REG; i++)
            positions[i] = 0;
        srand(time(NULL));
        lock = 1;
    }

    //sorteio de posição segundo o máximo de registros
    int position = rand () % MAX_REG;

    //buscar pela proxima posição, caso a posição sorteada já foi usada
    for(i = 0; positions[position] != 0 && i < MAX_REG; i++, position++){
        //caso a posição atinja o fim do vetor, voltar para o começo
        if(position == MAX_REG - 1)
            position = -1; //haverá incremento no for, passando a ser 0
    }

    //só há retorno elegível a posição, caso o looping não percorreu todo o vetor
    if(i < MAX_REG){
        positions[position] = 1;
        return position;
    }
    return -1;
}


/**
 * Função intermediária para leitura de campo/atributo de uma
 * serie. Ela irá fazer o parser no arquivo de catalogo, separados
 * pelo caracter de separação dado pelo parametro e retorna 
 * um ponteiro de uma memoria alocado dinamicamente com os dados
 * lidos do catalogo.
 *
 * PARAMETROS:
 *      FILE* pfile - ponteiro para arquivo de catalogo
 *      const char border - caracter separador de campos de uma serie
 *
 *  RETORNO:
 *      char* - ponteiro para string alocado dinamicamente, com
 *          os dados lidos do campo.
 *          NULL para quando der errado em algum momento.
 */
char* readFieldToImport (FILE* pfile, const char border){
    //ponteiro para memória alocado dinamicamente, para conter um campo da serie.
    char* straux = (char*) malloc(sizeof(char));

    //verificar legitimidade do ponteiro de arquivo e da string
    if(straux != NULL && pfile != NULL){
        int counter = 0; //contador de tamanho da string
        char byte; //variável auxiliar para contem um caracter lido

        //ler do arquivo byte a byte até encontrar o fim do arquivo ou fim do campo/atributo
        while(fscanf(pfile, "%c", &byte) > 0 && byte != border && straux != NULL){
            //realocar para caber mais um caracter na string
            straux = (char*) realloc(straux, sizeof(char*) * counter+2);
            //guardar o caracter
            straux[counter++] = byte;
        }
        //verificar se a leitura e alocação ocorreu corretamente.
        if(straux != NULL && counter > 0){
            straux[counter] = '\0';//adicionar identificador de string
            return straux;
        }    
    }
    return NULL;
}

/**
 * A função irá ler uma única série do arquivo de catálogo, dada
 * a sua posição dentro dele e retorna a estrutura de registro
 * alocada dinamicamente com os atributos copiados deste catalogo.
 * Função irá tratar posições inválidas e ponteiro para arquivo 
 * nulo.
 *
 * A leitura do arquivo de catálogo segue intuitivamente, uma vez
 * que o carregamento só ocorre no carregamento da aplicação. Os 
 * métodos de otimização e afins ocorrem na leitura e escrita do 
 * arquivo de dados.
 */
REG* readToImport (FILE* pfile, const int position){
    //começar a leitura desde o começo do arquivo
    rewind(pfile);

    //variável para contagem de series
    int counter = 0;
    //variável auxiliar para leitura de caracter
    char byte;

    //looping para calcular número de registro a partir de delimitadores
    while(position > counter && fscanf(pfile, "%c", &byte) != EOF){
        if(byte == MARGIN)
            counter ++;
    }

    //executar leitura se a posição existir
    if(counter == position){

        //alocar um registro
        REG* regist = createRegist(position);

        //testar o ponteiro de registro
        if(regist != NULL){
            //variáveis para recepção de dados da série temporariamente
            char* title = NULL;
            char* descrip = NULL;
            char* genre = NULL;
            char* country = NULL;
            int year;
            int season;
            int counter = 0;

            /*
             * As rotinas abaixo irão ler do arquivo um único
             * campo separado por um delimitador definido no
             * arquivo .h e retorna o valor lido do arquivo
             * de catalogo. A função de leitura irá retornar
             * um ponteiro com memoria alocada dinamicamente, 
             * assim para campos que são fixos devem ser
             * tratados a fim de manter esta propriedade.
             */
            //title
            title = readFieldToImport(pfile, BORDER);

            //description
            descrip = readFieldToImport(pfile, BORDER);

            //producer
            country = readFieldToImport(pfile, BORDER);

            //year - campo numerico, converter string para numero
            char* straux = readFieldToImport(pfile, BORDER);
            if(straux != NULL){
                year = atoi(straux);
                free(straux);
            }

            //season - campo numerico, converter string para numero
            straux = readFieldToImport(pfile, BORDER);
            if(straux != NULL){
                season = atoi(straux);
                free(straux);
            }

            //genre - unico campo com delimitador de serie
            genre = readFieldToImport(pfile, MARGIN /*border*/);

            //variável para verificação de status de operações Sets
            char status = 0;

            //as funções sets retornam -1 caso deem errados e 0, caso contrario
            status += setRegistTitle (regist, title);
            status += setRegistDescrip (regist, descrip);
            status += setRegistProducer (regist, country);
            status += setRegistYear (regist, year);
            status += setRegistSeason (regist, season);
            status += setRegistGenre (regist, genre);

            //se todos os dados foram salvos corretamento no registro, então retornar o ponteiro para o registro
            if(status >= 0){
                return regist;
            }

            //caso contrario, liberar toda memoria referente ao registro
            deleteRegist (&regist);
        }
    }
    return NULL;
}

/*
 * A função ira copiar os dados de uma memoria dentro da memoria
 * já existente segundo o seu tamanho.
 * Para tanto é dado o tamanho da memoria destino e memoria a ser 
 * copiada, e assim é possível copiar o bloco de memoria em sequencia
 * dos dados já existentes do bloco alvo após a realocação do 
 * tamanho de memoria.
 *
 * PARAMETROS:
 *      void* dest - ponteiro para bloco de memoria receptora
 *      const void* from - ponteiro para bloco de memoria a ser copiada
 *      unsigned int* size - ponteiro para tamanho atual do bloco de memoria dest
 *      unsigned int n - tamanho da memoria  ser copiada
 *
 *  RETORNO:
 *      void* dest - ponteiro para memoria com o novo dado realocado.
 */
void* addFieldMem (void* dest, const void* from, unsigned int* size, unsigned int n){
    //verificação de legitimidade dos parametros
    if(dest != NULL && from != NULL && size != NULL && (*size) >= 0 && n > 0){
        //realocação para comportar o novo dado no bloco de memoria
        dest = realloc(dest, (*size)+n);
        //escrita efetiva do novo dado na memoria
        memcpy(dest + (*size), from, n);
        //atualização do tamanho do bloco
        (*size) += n;
        return dest;
    }
    return NULL;
}

/**
 * A função irá escrever o registro dentro do arquivo de dados.
 * Ela irá verificar se o ponteiro do arquivo e do registro são
 * validos e irá um a um armazenar os campos em memória alocada
 * dinamicamente, para no fim, tendo todos os dados de um 
 * registro nele, em um único seek gravar no arquivo de dados.
 * Para cada campo existe um realocamento de memoria para
 * comportar os dados do registro. Desta forma existe verificação
 * de legitimidade do ponteiro para cada leitura de campo e para
 * escrita com seek no arquivo.
 * Função retorna 0 para sucesso e -1 para falha em algum momento
 * do processo.
 *
 * PARAMETROS:
 *  FILE* pfile - ponteiro para arquivo de dados aberto em modo
 *      de escrita.
 *  const REG* regist - ponteiro para o registro a ser escrito.
 *          Não é alterável pelo modificador const
 *
 *  RETORNO:
 *      int - valor simbólico do status do processo
 *              0 - sucesso, -1 - falha
 */
int importOneRegist (FILE *pfile, const REG* regist){
    //verificação de legitimidade do ponteiro de arquivo e registro
    if(pfile != NULL && regist != NULL){
        void* straux = NULL; //variavel auxiliar para receber string

        //ponteiro para armazenar todo dado de um registro como
        //um bloco de memoria
        void* mem = malloc(sizeof(char)); 

        int aux;//variavel auxiliar para comportar dados numericos
        unsigned int size = 0; //variavel para armazenar tamanho de mem

        /*
         * Rotinas para recuperar dados de cada campo e repassar
         * para o bloco de memoria mem.
         *
         * Para campos fixos o processo é intuitivo segundo o tamanho
         * em bytes e o tipo de variavel. Para isso é usado a 
         * variável auxiliar para se trabalhar com endereço.
         *
         * Para campos variáveis sempre é retornado uma string que
         * armazenado no bloco de memoria mem segundo o seu tamanho
         * (strlen). Para isso é usado o próprio ponteiro de string
         * para se trabalhar com endereço.
         *
         * A função addFieldMem(...) é reponsável por gerenciar a
         * realocação da memoria mem e armazenar os dados nele.
         */
        //ID - fix
        aux = (unsigned char) getRegistID(regist);
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1);

        //YEAR - fix
        aux = (unsigned short int) getRegistYear(regist);
        mem = addFieldMem (mem, &aux, &size, sizeof(short int)*1);
        
        //SEASON - fix
        aux = (unsigned char) getRegistSeason(regist);
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1);

        //TITLE - var
        straux = getRegistTitle(regist);
        mem = addFieldMem (mem, straux, &size, sizeof(char)*strlen(straux));
        aux = FIELD_DELI;
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1);
        
        //DESCRIPTION - var
        straux = getRegistDescrip(regist);
        mem = addFieldMem (mem, straux, &size, sizeof(char)*strlen(straux));
        aux = FIELD_DELI;
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1); 

        //PRODUCER - var
        straux = getRegistProducer(regist);
        mem = addFieldMem (mem, straux, &size, sizeof(char)*strlen(straux));
        aux = FIELD_DELI;
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1); 

        //GENRE - var
        straux = getRegistGenre(regist);
        mem = addFieldMem (mem, straux, &size, sizeof(char)*strlen(straux));
        aux = REG_DELI;
        mem = addFieldMem (mem, &aux, &size, sizeof(char)*1);

        //verificar se a alocação e leitura de dados ocorreu corretamente
        if(mem != NULL && size > 0){
            //escrever em um único seek todo bloco de memoria de um registro
            fwrite(mem, sizeof(char), size, pfile);
            return 0;
        }
    }
    return -1;
}

/**
 * Função que irá executar a rotina de parser do arquivo
 * de catalogo e escrever os registros lidos no arquivo
 * de dados. Ambos os arquivos devem ser dados por parametros
 * e já aberto, sendo de responsabilidade de fechar de quem
 * o chamou.
 *
 * A função irá eleger uma posição aleatória da série e 
 * ler para dentro de um registro alocado dinamicamente.
 * Em sequencia irá escrever o registro lido em um arquivo
 * de dados segundo as especificação do projeto, junto com
 * os delimitadores, tamanho dos campos e etc.
 *
 * Retorna o status da operação, 0 para sucesso e -1 para falha.
 */
int import (FILE* series, FILE*db){ 
    if(series != NULL && db != NULL){
        int i;//variavel para execução de MAX_REG vezes
        for(i = 0; i < MAX_REG; i++){
            int pos = randomPosition(); //posição aleatoria
            REG* regist = readToImport (series, pos); //ler um registro
            importOneRegist (db, regist);//escrever registro no arquivo de dados
            deleteRegist(&regist);//desalocar o registro dinamico
        }
        return 0;
    }
    return -1;
}

