#ifndef FUNC_FORCA_H
#define FUNC_FORCA_H

void ortografia();
void selecModo();
void jogo();
void jogoMultiplayer();
void exibeImagem(const char *arquivo);
char* escolhePalavra(char escolha[], char dica[]);
void resultado(int vitoria);
void desenhaMenu();
void exibeDica(char *dica);
void exibePalavra(char *tentativa);
void exibeInfo(int tentativas, int corretas, int limite_tentativas);
void salvaPontuacao(const char* nome, int pontuacao);
void exibePontuacoes();
void salvaNovaPalavra(const char* palavra, const char* dica);

typedef struct No {
    char letra;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} listaLSE;

listaLSE* criaLista();
void adicionaLetra(listaLSE *lista, char letra);
void exibeLista(listaLSE *lista);
void liberaLista(listaLSE *lista);

#endif
