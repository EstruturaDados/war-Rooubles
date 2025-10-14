/*
CONSTRUINDO A BASE DE JOGO WAR - NÍVEL INICIANTE
SERA CRIADO UMA BASE COM CAPACIDADE PARA CADASTRAR 5 TERRITÓRIOS
EXIBIR TERRITORIOS CADASTRADOS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTE GLOBAL
#define MAX_TERRITORIO 5

// -- Definição da estrutura (Struct)
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função auxiliar para limpar buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para remover o \n do fgets
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// -- FUNÇÃO PRINCIPAL
int main() {
    struct Territorio mapa[MAX_TERRITORIO];
    int totalTerritorio = 0;
    int opcao;

    // LAÇO PRINCIPAL DO MENU
    do {
        system("clear || cls"); // limpa a tela no Linux/Mac ou Windows
        printf("======================================\n");
        printf("                 WAR                  \n");
        printf("======================================\n");
        printf("1 - Cadastrar novo território\n");
        printf("2 - Exibir territórios cadastrados\n");
        printf("0 - Sair\n");
        printf("======================================\n");
        printf("\nEscolha uma opção: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);
        limparBufferEntrada();

        // PROCESSAMENTO DA OPÇÃO DIGITADA
        switch (opcao) {
        case 1: // CADASTRAR TERRITÓRIO
            printf("\n--- Cadastrar novo território ---\n");
            if (totalTerritorio < MAX_TERRITORIO) {
                printf("Nome do território: ");
                fgets(mapa[totalTerritorio].nome, 30, stdin);
                removerQuebraLinha(mapa[totalTerritorio].nome);

                printf("Cor do território: ");
                fgets(mapa[totalTerritorio].cor, 10, stdin);
                removerQuebraLinha(mapa[totalTerritorio].cor);

                printf("Quantidade de tropas: ");
                scanf("%d", &mapa[totalTerritorio].tropas);
                limparBufferEntrada();

                totalTerritorio++;

                printf("\nTerritório cadastrado com sucesso!\n");
            } else {
                printf("\nNúmero máximo de territórios cadastrados!\n");
            }

            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 2: // EXIBIR TERRITÓRIOS
            printf("\n--- Lista de territórios cadastrados ---\n");
            if (totalTerritorio == 0) {
                printf("Nenhum território foi cadastrado ainda!\n");
            } else {
                for (int i = 0; i < totalTerritorio; i++) {
                    printf("-----------------------------------------\n");
                    printf("Território: %d\n", i + 1);
                    printf("Nome: %s\n", mapa[i].nome);
                    printf("Cor: %s\n", mapa[i].cor);
                    printf("Tropas: %d\n", mapa[i].tropas);
                }
                printf("-----------------------------------------\n");
            }

            printf("\nPressione ENTER para continuar...");
            getchar();
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção inválida! Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
            break;
        }

    } while (opcao != 0);

    return 0;
}
