#include<stdio.h>
#include<stdlib.h>
typedef struct SNo{
	int chave;
	struct SNo *prox;
}SNo;

typedef struct fila{
	SNo *inicio;
	SNo *fim;
}fila;

fila * criaFila(){
	fila *f=(fila*)malloc(sizeof(fila));
	f->inicio=NULL;
	f->fim=NULL;
}

void insereFila(fila *f, int valor){
	SNo *novo = (SNo*)malloc(sizeof(SNo));
	novo->chave=valor;
	if(f->inicio==NULL){
		novo->prox=NULL;
		f->inicio=novo;
		f->fim=novo;
	}else{
		f->fim->prox=novo;
		novo->prox=f->inicio;
		f->fim=novo;
	}
}

void imprime(fila *f){
	SNo *temp = f->inicio;
	if(f->inicio==NULL){
		printf("Fila vazia\n");
	}else{
		do{
			printf("%i\n",temp->chave);
			temp=temp->prox;
		}while(temp!=f->inicio);
	}
}

void remover(fila *f){
	SNo *temp = f->inicio;
	if(f->inicio==NULL){
		printf("Fila vazia\n");
	}else{
		f->fim->prox=f->inicio->prox;
		f->inicio=f->inicio->prox;
		free(temp);
		return;
	}
}

void busca(fila *f,int valor){
	SNo *temp = f->inicio;
	if(f->inicio==NULL){
		printf("Fila vazia\n");
	}else{
		do{
			if(temp->chave==valor){
				printf("valor encontrado\n");
				return;
			}
			temp = temp->prox;
		}while(temp!=f->inicio);
	printf("valor nao encontrado\n");
	return;
	}
}


int main(){
	fila *f1 = criaFila();
	insereFila(f1,1);
	insereFila(f1,3);
	insereFila(f1,5);
	insereFila(f1,9);
	insereFila(f1,22);
	insereFila(f1,6);
	remover(f1);
	imprime(f1);
	busca(f1,44);
	
	
	return 0;
}
