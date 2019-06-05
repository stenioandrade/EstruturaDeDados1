#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
		char nome[52];
		struct node *prox;
		struct node *ant;
}node;
typedef struct Head {
		node* nose;
		node* tail;
		int tamanho;
		
	}head;
head *inicia(){
	head *h = (head*) malloc(sizeof(head));
	h->nose = NULL;
	h->tail = NULL;
	h->tamanho = 0;
	return h;
}
int busca(char str[52],head *h){
	node *no = (node*)malloc(sizeof(node));
	no = h->nose;
	if(h->nose==NULL) {
		return 0;
	}
	else if(strcmp(no->nome,str)==0){
		return 1;
	}
	while(no->prox != h->nose){
		no = no->prox;
		if(strcmp(no->nome,str)==0){
			return 1;
		}
	}
	return 0;
}
void insere(FILE* output,char str[52],head *h){
	node *no;
	node *novo = (node*) malloc(sizeof(node));
	novo->nome[0]='\0';
	strcpy(novo->nome,str);
	no = h->nose;
	if(h->nose==NULL){
		fprintf(output,"[%s] ADD-OK\n",novo->nome);
			h->nose = novo;
			h->tail = novo;
			novo->ant = novo;
			novo->prox = novo;
			h->tamanho++;
			return;
	}
	while(no->prox != h->nose){
		no = no->prox;
	}
	fprintf(output,"[%s] ADD-OK\n",novo->nome);
	no->prox = novo;
	novo->ant = no;
	h->tail = novo;
	novo->prox = h->nose;
	h->nose->ant = novo;
	h->tamanho++;
	return;
}
void mostra_lista(FILE* output,char str[52],head *h){
	node *no;
		no = h->nose;
		if (no == NULL){
			return;
		}
		if (strcmp(no->nome,str)==0){
			fprintf(output,"[%s]<-[%s]->[%s]\n",no->ant->nome,no->nome,no->prox->nome);
			return;
		}
		while(no->prox != h->nose){
			no = no->prox;
				if(strcmp(no->nome,str)==0){
					fprintf(output,"[%s]<-[%s]->[%s]\n",no->ant->nome,no->nome,no->prox->nome);
					return;
				}
		}
		return;
}
void removerPrimeiro(FILE* output,char str[52],head* h)//Remove o primeiro nó da lista
{
   if ((h->tamanho == 0) || (h == NULL))
        return;
    if (h->tamanho == 1)
    {
        free (h->nose);
        h->nose = NULL;
        h->tail = NULL;
        h->tamanho = 0;
        fprintf(output,"[%s] REMOVE-OK\n",str);
        return;
    }
    node *no = h->nose->prox;
    no->ant = h->tail;
    h->tail->prox = no;
    free(h->nose);
    h->nose = no;
    h->tamanho--;
    fprintf(output,"[%s] REMOVE-OK\n",str);
}
void remover(FILE* output,char str[52],head* h)
{
   if ((h->tamanho == 0) || (h == NULL))
        return;
    node *no = h->nose, *aux;
    if (strcmp(h->nose->nome,str)==0){
		removerPrimeiro(output,str,h);
		return;
	}
    while (no->prox != h->nose)
    {
        if (no == h->nose)
        {
            if (strcmp(no->nome,str)==0)
            {
                h->nose = no->prox;
                h->tail->prox = h->nose;
                free (no);
                h->tamanho--;
                no = h->nose;
                fprintf(output,"[%s] REMOVE-OK\n",str);
            }
        }
        else
        {
            if (strcmp(no->nome,str)==0)
            {
                no->ant->prox = no->prox;
                no->prox->ant = no->ant;
                aux = no;
                no = no->ant;
                free(aux);
                h->tamanho--;
                fprintf(output,"[%s] REMOVE-OK\n",str);
            }
        }
        no = no->prox;
    }
    if (strcmp(no->nome,str)==0)
    {
        h->tail = no->ant;
        h->tail->prox = h->nose;
        h->nose->ant = h->tail;
        free(no);
        h->tamanho--;
        fprintf(output,"[%s] REMOVE-OK\n",str);
    }
}
int main(int argc, char* argv[]){
	head *h = inicia();
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("output.txt","w");
	char modo[52]={0},add[52]="ADD",show[52]="SHOW",remove[52]="REMOVE",str[52]={0};
	while(!feof(input)){
		fscanf(input,"%s ",modo);
		fgets(str,51,input);
		if(str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
			if(strcmp(modo,add)==0){
				if(busca(str,h)) fprintf(output,"[%s] ADD-ERROR\n",str);
				else insere(output,str,h);
			}
			else if(strcmp(modo,show)==0){
					if(busca(str,h)) mostra_lista(output,str,h);
					else fprintf(output,"[%s] SHOW-ERROR\n",str);
			}
			else if(strcmp(modo,remove)==0){
					if(busca(str,h)) remover(output,str,h);
				else fprintf(output,"[%s] REMOVE-ERROR\n",str);
			}
			modo[0]='\0';
			str[0]='\0';
	}
	fclose(input);
	fclose(output);
	return 0;
}
