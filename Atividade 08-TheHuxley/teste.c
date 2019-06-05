#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int info;
    void *filho_esq;
    void *filho_dir;
    void *pai;
}No;

No *atual, *raiz=NULL, *cursor;

int altura=-1;
short int lado=0; //0 esq     1 dir
void busca(int n, int cont, No *ptr){
	if(ptr->info==n){
        altura=cont;
        return;
    }
	
    if(ptr->filho_esq!=NULL)busca(n,cont+1,ptr->filho_esq);
    if(ptr->filho_dir!=NULL)busca(n,cont+1,ptr->filho_dir);
}

int main(){    
    char c;
    char str[1000]; int i=0;
    while(scanf("%c", &c) && c!='\n'){
        if(c!=' '){
			str[i]=c;
			i++;
		}
	}
	i=0; int tam=strlen(str);

	while(i<tam){
        if(str[i]=='('){		
        }else{
            if(str[i]==')'){
				if(lado==1)
					lado=0;
				else lado=1;
				if(str[i-1]=='('){}
				else{	
					cursor=cursor->pai;
					lado=1;
				}
            }else{
				int j=i, a=0, valor;
				char aux[10]="";
				while(str[j]!='(' && str[j]!=')'){
					aux[a]=str[j];
					j++;a++;
				}
				valor = atoi(aux);
				atual=(No*)malloc(sizeof(No));
                atual->info=valor;
                atual->filho_dir=NULL;
                atual->filho_esq=NULL;
                
                if(raiz==NULL){ raiz=atual; raiz->pai=NULL;}
                else{
					if(lado==0)
						cursor->filho_esq=atual;
					else
						cursor->filho_dir=atual;
					
					atual->pai=cursor;
					lado=0;	
				}
				cursor=atual;
				i=j-1;
            }
        }
        i++;
	}
	
    int d;
    scanf("%d", &d);
    
    busca(d,0,raiz);
    
    if(altura==-1) printf("NAO ESTA NA ARVORE\n");
    else printf("ESTA NA ARVORE\n");
    printf("%d\n", altura);
    return 0;
}

