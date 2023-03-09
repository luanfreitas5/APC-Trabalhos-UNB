/**      @file: 150015585_trabalho02.c
 *     @author: Luan Mendes Gonçalves Freitas
 * @disciplina: Algoritmos e Programação de Computadores
 *      @turma: G
 *      @trabalho 2 - Jogo da Forca 2.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	void jogar(char palavraSecreta1[][5], char palavraSecreta2[][8],
			char palavraSecreta3[][13]);
	void configurar();
	void rank();
	void boasVindas();
	void limparTela();
	int opcaoMenu;
	char palavraSecreta1[10][5] = { { "cuba" }, { "gana" }, { "maca" },
			{ "pera" }, { "laos" }, { "peru" }, { "caju" }, { "chip" },
			{ "kiwi" }, { "jaca" } };
	char palavraSecreta2[10][8] = { { "abacaxi" }, { "abacate" }, { "uruguai" },
			{ "suica" }, { "suecia" }, { "mouse" }, { "teclado" }, { "linux" },
			{ "acerola" }, { "morango" } };
	char palavraSecreta3[10][13] = { { "framboesa" }, { "montenegro" }, {
			"tamarindo" }, { "luxemburgo" }, { "gronelandia" },
			{ "cazaquistao" }, { "seringuela" }, { "bielorrussia" }, {
					"processador" }, { "jabuticaba" } };
	boasVindas();
	do {
		printf("Escolha uma opção do menu:\n1 - Jogar\n2 - Configurações\n3 - Ranking\n0 - Sair do jogo\n");
		scanf("%d", &opcaoMenu);
		switch (opcaoMenu) {
		case 1:
			jogar(palavraSecreta1, palavraSecreta2, palavraSecreta3);
			break;
		case 2:
			configurar(palavraSecreta1, palavraSecreta2, palavraSecreta3);
			break;
		case 3:
			rank();
			break;
		case 0:
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
		char palavraSecreta3[][13]) {
	void imprimirForca(int pCodigo);
	void limparResposta(char pVetor[], int pTamanho);
	void limparErro(char pVetor[], int pTamanho);
	char lerLetra();
	int gerarNumero();
	void identificacao(char *nome, char *confimar);
	int tamanhoVetor(char pVetor[]);
	void fimJogo(int nivel, int codigo, char *resposta, char *erro);
	int i, tamanho = 0, indice, repetida;
	int vida, nivel = 1;
	char resposta[10], erro[7], letra, nome[100], confimar;
	int certo, pontos = 0, indiceErro = 0, terminarJogo = 0;

	nivel = 1;
	vida = 6;
	pontos = 0;
	terminarJogo = 0;
	indice = gerarNumero();
	tamanho = tamanhoVetor(palavraSecreta1[indice]);
	indiceErro = 0;
	limparResposta(resposta, tamanho);
	limparErro(erro, vida);
	do {
		while (getchar() != '\n');
		confimar = ' ';
		printf("Digite seu identificador (de 3 a 20 caracteres): ");
		scanf("%[^\n]", nome);
		identificacao(nome, &confimar);

	} while (confimar != 'S');
	printf("Voce e %s\n", nome);
	printf("Pressione a tecla ENTER para continuar!\n");
	getchar();
	limparTela();
	while (vida >= 0) {/* exibir a tela de jogo*/
		limparTela();
		printf("Nivel %d\n", nivel);
		imprimirForca(vida);
		printf("%s\n", resposta);
		printf("Letras Digitadas\n%s\n", erro);
		letra = lerLetra();
		certo = 0;
		repetida = 0;
		for (i = 0; i < tamanho; i++) {
			if (letra == resposta[i]) {
				printf("Letra ja informada\n");
				repetida = 1;
			}
		}
		for (i = 0; i < 7; i++) {
			if (letra == erro[i]) {
				printf("Letra ja informada\n");
				repetida = 1;
			}
		}
		/* verificar se existir a letra informada no vetor da palavraSecreta */
		if (nivel == 1) {
			if (repetida == 0) {
				for (i = 0; i < tamanho; i++) {
					if (letra == palavraSecreta1[indice][i]) {
						certo = 1;
						if (resposta[i] == '-') {
							resposta[i] = letra; /* revela a letra */
							pontos++; /* controla a quantidade de acertos */
						}
					}
				}
			}
		}
		/* verificar se existir a letra informada no vetor da palavraSecreta */
		else if (nivel == 2) {
			if (repetida == 0) {
				for (i = 0; i < tamanho; i++) {
					if (letra == palavraSecreta2[indice][i]) {
						certo = 1;
						if (resposta[i] == '-') {
							resposta[i] = letra; /* revela a letra */
							pontos++; /* controla a quantidade de acertos */
						}
					}
				}
			}
		}
		/* verificar se existir a letra informada no vetor da palavraSecreta */
		else {
			if (repetida == 0) {
				for (i = 0; i < tamanho; i++) {
					if (letra == palavraSecreta3[indice][i]) {
						certo = 1;
						if (resposta[i] == '-') {
							resposta[i] = letra; /* revela a letra */
							pontos++; /* controla a quantidade de acertos */
						}
					}
				}
			}
		}
		if (repetida == 0) {
			/* verificar se acertou a letra e numero de vidas no nivel */
			if (certo == 0) {
				vida--;
				if (vida < 0) { /* verifica se perdeu todas as vidas e perdeu o jogo */
					limparTela();
					printf("Nivel %d\n", nivel);
					imprimirForca(vida);
					printf("%s\n", resposta);
					printf("Letras Digitadas\n%s\n", erro);
					printf("Você perdeu :(\n");
					printf("Pressione a tecla ENTER para continuar ir ao menu principal!");
					getchar();
					limparTela();
				} else {
					erro[indiceErro] = letra; /* exibir a letra digita errado */
					indiceErro++;
				}
			} else {
				if (pontos == tamanho) { /* verifica se acertou todos as letra da palavra */
					if (nivel == 3) { /* verifica se acertou todos as letra da palavra */
						terminarJogo = vida;
						vida = -1;
					} else {
						nivel += 1;
						vida = 6;
						pontos = 0;
						indice = gerarNumero();
						if (nivel == 2) {
							tamanho = tamanhoVetor(palavraSecreta2[indice]);
						} else {
							tamanho = tamanhoVetor(palavraSecreta3[indice]);
						}
						indiceErro = 0;
						limparResposta(resposta, tamanho);
						limparErro(erro, vida);

					}
				}
			}
		}
	}
	if (nivel == 3) {
		fimJogo(nivel, terminarJogo, resposta, erro);
	}
}
void boasVindas() {
	printf("Bem vindo ao jogo : Jogo da Forca\nPressione a tecla ENTER para continuar ir ao menu principal!");
	getchar();
	limparTela();
}
void fimJogo(int nivel, int codigo, char *resposta, char *erro) {
	void imprimirForca(int pCodigo);
	printf("Nivel %d\n", nivel);
	imprimirForca(codigo);
	printf("%s\n", resposta);
	printf("Letras Digitadas\n%s\n", erro);
	printf("Venceu o jogo\n");
	getchar();
	limparTela();
}
void imprimirOpcoes() {
	int i, opcao[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (i = 0; i < 10; i++) {
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
		for (i = 0; i < 10; i++) {
			printf("%s\t", palavraSecreta1[i]);
		}
		printf("\n");
	} else if (novoNivel == 2) {
		imprimirOpcoes();
		for (i = 0; i < 10; i++) {
			printf("%s\t", palavraSecreta2[i]);
		}
		printf("\n");
	} else {
		imprimirOpcoes();
		for (i = 0; i < 10; i++) {
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
void rank() {
	printf("Rankink ainda não disponivel na versão 2.0\n");
	printf("Presione qualquer tecla para voltar ao menu\n");
	while (getchar() != '\n');
	getchar();
	limparTela();
}
void imprimirForca(int pCodigo) {
	switch (pCodigo) {
	case 6:
		printf("___________\n|\t |\n|\t_|_\n|\t\n|\t\n|\t\n|\n|\n|\n");
		break;

	case 5:
		printf("___________\n|\t |\n|\t_|_\n|\t O\t\n|\t\n|\t\n|\n|\n|\n");
		break;

	case 4:
		printf(
				"___________ \n|\t |\n|\t_|_\n|\t O\t\n|\t |\t\n|\t\n|\n|\n|\n\n");
		break;

	case 3:
		printf(
				"___________   \n|         |   \n|        _|_\n|         O    \n|        /|    \n|         \n| \n| \n| \n\n");
		break;

	case 2:
		printf(
				"___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|         \n| \n| \n| \n\n");
		break;

	case 1:
		printf(
				"___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        /  \n| \n| \n| \n\n");
		break;
	case 0:
		printf(
				"___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        / \\ \n| \n| \n| \n\n");
		break;
	case -1:
		printf(
				"___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        / \\ \n| \n| \n| \n\n");
		break;
	}
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
		if (!((nome[i] >= 'a' && nome[i] <= 'z') || (nome[i] >= 'A' && nome[i] <= 'Z'))) {
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
		printf("Digite novamente!Pressione a tecla ENTER para continuar ir ao menu principal!\n");
		critica = 1;
	}
	if (critica == 0) {
		printf("Corfima %s (S/N): ", nome);
		while (getchar() != '\n');
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

