#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "FuncForca.h"

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
