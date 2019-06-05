#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Node{
		int info;
		int alt;
		struct Node *esq;
		struct Node *dir;
	}node;

node *inicia(){
	node *raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}

int alt_No(struct Node *no){
	if(no == NULL) return -1;
	else return no->alt;
}

int fat_bal(node *no){
	return abs((alt_No(no->esq)) - (alt_No(no->dir)));
}

int maior(int x, int y){
	if(x > y) return x;
	else return y;
}

void rotacaoLL(node **raiz){
	node *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = maior(alt_No((*raiz)->esq),alt_No((*raiz)->dir)) + 1;
	no->alt = maior(alt_No(no->esq), (*raiz)->alt) + 1;
	*raiz = no;
}

void rotacaoRR(node **raiz){
	node *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->alt = maior(alt_No((*raiz)->esq),alt_No((*raiz)->dir)) + 1;
	no->alt = maior(alt_No(no->dir), (*raiz)->alt) + 1;
	*raiz = no;
}

void rotacaoLR(node **raiz){
	rotacaoRR(&(*raiz)->esq);
	rotacaoLL(raiz);	
}

void rotacaoRL(node **raiz){
	rotacaoLL(&(*raiz)->dir);
	rotacaoRR(raiz);
}

int insere(node **raiz, int valor){
	int res;
	if(*raiz == NULL){
		node *novo = (node*)malloc(sizeof(node));
		if(novo == NULL) return 0;
		novo->info = valor;
		novo->alt = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}
	node *atual = *raiz;
	if(valor < atual->info){
		if((res = insere(&(atual->esq), valor)) == 1){
			if(fat_bal(atual) >= 2){
				if(valor < (*raiz)->esq->info){
					rotacaoLL(raiz);
				}
				else{
					rotacaoLR(raiz);
				}
			}
		}
	}
	else{
		if((res = insere(&(atual->dir), valor)) == 1){
			if(fat_bal(atual) >= 2){
				if((*raiz)->dir->info < valor){
					rotacaoRR(raiz);
				}
				else{
					rotacaoRL(raiz);
				}
			}
		}
	}
	atual->alt = maior(alt_No(atual->esq),alt_No(atual->dir)) + 1;
	return res;
}

void busca(node *raiz, int valor){
	node *no = raiz;
	if(raiz == NULL){
		return;
	}
	if(valor < no->info){
		printf("%d->esq->",no->info);
		busca(no->esq, valor);
		return;
	}
	if(valor > no->info){
		printf("%d->dir->",no->info);
		busca(no->dir, valor);
		return;
	}
	printf("%d:\n",no->info);
	return;
}

int main(int argc, char* argv[]){
	node* raiz = inicia();
	int n;
	n = 1;
	n =-labs(n);
	printf("=%d=",n);
	insere(&raiz, 7);
	busca(raiz, 7);
	return 0;
}
