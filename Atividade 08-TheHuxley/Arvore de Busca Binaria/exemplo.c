#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
FILE* input;
FILE* output;
typedef struct Node{
		char info[200];
		int nsin;
		char sin[200][200];
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
	return fabs((alt_No(no->esq)) - (alt_No(no->dir)));
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

int insere(node **raiz, char valor[200]){
	if(*raiz == NULL){
		node *novo = (node*)malloc(sizeof(node));
		if(novo == NULL) return 0;
		int nsin,i;
		fscanf(input,"%d%*c",&nsin);
		novo->nsin = nsin;
			for(i=0;i<nsin;i++){
				fscanf(input,"%s%*c",novo->sin[i]);
			}
		strcpy(novo->info,valor);
		novo->alt = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}
	node *atual = *raiz;
	if(strcmp(valor,atual->info) < 0){
			insere(&(atual->esq), valor);
			if(fat_bal(atual) > 1){
				if(strcmp(valor,atual->esq->info) < 0){
					rotacaoLL(raiz);
				}
				else{
					rotacaoLR(raiz);
				}
			}
		
	}
	else{
			insere(&(atual->esq), valor);
				if(fat_bal(atual) > 1){
					if(strcmp(atual->dir->info,valor) < 0){
						rotacaoRR(raiz);
					}
					else{
						rotacaoRL(raiz);
					}
				}
			
	}
	atual->alt = maior(alt_No(atual->esq),alt_No(atual->dir)) + 1;
	return 1;
}

void busca(node *raiz, char valor[200]){
	node *no = raiz;
	int i;
	if(raiz == NULL){
		fprintf(output,"?:\n");
		fprintf(output,"[-]\n");
		return;
	}
	if(strcmp(valor,no->info) < 0){
		fprintf(output,"%s->",no->info);
		busca(no->esq, valor);
		return;
	}
	if(strcmp(valor,no->info) > 0){
		fprintf(output,"%s->",no->info);
		busca(no->dir, valor);
		return;
	}
	fprintf(output,"%s:\n",no->info);
		fprintf(output,"[");
		for(i=0;i<no->nsin;i++){
			fprintf(output,"%s",no->sin[i]);
			if(i == (no->nsin) - 1) break;
			fprintf(output,", ");
		}
		fprintf(output,"]\n");
	return;
}

int main(int argc, char* argv[]){
	input = fopen("dicionario.input.txt","r");
	output = fopen("output_1.txt","w");
	node* raiz = inicia();
	int npal,i,ncon;
	char pal[200]={0},con[200]={0};
		fscanf(input,"%d%*c",&npal);
		for(i=0;i<npal;i++){
			fscanf(input,"%s%*c",pal);
			insere(&raiz,pal);
			pal[0] = '\0';
		}
			fscanf(input,"%d%*c",&ncon);
			for(i=0;i<ncon;i++){
				fscanf(input,"%s%*c",con);
				busca(raiz,con);
				con[0] = '\0';
			}
				
	return 0;
}
