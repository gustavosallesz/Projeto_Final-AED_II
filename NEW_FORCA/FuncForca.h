#ifndef FUNC_FORCA_H
#define FUNC_FORCA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

/* Luiz = 2-Exemplifica��o de execu��o do programa, demonstrando
    carregamento e salvamento de dados em arquivos.
 */

// Estrutura de dados para armazenar as palavras e suas dicas
typedef struct Palavra {
    char palavra[50];   // Palavra secreta
    char dica[100];     // Dica associada � palavra
    struct Palavra *prox; // Ponteiro para a pr�xima palavra na lista
} Palavra;

// Fun��es relacionadas � configura��o de ortografia
void ortografia();

// Fun��es para manipula��o da lista de palavras
void carregaPalavras(Palavra **lista);
void salvaPalavras(Palavra *lista);
void adicionaPalavra(Palavra **lista, const char *palavra, const char *dica);
void removePalavra(Palavra **lista, const char *palavra);
void limpaLista(Palavra *lista);
void exibePalavras(Palavra *lista);

// Fun��es do jogo
void jogo(Palavra *lista);
void desenhaForca(int erros); // Desenha o boneco da forca baseado nos erros

#endif // FUNC_FORCA_H
