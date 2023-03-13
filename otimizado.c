#include<stdio.h>
#include<stdlib.h>
typedef struct SNo{
	int chave;
	struct SNo *prox;
	struct SNo *ant;
}SNo;

typedef struct lista{
	struct SNo *inicio;
	struct SNo *fim;	
}lista;

lista * crialista(){
	lista *l = (lista*)malloc(sizeof(lista));
	l->inicio=NULL;
	l->inicio=NULL;
	return l;
}

void insereLista(lista *l,int valor){
	SNo *novo=(SNo*)malloc(sizeof(SNo));
	novo->chave=valor;
	novo->ant=NULL;
	novo->prox=NULL;
	if(l->inicio==NULL){
		l->inicio=novo;
		l->fim=novo;
	}else{
		novo->ant=l->fim;
		novo->ant->prox=novo;
		l->fim=novo;
	}
}

void busca(lista *l, int valor){
	SNo *temp1 = l->inicio;
	SNo *temp2 = l->fim;
	
	if(temp1==NULL){
		printf("Lista vazia\n");
	}else{
		do{
			if((((temp1->chave)==valor)||(temp2->chave)==valor)){
				printf("elemento encontrado\n");
				return;
			}else{
				temp1=temp1->prox;
				if(temp2!=temp1){
					temp2=temp2->ant;
				}
				
			}
		}while(temp1!=temp2);
		printf("Elemento nao encontrado\n");
	}
}

void remover(lista *l,int valor){
	SNo *aux;
	SNo *temp1 = l->inicio;
	SNo *temp2 = l->fim;
	if(l->inicio==NULL){
		printf("Lista vazia\n");
	}else{
		do{
			if((temp1->chave)==valor){
				aux = temp1;
				if(temp1->ant==NULL){
					temp1=temp1->prox;
					l->inicio = temp1;
				}else{
					temp1->ant->prox=temp1->prox;
					temp1->prox->ant=temp1->ant;
				}
				free(aux);
				return;
			}else if((temp2->chave)==valor){
				aux = temp2;
				if(temp2->prox==NULL){
					temp2->ant->prox = temp2->prox;
					l->fim = temp2;
				}else{
					temp2->ant->prox=temp2->prox;
					temp2->prox->ant=temp2->ant;
				}				
				free(aux);	
				return;
			}
			temp1=temp1->prox;
			if(temp2!=temp1){
				temp2=temp2->ant;
			}			
		}while(temp1!=temp2);
		return;
	}
}

void imprime(lista *l){
	SNo *temp = l->inicio;
	if(l->inicio==NULL){
		printf("Lista vazia\n");
	}else{
			
		while(temp!=NULL){
			printf("%i\n",temp->chave);
			temp=temp->prox;
		}
	}
	
}
int main(){
	lista *l1 = crialista();
	insereLista(l1,51);
	insereLista(l1,99);
	insereLista(l1,81);
	insereLista(l1,70);
	busca(l1,70);
	remover(l1,81);
	busca(l1,51);
	imprime(l1);
	return 0;
}
