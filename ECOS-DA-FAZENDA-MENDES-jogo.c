#include <stdio.h>
#include <string.h>
#include <stdlib.h>//transforma string em num
#include <time.h> //Pra fazer timer
#include <stdbool.h> //Permite deixar True ou False
 
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
    bool coletado, utilizado;
};
 
struct Ambiente {
    int id; //8 locais
    char nome[50];
    char descricao[300];
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
 
void mostrarCarta() {
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
 
void MostrarPrologo() {
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
 
    if (jogador.localAtual == 0) { //Quintal
        printf("VA PARA CASA, VA PARA ARVORE, VASCULHE A CAIXA, ABRA A PORTA");
    }
    else if (jogador.localAtual == 1) { //Salão principal
    }
    else if (jogador.localAtual == 2) { //Cozinha
    }
    else if (jogador.localAtual == 3) { //Corredor
    }
    else if (jogador.localAtual == 4) { //Biblioteca
    }
    else if (jogador.localAtual == 5) { //Banheiro
    }
    else if (jogador.localAtual == 6) { //Quarto
    }
    else if (jogador.localAtual == 7) { //Laboratorio
    }
}
 
void aplicarDano(struct Player *jogador, int dano) {
    jogador->vida -= dano;//A seta (->) acessa a vida do jogador atraves do ponteiro
 
    if (jogador->vida < 0) {
        jogador->vida = 0;//Impede que a vida fique negativa
    }
} //aplicarDano(&jogador, 20); --> chama assim
 
void mostrarAmbiente(struct Player jogador, struct Ambiente *ambientes) {
    int i;
    
    for(i = 0; i < 8; i++){
        if (jogador.localAtual == ambientes[i].id) {
            printf("================%s===============\n\n %s %s \n", ambientes[0].nome, ambientes[i].arteASCII, ambientes[i].descricao);
        /////////TO-DO função para indentificar as saídas ////////////////
        //Se escrever va para casa, ela vai ta trancada
        //Se escreve va para arvore cai um galho na sua cabeça e perde 10 de vida
        //Se escrever vasculhe a caixa de ferramentas, acha a chave
        //E deve escrever após, abre a porta
        }
    }
}

//COMANDOS : VA, OLHAR, PEGUE, MAPA, BUSCAR, INVENTARIO, ABRIR, SALVAR
void iniciarJogo(struct Player *jogador, struct Ambiente *ambientes) {
 
    ambientes[0].id = 0;
    strcpy(ambientes[0].nome,"QUINTAL");
    strcpy(ambientes[0].descricao,
        "\nVoce esta no quintal da Fazenda Mendes.\n"
        "A casa principal esta diante de voce.\n"
        "Uma janela tem a luz acessa, mas fraca.\n"
        "Uma arvore antiga se encontra ao lado da casa.\n"
        "E uma caixa de ferramenta do outro lado.\n"
 
          );
    strcpy(ambientes[0].arteASCII,
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
    ambientes[0].saidas[0] = 2;
    ambientes[0].saidas[1] = -1;
    ambientes[0].saidas[2] = -1;
    ambientes[0].saidas[4] = -1;
    ambientes[0].visitado = true;
    ambientes[0].bloqueado = false;
 
    ambientes[1].id = 1;
    strcpy(ambientes[1].nome,"Sala principal");
    strcpy(ambientes[1].descricao,"descrição");
    strcpy(ambientes[1].arteASCII,"x");
    ambientes[1].saidas[0] = -1;
    ambientes[1].saidas[1] = -1;
    ambientes[1].saidas[2] = -1;
    ambientes[1].saidas[4] = -1;
    ambientes[1].visitado = false;
    ambientes[1].bloqueado = false;
 
    ambientes[2].id = 2;
    strcpy(ambientes[2].nome,"Cozinha");
    strcpy(ambientes[2].descricao,"descrição");
    strcpy(ambientes[2].arteASCII,"x");
    ambientes[2].saidas[0] = -1;
    ambientes[2].saidas[1] = -1;
    ambientes[2].saidas[2] = -1;
    ambientes[2].saidas[4] = -1;
    ambientes[2].visitado = false;
    ambientes[2].bloqueado = false;
 
    ambientes[3].id = 3;
    strcpy(ambientes[3].nome,"Corredor");
    strcpy(ambientes[3].descricao,"descrição");
    strcpy(ambientes[3].arteASCII,"x");
    ambientes[3].saidas[0] = -1;
    ambientes[3].saidas[1] = -1;
    ambientes[3].saidas[2] = -1;
    ambientes[3].saidas[4] = -1;
    ambientes[3].visitado = false;
    ambientes[3].bloqueado = false;
 
    ambientes[4].id = 4;
    strcpy(ambientes[4].nome,"Biblioteca");
    strcpy(ambientes[4].descricao,"descrição");
    strcpy(ambientes[4].arteASCII,"x");
    ambientes[4].saidas[0] = -1;
    ambientes[4].saidas[1] = -1;
    ambientes[4].saidas[2] = -1;
    ambientes[4].saidas[4] = -1;
    ambientes[4].visitado = false;
    ambientes[4].bloqueado = false;
 
    ambientes[5].id = 5;
    strcpy(ambientes[5].nome,"Banheiro");
    strcpy(ambientes[5].descricao,"descrição");
    strcpy(ambientes[5].arteASCII,"x");
    ambientes[5].saidas[0] = -1;
    ambientes[5].saidas[1] = -1;
    ambientes[5].saidas[2] = -1;
    ambientes[5].saidas[4] = -1;
    ambientes[5].visitado = false;
    ambientes[5].bloqueado = false;
 
    ambientes[6].id = 6;
    strcpy(ambientes[6].nome,"Quarto do Augusto");
    strcpy(ambientes[6].descricao,"descrição");
    strcpy(ambientes[6].arteASCII,"x");
    ambientes[6].saidas[0] = -1;
    ambientes[6].saidas[1] = -1;
    ambientes[6].saidas[2] = -1;
    ambientes[6].saidas[4] = -1;
    ambientes[6].visitado = false;
    ambientes[6].bloqueado = false;
 
    ambientes[7].id = 7;
    strcpy(ambientes[7].nome,"Laboratorio");
    strcpy(ambientes[7].descricao,"descrição");
    strcpy(ambientes[7].arteASCII,"x");
    ambientes[7].saidas[0] = -1;
    ambientes[7].saidas[1] = -1;
    ambientes[7].saidas[2] = -1;
    ambientes[7].saidas[4] = -1;
    ambientes[7].visitado = false;
    ambientes[7].bloqueado = false;

    strcpy(jogador->nome, "Robson"); //Define o nome do protagonista
    jogador->vida = 100; //Vida inicial
    jogador->localAtual = 0; //Comeca no quintal
    jogador->qtd_itens = 0; //Inventario vazio
    mostrarAmbiente(*jogador, ambientes);
    //salvarJogo("arquivo.txt", *jogador); //Cria um arquivo caso ele não exista.
    //carregarJogo("arquivo.txt", jogador); //carrega o jogo

    int comecar = 0;
    do {
        printf("Digite 1 para comecar o jogo: ");
        scanf("%d", &comecar);
        limparBuffer();
 
        MostrarPrologo();
 
    } while(comecar != 1);
 
  

 
}
 
void jogarQuintal(struct Player *jogador, struct Ambiente *ambiente, struct Item *chave) {
    char comando[100];
    int caiuGalho = 0;
 
    while (jogador->localAtual == 0 && jogador->vida > 0) {
 
        printf("\nOK, "); // Exibe a mensagem OK na tela
        fgets(comando, sizeof(comando), stdin); // Le o comando digitado pelo jogador e armazena na string comando
        comando[strcspn(comando, "\n")] = '\0'; // Remove o Enter (\n) da string, substituindo pelo fim da string (\0)
 
        if (strcmp(comando, "VA PARA CASA") == 0 ||strcmp(comando, "va para casa") == 0 ||strcmp(comando, "Va para casa") == 0) {
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
            if (chave->coletado = false) {
                printf("\nVoce encontrou uma chave!\n");
                chave->coletado = true;
                //adicionar ao inventario
                
            }
            else {
                printf("\nNão tem mais nada.\n");
            }
        }
 
        else if (strcmp(comando, "ABRA A PORTA") == 0 ||strcmp(comando, "abra a porta") == 0 ||strcmp(comando, "Abra a porta") == 0) {
            //temChave não foi criado
            int temChave =1; //variavel temporaria////////////////
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
            mostrarAmbiente(*jogador, ambiente);
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


int salvarJogo(char *caminho, struct Player jogador){

FILE *arquivo = fopen(caminho, "w");

if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }
    //nome;vida;localAtual;qtd_itens;inventario;
    fprintf(arquivo,"%s;%d;%d;%d;",jogador.nome, jogador.vida, jogador.localAtual, jogador.qtd_itens);
     int i;
if(jogador.qtd_itens > 0){
    for(i = 0; i < jogador.qtd_itens; i++){
        
        fprintf(arquivo,"%d;", jogador.inventario[i]);
    }
}

fclose(arquivo);
return 1;
}

int carregarJogo(char *caminho, struct Player *jogador){
    FILE *arquivo = fopen(caminho, "r");

    if(arquivo == NULL){
        printf("Nenhum arquivo encontrado");
        return 0;
    }

    if(fscanf(arquivo,"%49[^;];%d;%d;%d;", jogador->nome, &jogador->vida, &jogador->localAtual, &jogador->qtd_itens) != 4){
        printf("Arquivo de save corrompido ou vazio!\n");
        return 0;
    }

    for (int i = 0; i < jogador->qtd_itens; i++) {
        fscanf(arquivo, "%d;", &jogador->inventario[i]);
    }

    fclose(arquivo);
    return 1;
}
 
int main() {
 
    struct Player jogador;
    struct Ambiente ambientes[8];
    struct Item chave;
    chave.id = 1;
    strcpy(chave.nome, "Chave Principal");
    strcpy(chave.descricao, "Pode ser utilizada para abrir a porta principal");
    chave.coletado = false;
    chave.utilizado = false;
 
 
    mostrarTitulo();
    iniciarJogo(&jogador, ambientes);
  
    //TO-DO fazer função jogar ambiente - que indentifica onde o
    // o player está e com isso ele indentifica os desafios///////
    //FASE 1
    jogarQuintal(&jogador, ambientes, &chave);
 
    return 0;
}
