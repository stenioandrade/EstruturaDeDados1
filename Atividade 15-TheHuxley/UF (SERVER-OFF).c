#include <stdio.h>


int main(int argc, char **argv){
	int ntestes;
	int index;	
		scanf("%d",&ntestes);
		for(index=0;index<ntestes;index++){
			int npessoas, npares;
			int comb = ((2*npares)+1);
				scanf("%d %d",&npessoas, &npares);
			int i, j;
			//int maior = 0;
			//int cont = 0;
			//int amizade[npessoas+1];
			int pares[(2*npares)+1];
			int aux[npessoas+1];
			for(i=0;i<npessoas+1;i++) aux[i] = 0;	
				for(i=1;i<comb;i=i+2){
					scanf("%d %d",&pares[i],&pares[i+1]);
				}
				for(i=1;i<comb;i++){
					aux[i] = pares[i];
					for(j=1;j<comb;j=j+2){
						aux[j] = pares[j];
						//aux[];
					}
				}
			
		}
	
	return 0;
}
