#include <stdio.h>

int main(int argc, char* argv[]) {
	// Ilustrando uso de argumentos de programa
	printf("Quantidade de argumentos: %i\n", argc);
	printf("Nome do programa: %s\n", argv[0]);
	printf("Arquivo de entrada: %s\n", argv[1]);
	printf("Arquivo de saida: %s\n", argv[2]);
	// Abrindo arquivos
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");
	// Operacoes de leitura e de escrita em arquivos
	// fscanf
	// fprintf
	// Fechando arquivos
	fclose(input);
	fclose(output);
	// Finalizando programa
	return 0;
}