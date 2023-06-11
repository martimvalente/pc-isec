/** @file game.c
 *  @brief Jogo da Forca, para projeto final da 
 *         cadeira de Programação de Computadores
 *
 *  @author Martim Valente (2022128669@isec.pt)
 *  @author Celestino Lopéz (2022@isec.pt)
 *
 *  @bug Problema na escolha de tamanho que ocorre a cada 9-10 escolhas, corrigido com o uso de arrays, 
 *       possivelmente num ficheiro ".h" externo
 */


// bibliotecas de código
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// variáveis globais
#define MAX_PALAVRA 20
#define MAX_TENTATIVAS 5

// array de palavras fáceis
char palavrasFacil[][MAX_PALAVRA] = {
    "casa",
    "carro",
    "sol",
    "lua",
    "arvore"
};

// array de palavras médias
char palavrasMedio[][MAX_PALAVRA] = {
    "computador",
    "programacao",
    "escola",
    "cadeira",
    "teclado"
};

// array de palavras difíceis
char palavrasDificil[][MAX_PALAVRA] = {
    "desenvolvimento",
    "paralelepipedo",
    "extraterrestre",
    "complexidade",
    "eletronico"
};

// acha as palavras consoante o nível
int obterNumeroPalavras(int nivel) {
    switch (nivel) {
        case 1: return sizeof(palavrasFacil) / sizeof(palavrasFacil[0]);
        case 2: return sizeof(palavrasMedio) / sizeof(palavrasMedio[0]);
        case 3: return sizeof(palavrasDificil) / sizeof(palavrasDificil[0]);
        default: return 0;
    }
}

// tira uma palavra do array para  usar no jogo
char* escolherPalavra(int nivel) {
    int numPalavras = obterNumeroPalavras(nivel);
    if (numPalavras == 0) {
        return NULL;
    }

    srand(time(NULL));
    int indice = rand() % numPalavras;

    switch (nivel) {
        case 1: return palavrasFacil[indice];
        case 2: return palavrasMedio[indice];
        case 3: return palavrasDificil[indice];
        default: return NULL;
    }
}

//mecânica de jogo para adivinhar as letras
void adivinharLetra(char* palavra, char* palavraAdivinhada, char letra, int* tentativasRestantes) {
    int encontrada = 0;
    for (int i = 0; i < strlen(palavra); i++) {
        if (palavra[i] == letra) {
            palavraAdivinhada[i] = letra;
            encontrada = 1;
        }
    }

    if (!encontrada) {
        (*tentativasRestantes)--;
    }
}

// função principal que chama o jogo
void jogar() {
    int nivel = 1;
    int tentativasRestantes = MAX_TENTATIVAS;

    printf("Bem-vindo ao Jogo Adivinha-Palavras!\n");
    printf("by Valente&Marotta\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1 - Jogar\n");
        printf("2 - Definir número de tentativas\n");
        printf("3 - Definir dificuldade (nível de palavras)\n");
        printf("4 - Imprimir as regras do jogo\n");
        printf("5 - Sair\n");

        int opcao;
        printf("\nInsira uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o caractere de nova linha

        switch (opcao) { //opção 1 - Jogar
            case 1: {
                char* palavraSecreta = escolherPalavra(nivel);
                if (palavraSecreta == NULL) {
                    printf("Erro: Nível de dificuldade inválido!\n");
                    break;
                }

                int tamanhoPalavra = strlen(palavraSecreta);
                char palavraAdivinhada[MAX_PALAVRA];
                memset(palavraAdivinhada, '_', tamanhoPalavra);
                palavraAdivinhada[tamanhoPalavra] = '\0';

                tentativasRestantes = MAX_TENTATIVAS;

                printf("\nComeçou o jogo!\n");

                while (tentativasRestantes > 0 && strcmp(palavraAdivinhada, palavraSecreta) != 0) {
                    printf("\nTentativas restantes: %d\n", tentativasRestantes);
                    printf("Palavra: %s\n", palavraAdivinhada);
                    printf("Insira uma letra: ");

                    char letra;
                    scanf(" %c", &letra);
                    getchar(); // Limpar o caractere de nova linha

                    adivinharLetra(palavraSecreta, palavraAdivinhada, letra, &tentativasRestantes);
                }

                if (strcmp(palavraAdivinhada, palavraSecreta) == 0) {
                    printf("\nParabéns! Você adivinhou a palavra secreta: %s\n", palavraSecreta);
                } else {
                    printf("\nGame Over! A palavra secreta era: %s\n", palavraSecreta);
                }

                break;
            }

            case 2: { // muda as tentativas
                int novoNumTentativas;
                printf("Insira o novo número de tentativas (entre 3 e 15): ");
                scanf("%d", &novoNumTentativas);
                getchar(); // Limpar o caractere de nova linha

                if (novoNumTentativas < 3 || novoNumTentativas > 15) {
                    printf("Erro: Número de tentativas inválido!\n");
                } else {
                    tentativasRestantes = novoNumTentativas;
                    printf("Número de tentativas atualizado para: %d\n", tentativasRestantes);
                }

                break;
            }

            case 3: { // muda as dificuldades
                printf("Níveis de dificuldade:\n");
                printf("1 - Fácil\n");
                printf("2 - Médio\n");
                printf("3 - Difícil\n");

                printf("Insira o novo nível de dificuldade: ");
                scanf("%d", &nivel);
                getchar();

                if (nivel < 1 || nivel > 3) {
                    printf("Erro: Nível de dificuldade inválido!\n");
                } else {
                    printf("Nível de dificuldade atualizado para: %d\n", nivel);
                }

                break;
            }

            case 4: { // dá print às regras
                printf("\nRegras do Jogo:\n");
                printf("- Será apresentada uma palavra secreta que você deve adivinhar.\n");
                printf("- A palavra será representada por traços, indicando as letras que você precisa descobrir.\n");
                printf("- Você deve inserir uma letra por vez para tentar adivinhar a palavra.\n");
                printf("- Se a letra estiver presente na palavra secreta, ela será revelada na posição correta.\n");
                printf("- Caso contrário, uma tentativa será descontada.\n");
                printf("- O jogo termina quando todas as letras forem adivinhadas ou quando o número de tentativas se esgotar.\n");
                printf("- Boa sorte!\n");

                break;
            }

            case 5: { // sair do jogo
                printf("Obrigado por jogar! Até logo!\n");
                exit(0);
            }

            default: //opção default é inv. para controlo de erros
                printf("Erro: Opção inválida!\n");
                break;
        }
    }
}

int main() { // ao dar boot ao jogo, chamar a função principal
    jogar();

    return 0;
}
