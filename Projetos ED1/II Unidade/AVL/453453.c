#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node{
	int key;
	int fb;
	struct Node *pai;
	struct Node *esq;
	struct Node *dir;
}node;

node *inicia(){
	node *raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}

void rotacaoLL(node **raiz){
	node *eixo = (*raiz)->esq;
	(*raiz)->esq = eixo->dir;
	eixo->dir = *raiz;
	*raiz = eixo;
	fat_bal(&(*raiz)->dir);
}

void rotacaoRR(node **raiz){
	node *eixo = (*raiz)->dir;
	(*raiz)->dir = eixo->esq;
	eixo->esq = *raiz;
	*raiz = eixo;
	fat_bal(&(*raiz)->esq);
}

void rotacaoLR(node **raiz){
	rotacaoRR(&(*raiz)->esq);
	rotacaoLL(raiz);
}

void rotacaoRL(node **raiz){
	rotacaoLL(&(*raiz)->dir);
	rotacaoRR(raiz);
}

void fat_bal(node **raiz){
	if(((*raiz)->dir == NULL) && ((*raiz)->esq == NULL)){
		(*raiz)->fab = 0;
	}
	else if((*raiz)->dir == NULL){
		(*raiz)->fab = -labs((*raiz)->esq->fab) + 1;
		if((*raiz)->fab < -1){
			if((*raiz)->esq->fab < 0){
				rotacaoLL(raiz);
			}
			if((*raiz)->esq->fab > 0){
				//rotacaoLR
			}
		}
	}
	else if((*raiz)->esq == NULL){
		(*raiz)->fab = labs((*raiz)->dir->fab) + 1;
		if((*raiz)->fab > 1){
			if((*raiz)->dir->fab > 0){
				//rotacaoRR
			}
			if((*raiz)-dir->fab < 0){
				//rotacaoRL
			}
		}
	}
	else if(((*raiz)->dir != NULL) && ((*raiz)->esq != NULL)){
		(*raiz)->fab = labs((*raiz)->dir->fab) - labs((*raiz)->esq->fab);
		if((*raiz)->fab < -1){
			if((*raiz)->esq->fab < 0){
				//ROTACAOLL
			}
			if((*raiz)->esq->fab > 0){
				//rotacaoLR
			}
		}
		if((*raiz)->fab > 1){
			if((*raiz)->dir->fab > 0){
				//rotacaoRR
			}
			if((*raiz)-dir->fab < 0){
				//rotacaoRL
			}
		}
	}
	if((*raiz)->pai == NULL) return;
	fat_bal(&(*raiz)->pai);
}

void insere(node **raiz, int k){
	if(*raiz == NULL){
		node *no = (node*)malloc(sizeof(node));
		no->key = k;
		no->fab = 0;
		no->pai = NULL;
		no->esq = NULL;
		no->dir = NULL;
		*raiz = no;
		return;
	}
	if((*raiz)->key > k){
		insere((*raiz)->esq, k);
			(*raiz)->esq->pai = *raiz;
				fat_bal(raiz);
			if((*raiz)->fab < -1){
				if((*raiz)->)
			}
			
	}
}
