#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int comp(int *s, int i){
	int j,x = i-1;
	for(j=x;j>-1;j--){
		if(s[i] == s[j]) return 1;
	}
	return 0;
}
int main(){
	FILE *output = fopen("testes.txt","w");
	int p,a,i,s[10],n[15],j,cod;
	printf("Digite o valor do premio: ");
	scanf("%d",&p);
	fprintf(output,"%d\n",p);
	printf("Digite o numero de apostadores: ");
	scanf("%d",&a);
	fprintf(output,"%d\n",a);
	srand(time(NULL));
	for(i=0;i<10;i++){
		s[i] = 1+rand()%49;
			while(comp(s,i))
				s[i] = 1+rand()%49;
		fprintf(output,"%d",s[i]);
		if(i<9) fprintf(output," ");
	}
	for(i=0;i<a;i++){
		cod = 1+rand()%999999999999999999;
		fprintf(output,"\n%x",cod);
		for(j=0;j<15;j++){
			n[j] = 1+rand()%49;
			while(comp(n,j))
				n[j] = 1+rand()%49;
			fprintf(output," %d",n[j]);
		}
	}
	return 0;
}
