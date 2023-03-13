#include<stdio.h>
#include<stdlib.h>
typedef struct SNo{
	int chave;
	struct SNo *prox;
}SNo;

typedef struct lista{
	struct SNo *inicio;
	struct SNo *fim;
}lista;

lista * crialista(){
	lista *l = (lista*)malloc(sizeof(lista));
	l->fim = NULL;
	l->inicio = NULL;
	return l;
}

void insereLista(lista *l, int valor){
	SNo *ant = NULL;
	SNo *temp = l->inicio;
	
	SNo *novo = (SNo*)malloc(sizeof(SNo));
	novo->chave = valor;
	novo->prox =NULL;
	
	if(l->inicio==NULL){
		l->inicio = novo;
		l->fim = novo;
	}else{
		while((temp!=NULL)&&(temp->chave<valor)){
			ant=temp;
			temp = temp->prox;
		}
		if(ant==NULL){
				l->inicio = novo;
				novo->prox = temp;
			}else{
				ant->prox = novo;
				novo->prox = temp;	
		}	
	} 
}

void imprime(lista *l){
	SNo *temp  = l->inicio;
	if(temp!=NULL){
		while(temp!=NULL){
			printf("%i\n",temp->chave);
			temp = temp->prox;
		}	
	}else{
		printf("Lista vazia\n");
	}
		
}

void buscaLista(lista *l, int valor){
	SNo *temp = l->inicio;
	if(temp!=NULL){
		while(temp!=NULL){
			if((temp->chave)==valor){
				printf("valor encontrado\n");
				return;
			}
			temp = temp->prox;
		}
		printf("valor nao encontrado\n");
		return;
	}else{
		printf("Lista vazia\n");
	}
}

void remover(lista *l, int valor){
	SNo *ant = NULL;
	SNo *temp = l->inicio;
	if(temp!=NULL){
		while(temp!=NULL){
			if(temp->chave==valor){
				if(ant==NULL){
					l->inicio = temp->prox;
					free(temp);
					temp = l->inicio;
					
				}else{
					if(temp->prox==NULL){
						ant->prox =NULL;
						l->fim = ant;
						free(temp);
						return;
					}
						ant->prox=temp->prox;
						free(temp);
						temp = ant->prox;
					
				}
			}
			ant=temp;
			temp= temp->prox;
		
		}
		return;
	}else{
		printf("Lista vazia\n");
	}
}


int main(){
	lista *L1 = crialista();
    lista *L2 = crialista();

    insereLista(L1, 6);
    insereLista(L1, 160);
    insereLista(L1, 44);
    insereLista(L1, 99);
    insereLista(L2, 10);
    insereLista(L2, 70);
    insereLista(L2, 66);
    insereLista(L2, 65);
	remover(L1,65);
    imprime(L1);

    printf("\n");

    imprime(L2);

    buscaLista(L1, 11);

    return 0;
}
