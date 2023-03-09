/**      @file: 150015585_trabalho03.c
 *     @author: Luan Mendes Gonçalves Freitas
 * @disciplina: Algoritmos e Programação de Computadores
 *      @turma: G
 *      @trabalho 3 - Jogo da Forca 3.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[20];
    int pontuacao;
} tipoJogador;
FILE * criarArquivoTexto(char* arquivo) {
    FILE *fp = fopen(arquivo, "wb+");

    if (fp == NULL) {
        printf("Não foi possível abrir \"%s\".\n", arquivo);
        return NULL;
    } else {
        return fp;
    }

}
int comparar(const void * p1, const void * p2) {
    tipoJogador * q1 = (tipoJogador *) p1;
    tipoJogador * q2 = (tipoJogador *) p2;

    return q2->pontuacao - q1->pontuacao; /* ordem decrescente (maior para menor) */
}
void salvar(FILE * arquivoBinario, FILE *arquivoFruta, FILE *arquivoComputacao, FILE *arquivoPaises,
            char palavraSecreta1[][5], char palavraSecreta2[][8],
            char palavraSecreta3[][13], tipoJogador *listaJogadores) {

    int i, j, nivel, quantidade=0;

    for (i = 0; i < 10; i++) {
        if (listaJogadores[i].pontuacao > 0) {
            printf("%d - %-20s  -> %-5d\n", i + 1, listaJogadores[i].nome,
                   listaJogadores[i].pontuacao);
        }
    }

    for(i=0; i<50; i++) {
        if(listaJogadores[i].pontuacao > 0) {
            quantidade++;
        }
    }


    fwrite(listaJogadores, sizeof(tipoJogador), quantidade, arquivoBinario);

    if (arquivoFruta != NULL) {
        for (i = 1; i <= 1; i++) {
            fscanf(arquivoFruta, "%d\n", &nivel);
            for (j = 0; j < 10; j++) {
                if (nivel == 1) {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta3[j]);

                }
            }

        }

    }

    if (arquivoComputacao != NULL) {

        for (i = 1; i <= 3; i++) {
            fscanf(arquivoComputacao, "%d\n", &nivel);
            for (j = 10; j < 20; j++) {
                if (nivel == 1) {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta3[j]);

                }
            }

        }
    }

    if (arquivoPaises != NULL) {

        for (i = 1; i <= 3; i++) {
            fscanf(arquivoPaises, "%d\n", &nivel);
            for (j = 20; j < 30; j++) {
                if (nivel == 1) {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta3[j]);

                }
            }

        }
    }

}
void iniciarBinario(FILE *arquivo, tipoJogador *listaJogadores, int *vazio) {
    void copiarVetor(char *VetorSubstituir, char *vetorTroca);
    void limparErro(char *pVetor, int pTamanho);
    int i = 0, tamanhoArquivo, quantidade;
    if (arquivo != NULL) {
        for (i = 0; i < 50; i++) {
            limparErro(listaJogadores[i].nome, 20);
            listaJogadores[i].pontuacao = 0;
        }

        fseek(arquivo, 0, SEEK_END); /* vai para o final do arquivo */
        tamanhoArquivo = ftell(arquivo); /* diz a posicao do cursor no final do arquivo (qtd bytes) */
        fseek(arquivo, 0, SEEK_SET); /* volta para o comeco do arquivo */

        quantidade = (tamanhoArquivo / sizeof(tipoJogador));
        if (tamanhoArquivo == 0) {
            *(vazio) = 1;
        } else {
            fread(listaJogadores, sizeof(tipoJogador), quantidade, arquivo);
            qsort(listaJogadores, quantidade, sizeof(tipoJogador), comparar);
        }

    }

}
FILE * abrirArquivoBinario(char* arquivo) {
    FILE *fp = fopen(arquivo, "r+b");

    if (fp == NULL) {

        fp = fopen(arquivo, "wb+");
        if (fp == NULL) {
            printf("Não foi possível criar \"%s\".\n", arquivo);
            return NULL;
        } else {
            return fp;
        }



    } else {
        return fp;
    }

}
char gerarLetraComputador() {
    int i;
    char alfabetico[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'
    };

    srand(time(NULL));
    i = rand() % 26;

    return alfabetico[i];
}
void copiarVetor(char *VetorSubstituir, char *vetorTroca) {
    int i;
    for (i = 0; vetorTroca[i] != '\0'; ++i) {
        VetorSubstituir[i] = vetorTroca[i];
    }
    *(VetorSubstituir + i) = '\0';
}
void gerarForca(char forca[][10], int nivel) {
    void copiarVetor(char *VetorSubstituir, char *vetorTroca);
    switch (nivel) {
    case 6:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|");
        copiarVetor(forca[3],"|");
        copiarVetor(forca[4],"|");
        copiarVetor(forca[5],"========");
        break;
    case 5:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"|");
        copiarVetor(forca[4],"|");
        copiarVetor(forca[5],"========");
        break;

    case 4:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"|  |");
        copiarVetor(forca[4],"|");
        copiarVetor(forca[5],"========");

        break;
    case 3:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"| /|");
        copiarVetor(forca[4],"|");
        copiarVetor(forca[5],"========");
        break;

    case 2:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"| /|\\");
        copiarVetor(forca[4],"| ");
        copiarVetor(forca[5],"========");
        break;

    case 1:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"| /|\\");
        copiarVetor(forca[4],"| /");
        copiarVetor(forca[5],"========");
        break;

    default:
        copiarVetor(forca[0],"+------+");
        copiarVetor(forca[1],"|--|");
        copiarVetor(forca[2],"|  o");
        copiarVetor(forca[3],"| /|\\");
        copiarVetor(forca[4],"| / \\");
        copiarVetor(forca[5],"========");

        break;
    }
}

void imprimirForcaSimples(char forca1[][10]) {
    int i;
    printf("%-30s\n", "jogador");
    for (i = 0; i < 6; i++) {
        printf("%-30s\n", forca1[i]);
    }
}

void imprimirForcaDupla(char forca1[][10], char forca2[][10]) {

    int j;

    printf("%-30s%-30s\n", "jogador", "computador");
    for (j = 0; j < 6; j++) {
        printf("%-30s%-30s\n", forca1[j], forca2[j]);
    }

}
void minuscula(char palavra[]) {
    int tamanhoVetor(char *pVetor);
    int i;
    for (i = 0; i < tamanhoVetor(palavra); i++) {
        if (palavra[i] > 64 && palavra[i] < 91) { /* converter palavra   maiscula para minuscula */
            palavra[i] += 32;
        }
    }
}
FILE * abrirArquivoTexto(char *arquivo) {
    FILE *fp = fopen(arquivo, "r+");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo\n");
        return NULL;
    } else {
        return fp;
    }
}
void iniciarTexto(FILE *arquivoFruta, FILE *arquivoComputacao,
                  FILE *arquivoPaises, char palavraSecreta1[][5],
                  char palavraSecreta2[][8], char palavraSecreta3[][13]) {
    int i, j, nivel;
    if (arquivoFruta != NULL) {
        for (i = 1; i <= 3; i++) {
            fscanf(arquivoFruta, "%d\n", &nivel);
            for (j = 0; j < 10; j++) {
                if (nivel == 1) {
                    fscanf(arquivoFruta, "%s\n", palavraSecreta1[j]);
                    minuscula(palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fscanf(arquivoFruta, "%s\n", palavraSecreta2[j]);
                    minuscula(palavraSecreta2[j]);
                } else {
                    fscanf(arquivoFruta, "%s\n", palavraSecreta3[j]);
                    minuscula(palavraSecreta3[j]);
                }
            }

        }
    }

    if (arquivoComputacao != NULL) {
        for (i = 1; i <= 3; i++) {
            fscanf(arquivoComputacao, "%d\n", &nivel);
            for (j = 10; j < 20; j++) {
                if (nivel == 1) {
                    fscanf(arquivoComputacao, "%s\n", palavraSecreta1[j]);
                    minuscula(palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fscanf(arquivoComputacao, "%s\n", palavraSecreta2[j]);
                    minuscula(palavraSecreta2[j]);
                } else {
                    fscanf(arquivoComputacao, "%s\n", palavraSecreta3[j]);
                    minuscula(palavraSecreta3[j]);
                }
            }

        }
    }

    if (arquivoPaises != NULL) {
        for (i = 1; i <= 3; i++) {
            fscanf(arquivoPaises, "%d\n", &nivel);
            for (j = 20; j < 30; j++) {
                if (nivel == 1) {
                    fscanf(arquivoPaises, "%s\n", palavraSecreta1[j]);
                    minuscula(palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fscanf(arquivoPaises, "%s\n", palavraSecreta2[j]);
                    minuscula(palavraSecreta2[j]);
                } else {
                    fscanf(arquivoPaises, "%s\n", palavraSecreta3[j]);
                    minuscula(palavraSecreta3[j]);
                }
            }

        }
    }
}
int main() {
    void jogar(char palavraSecreta1[][5], char palavraSecreta2[][8],
               char palavraSecreta3[][13], int escolha,
               tipoJogador *listaJogadores);
    void configurar();
    void rank();
    void boasVindas();
    void limparTela();
    int opcaoMenu;
    char nomeArquivoFruta[30] = "frutas.txt";
    char nomeArquivoComputacao[30] = "computacao.txt";
    char nomeArquivopaises[30] = "paises.txt";

    char nomeArquivoRanking[30] = "ranking.bin";
    FILE *arquivoRanking;

    FILE *arquivoFruta;
    FILE *arquivoComputacao;
    FILE *arquivoPaises;
    int vazio = 0;
    tipoJogador listaJogadores[50];
    char palavraSecreta1[30][5];
    char palavraSecreta2[30][8];
    char palavraSecreta3[30][13];

    arquivoFruta = abrirArquivoTexto(nomeArquivoFruta);
    arquivoComputacao = abrirArquivoTexto(nomeArquivoComputacao);
    arquivoPaises = abrirArquivoTexto(nomeArquivopaises);

    if (arquivoFruta != NULL && arquivoComputacao != NULL
            && arquivoPaises != NULL) {
        iniciarTexto(arquivoFruta, arquivoComputacao, arquivoPaises,
                     palavraSecreta1, palavraSecreta2, palavraSecreta3);
        fclose(arquivoFruta);
        fclose(arquivoComputacao);
        fclose(arquivoPaises);
    }

    arquivoRanking = abrirArquivoBinario(nomeArquivoRanking);
    if (arquivoRanking != NULL) {
        iniciarBinario(arquivoRanking, listaJogadores, &vazio);
        fclose(arquivoRanking);
    }

    boasVindas();
    do {
        printf(
            "Escolha uma opção do menu:\n1 - Jogar\n2 - Configurações\n3 - Ranking\n0 - Sair do jogo\n");
        scanf("%d", &opcaoMenu);
        switch (opcaoMenu) {
        case 1:
            do {
                printf(
                    "1 - Jogar sozinho\n2 - Jogar contra o computador\n3 - Voltar ao menu\n");
                scanf("%d", &opcaoMenu);

                if (opcaoMenu == 1 || opcaoMenu == 2)
                    jogar(palavraSecreta1, palavraSecreta2, palavraSecreta3,
                          opcaoMenu, listaJogadores);

            } while (opcaoMenu != 3);
            limparTela();
            break;
        case 2:
            configurar(palavraSecreta1, palavraSecreta2, palavraSecreta3);
            break;
        case 3:
            rank(listaJogadores, vazio);
            break;
        case 0:
            arquivoFruta = abrirArquivoTexto(nomeArquivoFruta);
            arquivoComputacao = abrirArquivoTexto(nomeArquivoComputacao);
            arquivoPaises = abrirArquivoTexto(nomeArquivopaises);
            arquivoRanking = criarArquivoTexto(nomeArquivoRanking);
            salvar(arquivoRanking,arquivoFruta, arquivoComputacao, arquivoPaises,
                   palavraSecreta1, palavraSecreta2, palavraSecreta3,
                   listaJogadores);
            fclose(arquivoFruta);
            fclose(arquivoComputacao);
            fclose(arquivoPaises);
            fclose(arquivoRanking);
            break;
        default:
            printf("Opção Errada Digite novamente\n");
        }
    } while (opcaoMenu != 0);
    printf("Jogo Encerrado!\n");
    limparTela();

    return 0;
}
void limparTela() {
    system("clear");
}
void jogar(char palavraSecreta1[][5], char palavraSecreta2[][8],
           char palavraSecreta3[][13], int escolha, tipoJogador *listaJogadores) {
    void imprimirForca(int pCodigo);
    void limparResposta(char pVetor[], int pTamanho);
    void limparErro(char pVetor[], int pTamanho);
    char lerLetra();
    int gerarNumero();
    void identificacao(char *nome, char *confimar);
    int tamanhoVetor(char pVetor[]);
    void fimJogo(int nivel, int codigo, char *resposta, char *erro);
    tipoJogador jogador, computador = { "computador,0" };
    int i, tamanhoJogador = 0, tamanhoComputador = 0, indiceJogador,
           indiceComputador, repetida;
    int vidaJogador, vidaComputador, nivel = 1, indice=0;
    char respostaJogador[20], respostaComputador[20],
         erroJogador[7], erroCompututador[7], letraJogador, letraComputador,
         confimar;
    int certoJogador, certoComputador, pontosJogador = 0, pontosComputador = 0,
                                       indiceErroComputador = 0, indiceErroJogador = 0;

    int totalLetraJogador = 0, totalLetraComputador = 0, totalErrosJogador = 0,
        totalErrosComputador = 0;
    char forca1[6][10], forca2[6][10];

    nivel = 1;
    vidaJogador = 6;
    vidaComputador = 6;
    pontosJogador = 0;
    pontosComputador = 0;
    indiceJogador = gerarNumero();
    indiceComputador = gerarNumero();
    tamanhoJogador = tamanhoVetor(palavraSecreta1[indiceJogador]);
    limparResposta(respostaJogador, tamanhoJogador);
    tamanhoComputador = tamanhoVetor(palavraSecreta1[indiceComputador]);
    indiceErroJogador = 0;
    indiceErroComputador = 0;
    limparResposta(respostaComputador, tamanhoComputador);
    limparErro(erroJogador, vidaJogador);
    limparErro(erroCompututador, vidaComputador);

    do {
        while (getchar() != '\n')
            ;
        confimar = ' ';
        printf("Digite seu identificador (de 3 a 20 caracteres): ");
        scanf("%[^\n]", jogador.nome);
        identificacao(jogador.nome, &confimar);

    } while (confimar != 'S');

    printf("Voce e %s\n", jogador.nome);

    printf("Pressione a tecla ENTER para continuar!\n");
    getchar();
    limparTela();
    while (nivel < 4) {/* exibir a tela de jogo*/
        limparTela();
        printf("Nivel %d\n", nivel);
        gerarForca(forca1, vidaJogador);
        gerarForca(forca2, vidaComputador);
        if (escolha == 1) {
            imprimirForcaSimples(forca1);
            printf("%-30s\n", respostaJogador);
            printf("%-30s\n", "Letras Digitadas Jogador");
            printf("%-30s\n", erroJogador);
        } else {
            imprimirForcaDupla(forca1, forca2);
            printf("%-30s%-30s\n", respostaJogador, respostaComputador);
            printf("%-30s%-30s\n", "Letras Digitadas Jogador",
                   "Letras Digitadas Computador");
            printf("%-30s%-30s\n", erroJogador, erroCompututador);
        }
        certoComputador = 0;
        certoJogador = 0;
        letraComputador = ' ';
        do {
            repetida = 0;
            letraJogador = lerLetra();
            for (i = 0; i < tamanhoJogador; i++) {
                if (letraJogador == respostaJogador[i]) {
                    printf("Letra ja informada\n");
                    repetida = 1;
                }
            }
            for (i = 0; i < 7; i++) {
                if (letraJogador == erroJogador[i]) {
                    printf("Letra ja informada\n");
                    repetida = 1;
                }
            }

        } while (repetida != 0);

        if (escolha == 2) {
            do {
                repetida = 0;
                letraComputador = gerarLetraComputador();
                for (i = 0; i < tamanhoComputador; i++) {
                    if (letraComputador == respostaComputador[i]) {
                        repetida = 1;
                    }
                }
                for (i = 0; i < 7; i++) {
                    if (letraComputador == erroCompututador[i]) {
                        repetida = 1;
                    }
                }

            } while (repetida != 0);

        }

        /* verificar se existir a letra informada no vetor da palavraSecreta */
        if (nivel == 1) {
            for (i = 0; i < tamanhoJogador; i++) {
                if (letraJogador == palavraSecreta1[indiceJogador][i]) {
                    certoJogador = 1;
                    if (respostaJogador[i] == '-') {
                        respostaJogador[i] = letraJogador; /* revela a letra */
                        pontosJogador++; /* controla a quantidade de acertos */
                        totalLetraJogador++;

                    }
                }
            }
            if (escolha == 2) {
                for (i = 0; i < tamanhoComputador; i++) {
                    if (letraComputador
                            == palavraSecreta1[indiceComputador][i]) {
                        certoComputador = 1;
                        if (respostaComputador[i] == '-') {
                            respostaComputador[i] = letraComputador; /* revela a letra */
                            pontosComputador++; /* controla a quantidade de acertos */
                            totalLetraComputador++;
                        }
                    }
                }

            }

        }
        /* verificar se existir a letra informada no vetor da palavraSecreta */
        else if (nivel == 2) {

            for (i = 0; i < tamanhoJogador; i++) {
                if (letraJogador == palavraSecreta2[indiceJogador][i]) {
                    certoJogador = 1;
                    if (respostaJogador[i] == '-') {
                        respostaJogador[i] = letraJogador; /* revela a letra */
                        pontosJogador++; /* controla a quantidade de acertos */
                        totalLetraJogador++;
                    }
                }
            }
            if (escolha == 2) {
                for (i = 0; i < tamanhoComputador; i++) {
                    if (letraComputador
                            == palavraSecreta2[indiceComputador][i]) {
                        certoComputador = 1;
                        if (respostaComputador[i] == '-') {
                            respostaComputador[i] = letraComputador; /* revela a letra */
                            pontosComputador++; /* controla a quantidade de acertos */
                            totalLetraComputador++;
                        }
                    }
                }
            }

        }
        /* verificar se existir a letra informada no vetor da palavraSecreta */
        else {

            for (i = 0; i < tamanhoJogador; i++) {
                if (letraJogador == palavraSecreta3[indiceJogador][i]) {
                    certoJogador = 1;
                    if (respostaJogador[i] == '-') {
                        respostaJogador[i] = letraJogador; /* revela a letra */
                        pontosJogador++; /* controla a quantidade de acertos */
                        totalLetraJogador++;
                    }
                }
            }
            if (escolha == 2) {
                for (i = 0; i < tamanhoComputador; i++) {
                    if (letraComputador
                            == palavraSecreta3[indiceComputador][i]) {
                        certoComputador = 1;
                        if (respostaComputador[i] == '-') {
                            respostaComputador[i] = letraComputador; /* revela a letra */
                            pontosComputador++; /* controla a quantidade de acertos */
                            totalLetraComputador++;
                        }
                    }
                }
            }
        }

        /* verificar se acertou a letra e numero de vidas no nivel */

        if (certoJogador == 0) {
            vidaJogador--;
        }
        if (vidaJogador < 0 || pontosJogador == tamanhoJogador) { /* verifica se perdeu todas as vidas e perdeu o jogo */
            nivel += 1;
            vidaJogador = 6;
            vidaComputador = 6;
            pontosJogador = 0;
            pontosComputador = 0;
            indiceJogador = gerarNumero();
            indiceComputador = gerarNumero();
            if (nivel == 2) {
                tamanhoJogador = tamanhoVetor(palavraSecreta2[indiceJogador]);
                tamanhoComputador = tamanhoVetor(
                                        palavraSecreta2[indiceComputador]);
            } else {
                tamanhoJogador = tamanhoVetor(palavraSecreta3[indiceJogador]);
                tamanhoComputador = tamanhoVetor(
                                        palavraSecreta2[indiceComputador]);
            }
            indiceErroJogador = 0;
            indiceErroComputador = 0;
            limparResposta(respostaJogador, tamanhoJogador);
            limparResposta(respostaComputador, tamanhoComputador);
            limparErro(erroJogador, vidaJogador);
            limparErro(erroCompututador, vidaComputador);
        } else if (certoJogador == 0) {
            erroJogador[indiceErroJogador] = letraJogador; /* exibir a letra digita errado */
            indiceErroJogador++;
            totalErrosJogador++;
        }
        if (escolha == 2) {
            if (certoComputador == 0) {
                vidaComputador--;
            }
            if (vidaComputador < 0 || pontosComputador == tamanhoComputador) { /* verifica se perdeu todas as vidas e perdeu o jogo */
                nivel += 1;
                vidaJogador = 6;
                vidaComputador = 6;
                pontosJogador = 0;
                pontosComputador = 0;
                indiceJogador = gerarNumero();
                indiceComputador = gerarNumero();
                if (nivel == 2) {
                    tamanhoJogador = tamanhoVetor(
                                         palavraSecreta2[indiceJogador]);
                    tamanhoComputador = tamanhoVetor(
                                            palavraSecreta2[indiceComputador]);
                } else {
                    tamanhoJogador = tamanhoVetor(
                                         palavraSecreta3[indiceJogador]);
                    tamanhoComputador = tamanhoVetor(
                                            palavraSecreta2[indiceComputador]);
                }
                indiceErroJogador = 0;
                indiceErroComputador = 0;
                limparResposta(respostaJogador, tamanhoJogador);
                limparResposta(respostaComputador, tamanhoComputador);
                limparErro(erroJogador, vidaJogador);
                limparErro(erroCompututador, vidaComputador);
            } else if (certoComputador == 0) {
                erroCompututador[indiceErroComputador] = letraComputador; /* exibir a letra digita errado */
                indiceErroComputador++;
                totalErrosComputador++;
            }

        }

    }

    if (nivel > 3) {
        indice=-1;
        for(i=0; i<50; i++) {
            if(listaJogadores[i].pontuacao == 0) {
                if (indice==-1) {
                    indice=i;
                }
            }
        }
        pontosJogador = totalLetraJogador - totalErrosJogador;
        pontosComputador = totalLetraComputador - totalErrosComputador;
        if ((pontosComputador > pontosJogador) || (totalLetraJogador > 21)) {
            printf("Derrota para Jorgador\n");
            computador.pontuacao = pontosComputador;
            copiarVetor(listaJogadores[indice].nome,computador.nome );
            listaJogadores[indice].pontuacao = computador.pontuacao;

        } else {
            printf("Vitoria para jogador\n");
            jogador.pontuacao = pontosJogador;
            copiarVetor(listaJogadores[indice].nome,jogador.nome );
            listaJogadores[indice].pontuacao = jogador.pontuacao;
        }
    }
}
void boasVindas() {
    printf(
        "Bem vindo ao jogo : Jogo da Forca\nPressione a tecla ENTER para continuar ir ao menu principal!");
    getchar();
    limparTela();
}
void fimJogo(int nivel, int codigo, char *resposta, char *erro) {
    void imprimirForca(int pCodigo);
    printf("Nivel %d\n", nivel);
    printf("%s\n", resposta);
    printf("Letras Digitadas\n%s\n", erro);
    printf("Venceu o jogo\n");
    getchar();
    limparTela();
}
void imprimirOpcoes() {
    int i, opcao[30] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29 };
    for (i = 0; i < 30; i++) {
        printf("%d\t", opcao[i]);
    }
    printf("\n");
}
void atualizarPalavra(int nivel, char *palavraSecreta) {
    int i, tamanho = 0, tamanhoNovo;
    char novaPalavraSecreta[100];
    int tamanhoVetor(char pVetor[]);
    int lerPalavra(char *novaPalavraSecreta, int numeroInicial, int numeroFinal);
    tamanho = 0;
    tamanho = tamanhoVetor(palavraSecreta);
    if (nivel == 1) {
        tamanhoNovo = lerPalavra(novaPalavraSecreta, 3, 4);
    } else if (nivel == 2) {
        tamanhoNovo = lerPalavra(novaPalavraSecreta, 5, 7);
    } else {
        tamanhoNovo = lerPalavra(novaPalavraSecreta, 8, 12);
    }
    for (i = 0; i < tamanho; i++) {
        *(palavraSecreta + i) = ' ';
    }
    for (i = 0; i < tamanhoNovo; i++) {
        *(palavraSecreta + i) = novaPalavraSecreta[i];
    }
}
void configurar(char palavraSecreta1[][5], char palavraSecreta2[][8],
                char palavraSecreta3[][13]) {
    int novoNivel, i, opcaoEscolida;
    limparTela();
    do {
        printf("Escolha um nível para alterar: ");
        scanf("%d", &novoNivel);
        if (novoNivel < 1 || novoNivel > 3) {
            printf("Nível invalido digite novamente\n");
        }
    } while (novoNivel < 1 || novoNivel > 3);
    printf("Nível %d:\n", novoNivel);
    if (novoNivel == 1) {
        imprimirOpcoes();
        for (i = 0; i < 30; i++) {
            printf("%s\t", palavraSecreta1[i]);
        }
        printf("\n");
    } else if (novoNivel == 2) {
        imprimirOpcoes();
        for (i = 0; i < 30; i++) {
            printf("%s\t", palavraSecreta2[i]);
        }
        printf("\n");
    } else {
        imprimirOpcoes();
        for (i = 0; i < 30; i++) {
            printf("%s\t", palavraSecreta3[i]);
        }
        printf("\n");
    }
    do {
        printf("Escolha uma palavra para alterar(0-9): ");
        scanf("%d", &opcaoEscolida);
        if (opcaoEscolida < 0 || opcaoEscolida > 9) {
            printf("Indice invalido digite novamente\n");
        }
    } while (opcaoEscolida < 0 || opcaoEscolida > 9);

    if (novoNivel == 1) {
        atualizarPalavra(novoNivel, palavraSecreta1[opcaoEscolida]);
    } else if (novoNivel == 2) {
        atualizarPalavra(novoNivel, palavraSecreta2[opcaoEscolida]);
    } else {
        atualizarPalavra(novoNivel, palavraSecreta3[opcaoEscolida]);
    }
    limparTela();
}
int lerPalavra(char *novaPalavraSecreta, int numeroInicial, int numeroFinal) {
    int tamanhoNovo;
    int tamanhoVetor(char *pVetor);
    do {
        while (getchar() != '\n');
        printf("Digite uma nova-palavra secreta: ");
        scanf("%[^\n]", novaPalavraSecreta);
        tamanhoNovo = tamanhoVetor(novaPalavraSecreta);
        if (tamanhoNovo < numeroInicial || tamanhoNovo > numeroFinal) {
            printf("Tamanho invalido digite novamente\n");
        }
    } while (tamanhoNovo < numeroInicial || tamanhoNovo > numeroFinal);
    return tamanhoNovo;
}
void rank(tipoJogador *listaJogadores, int vazio) {

    int i, indice = -1;

    for(i=0; i<50; i++) {
        if(listaJogadores[i].pontuacao == 0) {
            if (indice==-1) {
                indice=i;
            }
        }
    }
    if (vazio == 1 && indice == -1) {
        printf("Raking vazio\n");
    } else {
        printf("raking\n");
        for (i = 0; i < 10; i++) {
            if (listaJogadores[i].pontuacao > 0) {
                printf("%d - %-20s  -> %-5d\n", i + 1, listaJogadores[i].nome,
                       listaJogadores[i].pontuacao);
            }

        }
    }

    printf("Presione qualquer tecla para voltar ao menu\n");
    while (getchar() != '\n')
        ;
    getchar();
    limparTela();
}

void limparResposta(char *pVetor, int pTamanho) {
    int i;
    for (i = 0; i < pTamanho; i++) {
        *(pVetor + i) = '-';
    }
    *(pVetor + i) = '\0';
}
void limparErro(char *pVetor, int pTamanho) {
    int i;
    for (i = 0; i < pTamanho; i++) {
        *(pVetor + i) = ' ';
    }
    *(pVetor + i) = '\0';
}
int tamanhoVetor(char *pVetor) {
    int i, tamanho = 0;
    for (i = 0; *(pVetor + i) != '\0'; i++) {
        tamanho++;
    }
    return tamanho;
}
char lerLetra(char palavraSecreta1[][5], char palavraSecreta2[][8],
              char palavraSecreta3[][13]) {
    int tamanhoVetor(char pVetor[]);
    char letra, buffer[100];
    do {
        printf("Digite uma letra\n");
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%c", &letra);
        if (letra == '\n') {
            printf("Invalido digite novamente\n");
        }
    } while (letra == '\n');
    if (letra > 64 && letra < 91) { /* converter palavra maiscula para minuscula */
        letra += 32;
    }

    return letra;
}
void identificacao(char *nome, char *confimar) {
    int critica, i, tamanho = 0;
    critica = 0;
    for (i = 0; nome[i] != '\0'; i++) {
        if (!((nome[i] >= 'a' && nome[i] <= 'z')
                || (nome[i] >= 'A' && nome[i] <= 'Z'))) {
            printf(
                "ERRO! Identificador deve conter somente caracteres alfa numericos\n");
            printf(
                "Digite novamente!Pressione a tecla ENTER para continuar ir ao menu principal!\n");
            critica = 1;
        }

    }
    tamanho = 0;
    for (i = 0; nome[i] != '\0'; i++) {
        tamanho++;
    }
    if (tamanho < 3 || tamanho > 20) {
        printf("ERRO! Número de caracteres invalido\n");
        printf(
            "Digite novamente!Pressione a tecla ENTER para continuar ir ao menu principal!\n");
        critica = 1;
    }
    if (critica == 0) {
        printf("Corfima %s (S/N): ", nome);
        while (getchar() != '\n')
            ;
        scanf("%c", confimar);
        if (*confimar == 's') { /* converter palavra minuscula para maiscula */
            *confimar -= 32;
        }
    }

}
int gerarNumero() {
    int i;
    srand(time(NULL));
    srand(time(NULL));
    i = rand() % 10; /* retorna um aletorio entre 0 e 9 */
    return i - 1;
}
