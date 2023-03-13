#include <stdio.h>
#include <stdlib.h>

typedef struct sapato{
	int numerodotenis;
	struct sapato*caixinhaesq;
	struct sapato*caixinhadir;
}sapato;

void criArvere(sapato **caixona){
	*caixona=NULL;
}

void colocar(sapato **caixona, int nro){
	if(*caixona==NULL){
		*caixona=(sapato *)malloc(sizeof(sapato));
		(*caixona)->caixinhaesq=NULL;
		(*caixona)->caixinhadir=NULL;
		(*caixona)->numerodotenis=nro;
	}else{
		if(nro<(*caixona)->numerodotenis){
			colocar(&(*caixona)->caixinhaesq, nro);
		}else{
			colocar(&(*caixona)->caixinhadir, nro);
		}
	}
}

void procura(sapato **caixona, int nro){
	if(*caixona==NULL){
		printf("Nao achei!\n");
		
	}else{
		if((*caixona)->numerodotenis==nro){
			printf("Achei!\n");
			return;
		}else{
			if((*caixona)->numerodotenis>nro){
				procura(&(*caixona)->caixinhaesq, nro);
			}
			if((*caixona)->numerodotenis<nro){
				procura(&(*caixona)->caixinhadir, nro);
			}
		}
	}
}

void PreOrdem(sapato *caixinha){
	if(caixinha != NULL){
	printf("%d ",caixinha->numerodotenis);
	PreOrdem(caixinha->caixinhaesq);
	PreOrdem(caixinha->caixinhadir);
	}
}

void PosOrdem(sapato *caixinha){
	if(caixinha != NULL){
	PosOrdem(caixinha->caixinhaesq);
	PosOrdem(caixinha->caixinhadir);
	printf("%d ",caixinha->numerodotenis);
	}
}

void Simetrica(sapato *caixinha){
	if(caixinha != NULL){
	Simetrica(caixinha->caixinhaesq);
	printf("%d ",caixinha->numerodotenis);
	Simetrica(caixinha->caixinhadir);
	}
}


int main(){
	sapato*caixinha;
	criArvere(&caixinha);
	colocar(&caixinha, 8);
	colocar(&caixinha, 3);
	colocar(&caixinha, 14);
	colocar(&caixinha, 5);
	
	PreOrdem(caixinha);
	printf("\n");
	PosOrdem(caixinha);
	printf("\n");
	Simetrica(caixinha);
	printf("\n");
	
	procura(&caixinha, 5);
	procura(&caixinha, 7);
	
}
