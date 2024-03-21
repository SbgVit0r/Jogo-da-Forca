
#include <stdio.h>
#include <string.h>

// variaveis globais
char palavrasecreta[20];
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

        chutes[tentativas] = chute;
        tentativas++;
}

int jachutou(char letra){
       int achou = 0;

            // A letra já foi chutada?
            for(int j = 0; j < tentativas; j++) {
                if(chutes[j] == letra) {
                    achou = 1;
                    break;
                }
            }
        return achou;
}

void desenhaforca(){
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

void escolhapalavra(){
    sprintf(palavrasecreta, "MELANCIA");
}

int main() {

    int acertou = 0;
    int enforcou = 0;
  
    escolhapalavra();
    cabecalho();
    
    do {
        
        desenhaforca();
        chuta();
        
    } while (!acertou && !enforcou);
}
