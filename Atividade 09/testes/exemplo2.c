#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
void delay();
int inserir();
void menu();
void insereArq();
void historico();
void limpaHistorico();

FILE* ArqMusica;

typedef struct musica{
		char nome[200];
		char autor[200];
		struct musica *prox;
}musica;

typedef struct head{
		musica *first;
	}head;
	
head *inicia(){
	head *h =  (head*) malloc(sizeof(head));
	h->first = NULL;
	return h;
}

musica *busca(char nome[200], head *h){
	musica *m;
	m = h->first;
	if(h->first == NULL){
		return NULL;
	}
	else if(strcmp(nome, m->nome) == 0){
		return m;
	}
	while(m->prox != NULL){
		m = m->prox;
		if(strcmp(nome,m->nome) == 0){
			return m;
		}
	}
	return NULL;
}

void consultar(head *h){
	int op;
	
	if(h->first == NULL){
		printf("                       ");
		printf("Lista vazia!\n\n");
		printf("                       ");
		printf("Deseja inserir novas?\n");
		printf("                       ");
		printf("Sim(1)/Nao(0):");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
	return;
	}
	
	musica *m = (musica*)malloc(sizeof(musica));
	char nome[200];
	
	system("cls");
	printf("                       ");
	printf("          CONSULTAR\n");
	
	printf("                       ");
	printf("Insira o nome da musica: ");
	scanf("%s",nome);
	m = busca(nome,h);
	if(m == NULL){
		printf("                       ");
		printf("Esta musica n se encontra na lista!\n");
		printf("                       ");
		printf("Deseja consultar outro autor sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if(op == 1) consultar(h);
	return;
	}
		printf("                       ");
		printf("Musica: %s\n",m->nome);
		printf("                       ");
		printf("Autor: %s\n",m->autor);
		printf("                       ");
		printf("Deseja consultar outro autor sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if(op == 1) consultar(h);
return;
}

int inserir(head *h){
	char nome[200];
	int op = 0;
	musica *m = (musica*)malloc(sizeof(musica));
	musica *atual, *prox;
	
	system("cls");
	printf("                       ");
	printf("          INSERIR\n");
	
	if(!m) {
		printf("                       ");
		puts("Falha na alocacao!\n");
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return 0;
	}
	m->nome[0]='\0';
	m->autor[0]='\0';
	m->prox = NULL;
		printf("                       ");
		printf("Insira o nome da musica: ");
		scanf(" %[^\n]s",nome);
	if(busca(nome,h) != 0){
		printf("                       ");
		puts("Esta musica ja foi inserida!\n");
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return 0;
	}
	
	strcpy(m->nome,nome);
		printf("                       ");
		printf("Insira o nome do autor: ");
		scanf(" %[^\n]s",m->autor);
	
	if(h->first == NULL){
		h->first = m;
		insereArq(m);
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return 1;
	}
	
	atual = h->first;
	
	if(strcmp(nome,atual->nome) < 0){
		h->first = m;
		insereArq(m);
		m->prox = atual;
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return 1;
	}
	
	while(atual->prox != NULL){
		prox = atual->prox;
		if(strcmp(nome,prox->nome) < 0){
			atual->prox = m;
			m->prox = prox;
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
			return 1;
		}
		atual = atual->prox;
	}
	
	 prox = atual->prox;
	 atual->prox = m;
		insereArq(m);
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
	 return 1;
}

void insereArq(musica *m){
	ArqMusica = fopen("historico.dat","ab");
	fwrite(m->nome,sizeof(char),200,ArqMusica);
	fwrite(m->autor,sizeof(char),200,ArqMusica);
	fclose(ArqMusica);
}

void remover(head *h){
	char nome[200];
	int op=0;
	if(h->first == NULL){
		printf("                       ");
		puts("Lista vazia!\n");
		printf("                       ");
		printf("Deseja inserir novas?\n");
		printf("                       ");
		printf("Sim(1)/Nao(0):");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return;
	}
	
	system("cls");
	printf("                       ");
	printf("          REMOVER\n");
	
	
	if(h->first == NULL){
		printf("                       ");
		printf("N removeu!\n");
		printf("                       ");
		printf("Deseja inserir outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		if (op == 1) remover(h);
		return;
	}
	musica *m = h->first, *aux;
		printf("                       ");
	printf("Insira o nome da musica a ser removida: ");
	scanf(" %[^\n]s",nome);
	if (busca(nome, h) == 0){
		printf("                       ");
		printf("N removeu!\n");
		printf("                       ");
		printf("Deseja remover outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) remover(h);
		return;
	}
	
	if(strcmp(nome, m->nome)  == 0){
		h->first = m->prox;
		free(m);
		printf("                       ");
		printf("Removeu!\n");
		printf("                       ");
		printf("Deseja remover outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) remover(h);
		return;
	}
	while(m->prox != NULL){
		if(strcmp(nome, m->prox->nome) == 0){
			aux = m->prox;
			m->prox = m->prox->prox;
			free(aux);
		printf("                       ");
		printf("Removeu!\n");
		printf("                       ");
		printf("Deseja remover outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) remover(h);
			return;
		}
		m = m->prox;
	}
		printf("                       ");
		printf("N removeu!\n");
		printf("                       ");
		printf("Deseja remover outra Sim(1)/Nao(0): ");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) remover(h);
	return;
}

void mostrar(head *h){
	int op;
	if(h->first == NULL){
		printf("                       ");
		puts("Lista vazia!\n");
		printf("                       ");
		printf("Deseja inserir novas?\n");
		printf("                       ");
		printf("Sim(1)/Nao(0):");
		scanf("%d",&op);
		if (op == 1) inserir(h);
		return;
	}
	
	system("cls");
	printf("                       ");
	printf("          MOSTRAR\n");
	
	
	musica *m;
	m = h->first;
	while(m != NULL){
		printf("                       ");
		printf("Musica: %s\n",m->nome);
		printf("                       ");
		printf("Autor: %s\n\n",m->autor);
		m = m->prox;
	}
		printf("                       ");
		system("pause");
	return;
}

void delay(unsigned int msec){
    clock_t lim = msec + clock();
    while (lim > clock());
}

void tocar(head *h){
	int op;
	if(h->first == NULL){
		printf("                       ");
		printf("Sem musicas na lista de reproducao!\n");
		printf("                       ");
		printf("Deseja inserir novas?\n");
		printf("                       ");
		printf("Sim(1)/Nao(0):");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
		return;
	}
	musica *aux;
	musica *m = (musica*)malloc(sizeof(musica));
	int i,x=5;
	char bar[33]="|                              |";
	while(h->first != NULL){
		m = h->first;
		insereArq(m); //insere o nome e o autor do primeiro no no arquivo e como ele o remove dps, e faz isso até o fim da lista, ele insere todos os nome e autores no arquivo
		m = NULL;
		for(i=1;i<31;i++){
			system("cls");
			printf("                       ");
			printf("Tocando...\n");
			printf("                       ");
			printf("Musica: %s\n",h->first->nome);
			printf("                       ");
			printf("Autor: %s\n",h->first->autor);
			if(i%2 == 0) bar[i]= '-';
			else bar[i] = '_'; 
			printf("                       ");
			printf("%s",bar);
			if(i==6 || i==12 || i==18 || i==24 || i==30) x--;
			printf(" 00:0%d",x);
			if(i%2 == 0) printf(" Tuts...");
			else         printf("        Tuts...\n");
			delay(50);
		}
		strcpy(bar,"|                              |");
		x = 5;
		aux = h->first->prox;
		free(h->first);
		h->first = aux;
	}
		
		system("cls");
		printf("                       ");
		printf("Todas as musicas ja foram reporduzidas!\n");
		printf("                       ");
		printf("Deseja inserir novas?\n");
		printf("                       ");
		printf("Sim(1)/Nao(0):");
		scanf("%d",&op);
		while(op != 0 && op != 1){
			printf("                       ");
			printf("Insira uma opcao valida:");
			scanf("%d",&op);
		}
		if (op == 1) inserir(h);
	return;
}

void tocarArq(){
	
}

void historico(){
	system("cls");
	printf("                       ");
	printf("          HISTORICO\n");
	ArqMusica = fopen("historico.dat","rb");
	if (!ArqMusica){
		printf("\nErro ao abrir arquivo\n");
		return;
	}
	fseek(ArqMusica,0,2);
	long int tamanho = ftell(ArqMusica);
	if(tamanho < 400){
		printf("Historico vazio! Arquivo com %ld bytes sendo 400 por musica\n",tamanho);
		system("pause");
		return;
	}
	char nome[200],autor[200];
	long int cursor = fseek(ArqMusica,0,0);
	int cont=0;
	while(cursor < tamanho){
		fread(nome,sizeof(char),200,ArqMusica);
		printf("\nNome: %s\n",nome);
		fread(autor,sizeof(char),200,ArqMusica);
		printf("Autor: %s\n",autor);
		cursor = ftell(ArqMusica);
		cont++;
	}
	printf("\nSeu historico possui %d musica(s)!\n",cont);
	fclose(ArqMusica);
	system("pause");
}

void limpaHistorico(){
	system("cls");
	printf("                       ");
	printf("     LIMPA HISTORICO\n");
	ArqMusica = fopen("historico.dat","rb");
	if (!ArqMusica){
		printf("\nErro ao abrir arquivo\n");
		return;
	}
	fseek(ArqMusica,0,2);
	long int tamanho = ftell(ArqMusica);
	if(tamanho < 400){
		printf("\nHistorico ja vazio! Arquivo possui %ld bytes sendo 400 bytes por musica\n",tamanho);
		printf("Deseja limpar mesmo assim? Sim(1)/Nao(0)\n");
		int op;
		scanf("%d",&op);
		if(op == 0){
			return;
		}
		else{
				ArqMusica = fopen("historico.dat","wb");
				fclose(ArqMusica);
				printf("\nFEITO!\n");
				system("pause");
		}
	}
	else{
			ArqMusica = fopen("historico.dat","wb");
			fclose(ArqMusica);
			printf("\nFEITO!\n");
			system("pause");
	}
	
}

void menu(head *h){
		int op = 0;
		do{
			system("cls");
			printf("                       ########################################\n");
			printf("                       #                                      #\n");
			printf("                       #    SIMULADOR DE TOCADOR DE MUSICA    #\n");
			printf("                       #                                      #\n");
			printf("                       ########################################\n");
			printf("                       #                                      #\n");
			printf("                       # 1 - Inserir                          #\n");
			printf("                       # 2 - Consultar Autor                  #\n");
			printf("                       # 3 - Remover                          #\n");
			printf("                       # 4 - Mostrar Lista Ordenada           #\n");
			printf("                       # 5 - Tocar                            #\n");
			printf("                       # 6 - Historico                        #\n");
			printf("                       # 7 - Limpar Historico                 #\n");
			printf("                       # 0 - Sair                             #\n");
			printf("                       #                                      #\n");
			printf("                       ########################################\n");
			printf("                       O que deseja fazer: ");
			scanf("%d",&op);
			while(op != 0 && op!= 1 && op!= 2 && op!= 3 && op!= 4 && op!= 5 && op!= 6 && op!= 7){
				printf("                       ");
			printf("Insira uma opcao valida!");
				delay(500);
				menu(h);
			}
			switch(op){
				case 1: inserir(h); break;
				case 2: consultar(h); break;
				case 3: remover(h); break;
				case 4: mostrar(h); break;
				case 5: tocar(h); break;
				case 6: historico(); break;
				case 7: limpaHistorico(); break;
			}
			printf("\n");
		}while(op != 0);
		
		printf("                                            ");
		printf("Bye Bye !");
		
	return;
}

int main(){
		head *h = inicia();
		menu(h);
	return 0;
}
