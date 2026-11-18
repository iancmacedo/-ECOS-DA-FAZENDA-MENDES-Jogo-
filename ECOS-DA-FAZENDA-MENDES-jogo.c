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
    char arteASCII[800];
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
    puts("                                                                                                                     \n"
    "#####  ###   ###   ####    ####   ###     #####  ###  ##### ##### #   # ####   ###     #   # ##### #   # ####  #####  ####\n"
    "#     #     #   # #        #   # #   #    #     #   #    #  #     ##  # #   # #   #    ## ## #     ##  # #   # #     #    \n"
    "####  #     #   #  ###     #   # #####    ####  #####   #   ####  # # # #   # #####    # # # ####  # # # #   # ####   ### \n"
    "#     #     #   #     #    #   # #   #    #     #   #  #    #     #  ## #   # #   #    #   # #     #  ## #   # #         #\n"
    "#####  ###   ###  ####     ####  #   #    #     #   # ##### ##### #   # ####  #   #    #   # ##### #   # ####  ##### #### \n"
    "\n\n\n"
        "####  #   #      ###  ###  #   #\n"
        "#   #  # #  #     #  #   # ##  #\n"
        "####    #         #  ##### # # #\n"
        "#   #   #   #     #  #   # #  ##\n"
        "####    #        ### #   # #   #\n"
        "\n\n"
        "Se ficar em duvida digite 'DICA'\n"
    );
}

void mostrarCarta(){
    puts("\n"
    "+--------------------------------------------------+\n"
    "|                                                  |\n"
    "|                 CARTA DE JAILSON                 |\n"
    "|                                                  |\n"
    "| Robson,                                          |\n"
    "|                                                  |\n"
    "| Se voce esta lendo isso, ainda estou vivo.       |\n"
    "| Estou preso na Fazenda Mendes.                   |\n"
    "|                                                  |\n"
    "| A familia nao e mais a mesma.                    |\n"
    "| Existe alguma coisa crescendo dentro deles.      |\n"
    "|                                                  |\n"
    "| O velho Augusto me trancou em um lugar secreto.  |\n"
    "| Ele diz que estou doente, mas eu sei a verdade.  |\n"
    "|                                                  |\n"
    "| Existe um laboratorio debaixo da casa.           |\n"
    "| Foi la que tudo comecou.                         |\n"
    "|                                                  |\n"
    "| Se vier me procurar, tome cuidado.               |\n"
    "| Os alarmes atraem alguma coisa.                  |\n"
    "|                                                  |\n"
    "| Procure o retrato da familia na sala.            |\n"
    "|                                                  |\n"
    "| E Robson...                                      |\n"
    "| Se ouvir alguem chamando meu nome, nao responda. |\n"
    "|                                                  |\n"
    "|                         Seu amigo, Jailson       |\n"
    "+--------------------------------------------------+\n"
    );
}

void MostrarPrologo(){
    puts(
        "\n====================================\n"
        "              PROLOGO                 \n"
        "======================================\n"
        "\n"
        "\nHa dois anos, Jailson desapareceu misteriosamente.\n"
        "Ele havia ido ate a Fazenda Mendes para realizar\n"
        "um servico na propriedade vizinha.\n"
        "\nDesde entao, Robson nunca mais teve noticias do amigo.\n"
        "Ate que, em uma tarde chuvosa, uma carta chegou...\n"
        "\nPressione ENTER para continuar..."
    );
    getchar();
    mostrarCarta();

    puts("\nPressione ENTER para continuar...");
    getchar();

    puts(
        "\nRobson decide ir ate a Fazenda Mendes procurar Jailson.\n"
        "Ao anoitecer, ele chega diante do portao da propriedade.\n"
        "\n"
        "Pressione ENTER para continuar...");
    getchar();

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

void mostrarAmbiente(struct Player jogador) {
    if (jogador.localAtual == 0) {
        puts(
            "\n========== QUINTAL ==========\n\n"
            "                                 /\\\n"
            "                                /**\\\n"
            "               /\\             /****\\\n"
            "              /  \\           /******\\\n"
            "         ____/____\\____     /********\\\n"
            "         |  []    []  |          ||\n"
            "   _     |     __     |          ||\n"
            "  |_|    |____|__|____|          ||\n"
            "    _________________________________\n"
        ); 
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

void iniciarJogo(struct Player *jogador, struct Ambiente *ambientes) {
    //bloco para implementação
    
    /*
    ambientes[0].id = 1;
    ambientes[0].nome = "Quintal";
    ambientes[0].descricao = "descrição";
    ambientes[0].arteASCII = "x";
    ambientes[0].saida = (int[4]){2, -1, -1, -1}; 
    ambientes[0].saida[0] =
    ambientes[1].saida[1] =
    ambientes[2].saida[2] =
    ambientes[3].saida[4] =
    ambientes[0].visitado = true;
    ambientes[0].bloqueado = false;

    ambientes[1].id = 2;
    ambientes[1].nome = "Sala principal";
    ambientes[1].descricao = "Descricao do ambiente 2";
    ambientes[1].arteASCII = "x";
    ambientes[1].saida = (int[4]){-1, 1, -1, -1};
    ambientes[1].visitado = false;
    ambientes[1].bloqueado = false;

    ambientes[2].id = 3;
    ambientes[2].nome = "Conzinha";
    ambientes[2].descricao = "Descricao do ambiente 3";
    ambientes[2].arteASCII = "x";
    ambientes[2].saida = (int[4]){-1, -1, 1, -1};
    ambientes[2].visitado = false;
    ambientes[2].bloqueado = false;

    ambientes[3].id = 4;
    ambientes[3].nome = "Biblioteca";
    ambientes[3].descricao = "Descricao do ambiente 4";
    ambientes[3].arteASCII = "x";
    ambientes[3].saida = (int[4]){-1, -1, -1, 1};
    ambientes[3].visitado = false;
    ambientes[3].bloqueado = false;

    ambientes[4].id = 5;
    ambientes[4].nome = "Corredor";
    ambientes[4].descricao = "Descricao do ambiente 5";
    ambientes[4].arteASCII = "x";
    ambientes[4].saida = (int[4]){-1, -1, -1, -1};
    ambientes[4].visitado = false;
    ambientes[4].bloqueado = false;

    ambientes[5].id = 6;
    ambientes[5].nome = "Quarto de Augusto";
    ambientes[5].descricao = "Descricao do ambiente 6";
    ambientes[5].arteASCII = "x";
    ambientes[5].saida = (int[4]){-1, -1, -1, -1};
    ambientes[5].visitado = false;
    ambientes[5].bloqueado = false;

    ambientes[6].id = 7;
    ambientes[6].nome = "Banhero";
    ambientes[6].descricao = "Descricao do ambiente 7";
    ambientes[6].arteASCII = "x";
    ambientes[6].saida = (int[4]){-1, -1, -1, -1};
    ambientes[6].visitado = false;
    ambientes[6].bloqueado = false;

    ambientes[7].id = 8;
    ambientes[7].nome = "Porão";
    ambientes[7].descricao = "Descricao do ambiente 8";
    ambientes[7].arteASCII = "x";
    ambientes[7].saida = (int[4]){-1, -1, -1, -1};
    ambientes[7].visitado = false;
    ambientes[7].bloqueado = false; */
    
    int comecar = 0;
    do{
    printf("Digite 1 para comecar o jogo: ");
    scanf("%d", &comecar);
    limparBuffer();

    MostrarPrologo();

    } while(comecar != 1);
    
    strcpy(jogador->nome, "Robson"); //Define o nome do protagonista
    jogador->vida = 100; //Vida inicial
    jogador->localAtual = 0; //Comeca no quintal
    jogador->qtd_itens = 0; //Inventario vazio

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

//Comandos mínimos: NORTE SUL LESTE OESTE OLHAR PEGAR TOCHA USAR CHAVE  EXAMINAR ALTAR INVENTARIO  MAPA BUSCAR CRIPTA SALVAR      CARREGAR    AJUDA SAIR
//O programa deverá interpretar strings, validar comandos e tratar operações inválidas.

int main(){

    struct Player jogador;
    struct Ambiente ambientes[8]; //muda de acordo com a quantidade de ambientes.
    struct Item itens[1]; //itens do jogo
    
    mostrarTitulo();
    iniciarJogo(&jogador, ambientes);

    //FASE 1
    jogarQuintal(&jogador);

return 0;
}
