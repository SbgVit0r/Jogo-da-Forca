
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

// variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;


// variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int tentativas = 0;


void cabecalho(){
    printf("*******************\n");
    printf("*  Jogo de Forca  *\n");
    printf("*******************\n\n");
}

void chuta(){
        char chute;
        printf("Qual letra? ");
        scanf(" %c", &chute);

        chutes[chutesdados] = chute;
        chutesdados++;
}

int jachutou(char letra){
       int achou = 0;

            // A letra já foi chutada?
            for(int j = 0; j < chutesdados; j++) {
                if(chutes[j] == letra) {
                    achou = 1;
                    break;
                }
            }
        return achou;
}

void desenhaforca(){
            int erros = chuteserrados();
        
            printf("  _______      \n");
            printf(" |/      |     \n");
            printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
            printf(" |      %c%c%c   \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
            printf(" |       %c     \n",  (erros >= 1 ? '|' : ' '));
            printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
            printf(" |             \n");
            printf("_|___          \n");
            printf("\n\n");
      
        for(int i = 0; i < strlen(palavrasecreta); i++) {
            
            int achou = jachutou(palavrasecreta[i]);

            if(achou) {
                printf("%c ", palavrasecreta[i]);
            } else {
                printf("_ ");
            }
        }
        printf("\n");
}

void adicionapalavra(){

    char quer;
    printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados não disponivel\n\n");
        }

        int qtd;
        fscanf(f,"%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);  
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

void escolhapalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");

    // Tratamento de erro caso o arquivo .h não esteja na pasta
    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel\n\n");
        exit(1);
    }

    // Gerador de semente aleatoria
    srand(time(0));

    int qtddepalavras;

    fscanf(f, "%d", &qtddepalavras);

    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int chuteserrados(){
     int erros = 0;

    for(int i = 0; i < chutesdados; i++){

        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++){

            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }

        }

        if (!existe) erros++;

    }

    return erros;
}

int enforcou(){

    return chuteserrados() >= 5;
    
}

int main() {

    escolhapalavra();
    cabecalho();
    
    do {
        
        desenhaforca();
        chuta();
        
    } while (!acertou() && !enforcou());
    adicionapalavra();

    if(acertou){

    }
}