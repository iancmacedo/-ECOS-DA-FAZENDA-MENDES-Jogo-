#include <stdio.h>
#include <string.h>
#include <time.h> //Pra fazer timer
#include <conio.h>//será utilizada para permitir que o jogador digite durante o timer sem que o programa fique parado esperando o Enter.
#include <stdbool.h> //Permite deixar True ou False

//                            banheiro[5]
//                                |
//Entrada[0] ___ salão[1] ___corredor[3] __________Quarto[6]_____Laboratório[7]
//                   |               |
//              cozinha[2]    biblioteca[4]  

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
    char descricao[500];
    char arteASCII[800];
    int saidas[4]; //Norte, Sul, Leste, Oeste
    bool visitado, bloqueado; //Os 7 ambientes tem que ser visitados para liberar o enigma do ultimo
};
 
struct Enigma {
    int id;
    char descricao[100];
    char resposta[100];
    bool resolvido;
};

void jogarQuintal(struct Player *jogador, struct Ambiente *ambientes, struct Item *itens) {
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
            if (itens->coletado == false) {
                printf("\nVoce encontrou uma chave!\n");
                itens->coletado = true;
                //adicionar ao inventario
                
            }
            else {
                printf("\nNão tem mais nada.\n");
            }
        }
 
        else if (strcmp(comando, "ABRA A PORTA") == 0 ||strcmp(comando, "abra a porta") == 0 ||strcmp(comando, "Abra a porta") == 0) {
            
            if (itens->coletado == true) {
                printf("\nVoce utiliza a chave.\n");
                printf("A porta se abre lentamente...\n");
                itens->utilizado = true;
                
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
            mostrarAmbiente(jogador->localAtual, ambientes);
        }
 
        else {
            printf("\nComando invalido!\n");
        }

        ambientes[0].visitado = true;
    }
}

void jogarSala(struct Player *jogador, struct Ambiente *ambientes, struct Item *itens){ 
    char comando[100];
    int tocar = 0;
    int examinar = 0;

    while (jogador->localAtual == 1 && jogador->vida > 0){//voce pode examinar as manchas na parede
 
        printf("\nOK, "); // Exibe a mensagem OK na tela
        fgets(comando, sizeof(comando), stdin); // Le o comando digitado pelo jogador e armazena na string comando
        comando[strcspn(comando, "\n")] = '\0'; // Remove o Enter (\n) da string, substituindo pelo fim da string (\0)

        if (strcmp(comando, "VA PARA MESA DE JANTAR") == 0 ||strcmp(comando, "va para mesa de jantar") == 0 ||strcmp(comando, "Va para mesa de jantar") == 0) {
            //imagem da mesa
            printf("\nVoce se aproxima da mesa.\n");
            printf("Nela ha as mesmas manchas da parede.\n");
        }
 
        else if (strcmp(comando, "VA PARA COMODA") == 0 ||strcmp(comando, "va para comoda") == 0 ||strcmp(comando, "Va para comoda") == 0) {
            printf("\nVoce se aproxima da comoda.\n");
            printf("Nela ha um retrato da familia Mendes.\n");
            //imagem da comoda
        }
 
        else if (strcmp(comando, "EXAMINE O RETRATO") == 0 ||strcmp(comando, "examine o retrato") == 0 ||strcmp(comando, "Examine o retrato") == 0) {
            printf("\nVoce olha atras dele, e vem uma anotação\n");
            puts("O que está debaixo desta casa nunca deveria ter sido trazido para a superfície.\n"
                "Se os alarmes começarem, não tente correr. Descubra como desligá-los"
                );
           //mostre um retrato
        }

        else if (strcmp(comando, "VA PARA O ARMARIO") == 0 ||strcmp(comando, "va para o armario") == 0 ||strcmp(comando, "Va para o armario") == 0) {
            
            if (itens->coletado == false) {
                printf("\nVoce abre o armario e ve algumas baratas passando dentro dele");
                printf("E logo abaixo voce encontra uma chave enferrujada.\n");
                itens->coletado = true;
            }

            else {
                printf("\nNao ha mais nada no armario.\n");
            }
        }

        else if (strcmp(comando, "EXAMINE AS MANCHAS") == 0 ||strcmp(comando, "examine as manchas") == 0 ||strcmp(comando, "Examine as manchas") == 0) {
            if(examinar == 0){
                printf("\nVoce chega perto das manchas que são bem escuras e tem o cheiro ruim.\n");
                printf("Voce nunca viu isso antes. Deseja tocar 1(SIM) 2(NAO).\n");
                scanf("%d",&tocar);
                getchar(); //Consome o Enter que ficou no buffer de entrada.

                if(tocar == 1){
                    printf("\nVocê toca.\n");
                    printf("A PELE DO SEU DEDO QUEIMA.(PERDE 10 DE VIDA)\n");
                    aplicarDano(jogador, 10);
                }

                else{ //se não toca na 
                    printf("\nVoce se afasta.\n");
                }

                puts("Nesse momento, Voce escuta passos pesados no andar superior.\n"
                    "Uma voz masculina rouca ecoa pelo corredor: Tem alguém mexendo nas minhas coisas?\n"
                    "É Augusto Mendes.\n"
                    );

                    printf("\nVoce tem 20 segundos para se esconder!\n");
                    printf("\nLugares disponiveis:\n");
                    printf("- ESCONDA ATRAS DO ARMARIO\n");
                    printf("- ESCONDA EMBAIXO DA MESA\n");

                    time_t inicio = time(NULL);// Registra o horario atual e inicia a contagem dos 20 segundos
                    int tempoRestante = 20;// Variavel que armazena o tempo restante
                    int pos = 0;// Posicao atual do vetor que armazena o comando digitado
                    int tecla;// Armazena a tecla pressionada pelo jogador
                    int escondido = 0;// Indica se o jogador conseguiu se esconder (0 = nao, 1 = sim)
                    char esconder[100] = "";// Vetor que armazena o comando digitado pelo jogador

                    printf("\nDigite seu comando: ");

                    while (difftime(time(NULL), inicio) < 20 && escondido == 0) {// Continua enquanto nao passarem 20 segundos e o jogador nao estiver escondido
                        if (kbhit()) {// Verifica se alguma tecla foi pressionada
                            tecla = getch(); // Captura a tecla pressionada sem precisar apertar ENTER

                            if (tecla == '\r') {// Verifica se o jogador apertou ENTER
                                esconder[pos] = '\0';// Finaliza a string colocando o caractere nulo

                                // Verifica se o jogador escolheu se esconder atras do armario
                                if (strcmp(esconder, "ESCONDA ATRAS DO ARMARIO") == 0 || strcmp(esconder, "esconda atras do armario") == 0) {
                                    printf("\n\nVoce se esconde atras do armario.");
                                    escondido = 1;
                                }

                                // Verifica se o jogador escolheu se esconder embaixo da mesa
                                else if (strcmp(esconder, "ESCONDA EMBAIXO DA MESA") == 0 || strcmp(esconder, "esconda embaixo da mesa") == 0) {
                                    printf("\n\nVoce se esconde embaixo da mesa.");
                                    escondido = 1;
                                }

                                else {
                                    printf("\nComando invalido! Tente novamente: ");
                                    pos = 0; // Reinicia a posicao do vetor para receber outro comando
                                    esconder[0] = '\0';// Limpa o conteudo anterior da string
                                }
                            }

                            else if (tecla == '\b' && pos > 0) {// Verifica se o jogador apertou BACKSPACE
                                pos--;
                                esconder[pos] = '\0'; //o texto armazenado também é atualizado quando o jogador apaga uma letra
                                printf("\b \b");// Apaga visualmente o ultimo caractere digitado
                            }

                            else if (pos < 99 && tecla >= 32 && tecla <= 126) { // Verifica se a tecla digitada e um caractere imprimivel e se ainda existe espaco no vetor
                                esconder[pos] = tecla;// Armazena a tecla na posicao atual do vetor
                                pos++;
                                printf("%c", tecla); // Mostra na tela o caractere digitado
                            }
                        }

                        int novoTempo = 20 - (int)difftime(time(NULL), inicio);// Calcula quantos segundos ja passaram desde o inicio

                        if (novoTempo != tempoRestante) {// Verifica se o tempo restante mudou
                            tempoRestante = novoTempo; // Atualiza o tempo restante

                            printf("\nTempo restante: %d segundos\n", tempoRestante);// Exibe quantos segundos ainda restam
                            printf("Comando: %s", esconder);// Exibe novamente o comando que esta sendo digitado
                        }
                    }

                    if (escondido == 0) { 

                        printf("\n\nVoce demorou demais!\n");
                        printf("Augusto encontrou voce.\n");
                        printf("GAME OVER!\n");

                        jogador->vida = 0;
                    }
                    else {
                        printf("\nVoce ve ele, sua pele apresenta manchas escuras e pequenas formações semelhantes a fungos. Ele ainda parece humano, mas seus movimentos são anormais.\n");
                        printf("Augusto nao ve nada e retorna ao segundo andar.\n");
                        printf("Apos essa euforia, se voce ja viu tudo da sala, va para a cozinha\n");
                    }

                examinar = 1;
            }

            else{
                printf("\nVoce ja examinou as manchas.\n");
            }
        }
 
        else if (strcmp(comando, "DICA") == 0) {
            Dica(*jogador);
        }
 
        else if (strcmp(comando, "OLHAR") == 0) {
            mostrarAmbiente(jogador->localAtual, ambientes);
        }
    
        else if (strcmp(comando, "VA PARA A COZINHA") == 0 || strcmp(comando, "va para a cozinha") == 0 || strcmp(comando, "Va para a cozinha") == 0) {

            printf("\nVoce abre a porta.\n");
            jogador->localAtual = 2;
            printf("\nVoce chegou a cozinha!\n");
        }

        else if (strcmp(comando, "VA PARA O CORREDOR") == 0 || strcmp(comando, "va para o corredor") == 0 || strcmp(comando, "Va para o corredor") == 0) {
            printf("\nVoce caminha em direcao ao corredor.\n");
            printf("O ambiente fica cada vez mais escuro...\n");

            jogador->localAtual = 3;

            printf("\nVoce chegou ao corredor!\n");
        }
 
        else {
            printf("\nComando invalido!\n");
        } 

        ambientes[1].visitado = true;

    }
}

void jogarCozinha(struct Player *jogador, struct Ambiente *ambientes){

}
void jogarCorredor(struct Player *jogador, struct Ambiente *ambientes){

}
void jogarBiblioteca(struct Player *jogador, struct Ambiente *ambientes){

}
void jogarBanheiro(struct Player *jogador, struct Ambiente *ambientes){

}
void jogarQuarto(struct Player *jogador, struct Ambiente *ambientes){

}
void jogarLaboratorio(struct Player *jogador, struct Ambiente *ambientes){

}
 
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
        printf("VA PARA MESA DE JANTAR, VA PARA COMODA, EXAMINE O RETRATO, VA PARA O ARMARIO, EXAMINAR MANCHAS, VA PARA A COZINHA, VA PARA O CORREDOR");
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
 
void mostrarAmbiente(int localAtual, struct Ambiente ambientes[]) { //chamar função mostrarAmbiente(jogador.localAtual, ambientes);
    int i;

    for(i = 0; i < 8; i++){
        if (localAtual == ambientes[i].id) {
            printf("================%s===============\n\n %s %s", ambientes[i].nome, ambientes[i].arteASCII, ambientes[i].descricao);
        /////////TO-DO função para indentificar as saídas ////////////////
        //Se escrever va para casa, ela vai ta trancada
        //Se escreve va para arvore cai um galho na sua cabeça e perde 10 de vida
        //Se escrever vasculhe a caixa de ferramentas, acha a chave
        //E deve escrever após, abre a porta
        }
    }
} 

void iniciarJogo(struct Player *jogador, struct Ambiente ambientes[]) {

    //QUINTAL
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
           "                                 /\\\\\n"
           "                                /**\\\\\n"
           "               /\\             /****\\\\\n"
           "              /  \\           /******\\\\\n"
           "         ____/____\\\\____     /********\\\\\n"
           "         |  []    []  |          ||\n"
           "   _     |     __     |          ||\n"
           "  |_|    |____|__|____|          ||\n"
           "    _____________________________\n"
          );
    ambientes[0].saidas[0] = 1;//SALA
    ambientes[0].saidas[1] = -1;
    ambientes[0].saidas[2] = -1;
    ambientes[0].saidas[3] = -1;
    ambientes[0].visitado = true;
    ambientes[0].bloqueado = false;

    //SALA PRINCIPAL
    ambientes[1].id = 1;
    strcpy(ambientes[1].nome,"Sala principal");
    strcpy(ambientes[1].descricao,
        "\nVoce esta na Sala Principal da Casa.\n"
        "No interior, o ambiente parece ter sido abandonado às pressas.\n"
        "Na sua frente uma mesa de jantar permanece posta.\n"
        "A sua esquerda uma comoda coberta de poeira, e a sua direita um armario tambem empoeirado\n"
        "O armario parece estar destrancado.\n"
        "Manchas de uma substância escura se espalham pelas paredes.(elas podem ser examinadas)\n"
        "No canto esquerdo da mesa, tem uma porta que leva a cozinha.\n"
        );
    strcpy(ambientes[1].arteASCII,"x");
    ambientes[1].saidas[0] = 3;//CORREDOR
    ambientes[1].saidas[1] = 0;//ENTRADA
    ambientes[1].saidas[2] = 2;//COZINHA
    ambientes[1].saidas[3] = -1;
    ambientes[1].visitado = false;
    ambientes[1].bloqueado = false;

    //COZINHA
    ambientes[2].id = 2;
    strcpy(ambientes[2].nome,"Cozinha");
    strcpy(ambientes[2].descricao,"descrição");
    strcpy(ambientes[2].arteASCII,"x");
    ambientes[2].saidas[0] = 1;//SALA
    ambientes[2].saidas[1] = -1;
    ambientes[2].saidas[2] = -1;
    ambientes[2].saidas[3] = -1;
    ambientes[2].visitado = false;
    ambientes[2].bloqueado = false;

    //CORREDOR
    ambientes[3].id = 3;
    strcpy(ambientes[3].nome,"Corredor");
    strcpy(ambientes[3].descricao,"descrição");
    strcpy(ambientes[3].arteASCII,"x"
        " ___________________________________________  \n"
        "/              |__|                         \\  \n"
        "|       ___    |__|                ___       | \n"
        "|      |   |   |__|      __       |   |      | \n"
        "|      |   |   |__|     |  |      |   |      | \n" 
        "|      |@  |   |__|     |. |      |  @|      | \n"
        "|      |   |   |  |     |  |      |   |      | \n"
    );
    ambientes[3].saidas[0] = 1; //salao
    ambientes[3].saidas[1] = 4; //biblioteca
    ambientes[3].saidas[2] = 5; //banhero
    ambientes[3].saidas[3] = 6 ; //quarto do augusto
    ambientes[3].visitado = false;
    ambientes[3].bloqueado = false;

    //BIBLIOTECA
    ambientes[4].id = 4;
    strcpy(ambientes[4].nome,"Biblioteca");
    strcpy(ambientes[4].descricao,"descrição");
    strcpy(ambientes[4].arteASCII,"x");
    ambientes[4].saidas[0] = 3;
    ambientes[4].saidas[1] = -1;
    ambientes[4].saidas[2] = -1;
    ambientes[4].saidas[3] = -1;
    ambientes[4].visitado = false;
    ambientes[4].bloqueado = false;

    //BANHEIRO
    ambientes[5].id = 5;
    strcpy(ambientes[5].nome,"Banheiro");
    strcpy(ambientes[5].descricao,"descrição");
    strcpy(ambientes[5].arteASCII,"x");
    ambientes[5].saidas[0] = 3;
    ambientes[5].saidas[1] = -1;
    ambientes[5].saidas[2] = -1;
    ambientes[5].saidas[3] = -1;
    ambientes[5].visitado = false;
    ambientes[5].bloqueado = false;

    //QUARTO
    ambientes[6].id = 6;
    strcpy(ambientes[6].nome,"Quarto do Augusto");
    strcpy(ambientes[6].descricao,"descrição");
    strcpy(ambientes[6].arteASCII,"x");
    ambientes[6].saidas[0] = 3;
    ambientes[6].saidas[1] = 7;
    ambientes[6].saidas[2] = -1;
    ambientes[6].saidas[3] = -1;
    ambientes[6].visitado = false;
    ambientes[6].bloqueado = false;

    //LABORATÓRIO
    ambientes[7].id = 7;
    strcpy(ambientes[7].nome,"Laboratorio");
    strcpy(ambientes[7].descricao,"descrição");
    strcpy(ambientes[7].arteASCII,"x");
    ambientes[7].saidas[0] = 6;
    ambientes[7].saidas[1] = -1;
    ambientes[7].saidas[2] = -1;
    ambientes[7].saidas[3] = -1;
    ambientes[7].visitado = false;
    ambientes[7].bloqueado = false;

    strcpy(jogador->nome, "Robson"); //Define o nome do protagonista
    jogador->vida = 100; //Vida inicial
    jogador->localAtual = 0; //Comeca no quintal
    jogador->qtd_itens = 0; //Inventario vazio
    
    MostrarPrologo();

    mostrarAmbiente(jogador->localAtual, ambientes);

}
 
//void mostrarInventario(const Jogador &jogador);
 
//bool coletarItem(Jogador &jogador, Item &item);
  
//int (quantidade, int direcao);
   
//bool resolverEnigma(Enigma &enigma,const std::string &resposta);
 
int encontrarAmbiente(struct Ambiente *ambientes, int localAtual, int localAlvo, int *visitado){
    visitado[localAtual] = 1;
    printf("Explorando: %d\n", localAtual);
    if(localAtual == localAlvo){
        printf("Sala %d encontrada", localAlvo);
        return 1;
    }

    for(int i = 0; i < 4; i++){
        int proximaSala = ambientes[localAtual].saidas[i];
    
        if(proximaSala != -1 && !visitado[proximaSala] && !ambientes[proximaSala].bloqueado){
            if (encontrarAmbiente(ambientes, proximaSala, localAlvo, visitado)) {
                    return 1; 
            }
        }
    }

    return 0;

}
   
//Comandos mínimos: NORTE SUL LESTE OESTE OLHAR PEGAR TOCHA USAR CHAVE  EXAMINAR ALTAR INVENTARIO  MAPA BUSCAR CRIPTA SALVAR      CARREGAR    AJUDA SAIR
//O programa deverá interpretar strings, validar comandos e tratar operações inválidas.

//salvarJogo("arquivo.txt", *jogador); //Cria um arquivo caso ele não exista.
//carregarJogo("arquivo.txt", jogador); //carrega o jogo

int salvarJogo(char *caminho, struct Player jogador){

    FILE *arquivo = fopen(caminho, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");

        return 0;
    }
    //nome;vida;localAtual;qtd_itens;inventario;//////////enigmas quando implementar//////////////////////////////////
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

//encontrarAmbiente(Ambientes,jogador.localAtual,localAlvo,visitado);
//TERMINAR FUNÇÃO

int main() {

    struct Player jogador;
    struct Ambiente ambientes[8];
    struct Item itens;
    
    itens.id = 1;
    strcpy(itens.nome, "Chave Principal");
    strcpy(itens.descricao, "Pode ser utilizada para abrir a porta principal");
    itens.coletado = false;
    itens.utilizado = false;

    itens.id = 2;
    strcpy(itens.nome, "Chave Enferrujada");
    strcpy(itens.descricao, "Talvez possa abrir alguma cela");
    itens.coletado = false;
    itens.utilizado = false;

    int comecar = 0;
    do {
        printf("Digite 1 para comecar o jogo: ");
        scanf("%d", &comecar);
        limparBuffer();

    } while(comecar != 1);

    mostrarTitulo();
    iniciarJogo(&jogador, ambientes); 
    RealizarAcao(jogador,ambientes);

    while (jogador.vida > 0) {

        if (jogador.localAtual == 0) { //FASE 1
            jogarQuintal(&jogador, ambientes, &itens);
        }

        else if (jogador.localAtual == 1) { //FASE 2
            jogarSala(&jogador, ambientes, &itens);
        }

        else if (jogador.localAtual == 2) { //FASE 3
            jogarCozinha(&jogador, ambientes);
        }

        else if (jogador.localAtual == 3) { //FASE 4
            jogarCorredor(&jogador, ambientes);
        }

        else if (jogador.localAtual == 4) { //FASE 5
            jogarBiblioteca(&jogador, ambientes); //Puzzle com 3 min - cofre
        }

        else if (jogador.localAtual == 5) { //FASE 6
            jogarBanheiro(&jogador, ambientes);
        }

        else if (jogador.localAtual == 6) { //FASE 7
            jogarQuarto(&jogador, ambientes); //Puzzle com 3 min - abrir passagem
        }

        else if (jogador.localAtual == 7) { //FASE 8
            jogarLaboratorio(&jogador, ambientes); //Puzzle com 2 min pra fugir - fuigir da casa
        }

    }

    return 0;
}
