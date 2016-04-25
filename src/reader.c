/*==========================================
    Aluno(a):                       Nº USP:
    Bárbara Darques Barros          7243081
    Laís Helena Chiachio de Miranda 8517032
    Saulo Tadashi Iguei             7573548
    Vinícius Volponi Ferreira       9039292
============================================= */

#include "reader.h"

/* Ordem dos Campos:
    id                  char
    ano                 short int
    temporadas          char
    título              char[variável]
    descrição           char[variável]
    país de produção    char[variável]
    genero              char[variável]
*/

char* readStringField(FILE* fp){
    char* str = (char*) malloc(255); // 255 é o tamanho máximo dos campos de string
    char ch;
    int i = 0;
    while((ch=fgetc(fp))!=FIELD_DELIMITER && ch!=REG_DELIMITER){
        str[i] = ch;
        ++i;
    }
    str[i] = '\0';
    return str;
}

int findSeries(int val, char* filename){
    int ch1, ch2;
    char id, seasons, delimiter;
    short int year;
    char *title, *desc, *country, *genre;
    FILE *fp = fopen(filename, "rb");
    while((ch1=fgetc(fp))!=EOF){
        ungetc(ch1, fp);
        fread(&id, sizeof(char), 1, fp);
        if(id==val){
            fread(&delimiter, sizeof(char), 1, fp);
            fread(&year, sizeof(short int), 1, fp);                 fread(&delimiter, sizeof(char), 1, fp);
            fread(&seasons, sizeof(char), 1, fp);                   fread(&delimiter, sizeof(char), 1, fp);
            title = readStringField(fp);
            desc = readStringField(fp);
            country = readStringField(fp);
            genre = readStringField(fp);
            printf("\n============= Série Encontrada! =============\n\n");
            printf("- Id:\t\t\t%d\n", (int)id);
            printf("- Título:\t\t%s\n", title);
            printf("- Descrição:\t\t%s\n", desc);
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
        // pula os campos fixos que seguem o id
        fseek(fp, 6, SEEK_CUR); // sizeof(year+seasons+3*'|')
        do {
            ch2=fgetc(fp);
        } while (ch2 != REG_DELIMITER);
    }
    
    fclose(fp);
    return FALSE;
}

void readFile(char* filename){ // imprime todos os registros ordenadamente
    int ch;
    char id, seasons;
    char delimiter;
    short int year;
    char *title, *desc, *country, *genre;
    FILE *fp = fopen(filename, "rb");
    
    while((ch=fgetc(fp))!=EOF){
        ungetc(ch, fp); // retorna o char que foi lido só para testar o EOF
        fread(&id, sizeof(char), 1, fp);                        fread(&delimiter, sizeof(char), 1, fp);
        fread(&year, sizeof(short int), 1, fp);                 fread(&delimiter, sizeof(char), 1, fp);
        fread(&seasons, sizeof(char), 1, fp);                   fread(&delimiter, sizeof(char), 1, fp);
        title = readStringField(fp);
        desc = readStringField(fp);
        country = readStringField(fp);
        genre = readStringField(fp);
        printf("\n==========================================\n\n");
        printf("- Id:\t\t\t%d\n", (int)id);
        printf("- Título:\t\t%s\n", title);
        printf("- Descrição:\t\t%s\n", desc);
        printf("- Produzido em:\t\t%s\n", country);
        printf("- Ano de Lançamento:\t%d\n", (int)year);
        printf("- Número de Temporadas:\t%hhd\n", (int)seasons);
        printf("- Gênero:\t\t%s\n\n", genre);
        free(title);
        free(desc);
        free(country);
        free(genre);
    }
    
    fclose(fp);
    
}

int addSeries(char* filename){
    char id, seasons;
    short int year;
    char title[55], desc[255], country[50], genre[30];
    FILE *fp = fopen(filename, "ab");
    char fieldEnd = FIELD_DELIMITER;
    char regEnd = REG_DELIMITER;
    
    // Lê os campos da entrada
    // -- Obs.: getchar() é usado aqui para consumir o '\n' de cada entrada
    scanf("%hhd", &id);     getchar();
    scanf("%55[^\n]", title);    getchar();
    scanf("%255[^\n]", desc);   getchar();
    scanf("%50[^\n]", country);     getchar();
    scanf("%hd", &year);    getchar();
    scanf("%hhd", &seasons);  getchar();
    scanf("%30[^\n]", genre);     getchar();

    // Escreve no arquivo de dados
    fwrite(&id, sizeof(char), 1, fp);                       fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(&year, sizeof(short int), 1, fp);                fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(&seasons, sizeof(char), 1, fp);                  fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(title, sizeof(char), strlen(title), fp);         fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(desc, sizeof(char), strlen(desc), fp);           fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(country, sizeof(char), strlen(country), fp);     fwrite(&fieldEnd, sizeof(char), 1, fp);
    fwrite(genre, sizeof(char), strlen(genre), fp);         fwrite(&regEnd, sizeof(char), 1, fp);
    
    fclose(fp);
}