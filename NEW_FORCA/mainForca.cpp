#include "FuncForca.h"
#include <locale.h>

int main() {

    setlocale(LC_ALL, "Portuguese");
    Palavra *listaPalavras = NULL;
    carregaPalavras(&listaPalavras);

    int opcao;

    do {
        printf("\n=====================\n");
        printf("  JOGO DA FORCA  \n");
        printf("=====================\n");
        printf(" \n1. Jogar");
        printf(" \n2. Adicionar palavra");
        printf(" \n3. Exibir palavras");
        printf(" \n4. Remover palavra");
        printf(" \n5. Sair");
        printf("\n\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                jogo(listaPalavras);
                break;
            case 2: {
                char palavra[50], dica[100];
                printf("Digite a nova palavra, em CAPSLOCK e havendo espaço, use '-': ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                printf("Digite a dica: ");
                fgets(dica, sizeof(dica), stdin);
                dica[strcspn(dica, "\n")] = '\0';

                adicionaPalavra(&listaPalavras, palavra, dica);
                salvaPalavras(listaPalavras);
                printf("\nPalavra adicionada com sucesso!\n");
                break;
            }
            case 3:
                exibePalavras(listaPalavras);
                break;
            case 4:
                char palavra[50];
                printf("Digite a palavra que deseja remover: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';
                removePalavra(&listaPalavras, palavra);
                break;
            case 5:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    limpaLista(listaPalavras);
    return 0;
}
