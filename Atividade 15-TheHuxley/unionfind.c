#include <stdio.h>

void conecta(int amizade[], int pessoas, int x, int y ){
    int aux = amizade[x];
    int i;
    for(i=0;i<pessoas;i++)
        if(amizade[i] == aux)
            amizade[i] = amizade[y];
}

int contador(int array[], int pessoas, int root){
    int i, cont = 0;
    for (i=1;i<pessoas+1;i++)
        if(array[i] == root)
            cont++;
    return cont;
}

int main(){

    int testes, index, maior;
    scanf("%d", &testes);
    for(index=0;index<testes;index++){
		maior = 0;
		int i, j, pessoas, pares, x, y, aux;
			scanf("%d %d", &pessoas, &pares);
			int amizade[pessoas];
			
			for(i = 1;i <= pessoas; i++) amizade[i] = i;
			
			for (i = 0; i < pares; i++) {
				scanf("%d %d",&x, &y);
				conecta(amizade,pessoas,x,y);
			}
			
			for (j = 1; j <= pessoas; j++) {
				aux = contador(amizade,pessoas,j);
				if(aux > maior) maior = aux;
			}
		
        printf("%d\n",maior);
    }

    return 0;
}
