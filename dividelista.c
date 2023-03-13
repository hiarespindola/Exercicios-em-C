#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct SNo{
	int chave;
	struct SNo *prox;
}SNo;

typedef struct Lista{
	SNo *Inicio;
	SNo *Fim;
}Lista;


//Criar a lista principal vazia
Lista * criaLista(){
	Lista *L1 = malloc (sizeof(Lista));
	L1->Inicio = NULL;
	L1->Fim = NULL;
}


//Inserir na lista
void insereLista(Lista *L1, int valor){
	SNo *Novo = malloc (sizeof(SNo));
	Novo->chave = valor;
	Novo->prox = L1->Inicio;
	L1->Inicio = Novo;
}


//Funçao para dividir a lista principal em duas
Lista * divideLista(Lista *L1){
	Lista *L2 = criaLista();
	int i, tamanhoL=0;
	SNo *temp = L1->Inicio;
		
		//Contar a lista
		while (temp != NULL){
			temp = temp->prox;
			tamanhoL++;
		}
		
		//o temporario esta no inicio da primeira lista
		temp = L1->Inicio;
		
		//para ver se é par ou impar
		if( tamanhoL%2 == 0){
			tamanhoL = tamanhoL/2;
			tamanhoL = tamanhoL-1;
		} else {
			tamanhoL = tamanhoL/2;
		}
		
		//o tamanho foi dividido e será inserido na primeira lista
		for(i=0; i < tamanhoL; i++){
			temp = temp->prox;
		}
		
		L1->Fim = temp; //o ultimo temporario virou o fim da minha primeira lista
		L2->Inicio = temp->prox; //o inicio da minha segunda lista é o próximo temporario
		
		//inserção na segunda lista, pois como dito acima, o temp->prox é o inicio da minha L2
		while(temp->prox != NULL){
			temp = temp->prox;
		}
		
		L2->Fim = temp; //fim da lista 2 é o ultimo temp inserido
		L1->Fim->prox = NULL; //fim da lista 1 aposta pro proxima e o guarda como null
	return L2;
}

//Printar a lista principal
void imprimeLista(Lista *L1){
	SNo *temp=L1->Inicio;
	
		if(L1->Inicio == NULL){
			printf("Lista vazia");
		}
		
		while(temp != NULL){
			printf("%d ", temp->chave);
			temp = temp->prox;
		}
	printf(" Fim! \n");
}


int main(){
	Lista *L1 = criaLista();
	Lista *L2; //deve criar uma L2, mas sem criar a lista dentro dela, para poder dividir.
	
	insereLista(L1, 2);
	insereLista(L1, 3);
	insereLista(L1, 4);
	insereLista(L1, 5);
	insereLista(L1, 2);
	
	printf("L1: ");
	imprimeLista(L1); //L1 completa
	
	L2 = divideLista(L1); //chamado para dividir a L1 e transformar em L2;
	
	printf("L2: ");
	imprimeLista(L1); //divisao da primeira lista como L2
	printf("L3: ");
	imprimeLista(L2); //divisao da lista para L3
}



