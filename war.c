// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

//inclusão de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//constantes globais
#define TERRITORIOS_SUP 5
#define TAM_NOME 30
#define TAM_COR 10
#define MISSAO 5

// Definição da estrutura territorio
struct territorio {
    char nome [TAM_NOME];
    char cor [TAM_COR];
    int tropas;
} territorio;
    
//nova estrutura para ataque
typedef struct ataque {
    int indice_atacante;
    int indice_defensor;
    char resultado[20];
} ataque;

//prototipos das funções
void limparBuffer();
void listardadosterritorios(struct territorio territorios[], int tamanho);
void ataqueterritorio(struct territorio *atacante, struct territorio* defensor);
void atribuirmissao(char* destino, char* missoes[], int totalMissoes);
void verificarMissao(char* missao, struct territorio * mapa, int tamanho);
void liberarMemoria(struct territorio *territorios, struct ataque *ataqueterritorios);
int exibirmenu();

// função pára limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Função para exibir dados dos territórios
void listardadosterritorios(struct territorio territorios[], int tamanho) {
    printf("------------------------------------------\n");
    printf("=====MAPA DO MUNDO - ESTADO ATUAL =====\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio %d: %s (Cor: %s, Tropas: %d)\n", i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
        printf("                                             \n");
}

//Função de ataque
void ataqueterritorio(struct territorio *atacante, struct territorio* defensor) {

     printf("Iniciando ataque do territorio %s contra o territorio %s...\n", atacante->nome, defensor->nome);
     printf("                                             \n");
     int time_seed = (int)time(NULL);
     srand(time_seed);
     int ataque_valor = rand() % 5 + 1; 
     int defesa_valor = rand() % 5 + 1; // Valor aleatório entre 1 a 5
        printf("                               \n");
        printf("---  RESULTADO DA BATALHA  ---:\n");
        printf("O atacante %s rolou o dado e tirou: %d\n", atacante->nome, ataque_valor);
        printf("O defensor %s rolou o dado e tirou: %d\n", defensor->nome, defesa_valor);    
     if (ataque_valor > defesa_valor) {
         printf("ATAQUE BEM SUCEDIDO! O territorio %s venceu o territorio %s.\n", atacante->nome, defensor->nome);
         defensor->tropas -= 1; // Reduz o número de tropas do defensor
         if (defensor->tropas < 0) {
             defensor->tropas = 0; //Garante que o número de tropas não seja negativo
         }
         //Se ficar sem tropas, o territorio e conquistado
          if (defensor->tropas == 0) {
             printf("VITORIA !!! O territorio %s foi conquistado pelo exercito %s!\n", defensor->nome, atacante->cor);
             defensor->tropas = 0; // O novo dono coloca 1 tropa no território conquistado
             atacante->tropas -= 1; // O atacante perde 1 tropa para conquistar
             if (atacante->tropas < 0 ) {
                 atacante->tropas = 1; // Garante que o número de tropas não seja negativo
             }
         }
     } else {
         printf("ATAQUE FALHOU! O territorio %s defendeu com sucesso contra o territorio %s.\n", defensor->nome, atacante->nome);
         printf("O territorio %s perdeu 1 tropa no ataque.\n", atacante->nome);
         atacante->tropas -= 1; // Reduz o número de tropas do atacante
         if (atacante->tropas < 1) {
             atacante->tropas = 1; // Garante que o número de tropas não seja negativo
         };
         printf("                  \n");
         printf("Tropas restantes do territorio %s: %d\n", atacante->nome, atacante->tropas);
         printf("                  \n");
         printf("Pressione ENTER para exibir o menu de opcoes\n");
         getchar(); // Espera o usuário pressionar Enter
     }
}

//função atribuir missão
void atribuirmissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
    printf("------------------------------------------\n");
    printf("          MISSAO ATRIBUIDA                \n");
    printf("------------------------------------------\n");
    printf("Sua missao e conquistar o territorio: %s\n", destino);
    printf("Pressione ENTER para continuar\n");
    getchar(); // Espera o usuário pressionar Enter
}

//função verificar missão
void verificarmissao(char* missao, struct territorio * mapa, int tamanho) {
    printf("------------------------------------------\n");
    printf("        VERIFICACAO DE MISSAO            \n");
    printf("------------------------------------------\n");
    int encontrada = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].nome, missao) == 0 && mapa[i].tropas > 0) {
            encontrada = 1;
            break;
        }
    }
    if (encontrada) {
        printf("Missao cumprida! Parabens! Voce venceu o territorio %s.\n", missao);
    } else {
        printf("Missao nao cumprida. continue tentando! Voce nao venceu o territorio %s.\n", missao);
    }
    printf("Pressione ENTER para exibir o menu de opcoes\n");
    getchar(); // Espera o usuário pressionar Enter
}

// Função principal 
int main() {
    //declaração de variáveis
    struct territorio *territorios;
    struct ataque *ataqueterritorios;

    territorios = (struct territorio *) malloc (TERRITORIOS_SUP * sizeof (struct territorio));
    ataqueterritorios = (struct ataque *) malloc (sizeof (struct ataque));
 //alocação dinâmica de memória
    if (territorios == NULL || ataqueterritorios == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return 1; //retorna 1 em caso de erro.
    }

    int totalterritorios = 0;
    int totalataques = 0;
    int totalmissoes = 0;
    int opcao;

    //cabeçalho do programa
    printf("---------------------------------------------\n");
    printf("             PROJETO WAR PARTE 1\n");
    printf("---------------------------------------------\n");
    printf("Cadastro de Territorios:\n");
    printf("                                             \n");

    //laço principal
    for(int i = 0; i < TERRITORIOS_SUP; i++)
    {
        printf("Digite o nome do territorio %d: ", i + 1);
        fgets(territorios[i].nome, TAM_NOME, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0; 
        printf("Digite a cor do territorio %d: ", i + 1);
        fgets(territorios[i].cor, TAM_COR, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0; 
        printf("Digite o numero de tropas no territorio %d: ", i + 1);
        scanf("%d", &territorios[i].tropas);
        printf("---------------------------------------------\n");
        printf("                                             \n");

        limparBuffer(); // Limpa o buffer de entrada
    }
 //comando para exibir o menu de opções
    printf("Cadastro concluido com sucesso!\n");
    printf("Aperte Enter para exibir o menu de opcoes\n");
    getchar(); // Espera o usuário pressionar Enter

    //le a opção do usuário
    do {
        printf("                             \n");
        printf("============ MENU =============\n");
        printf("                             \n");
        printf("1. Listar dados do territorio\n");
        printf("2. Atribuir missao\n");
        printf("3. Realizar ataques\n");
        printf("4. Verificar missao\n");
        printf("0. Sair\n");
        printf("-----------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
    
    limparBuffer(); // Limpa o buffer de entrada
    
   switch (opcao) {
        case 1: // Listar dados dos territórios
            listardadosterritorios(territorios, TERRITORIOS_SUP);
            break;
        case 2: // Atribuir missão
        {
            char* missoes[MISSAO] = {
                "Territorio 1",
                "Territorio 2",
                "Territorio 3",
                "Territorio 4",
                "Territorio 5"
            };
            char missao_atribuida[TAM_NOME];
            atribuirmissao(missao_atribuida, missoes, MISSAO);
            totalmissoes++;
            break;
        }   
        case 3:// Realizar ataques
        {
            int atacante_idx, defensor_idx;
            printf("                             \n");
            printf("------FASE DE ATAQUE-------\n");
            printf("Digite o territorio atacante (1 a %d): ", TERRITORIOS_SUP);
            scanf("%d", &atacante_idx);
            printf("Digite o territorio defensor (1 a %d): ", TERRITORIOS_SUP);
            scanf("%d", &defensor_idx);
            if (atacante_idx < 1 || atacante_idx > TERRITORIOS_SUP || defensor_idx < 1 || defensor_idx > TERRITORIOS_SUP) {
                printf("Indices invalidos. Tente novamente.\n");
            } else {
                ataqueterritorio(&territorios[atacante_idx - 1], &territorios[defensor_idx - 1]);
                totalataques++;
            }
            getchar(); // Espera o usuário pressionar Enter
            break;
        }
        case 4: // Verificar missão
        {
            char missao_verificar[TAM_NOME];
            printf("Digite o nome do territorio da sua missao para verificar: ");
            fgets(missao_verificar, TAM_NOME, stdin);
            missao_verificar[strcspn(missao_verificar, "\n")] = 0; 
            verificarmissao(missao_verificar, territorios, TERRITORIOS_SUP);
            break;
        }
        case 0:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    // Função para liberar memória alocada
void liberarMemoria(struct territorio *territorios, struct ataque *ataqueterritorios); {
    free(territorios);
    free(ataqueterritorios);
    printf("Memoria liberada. jogo encerrado com sucesso!\n");
    return 0;
    }
}
