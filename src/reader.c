/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

#include "reader.h"
#include <string.h>

/* Ordem dos Campos:
    id                  char
    ano                 short int
    temporadas          char
    título              char[variável]
    descrição           char[variável]
    país de produção    char[variável]
    genero              char[variável]
*/

/*
 *  Função que busca e imprime série com o ID igual ao fornecido.
 *
 *  PARÂMETROS:
 *      int val - valor do ID da série desejada.
 *      char* filename - endereço local do arquivo de registros.
 *  RETORNO:
 *      int - 1 se série existir, 0 caso contrário.
 *
 */
int findSeries(int val, char* filename){
    int ch1, ch2;
    char id, seasons, delimiter;
    short int year;
    char *title, *desc, *country, *genre;
    FILE *fp = fopen(filename, "rb");
    while((ch1=fgetc(fp))!=EOF){ // lê o arquivo de registros até o final
        id = (char) ch1;
        if(id==val){ // se encontrada uma série com o mesmo ID procurado
        
            // leitura de campos
            fread(&year, sizeof(short int), 1, fp);                 
            fread(&seasons, sizeof(char), 1, fp);                   
            title = readStringField(fp);
            desc = readStringField(fp);
            country = readStringField(fp);
            genre = readStringField(fp);
            
            // impressão dos campos lidos
            printf("\n============= Série Encontrada! =============\n\n");
            printf("- Título:\t\t%s\n", title);
            printf("- ID:\t\t\t%d\n", (int)id);
            printf("- Descrição:\t\t");
            printDescription(desc);
            printf("- Produzido em:\t\t%s\n", country);
            printf("- Ano de Lançamento:\t%d\n", (int)year);
            printf("- Número de Temporadas:\t%d\n", (int)seasons);
            printf("- Gênero:\t\t%s\n\n", genre);
            printf("=============================================\n\n");
            free(title);
            free(desc);
            free(country);
            free(genre);
            return TRUE;
        } 
        
        // pula os campos de tamanho fixo que seguem o ID
        fseek(fp, 3, SEEK_CUR); // sizeof(year+seasons)
        
        // pula o restante dos campos
        do {
            ch2=fgetc(fp);
        } while (ch2 != REG_DELIMITER);
        
        // segue loop lendo o ID do próximo registro...
    }
    
    fclose(fp);
    return FALSE;
}

/*
 *  Função que lê e imprime todos os registros salvos em arquivo.
 *
 *  PARÂMETRO:
 *      char* filename - endereço local do arquivo de registros
 *
 */

void readFile(char* filename){
    char id, seasons;
    char delimiter, aux;
    int ch;
    short int year;
    char *title, *desc, *country, *genre;
    FILE *fp = fopen(filename, "rb");
    printf("\n\n=============================================================\n");
    printf("\t\t    SÉRIES CADASTRADAS\n");
    printf("=============================================================\n\n");
    
    // cada iteração lê um registro (até o fim do arquivo de registros)
    while((ch=fgetc(fp))!=EOF){
        id = (char) ch;                  
        fread(&year, sizeof(short int), 1, fp);                 
        fread(&seasons, sizeof(char), 1, fp);                   
        title = readStringField(fp);
        desc = readStringField(fp);
        country = readStringField(fp);
        genre = readStringField(fp);
        printf("- Título:\t\t%s\n", title);
        printf("- ID:\t\t\t%d\n", (int)id);
        printf("- Descrição:\t\t");
        printDescription(desc); // imprime a descrição em várias linhas
        printf("- Produzido em:\t\t%s\n", country);
        printf("- Ano de Lançamento:\t%d\n", (int)year);
        printf("- Número de Temporadas:\t%hhd\n", (int)seasons);
        printf("- Gênero:\t\t%s\n", genre);
        printf("\n-------------------------------------------------------------\n\n");
        free(title);
        free(desc);
        free(country);
        free(genre);
    }
    
    fclose(fp);
    
}


/*
 *  Função que lê e imprime todos os registros salvos em arquivo.
 *
 *  PARÂMETRO:
 *      FILE* fp - ponteiro para a posição no arquivo de registros de um
 *      determinado campo de tamanho variável (sempre strings).
 *  RETORNO:
 *      char* - string correspondente ao campo lido.
 *
 */
 
char* readStringField(FILE* fp){
    char* str = (char*) malloc(255); // 255 é o tamanho máximo dos campos de string
    char ch;
    int i = 0;
    
    // lê byte a byte até encontrar um delimitador
    while((ch=fgetc(fp))!=FIELD_DELIMITER && ch!=REG_DELIMITER){ 
        str[i] = ch;
        ++i;
    }
    str[i] = '\0'; // encerra a string
    return str;
}

/*
 *  Função que imprime linha por linha o texto de descrição,
 *  tomando o cuidado para não dividir palavras ao meio.
 *  
 *  PARÂMETRO:
 *      char* desc - texto do campo descrição.
 */
 
void printDescription(char* desc){
    int offset, i = 0; 
    char aux;
    int len = strlen(desc);
    int line_counter = 1;
    
    while(i<len){ // enquanto ainda houver texto para ser impresso
        offset = 37; // quantidade de caracteres a serem impressos naquela linha
        if(i+37<len){ // caso essa não seja a última linha da descrição
            // procura finais de palavras ou frases
             while(!(desc[i+offset]==' ' || desc[i+1+offset]==' ' || desc[i+offset]=='.' || desc[i+offset]==',')){
                --offset;
            }
            aux = desc[i+offset];
            // reposiciona momentaneamente o fim da string para limitar a impressão via printf
            desc[i+offset] = '\0';
        }
        if(line_counter==1){ // se for a primeira linha da descrição
            printf("%s\n", &desc[i]);
        } else {
            printf("\t\t\t%s\n", &desc[i]);
        }
        if(i+37<len){
            // retira o '\0' auxiliar e volta a string para o que era antes
            desc[i+offset] = aux;
        }
        // (+1) para ignorar o espaço que vem após espaços e sinais de pontuação no fim da linha
        i+=offset+1; 
        ++line_counter;
    }
}
