/*
CONSTRUINDO A BASE DE JOGO WAR - NÍVEL AVENTUREIRO (v3)
Cada cor possui sua própria missão.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 5
#define TOTAL_MISSOES 5
#define MAX_JOGADORES 2

// === Estrutura principal de território ===
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// === Estrutura de jogador (exército) ===
struct Jogador {
    char cor[10];
    char missao[100];
    int ataquesBemSucedidos;
    int defesasBemSucedidas;
    int territoriosConquistados;
    int vivo;
};

// === Variáveis globais ===
struct Territorio *mapa;
int totalTerritorio = 0;
struct Jogador jogadores[MAX_JOGADORES];

// === Missões possíveis ===
char *missoes[] = {
    "Conquistar 3 territorios",
    "Realizar 5 defesas bem-sucedidas",
    "Realizar 5 ataques bem-sucedidos",
    "Ter o maior numero de tropas",
    "Ter o menor numero de tropas"
};

// === Funções utilitárias ===
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void liberarMemoria() {
    free(mapa);
    printf("\nMemoria liberada.\n");
}

void sortearMissao(char *destino) {
    int indice = rand() % TOTAL_MISSOES;
    strcpy(destino, missoes[indice]);
}

// === Cadastro de territórios ===
void Cadastrar() {
    printf("\nNome do territorio: ");
    fgets(mapa[totalTerritorio].nome, 30, stdin);
    removerQuebraLinha(mapa[totalTerritorio].nome);

    printf("Cor do territorio: ");
    fgets(mapa[totalTerritorio].cor, 10, stdin);
    removerQuebraLinha(mapa[totalTerritorio].cor);

    printf("Quantidade de tropas: ");
    scanf("%d", &mapa[totalTerritorio].tropas);
    limparBufferEntrada();

    totalTerritorio++;
    printf("\nTerritorio cadastrado com sucesso!\n");
}

// === Exibir o mapa ===
void Exibir() {
    printf("\n================== MAPA MUNDO ==================\n");
    for (int i = 0; i < totalTerritorio; i++) {
        printf("%d - %-15s | Exército: %-8s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================================\n");
}

// === Verificar se o jogador cumpriu a missão ===
int verificarMissao(struct Jogador jogador) {
    if (strcmp(jogador.missao, "Conquistar 3 territorios") == 0 &&
        jogador.territoriosConquistados >= 3)
        return 1;

    if (strcmp(jogador.missao, "Realizar 5 defesas bem-sucedidas") == 0 &&
        jogador.defesasBemSucedidas >= 5)
        return 1;

    if (strcmp(jogador.missao, "Realizar 5 ataques bem-sucedidos") == 0 &&
        jogador.ataquesBemSucedidos >= 5)
        return 1;

    if (strcmp(jogador.missao, "Ter o maior numero de tropas") == 0) {
        int maior = 0;
        for (int i = 0; i < totalTerritorio; i++)
            if (mapa[i].tropas > maior)
                maior = mapa[i].tropas;
        for (int i = 0; i < totalTerritorio; i++)
            if (mapa[i].tropas == maior && strcmp(mapa[i].cor, jogador.cor) == 0)
                return 1;
    }

    if (strcmp(jogador.missao, "Ter o menor numero de tropas") == 0) {
        int menor = 9999;
        for (int i = 0; i < totalTerritorio; i++)
            if (mapa[i].tropas < menor)
                menor = mapa[i].tropas;
        for (int i = 0; i < totalTerritorio; i++)
            if (mapa[i].tropas == menor && strcmp(mapa[i].cor, jogador.cor) == 0)
                return 1;
    }

    return 0;
}

// === Simulação de ataque ===
void Ataque(struct Territorio *atacante, struct Territorio *defensor, struct Jogador *jogadorAtual) {
    int dado_ataque = (rand() % 6) + 1;
    int dado_defesa = (rand() % 6) + 1;

    printf("\n*** %s (Ataque: %s) x %s (Defesa: %s) ***\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    printf("Dado Ataque: %d | Dado Defesa: %d\n", dado_ataque, dado_defesa);

    if (dado_ataque > dado_defesa) {
        printf("Ataque bem-sucedido!\n");
        defensor->tropas -= 1;
        atacante->tropas += 1;
        jogadorAtual->ataquesBemSucedidos++;

        // Conquista território
        if (defensor->tropas <= 0) {
            printf("\n*** TERRITÓRIO CONQUISTADO! (%s agora pertence a %s) ***\n",
                   defensor->nome, jogadorAtual->cor);
            strcpy(defensor->cor, jogadorAtual->cor);
            defensor->tropas = 1;
            jogadorAtual->territoriosConquistados++;
        }

    } else {
        printf("Defesa bem-sucedida!\n");
        atacante->tropas -= 1;
        defensor->tropas += 1;
        jogadorAtual->defesasBemSucedidas++;

        // Eliminação do jogador
        if (atacante->tropas <= 0) {
            printf("\n*** O atacante perdeu todas as tropas e foi ELIMINADO! ***\n");
            jogadorAtual->vivo = 0;
            return;
        }
    }

    printf("\nPressione ENTER para continuar...");
    getchar();
}

// === Função principal ===
int main() {
    srand(time(NULL));
    mapa = (struct Territorio *) calloc(MAX_TERRITORIO, sizeof(struct Territorio));

    if (!mapa) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // === Cadastro dos territórios ===
    for (int i = 0; i < MAX_TERRITORIO; i++)
        Cadastrar();

    // === Definir jogadores ===
    printf("\n=== CADASTRO DE EXÉRCITOS ===\n");
    for (int i = 0; i < MAX_JOGADORES; i++) {
        printf("Cor do exercito %d: ", i + 1);
        fgets(jogadores[i].cor, 10, stdin);
        removerQuebraLinha(jogadores[i].cor);
        sortearMissao(jogadores[i].missao);
        jogadores[i].ataquesBemSucedidos = 0;
        jogadores[i].defesasBemSucedidas = 0;
        jogadores[i].territoriosConquistados = 0;
        jogadores[i].vivo = 1;
    }

    // === Início do jogo ===
    int turno = 0;
    int opcao;

    while (1) {
        struct Jogador *jogadorAtual = &jogadores[turno % MAX_JOGADORES];

        if (!jogadorAtual->vivo) {
            turno++;
            continue; // pula turno se o jogador foi eliminado
        }

        Exibir();
        printf("\n--- TURNO DO EXÉRCITO: %s ---\n", jogadorAtual->cor);
        printf("Missão: %s\n", jogadorAtual->missao);

        printf("\nEscolha o território ATACANTE (0 para sair): ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        if (opcao == 0) break;

        int iAtacante = opcao - 1;

        printf("Escolha o território DEFENSOR: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        int iDefensor = opcao - 1;

        if (iAtacante >= 0 && iAtacante < totalTerritorio &&
            iDefensor >= 0 && iDefensor < totalTerritorio &&
            strcmp(mapa[iAtacante].cor, jogadorAtual->cor) == 0 &&
            iAtacante != iDefensor) {

            Ataque(&mapa[iAtacante], &mapa[iDefensor], jogadorAtual);

            if (!jogadorAtual->vivo) {
                printf("\n### O exército %s foi eliminado! ###\n", jogadorAtual->cor);
            }

            if (verificarMissao(*jogadorAtual)) {
                printf("\n### PARABÉNS, %s! Você completou sua missão: %s ###\n",
                       jogadorAtual->cor, jogadorAtual->missao);
                break;
            }

        } else {
            printf("Jogada inválida! Escolha um território seu e um inimigo.\n");
        }

        turno++;
    }

    liberarMemoria();
    printf("\n=== Fim do jogo ===\n");
    return 0;
}
