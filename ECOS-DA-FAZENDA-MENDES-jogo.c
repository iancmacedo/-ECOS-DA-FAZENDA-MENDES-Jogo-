#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct Player {
    char nome[10]; //Robson
    int vida; //100
    int localAtual;
    int inventario[10];
    int qtd_itens; //Inicia com 0
};

struct Item {
    int id;
    char nome[50];
    char descricao[100];
    bool coletavel, utilizado;
};

struct Ambiente {
    int id; //8 locais
    char nome[50];
    char descricao[100];
    int saidas[4]; //Norte, Sul, Leste, Oeste
    bool visitado, bloqueado;
};

struct Enigma {
    int id;
    char descricao[100];
    char resposta[100];
    bool resolvido;
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarTitulo() {
    printf("\n");
    printf("#####  ###   ###   ####    ####   ###     #####  ###  ##### ##### #   # ####   ###     #   # ##### #   # ####  #####  ####\n");
    printf("#     #     #   # #        #   # #   #    #     #   #    #  #     ##  # #   # #   #    ## ## #     ##  # #   # #     #\n");
    printf("####  #     #   #  ###     #   # #####    ####  #####   #   ####  # # # #   # #####    # # # ####  # # # #   # ####   ###\n");
    printf("#     #     #   #     #    #   # #   #    #     #   #  #    #     #  ## #   # #   #    #   # #     #  ## #   # #         #\n");
    printf("#####  ###   ###  ####     ####  #   #    #     #   # ##### ##### #   # ####  #   #    #   # ##### #   # ####  ##### ####\n");
    printf("\n");

    printf("\n");
    printf("\n");
    printf("####  #   #      ###  ###  #   #\n");
    printf("#   #  # #  #     #  #   # ##  #\n");
    printf("####    #         #  ##### # # #\n");
    printf("#   #   #   #     #  #   # #  ##\n");
    printf("####    #        ### #   # #   #\n");
    printf("se ficar em duvida digite dica");
    printf("\n");
    

}

void Dica(struct Player jogador) {

    printf("\n========== DICA ==========\n");

    if (jogador.localAtual == 0) {
        printf("VA PARA CASA, VA PARA ARVORE, VASCULHE A CAIXA, ABRA A PORTA");
    }
    else if (jogador.localAtual == 1) {
    }
    else if (jogador.localAtual == 2) {
    }
    else if (jogador.localAtual == 3) {
    }
    else if (jogador.localAtual == 4) {
    }
    else if (jogador.localAtual == 5) {
    }
    else if (jogador.localAtual == 6) {
    }
    else if (jogador.localAtual == 7) {
    }
}

void aplicarDano(struct Player *jogador, int dano) {
    jogador->vida -= dano;//A seta (->) acessa a vida do jogador atraves do ponteiro

    if (jogador->vida < 0) {
        jogador->vida = 0;//Impede que a vida fique negativa
    }
} //aplicarDano(&jogador, 20); --> chama assim

void mostrarCarta(){
    printf("\n");
    printf("+--------------------------------------------------+\n");
    printf("|                                                  |\n");
    printf("|                 CARTA DE JAILSON                 |\n");
    printf("|                                                  |\n");
    printf("| Robson,                                          |\n");
    printf("|                                                  |\n");
    printf("| Se voce esta lendo isso, ainda estou vivo.       |\n");
    printf("| Estou preso na Fazenda Mendes.                   |\n");
    printf("|                                                  |\n");
    printf("| A familia nao e mais a mesma.                    |\n");
    printf("| Existe alguma coisa crescendo dentro deles.      |\n");
    printf("|                                                  |\n");
    printf("| O velho Augusto me trancou em um lugar secreto.  |\n");
    printf("| Ele diz que estou doente, mas eu sei a verdade.  |\n");
    printf("|                                                  |\n");
    printf("| Existe um laboratorio debaixo da casa.           |\n");
    printf("| Foi la que tudo comecou.                         |\n");
    printf("|                                                  |\n");
    printf("| Se vier me procurar, tome cuidado.               |\n");
    printf("| Os alarmes atraem alguma coisa.                  |\n");
    printf("|                                                  |\n");
    printf("| Procure o retrato da familia na sala.            |\n");
    printf("|                                                  |\n");
    printf("| E Robson...                                      |\n");
    printf("| Se ouvir alguem chamando meu nome, nao responda. |\n");
    printf("|                                                  |\n");
    printf("|                         Seu amigo, Jailson       |\n");
    printf("+--------------------------------------------------+\n");
}

void mostrarAmbiente(struct Player jogador) {

    if (jogador.localAtual == 0) {
        printf("\n========== QUINTAL ==========\n\n");

        printf("                                 /\\\n");
        printf("                                /**\\\n");
        printf("               /\\             /****\\\n");
        printf("              /  \\           /******\\\n");
        printf("         ____/____\\____     /********\\\n");
        printf("         |  []    []  |         ||\n");
        printf("   _     |     __     |         ||\n");
        printf("  |_|    |____|__|____|         ||\n");
        printf("    _________________________________\n");

        printf("\nVoce esta no quintal da Fazenda Mendes.\n");
        printf("A casa principal esta diante de voce.\n");
        printf("Uma janela tem a luz acessa, mas fraca.\n");
        printf("Uma arvore antiga se encontra ao lado da casa.\n");
        printf("E uma caixa de ferramenta do outro lado.\n");
        //Se escrever va para casa, ela vai ta trancada
        //Se escreve va para arvore cai um galho na sua cabeça e perde 10 de vida
        //Se escrever vasculhe a caixa de ferramentas, acha a chave
        //E deve escrever após, abre a porta
        
    }
}

void iniciarJogo(struct Player *jogador) {
    int comecar = 0;
    do{
    printf("Digite 1 para comecar o jogo: ");
    scanf("%d", &comecar);
    limparBuffer();
    } while(comecar != 1);
    
    strcpy(jogador->nome, "Robson"); //Define o nome do protagonista
    jogador->vida = 100; //Vida inicial
    jogador->localAtual = 0; //Comeca no quintal
    jogador->qtd_itens = 0; //Inventario vazio

    printf("\n====================================\n");
    printf("           PROLOGO                  \n");
    printf("====================================\n");

    printf("\nHa dois anos, Jailson desapareceu misteriosamente.\n");
    printf("Ele havia ido ate a Fazenda Mendes para realizar\n");
    printf("um servico na propriedade vizinha.\n");

    printf("\nDesde entao, Robson nunca mais teve noticias do amigo.\n");
    printf("Ate que, em uma tarde chuvosa, uma carta chegou...\n");

    printf("\nPressione ENTER para continuar...");
    getchar();

    mostrarCarta();

    printf("\nPressione ENTER para continuar...");
    getchar();

    printf("\nRobson decide ir ate a Fazenda Mendes procurar Jailson.\n");
    printf("Ao anoitecer, ele chega diante do portao da propriedade.\n");

    printf("\nPressione ENTER para continuar...");
    getchar();

    mostrarAmbiente(*jogador);
    
}

void jogarQuintal(struct Player *jogador) {
    char comando[100];
    int temChave = 0;
    int caiuGalho = 0;

    while (jogador->localAtual == 0 && jogador->vida > 0) {

        printf("\nOK, "); // Exibe a mensagem OK na tela
        fgets(comando, sizeof(comando), stdin); // Le o comando digitado pelo jogador e armazena na string comando
        comando[strcspn(comando, "\n")] = '\0'; // Remove o Enter (\n) da string, substituindo pelo fim da string (\0)

        if (strcmp(comando, "VA PARA CASA") == 0 ||strcmp(comando, "va para casa") == 0 ||strcmp(comando, "Va para casa") == 0){
            //imagem da porta
            printf("\nVoce se aproxima da casa.\n");
            printf("A porta principal esta trancada.\n");
        }

        else if (strcmp(comando, "VA PARA ARVORE") == 0 ||strcmp(comando, "va para arvore") == 0 ||strcmp(comando, "Va para arvore") == 0) {
            printf("\nVoce se aproxima da arvore antiga.\n");
            //imagem da arvore

            if (caiuGalho == 0) {
                printf("Um galho cai sobre sua cabeca!\n");
                //imagem com galho caido ao lado
                aplicarDano(jogador, 10);
                caiuGalho = 1;

                printf("Voce perdeu 10 de vida!\n");
                printf("Vida atual: %d\n", jogador->vida);
            }
            else {
                printf("Nao parece haver mais nada aqui.\n");
            }
        }

        else if (strcmp(comando, "VASCULHE A CAIXA") == 0 ||strcmp(comando, "vasculhe a caixa") == 0 ||strcmp(comando, "Vasculhe a caixa") == 0) {
            if (temChave == 0) {
                printf("\nVoce encontrou uma chave enferrujada!\n");
                temChave = 1;
            }
            else {
                printf("\nVoce ja encontrou a chave.\n");
            }
        }

        else if (strcmp(comando, "ABRA A PORTA") == 0 ||strcmp(comando, "abra a porta") == 0 ||strcmp(comando, "Abra a porta") == 0){
            if (temChave == 1) {
                printf("\nVoce utiliza a chave enferrujada.\n");
                printf("A porta se abre lentamente...\n");

                jogador->localAtual = 1;
                printf("\nVoce entrou na sala principal!\n");
            }
            else {
                printf("\nA porta esta trancada. Procure uma chave.\n");
            }
        }

        else if (strcmp(comando, "DICA") == 0) {
            Dica(*jogador);
        }

        else if (strcmp(comando, "OLHAR") == 0) {
            mostrarAmbiente(*jogador);
        }

        else {
            printf("\nComando invalido!\n");
        }
    }
}

//void mostrarInventario(const Jogador &jogador);

//bool coletarItem(Jogador &jogador, Item &item);

//bool moverJogador(Jogador &jogador,const Ambiente ambientes[]);

//int (quantidade, int direcao);

//bool coletarItem(Jogador &jogador, Item &item);

//void examinarObjeto(const Item &item); 

//bool resolverEnigma(Enigma &enigma,const std::string &resposta);

//void salvarJogo(const Jogador &jogador);

//bool carregarJogo(Jogador &jogador);

//Implementar uma função recursiva que determine a existência de um caminho entre dois ambientes. A função deverá verificar o destino, registrar ambientes visitados, explorar conexões recursivamente, impedir ciclos e retornar sucesso ou fracasso.

//Implementar SALVAR e CARREGAR, utilizando arquivos .txt para preservar o estado da partida. Exemplo: JOGADOR=Leonardo VIDA=75 LOCAL=4 INVENTARIO=1,3,5 PORTA_CRIPTA=ABERTA ENIGMA_ALTAR=RESOLVIDO ITEM_2_COLETADO=SIM

//Cada ambiente deverá apresentar descrição e representação ASCII, sem interface gráfica.

//Comandos mínimos: NORTE       SUL         LESTE OESTE       OLHAR       PEGAR TOCHA USAR CHAVE  EXAMINAR ALTAR INVENTARIO  MAPA        BUSCAR CRIPTA SALVAR      CARREGAR    AJUDA SAIR
//O programa deverá interpretar strings, validar comandos e tratar operações inválidas.

int main(){

    struct Player jogador;

    mostrarTitulo();
    iniciarJogo(&jogador);

    //FASE 1
    jogarQuintal(&jogador);


return 0;
}
