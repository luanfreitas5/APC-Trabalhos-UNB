/**      @file: 150015585_trabalho04.c
 *     @author: Luan Mendes Gonçalves Freitas
 * @disciplina: Algoritmos e Programação de Computadores
 *      @turma: G
 *      @trabalho 4 - Jogo da Forca 4.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char nome[20];
    int pontuacao;
} tipoJogador;
FILE * abrirArquivoBinario(char* arquivo);
void jogar(char **palavraSecreta1, char **palavraSecreta2,
           char **palavraSecreta3, int escolha, tipoJogador *listaJogadores,
           int **MatrizArquivo1, int **MatrizArquivo2, int **MatrizArquivo3);
void rankingClassificacao(FILE *arquivo, int opcaoMenu);
void rank(char *nomeArquivo);
void limparTela();

void boasVindas();

void configurar(char *nomeArquivoFruta, char *nomeArquivoComputacao,
                char *nomeArquivoPaises, FILE *arquivoFruta, FILE *arquivoComputacao,
                FILE *arquivoPaises, char **palavraSecreta1, char **palavraSecreta2,
                char **palavraSecreta3, char **palavraSecretaInserir,
                int **matrizArquivo1, int **matrizArquivo2, int **matrizArquivo3);

char gerarLetraComputador(int nivel, char * alfabetico) {
    int i;

    if (nivel == 1) {
        srand(time(NULL));
        i = rand() % 26;
    } else if (nivel == 2) {
        srand(time(NULL));
        i = rand() % 20;
    } else {
        srand(time(NULL));
        i = rand() % 13;
    }
    return alfabetico[i];
}

char * gerarAlfabeticoComputador(int nivel, char *palavraSecreta, int tamanho) {
    int i, j;
    char *alfabetico;
    char alfabeticoPadrao[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'x', 'y', 'z', '\0'
                              };

    if (nivel == 1) {
        alfabetico = (char *) malloc(27 * sizeof(char));
        strcpy(alfabetico, alfabeticoPadrao);

    } else if (nivel == 2) {
        alfabetico = (char *) malloc(21 * sizeof(char));
        strcpy(alfabetico, palavraSecreta);
        for (i = 0; i < 26; i++) {
            for (j = 0; j < 26; j++) {
                if (!(alfabetico[i] != alfabeticoPadrao[j]
                        && alfabeticoPadrao[j] != '0')) {
                    alfabeticoPadrao[j] = '0';
                }
            }
        }
        for (j = 0; j < 26; j++) {
            if (alfabeticoPadrao[j] != '0' && tamanho < 20) {
                alfabetico[tamanho] = alfabeticoPadrao[j];
                tamanho++;
            }
        }
        alfabetico[tamanho + 1] = '\0';
    } else {
        alfabetico = (char *) malloc(14 * sizeof(char));
        strcpy(alfabetico, palavraSecreta);
        for (i = 0; i < 26; i++) {
            for (j = 0; j < 26; j++) {
                if (!(alfabetico[i] != alfabeticoPadrao[j]
                        && alfabeticoPadrao[j] != '0')) {
                    alfabeticoPadrao[j] = '0';
                }
            }
        }
        for (j = 0; j < 26; j++) {
            if (alfabeticoPadrao[j] != '0' && tamanho < 13) {
                alfabetico[tamanho] = alfabeticoPadrao[j];
                tamanho++;
            }
        }

    }

    return alfabetico;
}

int gerarNumero(int quantidade) {
    int i;
    srand(time(NULL));
    if (quantidade > 0)
        i = rand() % quantidade;
    else
        i = 0;
    return i;
}

int obterQuantidadePalavras(int **matrizArquivo1, int **matrizArquivo2,
                            int **matrizArquivo3, int nivel) {
    int quantidade = 0;
    if (nivel == 1) {
        quantidade = matrizArquivo1[0][0] + matrizArquivo1[1][0]
                     + matrizArquivo1[2][0];
    } else if (nivel == 2) {
        quantidade = matrizArquivo2[0][0] + matrizArquivo2[1][0]
                     + matrizArquivo2[2][0];
    } else if (nivel == 3) {
        quantidade = matrizArquivo3[0][0] + matrizArquivo3[1][0]
                     + matrizArquivo3[2][0];

    }

    return quantidade;

}

void rank(char *nomeArquivo) {
    FILE *arquivoRanking = NULL;
    int opcaoMenu;
    do {
        printf(
            "1 - Top 10 \n2 - Todos\n3 - Para digitar quantos deseja ver\n4 - Resent Ranking\n5 - voltar menuo\n");
        scanf("%d", &opcaoMenu);

    } while (opcaoMenu < 1 || opcaoMenu > 5);

    arquivoRanking = abrirArquivoBinario(nomeArquivo);

    if (arquivoRanking != NULL) {
        rankingClassificacao(arquivoRanking, opcaoMenu);
        fclose(arquivoRanking);
    }

    printf("Presione qualquer tecla para voltar ao menu\n");
    while (getchar() != '\n')
        ;
    getchar();
    limparTela();
}
void imprimeRanking(tipoJogador *listaJogadores, int quantidade) {
    int i;
    printf("raking\n");
    for (i = 0; i < quantidade; i++) {
        if (listaJogadores[i].pontuacao > 0) {
            printf("%d - %-20s  -> %-5d\n", i + 1, listaJogadores[i].nome,
                   listaJogadores[i].pontuacao);
        }
    }
}
void ordernador(tipoJogador *listaJogadores, int quantidade) {

    int i, j;
    tipoJogador auxJogador;
    for (i = 0; i < quantidade; i++) {
        for (j = i + 1; j < quantidade; j++) {
            if (listaJogadores[i].pontuacao < listaJogadores[j].pontuacao) {
                auxJogador = listaJogadores[i];
                listaJogadores[i] = listaJogadores[j];
                listaJogadores[j] = auxJogador;
            }
        }

    }
}
void rankingClassificacao(FILE *arquivo, int opcaoMenu) {
    tipoJogador *listaJogadores;
    int tamanhoArquivo = 0, quantidadeRegistro = 0, quantidadeDesejaVer = 0;
    if (arquivo != NULL) {

        fseek(arquivo, 0, SEEK_END); /* vai para o final do arquivo */
        tamanhoArquivo = ftell(arquivo); /* diz a posicao do cursor no final do arquivo (qtd bytes)*/
        fseek(arquivo, 0, SEEK_SET); /* volta para o comeco do arquivo */

        quantidadeRegistro = (tamanhoArquivo / sizeof(tipoJogador));

        listaJogadores = (tipoJogador *) malloc(
                             quantidadeRegistro * sizeof(tipoJogador));
        fread(listaJogadores, sizeof(tipoJogador), quantidadeRegistro, arquivo);
        ordernador(listaJogadores, quantidadeRegistro);

        switch (opcaoMenu) {
        case 1:
            if (quantidadeRegistro > 10) {
                listaJogadores = (tipoJogador *) realloc(listaJogadores,
                                 10 * sizeof(tipoJogador));
                imprimeRanking(listaJogadores, 10);
            } else {
                imprimeRanking(listaJogadores, quantidadeRegistro);
            }
            break;
        case 2:
            imprimeRanking(listaJogadores, quantidadeRegistro);
            break;
        case 3:

            printf("digite quantidade deseja ver?\n");
            scanf("%d", &quantidadeDesejaVer);
            listaJogadores = (tipoJogador *) realloc(listaJogadores,
                             quantidadeDesejaVer * sizeof(tipoJogador));
            imprimeRanking(listaJogadores, quantidadeDesejaVer);
            break;
        case 4:
            listaJogadores = (tipoJogador *) realloc(listaJogadores,
                             0 * sizeof(tipoJogador));
            printf("raking vazio\n");
            break;

        }

    }

}

int **AlocarMatrizInt(int linha, int coluna) {
    int **matriz; /* ponteiro para a matriz */
    int i; /* variavel auxiliar      */
    if (linha < 1 || coluna < 1) { /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    /* aloca as linhas da matriz */
    matriz = (int **) malloc(linha * sizeof(int *));
    if (matriz == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for (i = 0; i < linha; i++) {
        matriz[i] = (int*) calloc(coluna, sizeof(int));
        if (matriz[i] == NULL) {
            printf("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (matriz); /* retorna o ponteiro para a matriz */
}
char **AlocarMatrizChar(int linha, int coluna) {
    char **matriz; /* ponteiro para a matriz */
    int i; /* variavel auxiliar      */
    if (linha < 1 || coluna < 1) { /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido **\n");
        return (NULL);
    }
    /* aloca as linhas da matriz */
    matriz = (char **) malloc(linha * sizeof(char *));
    if (matriz == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for (i = 0; i < linha; i++) {
        matriz[i] = (char*) calloc(coluna, sizeof(char));
        if (matriz[i] == NULL) {
            printf("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return (matriz); /* retorna o ponteiro para a matriz */
}
char ** realocarMatrizChar(char **matriz, int linha, int coluna,
                           int linhaAnterior) {
    /* ponteiro para a matriz */
    int i, quantidadeLinha = (linha + linhaAnterior); /* variavel auxiliar      */
    if (linha < 1 || coluna < 1) { /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido **\n");
        exit(1);
    }
    /* aloca as linhas da matriz */
    matriz = (char **) realloc(matriz, quantidadeLinha * sizeof(char *));
    if (matriz == NULL) {
        printf("** Erro: Memoria Insuficiente **");
        exit(1);
    }
    /* aloca as colunas da matriz */
    for (i = linhaAnterior; i < quantidadeLinha; i++) {
        matriz[i] = (char*) malloc(coluna * sizeof(char));

        if (matriz[i] == NULL) {
            printf("** Erro: Memoria Insuficiente **");
            exit(1);
        }
    }

    return matriz;
    /* retorna o ponteiro para a matriz */
}
float **LiberarMatriz(int linha, int coluna, float **matriz) {
    int i; /* variavel auxiliar */
    if (matriz == NULL)
        return (NULL);
    if (linha < 1 || coluna < 1) { /* verifica parametros recebidos */
        printf("** Erro: Parametro invalido coluna");
        return (matriz);
    }
    for (i = 0; i < linha; i++) {
        free(matriz[i]);
    } /* libera as linhas da matriz */
    free(matriz); /* libera a matriz */
    return (NULL); /* retorna um ponteiro nulo */
}
FILE * abrirArquivoBinarioApend(char* arquivo) {
    FILE *fp = fopen(arquivo, "ab+");

    if (fp == NULL) {
        printf("Não foi possível abrir \"%s\".\n", arquivo);
        return NULL;
    } else {
        return fp;
    }

}
FILE * criarArquivoTexto(char* arquivo) {
    FILE *fp = fopen(arquivo, "w+");

    if (fp == NULL) {
        printf("Não foi possível abrir \"%s\".\n", arquivo);
        return NULL;
    } else {
        return fp;
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

FILE * criarArquivoBinario(char* arquivo) {
    FILE *fp = fopen(arquivo, "wb+");

    if (fp == NULL) {
        printf("Não foi possível abrir \"%s\".\n", arquivo);
        return NULL;
    } else {
        return fp;
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
int comparar(const void * p1, const void * p2) {
    tipoJogador * q1 = (tipoJogador *) p1;
    tipoJogador * q2 = (tipoJogador *) p2;

    return q2->pontuacao - q1->pontuacao; /* ordem decrescente (maior para menor) */
}
void salvarRanking(FILE * arquivoBinario, tipoJogador *listaJogadores,
                   int quantidadeRegistroRanking) {

    fwrite(listaJogadores, sizeof(tipoJogador), quantidadeRegistroRanking,
           arquivoBinario);

}
void iniciarBinario(FILE *arquivo, tipoJogador *listaJogadores, int *vazio,
                    int *quantidadeRegistroRanking) {
    void copiarVetor(char *VetorSubstituir, char *vetorTroca);
    void limparErro(char *pVetor, int pTamanho);
    int i = 0, tamanhoArquivo;
    if (arquivo != NULL) {
        for (i = 0; i < 50; i++) {
            limparErro(listaJogadores[i].nome, 20);
            listaJogadores[i].pontuacao = 0;
        }

        fseek(arquivo, 0, SEEK_END); /* vai para o final do arquivo */
        tamanhoArquivo = ftell(arquivo); /* diz a posicao do cursor no final do arquivo (qtd bytes) */
        fseek(arquivo, 0, SEEK_SET); /* volta para o comeco do arquivo */

        *(quantidadeRegistroRanking) = (tamanhoArquivo / sizeof(tipoJogador));
        if (tamanhoArquivo == 0) {
            *(vazio) = 1;
        } else {
            fread(listaJogadores, sizeof(tipoJogador),
                  *quantidadeRegistroRanking, arquivo);
            qsort(listaJogadores, *quantidadeRegistroRanking,
                  sizeof(tipoJogador), comparar);
        }

    }

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
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|");
        copiarVetor(forca[3], "|");
        copiarVetor(forca[4], "|");
        copiarVetor(forca[5], "========");
        break;
    case 5:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "|");
        copiarVetor(forca[4], "|");
        copiarVetor(forca[5], "========");
        break;

    case 4:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "|  |");
        copiarVetor(forca[4], "|");
        copiarVetor(forca[5], "========");

        break;
    case 3:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "| /|");
        copiarVetor(forca[4], "|");
        copiarVetor(forca[5], "========");
        break;

    case 2:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "| /|\\");
        copiarVetor(forca[4], "| ");
        copiarVetor(forca[5], "========");
        break;

    case 1:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "| /|\\");
        copiarVetor(forca[4], "| /");
        copiarVetor(forca[5], "========");
        break;

    default:
        copiarVetor(forca[0], "+------+");
        copiarVetor(forca[1], "|--|");
        copiarVetor(forca[2], "|  o");
        copiarVetor(forca[3], "| /|\\");
        copiarVetor(forca[4], "| / \\");
        copiarVetor(forca[5], "========");

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

char ** iniciarTextoSecreta(FILE *arquivoFruta, FILE *arquivoComputacao,
                            FILE *arquivoPaises, char **palavraSecreta1, char **palavraSecreta2,
                            char **palavraSecreta3, int **MatrizArquivo1, int **MatrizArquivo2,
                            int **MatrizArquivo3, int opcao) {

    int i, nivel, quantidadePalavra, j;
    int linhaAnterior, coluna1 = 5, coluna2 = 8, coluna3 = 13, quantidadeLinha =
                                     0;
    rewind(arquivoFruta);
    rewind(arquivoComputacao);
    rewind(arquivoPaises);

    if (arquivoFruta != NULL) {

        for (i = 0; i < 3; i++) {
            fscanf(arquivoFruta, "%d\n", &nivel);
            fscanf(arquivoFruta, "%d\n", &quantidadePalavra);
            MatrizArquivo1[i][0] = quantidadePalavra;

            if (nivel == 1) {
                palavraSecreta1 = AlocarMatrizChar(quantidadePalavra, coluna1);
            } else if (nivel == 2) {
                palavraSecreta2 = AlocarMatrizChar(quantidadePalavra, coluna2);
            } else {
                palavraSecreta3 = AlocarMatrizChar(quantidadePalavra, coluna3);
            }
            for (j = 0; j < quantidadePalavra; j++) {
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

        for (i = 0; i < 3; i++) {
            fscanf(arquivoComputacao, "%d\n", &nivel);
            fscanf(arquivoComputacao, "%d\n", &quantidadePalavra);
            MatrizArquivo2[i][0] = quantidadePalavra;

            if (nivel == 1) {
                linhaAnterior = MatrizArquivo1[0][0];
                palavraSecreta1 = realocarMatrizChar(palavraSecreta1,
                                                     quantidadePalavra, coluna1, linhaAnterior);
            } else if (nivel == 2) {
                linhaAnterior = MatrizArquivo1[1][0];
                palavraSecreta2 = realocarMatrizChar(palavraSecreta2,
                                                     quantidadePalavra, coluna2, linhaAnterior);
            } else {
                linhaAnterior = MatrizArquivo1[2][0];
                palavraSecreta3 = realocarMatrizChar(palavraSecreta3,
                                                     quantidadePalavra, coluna3, linhaAnterior);
            }
            quantidadeLinha = quantidadePalavra + linhaAnterior;
            for (j = linhaAnterior; j < quantidadeLinha; j++) {
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

        for (i = 0; i < 3; i++) {
            fscanf(arquivoPaises, "%d\n", &nivel);
            fscanf(arquivoPaises, "%d\n", &quantidadePalavra);
            MatrizArquivo3[i][0] = quantidadePalavra;

            if (nivel == 1) {
                linhaAnterior = MatrizArquivo2[0][0] + MatrizArquivo1[0][0];
                palavraSecreta1 = realocarMatrizChar(palavraSecreta1,
                                                     quantidadePalavra, coluna1, linhaAnterior);
            } else if (nivel == 2) {
                linhaAnterior = MatrizArquivo2[1][0] + MatrizArquivo1[1][0];
                palavraSecreta2 = realocarMatrizChar(palavraSecreta2,
                                                     quantidadePalavra, coluna2, linhaAnterior);
            } else {
                linhaAnterior = MatrizArquivo2[2][0] + MatrizArquivo1[2][0];
                palavraSecreta3 = realocarMatrizChar(palavraSecreta3,
                                                     quantidadePalavra, coluna3, linhaAnterior);
            }
            quantidadeLinha = quantidadePalavra + linhaAnterior;
            for (j = linhaAnterior; j < quantidadeLinha; j++) {
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
    /*	for (i = 0; i < 30; i++) {
     printf("%d - %-30s\n", i, palavraSecreta1[i]);
     }*/
    if (opcao == 1)
        return palavraSecreta1;
    else if (opcao == 2)
        return palavraSecreta2;
    else
        return palavraSecreta3;
}

void salvarConfiguracao(FILE *arquivoFruta, FILE *arquivoComputacao,
                        FILE *arquivoPaises, char **palavraSecreta1, char **palavraSecreta2,
                        char **palavraSecreta3, char **palavraSecretaInserir,
                        int **MatrizArquivo1, int **MatrizArquivo2, int **MatrizArquivo3,
                        int novoNivel, int quantidade) {
    int i, j, linhaAnterior, quantidadeLinha, totalPalavra = 0, totalGeral = 0,
                                              nivel;

    if (arquivoFruta != NULL) {
        for (i = 1; i <= 3; i++) {
            nivel = i;
            totalGeral = 0;
            totalPalavra = 0;
            if (nivel == novoNivel) {
                totalPalavra = MatrizArquivo1[nivel - 1][0];
                totalGeral = totalPalavra + quantidade;
                fprintf(arquivoFruta, "%d\n", nivel);
                fprintf(arquivoFruta, "%d\n", totalGeral);
                for (j = 0; j < quantidade; j++) {
                    fprintf(arquivoFruta, "%s\n", palavraSecretaInserir[j]);
                }

            } else {
                totalPalavra = MatrizArquivo1[nivel - 1][0];
                fprintf(arquivoFruta, "%d\n", nivel);
                fprintf(arquivoFruta, "%d\n", totalPalavra);

            }

            for (j = 0; j < totalPalavra; j++) {
                if (nivel == 1) {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoFruta, "%s\n", palavraSecreta3[j]);

                }
            }

        }
        fclose(arquivoFruta);

    }
    if (arquivoComputacao != NULL) {

        for (i = 1; i <= 3; i++) {
            nivel = i;
            totalGeral = 0;
            totalPalavra = 0;
            if (nivel == 1) {
                linhaAnterior = MatrizArquivo1[0][0];
            } else if (nivel == 2) {
                linhaAnterior = MatrizArquivo1[1][0];
            } else {
                linhaAnterior = MatrizArquivo1[2][0];
            }

            if (nivel == novoNivel) {
                totalPalavra = MatrizArquivo2[novoNivel - 1][0];
                totalGeral = totalPalavra + quantidade;
                fprintf(arquivoComputacao, "%d\n", nivel);
                fprintf(arquivoComputacao, "%d\n", totalGeral);
                for (j = 0; j < quantidade; j++) {
                    fprintf(arquivoComputacao, "%s\n",
                            palavraSecretaInserir[j]);
                }

            } else {
                totalPalavra = MatrizArquivo2[nivel - 1][0];
                fprintf(arquivoComputacao, "%d\n", nivel);
                fprintf(arquivoComputacao, "%d\n", totalPalavra);

            }

            quantidadeLinha = totalPalavra + linhaAnterior;
            for (j = linhaAnterior; j < quantidadeLinha; j++) {
                if (nivel == 1) {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoComputacao, "%s\n", palavraSecreta3[j]);

                }
            }

        }
        fclose(arquivoComputacao);
    }

    if (arquivoPaises != NULL) {

        for (i = 1; i <= 3; i++) {
            nivel = i;
            totalGeral = 0;
            totalPalavra = 0;
            if (nivel == 1) {
                linhaAnterior = MatrizArquivo2[0][0];
            } else if (nivel == 2) {
                linhaAnterior = MatrizArquivo2[1][0];
            } else {
                linhaAnterior = MatrizArquivo2[2][0];
            }

            if (nivel == novoNivel) {
                totalPalavra = MatrizArquivo3[novoNivel - 1][0];
                totalGeral = totalPalavra + quantidade;
                fprintf(arquivoPaises, "%d\n", nivel);
                fprintf(arquivoPaises, "%d\n", totalGeral);
                for (j = 0; j < quantidade; j++) {
                    fprintf(arquivoPaises, "%s\n", palavraSecretaInserir[j]);
                }

            } else {
                totalPalavra = MatrizArquivo3[nivel - 1][0];
                fprintf(arquivoPaises, "%d\n", nivel);
                fprintf(arquivoPaises, "%d\n", totalPalavra);

            }

            quantidadeLinha = totalPalavra + linhaAnterior;
            for (j = linhaAnterior; j < quantidadeLinha; j++) {
                if (nivel == 1) {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta1[j]);
                } else if (nivel == 2) {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta2[j]);

                } else {
                    fprintf(arquivoPaises, "%s\n", palavraSecreta3[j]);

                }
            }

        }
        fclose(arquivoPaises);
    }

}

int main() {

    int quantidadeRegistroRanking;

    int opcaoMenu;
    char nomeArquivoFruta[30] = "frutas.txt";
    char nomeArquivoComputacao[30] = "computacao.txt";
    char nomeArquivopaises[30] = "paises.txt";

    char nomeArquivoRanking[30] = "ranking.bin";
    FILE *arquivoRanking;

    FILE *arquivoFruta;
    FILE *arquivoComputacao;
    FILE *arquivoPaises;
    int vazio = 0, **matrizArquivo1, **matrizArquivo2, **matrizArquivo3;
    tipoJogador listaJogadores[50];
    char **palavraSecreta1 = NULL, **palavraSecreta2 = NULL, **palavraSecreta3 =
                                 NULL, **palavraSecretaInserir = NULL;

    arquivoFruta = abrirArquivoTexto(nomeArquivoFruta);
    arquivoComputacao = abrirArquivoTexto(nomeArquivoComputacao);
    arquivoPaises = abrirArquivoTexto(nomeArquivopaises);

    matrizArquivo1 = AlocarMatrizInt(3, 1);
    matrizArquivo2 = AlocarMatrizInt(3, 1);
    matrizArquivo3 = AlocarMatrizInt(3, 1);
    if (arquivoFruta != NULL && arquivoComputacao != NULL
            && arquivoPaises != NULL) {

        palavraSecreta1 = iniciarTextoSecreta(arquivoFruta, arquivoComputacao,
                                              arquivoPaises, palavraSecreta1, palavraSecreta2,
                                              palavraSecreta3, matrizArquivo1, matrizArquivo2, matrizArquivo3,
                                              1);

        palavraSecreta2 = iniciarTextoSecreta(arquivoFruta, arquivoComputacao,
                                              arquivoPaises, palavraSecreta1, palavraSecreta2,
                                              palavraSecreta3, matrizArquivo1, matrizArquivo2, matrizArquivo3,
                                              2);
        palavraSecreta3 = iniciarTextoSecreta(arquivoFruta, arquivoComputacao,
                                              arquivoPaises, palavraSecreta1, palavraSecreta2,
                                              palavraSecreta3, matrizArquivo1, matrizArquivo2, matrizArquivo3,
                                              3);

    }

    arquivoRanking = abrirArquivoBinario(nomeArquivoRanking);
    if (arquivoRanking != NULL) {
        iniciarBinario(arquivoRanking, listaJogadores, &vazio,
                       &quantidadeRegistroRanking);
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
                          opcaoMenu, listaJogadores, matrizArquivo1,
                          matrizArquivo2, matrizArquivo3);

            } while (opcaoMenu != 3);
            limparTela();
            break;
        case 2:

            configurar(nomeArquivoFruta, nomeArquivoComputacao,
                       nomeArquivopaises, arquivoFruta, arquivoComputacao,
                       arquivoPaises, palavraSecreta1, palavraSecreta2,
                       palavraSecreta3, palavraSecretaInserir, matrizArquivo1,
                       matrizArquivo2, matrizArquivo3);
            break;
        case 3:
            rank(nomeArquivoRanking);
            break;
        case 0:

            arquivoFruta = criarArquivoTexto(nomeArquivoFruta);
            arquivoComputacao = criarArquivoTexto(nomeArquivoComputacao);
            arquivoPaises = criarArquivoTexto(nomeArquivopaises);
            salvarConfiguracao(arquivoFruta, arquivoComputacao, arquivoPaises,
                               palavraSecreta1, palavraSecreta2, palavraSecreta3,
                               palavraSecretaInserir, matrizArquivo1, matrizArquivo2,
                               matrizArquivo3, 0, 0);

            /*  arquivoRanking = criarArquivoBinario(nomeArquivoRanking);
             salvarRanking(arquivoRanking, listaJogadores,
             quantidadeRegistroRanking);
             fclose(arquivoRanking);*/
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
void jogar(char **palavraSecreta1, char **palavraSecreta2,
           char **palavraSecreta3, int escolha, tipoJogador *listaJogadores,
           int **matrizArquivo1, int **matrizArquivo2, int **matrizArquivo3) {
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
    int vidaJogador, vidaComputador, nivel = 1,  flag = 0;
    char respostaJogador[20], respostaComputador[20], erroJogador[7],
         erroCompututador[7], letraJogador, letraComputador, confimar;
    int certoJogador, certoComputador, pontosJogador = 0, pontosComputador = 0,
                                       indiceErroComputador = 0, indiceErroJogador = 0;

    int totalLetraJogador = 0, totalLetraComputador = 0, totalErrosJogador = 0,
        totalErrosComputador = 0, quantidadePalavras = 0;
    char forca1[6][10], forca2[6][10];
    char *alfabeto;

    char nomeArquivoRanking[30] = "ranking.bin";
    FILE *arquivoRanking;

    nivel = 1;
    vidaJogador = 6;
    vidaComputador = 6;
    pontosJogador = 0;
    pontosComputador = 0;
    quantidadePalavras = obterQuantidadePalavras(matrizArquivo1, matrizArquivo2,
                         matrizArquivo3, nivel);
    indiceJogador = gerarNumero(quantidadePalavras);
    tamanhoJogador = tamanhoVetor(palavraSecreta1[indiceJogador]);
    indiceComputador = gerarNumero(quantidadePalavras);
    limparResposta(respostaJogador, tamanhoJogador);
    tamanhoComputador = tamanhoVetor(palavraSecreta1[indiceComputador]);
    indiceErroJogador = 0;
    indiceErroComputador = 0;
    limparResposta(respostaComputador, tamanhoComputador);
    limparErro(erroJogador, vidaJogador);
    limparErro(erroCompututador, vidaComputador);

    alfabeto = gerarAlfabeticoComputador(nivel,
                                         palavraSecreta1[indiceComputador], tamanhoComputador);

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
    while (nivel < 4) { /* exibir a tela de jogo*/
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
                letraComputador = gerarLetraComputador(nivel, alfabeto);
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
        flag = 0;
        if (certoJogador == 0) {
            vidaJogador--;
        }
        if (vidaJogador < 0 || pontosJogador == tamanhoJogador) { /* verifica se perdeu todas as vidas e perdeu o jogo */
            nivel += 1;
            vidaJogador = 6;
            vidaComputador = 6;
            pontosJogador = 0;
            pontosComputador = 0;
            quantidadePalavras = obterQuantidadePalavras(matrizArquivo1,
                                 matrizArquivo2, matrizArquivo3, nivel);
            indiceJogador = gerarNumero(quantidadePalavras);
            quantidadePalavras = obterQuantidadePalavras(matrizArquivo1,
                                 matrizArquivo2, matrizArquivo3, nivel);
            indiceComputador = gerarNumero(quantidadePalavras);
            flag = 1;
            if (nivel == 2) {
                tamanhoJogador = tamanhoVetor(palavraSecreta2[indiceJogador]);
                tamanhoComputador = tamanhoVetor(
                                        palavraSecreta2[indiceComputador]);
                alfabeto = gerarAlfabeticoComputador(nivel,
                                                     palavraSecreta2[indiceComputador], tamanhoComputador);

            } else {
                tamanhoJogador = tamanhoVetor(palavraSecreta3[indiceJogador]);
                tamanhoComputador = tamanhoVetor(
                                        palavraSecreta3[indiceComputador]);
                alfabeto = gerarAlfabeticoComputador(nivel,
                                                     palavraSecreta3[indiceComputador], tamanhoComputador);

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
        if (escolha == 2 && flag == 0) {
            if (certoComputador == 0) {
                vidaComputador--;
            }
            if (vidaComputador < 0 || pontosComputador == tamanhoComputador) { /* verifica se perdeu todas as vidas e perdeu o jogo */
                nivel += 1;
                vidaJogador = 6;
                vidaComputador = 6;
                pontosJogador = 0;
                pontosComputador = 0;
                quantidadePalavras = obterQuantidadePalavras(matrizArquivo1,
                                     matrizArquivo2, matrizArquivo3, nivel);
                indiceJogador = gerarNumero(quantidadePalavras);
                quantidadePalavras = obterQuantidadePalavras(matrizArquivo1,
                                     matrizArquivo2, matrizArquivo3, nivel);
                indiceComputador = gerarNumero(quantidadePalavras);
                if (nivel == 2) {
                    tamanhoJogador = tamanhoVetor(
                                         palavraSecreta2[indiceJogador]);
                    tamanhoComputador = tamanhoVetor(
                                            palavraSecreta2[indiceComputador]);
                    alfabeto = gerarAlfabeticoComputador(nivel,
                                                         palavraSecreta2[indiceComputador],
                                                         tamanhoComputador);

                } else {
                    tamanhoJogador = tamanhoVetor(
                                         palavraSecreta3[indiceJogador]);
                    tamanhoComputador = tamanhoVetor(
                                            palavraSecreta3[indiceComputador]);
                    alfabeto = gerarAlfabeticoComputador(nivel,
                                                         palavraSecreta3[indiceComputador],
                                                         tamanhoComputador);

                }
                indiceErroJogador = 0;
                indiceErroComputador = 0;
                limparResposta(respostaJogador, tamanhoJogador);
                limparResposta(respostaComputador, tamanhoComputador);
                limparErro(erroJogador, vidaJogador);
                limparErro(erroCompututador, vidaComputador);
            } else if (certoComputador == 0 && flag == 0) {
                erroCompututador[indiceErroComputador] = letraComputador; /* exibir a letra digita errado */
                indiceErroComputador++;
                totalErrosComputador++;
            }

        }

    }

    if (nivel > 3) {
        pontosJogador = totalLetraJogador - totalErrosJogador;
        pontosComputador = totalLetraComputador - totalErrosComputador;
        if ((pontosComputador > pontosJogador) || (totalLetraJogador > 21)) {
            printf("Derrota para Jorgador\n");
            computador.pontuacao = pontosComputador;
            computador.pontuacao = 76;
            arquivoRanking = abrirArquivoBinarioApend(nomeArquivoRanking);
            salvarRanking(arquivoRanking, &computador, 1);
            fclose(arquivoRanking);

        } else {
            printf("Vitoria para jogador\n");
            jogador.pontuacao = pontosJogador;
            arquivoRanking = abrirArquivoBinarioApend(nomeArquivoRanking);
            salvarRanking(arquivoRanking, &jogador, 1);
            fclose(arquivoRanking);
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
void imprimirOpcoes(int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("%d\t", i);
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
void configurar(char *nomeArquivoFruta, char *nomeArquivoComputacao,
                char *nomeArquivoPaises, FILE *arquivoFruta, FILE *arquivoComputacao,
                FILE *arquivoPaises, char **palavraSecreta1, char **palavraSecreta2,
                char **palavraSecreta3, char **palavraSecretaInserir,
                int **matrizArquivo1, int **matrizArquivo2, int **matrizArquivo3) {

    int novoNivel, i, opcao, opcaoEscolida, opcaoArquivo;

    int quantidade, totalPalavra = 0, coluna1 = 5, coluna2 = 8, coluna3 = 13;
    limparTela();

    do {
        printf("Escolha um nível para alterar: ");
        scanf("%d", &novoNivel);
        if (novoNivel < 1 || novoNivel > 3) {
            printf("Nível invalido digite novamente\n");
        }
    } while (novoNivel < 1 || novoNivel > 3);

    do {
        printf("1 - Alterar Palavra\n2 - Inserir palavras\n3 - voltar menuo\n");
        scanf("%d", &opcao);

    } while (opcao < 1 || opcao > 3);

    printf("Nível %d:\n", novoNivel);

    if (opcao == 2) {
        do {
            printf(
                "1 - arquivo fruta\n2 - arquivo computador \n3 arquivo computador");
            scanf("%d", &opcaoArquivo);

        } while (opcaoArquivo < 1 || opcaoArquivo > 3);

        printf("Quantas palavras deseja inserir?\n");
        scanf("%d", &quantidade);
        if (novoNivel == 1) {
            palavraSecretaInserir = AlocarMatrizChar(quantidade, coluna1);
        } else if (novoNivel == 2) {
            palavraSecretaInserir = AlocarMatrizChar(quantidade, coluna2);
        } else {
            palavraSecretaInserir = AlocarMatrizChar(quantidade, coluna3);
        }
        for (i = 0; i < quantidade; i++) {
            printf("Insira sua palavra numero : %d\n", i);
            while (getchar() != '\n')
                ;
            scanf("%[^\n]", palavraSecretaInserir[i]);
        }
        if (opcaoArquivo == 1) {
            arquivoFruta = criarArquivoTexto(nomeArquivoFruta);
            if (arquivoFruta != NULL) {

                salvarConfiguracao(arquivoFruta, arquivoComputacao,
                                   arquivoPaises, palavraSecreta1, palavraSecreta2,
                                   palavraSecreta3, palavraSecretaInserir, matrizArquivo1,
                                   matrizArquivo2, matrizArquivo3, novoNivel, quantidade);

            }
        } else if (opcaoArquivo == 2) {
            arquivoComputacao = criarArquivoTexto(nomeArquivoComputacao);
            if (arquivoComputacao != NULL) {
                salvarConfiguracao(arquivoFruta, arquivoComputacao,
                                   arquivoPaises, palavraSecreta1, palavraSecreta2,
                                   palavraSecreta3, palavraSecretaInserir, matrizArquivo1,
                                   matrizArquivo2, matrizArquivo3, novoNivel, quantidade);

            }
        } else if (opcaoArquivo == 3) {
            arquivoPaises = criarArquivoTexto(nomeArquivoPaises);
            if (arquivoPaises != NULL) {
                salvarConfiguracao(arquivoFruta, arquivoComputacao,
                                   arquivoPaises, palavraSecreta1, palavraSecreta2,
                                   palavraSecreta3, palavraSecretaInserir, matrizArquivo1,
                                   matrizArquivo2, matrizArquivo3, novoNivel, quantidade);

            }

        }
    }
    if (opcao == 1) {

        if (novoNivel == 1) {

            totalPalavra = matrizArquivo1[0][0] + matrizArquivo1[1][0]
                           + matrizArquivo1[2][0];
            imprimirOpcoes(totalPalavra);
            for (i = 0; i < totalPalavra; i++) {
                printf("%s\t", palavraSecreta1[i]);
            }
            printf("\n");
        } else if (novoNivel == 2) {

            totalPalavra = matrizArquivo1[0][0] + matrizArquivo1[1][0]
                           + matrizArquivo1[2][0];
            imprimirOpcoes(totalPalavra);
            for (i = 0; i < totalPalavra; i++) {
                printf("%s\t", palavraSecreta2[i]);
            }
            printf("\n");
        } else {

            totalPalavra = matrizArquivo1[0][0] + matrizArquivo1[1][0]
                           + matrizArquivo1[2][0];
            imprimirOpcoes(totalPalavra);
            for (i = 0; i < totalPalavra; i++) {
                printf("%s\t", palavraSecreta3[i]);
            }
            printf("\n");
        }
        do {
            printf("Escolha uma palavra para alterar(0-%d): ",
                   totalPalavra - 1);
            scanf("%d", &opcaoEscolida);
            if (opcaoEscolida < 0 || opcaoEscolida > (totalPalavra - 1)) {
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
    }
    limparTela();
}
int lerPalavra(char *novaPalavraSecreta, int numeroInicial, int numeroFinal) {
    int tamanhoNovo;
    int tamanhoVetor(char *pVetor);
    do {
        while (getchar() != '\n')
            ;
        printf("Digite uma nova-palavra secreta: ");
        scanf("%[^\n]", novaPalavraSecreta);
        tamanhoNovo = tamanhoVetor(novaPalavraSecreta);
        if (tamanhoNovo < numeroInicial || tamanhoNovo > numeroFinal) {
            printf("Tamanho invalido digite novamente\n");
        }
    } while (tamanhoNovo < numeroInicial || tamanhoNovo > numeroFinal);
    return tamanhoNovo;
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

