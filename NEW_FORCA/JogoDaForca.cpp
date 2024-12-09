#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <graphics.h>
#include "FuncForca.h"

void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

void exibeImagem(const char *arquivo) {
    readimagefile(arquivo, 0,0, 520, 520);
    while (!kbhit());
}

char* escolhePalavra(char escolha[], char dica[]) {
    FILE *arquivo = fopen("palavras.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de palavras!\n");
        return NULL;
    }
    int count = 0;
    char palavras[100][50];
    char dicas[100][50];
    while (fscanf(arquivo, "%s %s", palavras[count], dicas[count]) != EOF) {
        count++;
    }
    fclose(arquivo);

    if (count == 0) {
        printf("Nenhuma palavra encontrada!\n");
        return NULL;
    }

    int index = rand() % count;
    strcpy(escolha, palavras[index]);
    strcpy(dica, dicas[index]);
    return escolha;
}

void resultado(int vitoria) {
    if (vitoria) {
        exibeImagem("Vitoria.jpg");
    } else {
        exibeImagem("ForcaAzul.jpg");
    }
}

void desenhaMenu() {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 100, "________________________");
    outtextxy(150, 140, "       FORCA EM C           ");
    outtextxy(150, 160, "________________________");
    outtextxy(150, 200, "1 - JOGAR");
    outtextxy(150, 250, "2 - SAIR");
}

void exibeDica(char *dica) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    char texto[100];
    sprintf(texto, "Dica: %s", dica);
    outtextxy(50, 50, texto);
}

void exibePalavra(char *tentativa) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    char texto[100] = "";
    for (int i = 0; i < strlen(tentativa); i++) {
        sprintf(texto + strlen(texto), " %c ", tentativa[i]);
    }
    outtextxy(50, 100, texto);
}

void exibeInfo(int tentativas, int corretas, int limite_tentativas) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char texto[100];
    sprintf(texto, "Tentativas Restantes: %d", limite_tentativas - tentativas);
    outtextxy(50, 150, texto);
    sprintf(texto, "Acertos: %d", corretas);
    outtextxy(50, 200, texto);
}

void salvaPontuacao(const char* nome, int pontuacao) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuações!\n");
        return;
    }
    fprintf(arquivo, "Nome: %s, Pontuação: %d\n", nome, pontuacao);
    fclose(arquivo);
}

void exibePontuacoes() {
    FILE *arquivo = fopen("pontuacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuações!\n");
        return;
    }
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

void salvaNovaPalavra(const char* palavra, const char* dica) {
    FILE *arquivo = fopen("palavras.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de palavras!\n");
        return;
    }
    fprintf(arquivo, "%s %s\n", palavra, dica);
    fclose(arquivo);
}

listaLSE* criaLista() {
    listaLSE *lista = (listaLSE*)malloc(sizeof(listaLSE));
    lista->inicio = NULL;
    return lista;
}

void adicionaLetra(listaLSE *lista, char letra) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->letra = letra;
    novoNo->prox = lista->inicio;
    lista->inicio = novoNo;
}

void exibeLista(listaLSE *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        char texto[3];
        sprintf(texto, " %c ", atual->letra);
        outtextxy(50, 300, texto);
        atual = atual->prox;
    }
    printf("\n");
}

void liberaLista(listaLSE *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}

void jogo() {
    ortografia();

    listaLSE *tentativa = criaLista();
    listaLSE *letrasErradas = criaLista();
    char palavra[50], copiaPalavra[50], dica[50];
    int i, fim = 0, encontrei;
    int n_tentativas = 0, limite_tentativas, corretas = 0;
    char chute;
    char nomeJogador[50];

    printf("Digite seu nome: ");
    scanf("%s", nomeJogador);

    srand(time(NULL));
    escolhePalavra(palavra, dica);
    strcpy(copiaPalavra, palavra);

    limite_tentativas = 5;

    for (i = 0; i < strlen(palavra); i++) {
        adicionaLetra(tentativa, '_');
    }

    do {
        cleardevice();
        exibeDica(dica);
        exibeLista(tentativa); // Exibir a lista ao invés de vetor
        exibeInfo(n_tentativas, corretas, limite_tentativas);

        // Exibir letras erradas
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(50, 250, "Letras erradas:");
        exibeLista(letrasErradas);

        char texto[100];
        sprintf(texto, "Digite uma letra: ");
        outtextxy(50, 300, texto);

        char input[2];
        input[0] = getch();
        input[1] = '\0';
        chute = input[0];

        encontrei = 0;
        No *atual = tentativa->inicio;
        for (i = 0; i < strlen(copiaPalavra); i++) {
            if (toupper(copiaPalavra[i]) == toupper(chute)) {
                copiaPalavra[i] = '*';
                atual->letra = toupper(chute);
                corretas++;
                encontrei = 1;
            }
            atual = atual->prox;
        }

        if (!encontrei) {
            adicionaLetra(letrasErradas, toupper(chute));
            n_tentativas++;
        }

        if (n_tentativas >= limite_tentativas || corretas == strlen(palavra) || chute == '*') {
            fim = 1;
        }

    } while (!fim);

    cleardevice();

    if (n_tentativas >= limite_tentativas) {
        char texto[100];
        sprintf(texto, "Que pena! A palavra era: %s", palavra);
        outtextxy(50, 540, texto);
        sprintf(texto, "Pressione uma tecla para voltar ao menu principal");
        outtextxy(50, 570, texto);
        resultado(0);
        salvaPontuacao(nomeJogador, 0); // Salvar pontuação

    } else if (chute != '*') {
    char texto[100];
    sprintf(texto, "Parabéns! Você acertou a palavra: %s", palavra);
    outtextxy(50, 540, texto);
    sprintf(texto, "Pressione uma tecla para voltar ao menu principal");
    outtextxy(50, 570, texto);
    resultado(1); // Exibe vitória
    salvaPontuacao(nomeJogador, corretas); // Salva pontuação
 }
}
