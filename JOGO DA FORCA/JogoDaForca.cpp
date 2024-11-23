#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <graphics.h>
#include "FuncoesForca.h"

/*Esse jogo da forca exibe um menu para seleção do usuário. Eu planejo implementar um modo multi-player, para ha-ver disputa dos jogo, por isso deixei uma mensagem de aviso,
na parte de selecionar o modo de jogo. Ao vencer é exibido uma imagem de parabenização e uma frase coma  palavra adivinhada. Do contrário a famosa forca é exibida na tela e
logo abaixo a mensagem com a palavra correta. */


// Minhas funções
void ortografia();
void selecModo();
void jogo();
void exibeImagem(const char *arquivo);
char* escolhePalavra(char escolha[], char dica[]);
void resultado(int vitoria);
void desenhaMenu();
void exibeDica(char *dica);
void exibePalavra(char *tentativa);
void exibeInfo(int tentativas, int corretas, int limite_tentativas);

void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

void exibeImagem(const char *arquivo) {
    readimagefile(arquivo, 0,0, 520, 520);
    while (!kbhit());
}

char* escolhePalavra(char escolha[], char dica[]) {
    const char* palavras[] = {"PACIENCIA", "SALERNITANA", "TELEFONIA", "FOTOGRAFIA"};
    const char* dicas[] = {"É Difícil de Manter", "Time de Futebol Italiano", "Serviço de Comunicação", "Para ficar na Memória..."};
    int index = rand() % 4;
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

void jogo() {
    ortografia();

    char palavra[50], tentativa[50], copiaPalavra[50], dica[50];
    int i, fim = 0, encontrei;
    int n_tentativas = 0, limite_tentativas, corretas = 0;
    char chute;

    srand(time(NULL));
    escolhePalavra(palavra, dica);
    strcpy(copiaPalavra, palavra);

    limite_tentativas = 5;

    for (i = 0; i < strlen(palavra); i++) {
        tentativa[i] = '_';
    }

    do {
        cleardevice();
        exibeDica(dica);
        exibePalavra(tentativa);
        exibeInfo(n_tentativas, corretas, limite_tentativas);

        char texto[100];
        sprintf(texto, "Digite uma letra: ");
        outtextxy(50, 300, texto);

        char input[2];
        input[0] = getch();
        input[1] = '\0';
        chute = input[0];

        encontrei = 0;
        for (i = 0; i < strlen(copiaPalavra); i++) {
            if (toupper(copiaPalavra[i]) == toupper(chute)) {
                copiaPalavra[i] = '*';
                tentativa[i] = toupper(chute);
                corretas++;
                encontrei = 1;
            }
        }

        if (!encontrei) {
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
    }
        else if (chute != '*') {
        char texto[100];
        sprintf(texto, "Parabéns! Você acertou a palavra: %s", palavra);
        outtextxy(50, 540, texto);
        sprintf(texto, "Pressione uma tecla para voltar ao menu principal");
        outtextxy(50, 570, texto);

        resultado(1);
    }
}

void selecModo() {
    int modoJogo = -1;

    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(150, 100, "SELECIONE O MODO DE JOGO:");
    outtextxy(150, 150, " 1 - Modo single-player");
    outtextxy(150, 200, "Demais modos de jogo em produção");
    outtextxy(150, 230, "Por favor, selecione a opção 1: ");

    char input[2];
    input[0] = getch();
    input[1] = '\0';
    modoJogo = atoi(input);

    switch (modoJogo) {
        case 1:
            jogo();
            break;
        default:
            outtextxy(150, 270, "Opção Inválida!");
            delay(2000);
            selecModo();
            break;
    }
}

int main() {
    ortografia();
    int opcao = 1;

   initwindow(1150, 650, "Menu principal");

    do {
        desenhaMenu();

        char input[2];
        input[0] = getch();
        input[1] = '\0';
        opcao = atoi(input);

        switch (opcao) {
            case 1:
                selecModo();
                break;
            case 2:
                cleardevice();
                outtextxy(150, 250, "Saindo...");
                delay(2000);
                closegraph();
                exit(0);
            default:
                outtextxy(150, 300, "Escolha uma opção válida!");
                delay(2000);
                break;
        }
    } while (opcao != 2);

    return 0;
}
