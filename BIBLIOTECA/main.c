#include "FuncPucTeca.h"
#include <locale.h>

void menu() {
    setlocale(LC_ALL,"Portuguese");
    printf("\n=====================\n");
    printf("  BIBLIOTECA \n");
    printf("=====================\n");
    printf("1. Adicionar Livro\n");
    printf("2. Remover Livro\n");
    printf("3. Listar Livros\n");
    printf("4. Buscar Livro por Nome\n");
    printf("5. Buscar Livro por Gênero\n");
    printf("6. Ordenar Livros por Nome\n");
    printf("7. Ordenar Livros por Gênero\n");
    printf("8. Salvar e Sair\n");
    printf("==========================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Livro *biblioteca = carregarLivros("biblioteca.txt");
    int opcao;
    char nome[50], genero[30];
    int id;

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                id = gerarID(biblioteca);
                printf("Digite o nome do livro: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite o gênero do livro: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = '\0';
                adicionarLivro(&biblioteca, id, nome, genero);
                break;
            case 2:
                printf("Digite o ID do livro a ser removido: ");
                scanf("%d", &id);
                getchar(); // Limpar o buffer do teclado
                removerLivro(&biblioteca, id);
                break;
            case 3:
                listarLivros(biblioteca);
                break;
            case 4:
                printf("Digite o nome do livro para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarLivroPorNome(biblioteca, nome);
                break;
            case 5:
                printf("Digite o gênero do livro para buscar: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = '\0';
                buscarLivroPorGenero(biblioteca, genero);
                break;
            case 6:
                ordenarLivrosPorNome(&biblioteca);
                printf("Livros ordenados por nome!\n");
                break;
            case 7:
                ordenarLivrosPorGenero(&biblioteca);
                printf("Livros ordenados por gênero!\n");
                break;
            case 8:
                salvarLivros(biblioteca, "biblioteca.txt");
                printf("Dados salvos. Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 8);

    return 0;
}
