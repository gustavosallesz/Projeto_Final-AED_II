#ifndef FUNC_FORCA_H
#define FUNC_FORCA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

// Estrutura de dados para armazenar as palavras e suas dicas
typedef struct Palavra {
    char palavra[50];   // Palavra secreta
    char dica[100];     // Dica associada à palavra
    struct Palavra *prox; // Ponteiro para a próxima palavra na lista
} Palavra;

// Funções relacionadas à configuração de ortografia
void ortografia();

// Funções para manipulação da lista de palavras
void carregaPalavras(Palavra **lista);
void salvaPalavras(Palavra *lista);
void adicionaPalavra(Palavra **lista, const char *palavra, const char *dica);
void removePalavra(Palavra **lista, const char *palavra);
void limpaLista(Palavra *lista);
void exibePalavras(Palavra *lista);

// Funções do jogo
void jogo(Palavra *lista);
void desenhaForca(int erros); // Desenha o boneco da forca baseado nos erros

#endif // FUNC_FORCA_H
