/**      @file: 150015585_trabalho01.c
 *     @author: Luan Mendes Gonçalves Freitas
 * @disciplina: Algoritmos e Programação de Computadores
 *      @turma: G
 *      @trabalho 1 - Jogo da Forca 1.0 */

#include <stdio.h>
#include <stdlib.h>

int main() {

	int opcaoMenu;
	int novoNivel, i, tamanho = 0;
	char novaPalavraSecreta[100];
	char palavraSecreta1[5] = { "peru\0" };
	char palavraSecreta2[7] = { "turing\0" };
	char palavraSecreta3[9] = { "elefante\0" };
	int vida = 6, nivel = 1;
	char resposta[10], erro[7], letra, buffer[100];
	int certo, pontos = 0, indiceErro = 0, terminarJogo = 0;
	printf("Bem vindo ao jogo : Jogo da Forca\nPressione a tecla ENTER para continuar ir ao menu principal!");
	getchar();
	do {
		printf("Escolha uma opção do menu:\n1 - Jogar\n2 - Configurações\n3 - Ranking\n0 - Sair do jogo\n");
		scanf("%d", &opcaoMenu);
		switch (opcaoMenu) {
		case 1:
			nivel = 1;
			vida = 6;
			pontos = 0;
			terminarJogo = 0;
			tamanho = 4;
			indiceErro = 0;
			for (i = 0; i < tamanho; i++) {
				resposta[i] = '-';
			}
			resposta[i] = '\0';
			for (i = 0; i < 6; i++) {
				erro[i] = ' ';
			}
			erro[i] = '\0';
			while (getchar() != '\n')
				;
			while (vida > 0) { /* exibir a tela de jogo */
				printf("Nivel %d\n", nivel);
				switch (vida) {
				case 6:
					printf("___________\n|\t |\n|\t_|_\n|\t\n|\t\n|\t\n|\n|\n|\n");
					break;

				case 5:
					printf("___________\n|\t |\n|\t_|_\n|\t O\t\n|\t\n|\t\n|\n|\n|\n");
					break;

				case 4:
					printf("___________ \n|\t |\n|\t_|_\n|\t O\t\n|\t |\t\n|\t\n|\n|\n|\n\n");
					break;

				case 3:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|    \n|         \n| \n| \n| \n\n");
					break;

				case 2:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|         \n| \n| \n| \n\n");
					break;

				case 1:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        /  \n| \n| \n| \n\n");
					break;
				case 0:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        / \\ \n| \n| \n| \n\n");
					break;
				default:
					printf("codigo inválido\n");
					break;
				}
				printf("%s\n", resposta);
				printf("Letras Digitadas\n%s\n", erro);

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
				certo = 0;
				/* verificar se existir a letra informada no vetor da palavraSecreta */
				if (nivel == 1) {
					for (i = 0; i < 4; i++) {
						if (letra == palavraSecreta1[i]) {
							certo = 1;
							if (resposta[i] == '-') {
								resposta[i] = letra; /* revela a letra */
								pontos++; /* controla a quantidade de acertos */
							}
						}
					}
				} else if (nivel == 2) {
					for (i = 0; i < 6; i++) {
						if (nivel == 2 && letra == palavraSecreta2[i]) {
							certo = 1;
							if (resposta[i] == '-') {
								resposta[i] = letra; /* revela a letra */
								pontos++; /* controla a quantidade de acertos */
							}
						}
					}
				} else if (nivel == 3) {
					for (i = 0; i < 8; i++) {
						if (nivel == 3 && letra == palavraSecreta3[i]) {
							certo = 1;
							if (resposta[i] == '-') {
								resposta[i] = letra; /* revela a letra */
								pontos++; /* controla a quantidade de acertos */
							}
						}
					}
				}
				/* verificar se acertou a letra e numero de vidas no nivel */
				if (certo == 0) {
					vida--;
					if (vida == 0) { /* verifica se perdeu todas as vidas e perdeu o jogo */
						printf("Nivel %d\n", nivel);
						printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        / \\ \n| \n| \n| \n\n");
						printf("%s\n", resposta);
						printf("Letras Digitadas\n%s\n", erro);
						printf("Você perdeu :(\n");
					} else {
						erro[indiceErro] = letra; /* exibir a letra digita errado */
						indiceErro++;
					}
				} else {
					if (nivel == 1 && pontos == 4) { /* verifica se acertou todos as letra da palavra */
						nivel += 1;
						vida = 6;
						pontos = 0;
						tamanho = 6;
						indiceErro = 0;
						for (i = 0; i < tamanho; i++) {
							resposta[i] = '-';
						}
						resposta[i] = '\0';
						for (i = 0; i < 6; i++) {
							erro[i] = ' ';
						}
						erro[i] = '\0';
					} else if (nivel == 2 && pontos == 6) { /* verifica se acertou todos as letra da palavra */
						nivel += 1;
						vida = 6;
						pontos = 0;
						tamanho = 8;
						indiceErro = 0;
						for (i = 0; i < tamanho; i++) {
							resposta[i] = '-';
						}
						resposta[i] = '\0';
						for (i = 0; i < 6; i++) {
							erro[i] = ' ';
						}
						erro[i] = '\0';
					} else if (nivel == 3 && pontos == 8) { /* verifica se acertou todos as letra da palavra */
						terminarJogo = vida;
						vida = 0; /* sair do loop do jogo */
					}
				}
			}
			if (nivel == 3) {
				printf("Nivel %d\n", nivel);
				switch (terminarJogo) {
				case 6:
					printf("___________\n|\t |\n|\t_|_\n|\t\n|\t\n|\t\n|\n|\n|\n");
					break;

				case 5:
					printf("___________\n|\t |\n|\t_|_\n|\t O\t\n|\t\n|\t\n|\n|\n|\n");
					break;

				case 4:
					printf("___________ \n|\t |\n|\t_|_\n|\t O\t\n|\t |\t\n|\t\n|\n|\n|\n\n");
					break;

				case 3:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|    \n|         \n| \n| \n| \n\n");
					break;

				case 2:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|         \n| \n| \n| \n\n");
					break;

				case 1:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        /  \n| \n| \n| \n\n");
					break;
				case 0:
					printf("___________   \n|         |   \n|        _|_\n|         O    \n|        /|\\    \n|        / \\ \n| \n| \n| \n\n");
					break;
				default:
					printf("codigo inválido\n");
					break;
				}

				printf("%s\n", resposta);
				printf("Letras Digitadas\n%s\n", erro);
				printf("Venceu o jogo\n");
			}
			break;
		case 2:
			tamanho = 0;
			do {
				printf("Digite o nível que deseja alterar:\n");
				scanf("%d", &novoNivel);
				if (novoNivel < 1 || novoNivel > 3) {
					printf("Nível invalido digite novamente\n");
				}
			} while (novoNivel < 1 || novoNivel > 3);
			switch (novoNivel) {
			case 1:
				printf("Palavra secreta(Nível %d) - %s\n", novoNivel,
						palavraSecreta1);
				do {
					while (getchar() != '\n');
					printf("Digite uma nova-palavra secreta:\n");
					scanf("%[^\n]", novaPalavraSecreta);
					for (i = 0; novaPalavraSecreta[i] != '\0'; i++) {
						tamanho++;
					}
					if (tamanho != 4) {
						printf("Tamanho invalido digite novamente\n");
					}
				} while (tamanho != 4);
				for (i = 0; i < tamanho; i++) {
					palavraSecreta1[i] = novaPalavraSecreta[i];
				}
				break;
			case 2:

				printf("Palavra secreta(Nível %d) - %s\n", novoNivel,
						palavraSecreta2);
				do {
					while (getchar() != '\n')
						;
					printf("Digite uma nova-palavra secreta:\n");
					scanf("%[^\n]", novaPalavraSecreta);
					for (i = 0; novaPalavraSecreta[i] != '\0'; i++) {
						tamanho++;
					}
					if (tamanho != 6) {
						printf("Tamanho invalido digite novamente\n");
					}
				} while (tamanho != 6);
				for (i = 0; i < tamanho; i++) {
					palavraSecreta2[i] = novaPalavraSecreta[i];
				}
				break;
			case 3:
				printf("Palavra secreta(Nível %d) - %s\n", novoNivel,
						palavraSecreta3);
				do {
					while (getchar() != '\n');
					printf("Digite uma nova-palavra secreta:\n");
					scanf("%[^\n]", novaPalavraSecreta);
					for (i = 0; novaPalavraSecreta[i] != '\0'; i++) {
						tamanho++;
					}
					if (tamanho != 8) {
						printf("Tamanho invalido digite novamente\n");
					}
				} while (tamanho != 8);
				for (i = 0; i < tamanho; i++) {
					palavraSecreta3[i] = novaPalavraSecreta[i];
				}
				break;
			default:
				printf("Nivel invalido digite novamente\n");
				break;
			}
			break;
		case 3:
			printf("Rankink ainda não disponivel na versão 1.0\n");
			printf("Presione qualquer tecla para voltar ao menu\n");
			getchar();
			break;
		case 0:
			break;
		default:
			printf("Opção Errada Digite novamente\n");
		}
	} while (opcaoMenu != 0);
	printf("Programa Encerrado\n");

	return 0;
}


