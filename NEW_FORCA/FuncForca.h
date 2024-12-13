#ifndef FUNC_FORCA_H
#define FUNC_FORCA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

// Estrutura de lista para armazenarmos palavras e dicas
typedef struct Palavra {
    char palavra[50];
    char dica[100];
    struct Palavra *prox;
} Palavra;

// Declaração das nossas funções utilizadas no código
void ortografia();
void carregaPalavras(Palavra **lista);
void salvaPalavras(Palavra *lista);
void adicionaPalavra(Palavra **lista, const char *palavra, const char *dica);
void removePalavra(Palavra **lista, const char *palavra);
void limpaLista(Palavra *lista);
void exibePalavras(Palavra *lista);
void jogo(Palavra *lista);

#endif // FUNC_FORCA_H
