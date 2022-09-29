// Trabalho Algoritmos 2 - BINGO.
// Universidade do Vale do Itajai.
// Professor: Rafeal Ballottin Martins.
// Cursos: Engenharia da Computação e Ciência da Computação.
// Aluno: Yuri Rodrigues.
// Data de Conclusao: 07/09/2022.
#include <iostream>
#include <Windows.h>
#include <clocale>
#include <ctime>
#include <cstdlib>
#include <cstring>
//Definições das cores
#define BLACK        0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GREY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15
#define TAM 5 // Tamanho da matriz (cartela).
#define TAMVET 75 // Números sorteados a serem mostrados.

using namespace std;

void textcolor(int forecolor, int backcolor) { // Função para mudar as cores das letras.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(forecolor | backcolor << 4));
}

void cartela(int matriz[][TAM]) { // Fazer a cartela gerando os números conforme cada case.
	int linha, coluna, num, j, cond;

	for (linha = 0; linha < TAM; linha++) {
		for (coluna = 0; coluna < TAM; coluna++) {
			cond = 1;
			while (cond == 1) {
				cond = 0;
				switch (linha) { // Nesse switch, irá gerar os números conforme cada rand. Na primeira linha, irá gerar números de 1 á 15 e assim por diante.
				case 0:
					num = rand() % 15 + 1; // 1 á 15.
					break;
				case 1:
					num = rand() % 15 + 16; // 16 á 30.
					break;
				case 2:
					num = rand() % 15 + 31; // 31 á 45.
					break;
				case 3:
					num = rand() % 15 + 46; // 46 á 60.
					break;
				case 4:
					num = rand() % 15 + 61; // 61 á 75.
					break;
				}
				for (j = 0; j < TAM; j++) { // Verificador de números. Se algum número da linha for igual, irá gerar outros números.
					if (matriz[linha][j] == num) {
						cond = 1;
					}
				}
			}
			matriz[linha][coluna] = num; // Saída da matriz caso cond = 0.
		}
	}
}

void ordenar(int matriz[][TAM]) { // Ordenar a matriz em cada linha, no estilo BubbleSort.
	int i, j, cond, temp, linha = 0, coluna, vet[TAM];

	for (linha = 0; linha < TAM; linha++) {
		for (coluna = 0; coluna < TAM; coluna++) {
			vet[coluna] = matriz[linha][coluna];
		}
		cond = 1;
		for (i = TAM - 1; (TAM >= 1) && (cond == 1); i--) {
			cond = 0;
			for (j = 0; j < i; j++) {
				if (vet[j + 1] < vet[j]) {
					temp = vet[j];
					vet[j] = vet[j + 1];
					vet[j + 1] = temp;
					cond = 1;
				}
			}
		}
		for (coluna = 0; coluna < TAM; coluna++) { // Se tudo ordenado, os números irão para a matriz em cada linha correspondente.
			matriz[linha][coluna] = vet[coluna];
		}
	}
}

void sorteia1(int vet[]) { // Sortear um número por vez.
	int i, num, cond = 0;

	while (cond == 0) {
		num = rand() % TAMVET + 1;
		for (i = 0; i < TAMVET; i++) {
			if (vet[i] == 0) {
				vet[i] = num;
				cond = 1;
				break;
			}
			else if (vet[i] == num) {
				break;
			}
		}
	}
}

void imprimirVet(int* vet) { // Mostrar os números já sorteados
	cout << "\nOs numeros sorteados foram estes: ";
	for (int i = 0; i < TAMVET; i++) {
		if (vet[i] != 0) {
			textcolor(RED, BLACK);
			cout << "" << vet[i]<<" - ";
		}
		textcolor(WHITE, BLACK);
	}
	cout << endl;
}


void imprime(int matriz[][TAM], int vet[]) { // Função para mostrar as 5 cartelas.
	int linha = 0, coluna, i, cond = 0, temp = 0;

	for (linha = 0; linha < TAM; linha++) {
		for (coluna = 0; coluna < TAM; coluna++) {
			cond = 0;
			for (i = 0; i < TAMVET; i++) {
				if (vet[i] == matriz[linha][coluna]) {
					cond = 1;
				}
			}
			if (cond == 1) { // Se o número sorteado for igual ao número que tiver na cartela, o número estará na cor vermelho.
				textcolor(RED, BLACK);
				cout << matriz[linha][coluna] << "\t";
				temp++;
			}
			else { // Se não estiver em vermelho, mostrará em branco.
				textcolor(WHITE, BLACK);
				cout << matriz[linha][coluna] << "\t";
			}
		}
		cout << endl << endl;
		textcolor(WHITE, BLACK);
	}
}

int verificarDuasMat(int c1[][TAM], int c2[][TAM]) { // Função  para verificar os valores das matrizes, se uma matriz for igual a outra.
	int linha, coluna;
	for (linha = 0; linha < TAM; linha++) {
		for (coluna = 0; coluna < TAM; coluna++) {
			if (c1[linha][coluna] != c2[linha][coluna]) {
				return 1; // Retornar 1 caso for diferente.
			}
		}
	}
	return 0; // Retornar 0 caso for igual.
}

void verificaECriaTabela(int c1[][TAM], int c2[][TAM], int c3[][TAM], int c4[][TAM], int c5[][TAM]) {// Função para verificar a igualdade das matrizes.
	int linha, coluna, cond = 0;

	do {

		cond = 1;

		cartela(c1);
		cartela(c2);
		cartela(c3);
		cartela(c4);
		cartela(c5);

		// Se as matrizes forem iguais, o cond será igual a 0 e irá gerar novas cartelas.
		if (verificarDuasMat(c1, c2) == 0 || verificarDuasMat(c1, c3) == 0 || verificarDuasMat(c1, c4) == 0 || verificarDuasMat(c1, c5) == 0) {
			cond = 0;
		}
		if (verificarDuasMat(c2, c3) == 0 || verificarDuasMat(c2, c4) == 0 || verificarDuasMat(c2, c5) == 0) {
			cond = 0;
		}
		if (verificarDuasMat(c3, c4) == 0 || verificarDuasMat(c3, c5) == 0) {
			cond = 0;
		}
		if (verificarDuasMat(c4, c5) == 0) {
			cond = 0;
		}
	} while (cond == 0);// Só vai finalizar o processo quando o cond for diferente de 0.
}

void vencedor(int vet[], int mat[][TAM], string nome, int& stop, int numC) {// Função para indicar o vencedor.
	int linha, coluna, i, temp = 0;
	for (linha = 0; linha < TAM; linha++) {
		for (coluna = 0; coluna < TAM; coluna++) {
			for (i = 0; i < TAMVET; i++) {
				if (mat[linha][coluna] == vet[i]) {
					temp++;
				}
			}
		}
	}
	if (temp == 25) {// Se o temp for igual a 25 o vencedor é indicado.
		textcolor(AQUA, BLACK);
		cout << "\n" << nome << ", voce eh o vencedor do BINGO!" << endl;
		cout << "Cartela " << numC << ": " << endl << endl;
		for (linha = 0; linha < TAM; linha++) {
			for (coluna = 0; coluna < TAM; coluna++) {
				textcolor(RED, BLACK);
				cout << mat[linha][coluna] << "\t";
			}
			cout << endl << endl;
		}
		textcolor(WHITE, BLACK);
		stop = 1;
	}
}

void mostrarCartela(string nome, int n, int mat[][TAM], int vet[]) {
	textcolor(LIGHTRED, BLACK);
	cout << "\n" << nome;
	textcolor(AQUA, BLACK);
	cout << "\nCartela " << n << ":" << endl << endl;
	textcolor(WHITE, BLACK);
	imprime(mat, vet);
}
void game() {// Função do jogo com pausas.
	int vet[TAMVET] = { 0 };
	int	c1[TAM][TAM], c2[TAM][TAM], c3[TAM][TAM], c4[TAM][TAM], c5[TAM][TAM];
	int stop = 0; // Solicitar os nomes.
	string n1, n2, n3, n4, n5;
	textcolor(AQUA, BLACK);
	cout << "\nDigite o nome do primeiro jogador: ";
	textcolor(LIGHTRED, BLACK);
	cin >> n1;
	textcolor(AQUA, BLACK);
	cout << "\nDigite o nome do segundo jogador: ";
	textcolor(LIGHTRED, BLACK);
	cin >> n2;
	textcolor(AQUA, BLACK);
	cout << "\nDigite o nome do terceiro jogador: ";
	textcolor(LIGHTRED, BLACK);
	cin >> n3;
	textcolor(AQUA, BLACK);
	cout << "\nDigite o nome do quarto jogador: ";
	textcolor(LIGHTRED, BLACK);
	cin >> n4;
	textcolor(AQUA, BLACK);
	cout << "\nDigite o nome do quinto jogador: ";
	textcolor(LIGHTRED, BLACK);
	cin >> n5;

	system("cls");

	verificaECriaTabela(c1, c2, c3, c4, c5); // Verificar as cartelas, se possui alguma cartela completamente repetida.

	ordenar(c1);// Ordena as tabelas.
	ordenar(c2);
	ordenar(c3);
	ordenar(c4);
	ordenar(c5);

	textcolor(BLUE, BLACK);
	cout << "__________CARTELAS__________" << endl;
	mostrarCartela(n1, 1, c1, vet);
	mostrarCartela(n2, 2, c2, vet);
	mostrarCartela(n3, 3, c3, vet);
	mostrarCartela(n4, 4, c4, vet);
	mostrarCartela(n5, 4, c5, vet);
	system("pause");

	while (stop == 0) { // Parar o jogo se stop = 1 e todos os números da cartela serem preenchidas por vermelho, ou seja, já sorteados.

		system("cls");
		textcolor(AQUA, BLACK);
		cout << "-----BINGO-----" << endl;
		textcolor(WHITE, BLACK);
		sorteia1(vet);
		imprimirVet(vet);

		mostrarCartela(n1, 1, c1, vet);
		mostrarCartela(n2, 2, c2, vet);
		mostrarCartela(n3, 3, c3, vet);
		mostrarCartela(n4, 4, c4, vet);
		mostrarCartela(n5, 4, c5, vet);
		system("pause");
		system("cls");

		vencedor(vet, c1, n1, stop, 1);// Aqui é as chamadas de função para verificar quem foi o campeão.
		vencedor(vet, c2, n2, stop, 2);
		vencedor(vet, c3, n3, stop, 3);
		vencedor(vet, c4, n4, stop, 4);
		vencedor(vet, c5, n5, stop, 5);
	}
}



int main()
{
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	int escolha;

	int vetor[75] = { 0 };
	for (int i = 0; i < 75; i++) {
		//sorteia1(vetor);
	}

	//bubbleSort(vetor, 75);

	for (int i = 0; i < 75; i++) {
		///cout << vetor[i] << " ";
	}
	
	do { // Menu Inicial

		textcolor(AQUA, BLACK);
		cout << "|------------------------|" << endl;
		textcolor(LIGHTGREEN, BLACK);
		cout << "|          MENU          |" << endl;
		textcolor(AQUA, BLACK);
		cout << "|------------------------|" << endl;
		cout << "|                        |" << endl;
		textcolor(LIGHTGREEN, BLACK);
		cout << "|1:Jogo                  |" << endl;
		textcolor(AQUA, BLACK);
		cout << "|                        |" << endl;
		textcolor(LIGHTGREEN, BLACK);
		cout << "|2:Creditos              |" << endl;
		textcolor(AQUA, BLACK);
		cout << "|                        |" << endl;
		textcolor(LIGHTGREEN, BLACK);
		cout << "|3:Sair                  |" << endl;
		textcolor(AQUA, BLACK);
		cout << "|                        |" << endl;
		cout << "|------------------------|";
		cout << "\n|Ecolha uma das opcoes: ";
		cin >> escolha;
		system("cls");

		switch (escolha) {
		case 1:
			game();// Jogo com pausas.
			system("pause");
			system("cls");
			break;
		case 2:// Creditos.
			textcolor(LIGHTRED, BLACK);
			cout << "Trabalho Algoritmos 2 - BINGO." << endl;
			cout << "Universidade do Vale do Itajai" << endl;
			cout << "Professor: Rafeal Ballottin Martins." << endl;
			cout << "Cursos: Engenharia da Computação e Ciência da Computação." << endl;
			cout << "Aluno: Yuri Rodrigues." << endl;
			cout << "Data de Conclusao: 06/09/2022." << endl << endl;
			textcolor(WHITE, BLACK);
			system("pause");
			system("cls");
			break;
		case 3:// Sair do jogo.
			textcolor(WHITE, BLACK);
			break;
		default:
			cout << "Opção invalida!" << endl;
			system("pause");
			system("cls");
			break;
		}
	} while (escolha != 3);
}
