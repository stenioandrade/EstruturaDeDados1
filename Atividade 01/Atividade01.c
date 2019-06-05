#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
void delay();
int inserir();
void menu();
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
	int i,x=5;
	char bar[33]="|                              |";
	while(h->first != NULL){
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
			delay(250);
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
			printf("                       # 0 - Sair                             #\n");
			printf("                       #                                      #\n");
			printf("                       ########################################\n");
			printf("                       O que deseja fazer: ");
			scanf("%d",&op);
			while(op != 0 && op!= 1 && op!= 2 && op!= 3 && op!= 4 && op!= 5){
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
