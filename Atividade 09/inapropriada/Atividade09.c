#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

FILE* ArqBook;

/*
 * 	1 byte do char (0)
 * 	4 bytes do ISBN (1)
 * 	4 bytes do pos (5)
 * 	50 bytes do nome (9)
 *  40 bytes do autor (59)
 *  12 bytes da data (99)
*/

int insere();
void insereArq();
void imprime();
void reconstroi();

typedef struct Node{
	int ISBN;
	int fator;
	long int pos;
	char nome[50];
	char autor[40];
	char data[12];
	struct Node *esq;
	struct Node *dir;
}node;

node *inicia(){
	node *raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}

node* menor(node* raiz){
	node* no1 = raiz;
	node* no2 = raiz->esq;
	while(no2 != NULL){
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}

node* maior(node* raiz){
	node* no1 = raiz;
	node* no2 = raiz->dir;
	while(no2 != NULL){
		no1 = no2;
		no2 = no2->dir;
	}
	return no1;
}

int alt_No(node *no){
   
    int esq, dir;
   
    if ( no == NULL ) return -1;
   
    esq = alt_No ( no->esq );
    dir = alt_No ( no->dir );
   
    if ( esq > dir )
        return esq + 1;
    else
        return dir + 1;
}

int fat_bal(node *no){
	return alt_No(no->esq) - alt_No(no->dir);
}

void rotacaoLL(node **raiz){
	node *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->fator = alt_No((*raiz)->dir) - alt_No((*raiz)->esq);
	no->fator = alt_No(no->dir) - alt_No(no->esq);
	*raiz = no;
}

void rotacaoRR(node **raiz){
	node *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->fator = alt_No((*raiz)->dir) - alt_No((*raiz)->esq);
	no->fator = alt_No(no->dir) - alt_No(no->esq);
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

void delay(unsigned int msec){
    clock_t lim = msec + clock();
    while (lim > clock());
}

void constroi(node **raiz){
	ArqBook = fopen("books.dat","rb");
	fseek(ArqBook,0,2);
	long int tamanho = ftell(ArqBook);
	if(tamanho < 1) return;
	int ISBN = 0, flag = 0;
	long int pos = 0;
	char nome[50], autor[40], data[12], c;
	long int cursor = fseek(ArqBook,0,SEEK_SET);
	while(cursor < tamanho){
		fread(&c,sizeof(char),1,ArqBook);
		fread(&ISBN,sizeof(int),1,ArqBook);
		fread(&pos,sizeof(long int),1,ArqBook);
		fread(nome,sizeof(char),50,ArqBook);
		fread(autor,sizeof(char),40,ArqBook);
		fread(data,sizeof(char),12,ArqBook);
		cursor = ftell(ArqBook);
		if(c != '@') insere(raiz, ISBN, nome, autor, data, flag, pos);
		ISBN = 0;
		nome[0]='\0';
		autor[0]='\0';
		data[0]='\0';
	}
	fclose(ArqBook);
	
}

node* busca(node **raiz, int ISBN){
	node* no = (node*)malloc(sizeof(node));
	no = *raiz;
	if(*raiz == NULL) return NULL;
	if( ISBN == (*raiz)->ISBN ) return no;
	else if ( ISBN < (*raiz)->ISBN ) no = busca(&((*raiz)->esq),ISBN);
	else if ( ISBN > (*raiz)->ISBN ) no = busca(&((*raiz)->dir),ISBN);
	return no;
}

int insere(node **raiz, int ISBN, char nome[50], char autor[40], char data[12], int flag, long int pos){
	if(*raiz == NULL){
		node *novo = (node*)malloc(sizeof(node));
		if(novo == NULL) return 0;
		novo->ISBN = ISBN;
		strcpy(novo->nome,nome);
		strcpy(novo->autor,autor);
		strcpy(novo->data,data);
		novo->fator = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->pos = pos;
		*raiz = novo;
		if(flag != 0) insereArq(novo);
		return 1;
	}
	node *atual = *raiz;
	if( ISBN < atual->ISBN ){
			insere(&(atual->esq), ISBN, nome, autor, data, flag, pos);
				if (fat_bal(atual) == 2 ){
					if(fat_bal(atual->esq) == 1 ) rotacaoLL(raiz);
					else rotacaoLR(raiz);
				}
		
	}
	else{
			insere(&(atual->dir), ISBN, nome, autor, data, flag, pos);
				if(fat_bal(atual) == -2){
					if( fat_bal(atual->dir) == -1 ) rotacaoRR(raiz);
					else rotacaoRL(raiz);
				}
			
	}
	atual->fator = fat_bal(atual);
	return 1;
}

int remover(node** raiz, int ISBN){
	if(*raiz == NULL) return 0;
	int res = 0;
	if(ISBN < (*raiz)->ISBN ){
		if((res = remover((&(*raiz)->esq),ISBN)) == 1){
			if(fat_bal(*raiz) == 2){
				if(fat_bal((*raiz)->esq) == 1) rotacaoLL(raiz);
				else rotacaoLR(raiz);
			}
		}
	}
	else if( ISBN > (*raiz)->ISBN ){
		if((res = remover(&((*raiz)->dir),ISBN)) == 1){
			if(fat_bal(*raiz) == -2){
				if(fat_bal((*raiz)->dir) == -1) rotacaoRR(raiz);
				else rotacaoRL(raiz);
			}
		}
	}
	if((*raiz)->ISBN == ISBN){
		if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
			node* old = (*raiz);
			if((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
			else *raiz = (*raiz)->dir;
			free(old);
		}
		else{
			node* temp = menor((*raiz)->dir);
			(*raiz)->ISBN = temp->ISBN;
			(*raiz)->pos = temp->pos;
			strcpy((*raiz)->nome,temp->nome);
			strcpy((*raiz)->autor,temp->autor);
			strcpy((*raiz)->data,temp->data);
			res = remover(&((*raiz)->dir),(*raiz)->ISBN);
			if(fat_bal(*raiz) == -2){
				if(fat_bal((*raiz)->dir) == -1) rotacaoRR(raiz);
				else rotacaoRL(raiz);
			}
		}
		return 1;
	}
	return res;
}

void consulta(node** raiz, int ISBN){
	node* no = (node*)malloc(sizeof(node));
	no = busca(raiz,ISBN);
	imprime(no);
}

void imprime(node *no){
	if(no == NULL){
		printf("\nEste livro nao esta na biblioteca !\n");
		return;
	}
	printf("ISBN: %d",no->ISBN);
	printf("\nPosicao (111 bytes por item): %ld",no->pos);
	printf("\nNome: %s",no->nome);
	printf("\nAutor: %s",no->autor);
	printf("\nData: %s\n\n",no->data);
}

void listar(node *no){
	if(no != NULL){
		listar(no->esq);
		imprime(no);
		listar(no->dir);
	}
}

void insereArq(node *b){
	ArqBook = fopen("books.dat","ab");
	char c = '#';
	fwrite(&c,sizeof(char),1,ArqBook);
	fwrite(&(b->ISBN),sizeof(int),1,ArqBook);
	fwrite(&(b->pos),sizeof(long int),1,ArqBook);
	fwrite(b->nome,sizeof(char),50,ArqBook);
	fwrite(b->autor,sizeof(char),40,ArqBook);
	fwrite(b->data,sizeof(char),12,ArqBook);
	fclose(ArqBook);
}

void removeArq(long int pos){
	ArqBook = fopen("books.dat","r+b");
	fseek(ArqBook,pos,0);
	char c = '@';
	fwrite(&c,sizeof(char),1,ArqBook);
	fclose(ArqBook);
}

void auxinsere(node** raiz){
	system("cls");
	int i,n,ISBN,flag=1;
	char nome[50]={0}, autor[40]={0}, data[12]={0};
	node* no;
	printf("Quantos livros quer inserir ? ");
	scanf("%d",&n);
	long int pos;
	for(i=0;i<n;i++){
		ArqBook = fopen("books.dat","ab");
		fseek(ArqBook,0,2);
		pos = ftell(ArqBook);
		fclose(ArqBook);
		printf("\nISBN: ");
		scanf("%d",&ISBN);
		printf("\nNome: ");
		scanf(" %s", nome);
		printf("\nAutor: ");
		scanf(" %s", autor);
		printf("\nData: ");
		scanf(" %s", data);
		no = busca(raiz,ISBN);
		if(no == NULL) insere(raiz,ISBN,nome,autor,data, flag, pos);
		else{
			printf("\nLivro ja cadastrado, nao inserido ! \n");
			delay(1000);
		}
	}
}

void limpaArq(node** raiz){
	ArqBook = fopen("books.dat","wb");
	fclose(ArqBook);
	printf("Arquivo limpo !\n");
	reconstroi(raiz);
	system("pause");
}

void auxconsulta(node** raiz){
	system("cls");
	int ISBN;
	printf("Insira o ISBN do livro que deseja consultar: ");
	scanf("%d",&ISBN);
	consulta(raiz,ISBN);
	system("pause");
}

void auxlistar(node** raiz){
	system("cls");
	if(*raiz == NULL){
		printf("Nenhum livro cadastrado !\n");
		system("pause");
		return;
	}
	listar(*raiz);
	system("pause");
}

void auxremover(node** raiz){
	system("cls");
	int ISBN, flag;
	node* no;
	long int pos;
	printf("\nInsira o ISBN do livro que deseja remover: ");
	scanf("%d",&ISBN);
	no = busca(raiz,ISBN);
	if(no == NULL){
		printf("\nEste livro nao esta na biblioteca !\n");
		system("pause");
		return;
	}
	pos = no->pos;
	flag = remover(raiz,ISBN);
	if(flag) removeArq(pos);
	system("pause");
}

void reconstroi(node** raiz){
	*raiz = NULL;
	constroi(raiz);
}

void mostraAlt(node* no){
	if(no != NULL){
		printf("Altura de %d -> %d\n",no->ISBN,alt_No(no));
		mostraAlt(no->esq);
		mostraAlt(no->dir);
	}
}

void auxmostraAlt(node** raiz){
	system("cls");
	mostraAlt(*raiz);
	system("pause");
}

void menu(node** raiz){
		int op = 0;
		do{
			system("cls");
			printf("########################################\n");
			printf("#                                      #\n");
			printf("#              BIBLIOTECA              #\n");
			printf("#                                      #\n");
			printf("########################################\n");
			printf("#                                      #\n");
			printf("# 1 - Inserir                          #\n");
			printf("# 2 - Consultar                        #\n");
			printf("# 3 - Remover                          #\n");
			printf("# 4 - Listar Todos                     #\n");
			printf("# 5 - Mostrar altura dos nos           #\n");
			printf("# 6 - Limpar Arquivo e Reconstruir AVL #\n");
			printf("# 0 - Sair                             #\n");
			printf("#                                      #\n");
			printf("########################################\n");
			printf("O que deseja fazer: ");
			scanf("%d",&op);
			while(op != 0 && op!= 1 && op!= 2 && op!= 3 && op!= 4 && op!= 5 && op!= 6){
			printf("Insira uma opcao valida!");
				delay(500);
				menu(raiz);
			}
			switch(op){
				case 1: auxinsere(raiz); break;
				case 2: auxconsulta(raiz); break;
				case 3: auxremover(raiz); break;
				case 4: auxlistar(raiz); break;
				case 5: auxmostraAlt(raiz); break;
				case 6: limpaArq(raiz); break;
			}
			printf("\n");
		}while(op != 0);
		
		printf("                               ");
		printf("Bye Bye !");
		
	return;
	
}

int main(int argc, char* argv[]){
	node* raiz = inicia();
	constroi(&raiz);
	menu(&raiz);
	return 0;
}
