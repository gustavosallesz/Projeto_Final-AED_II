#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de dados dinâmica para livros
typedef struct no {
    int id;
    char nome[50];
    char genero[30];
    struct no *prox;
} Livro;

// Declaração das funções
void adicionarLivro(Livro **inicio, int id, const char *nome, const char *genero);
void removerLivro(Livro **inicio, int id);
void listarLivros(Livro *inicio);
void salvarLivros(Livro *inicio, const char *filename);
Livro* carregarLivros(const char *filename);
int gerarID(Livro *inicio);
void buscarLivroPorNome(Livro *inicio, const char *nome);
void buscarLivroPorGenero(Livro *inicio, const char *genero);
void ordenarLivrosPorNome(Livro **inicio);
void ordenarLivrosPorGenero(Livro **inicio);

#endif
