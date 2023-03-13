// Hiara Espindola, RGA: 201818050226
//
//  lista.c
//  
//
//  Created by Bruno Brandoli on 23/08/18.
//
//

#include <stdio.h>
#include <stdlib.h>

//declaracao do TAD
typedef struct SNo {
    int chave;
    struct SNo *prox;
}SNo;

SNo *Inicio = NULL; //decl. e atr null

// funcao insere alocando nos no inicio da lista
void insere(int valor) {
    SNo * Novo = malloc(sizeof(SNo));
	Novo->chave=valor;
	Novo->prox=Inicio;
	Inicio=Novo;
}

int busca(int valor) {
	
	SNo *bsc;
	
		if(Inicio == NULL){
			printf("Lista vazia \n");
		return 0;
		}
		
			bsc=Inicio;
		
		while(bsc!=NULL){
			if(bsc->chave==valor){
				printf("Encontrei\n");
				return 1;
			} else {
				bsc=bsc->prox;
			}
		
		}
	printf("O elemento %d nao se encontra na lista\n\n\n", valor);
	return 0;
}

int removevalor(int valor){
	
	SNo *temp, *ant;
	
	if(Inicio == NULL){
		printf("Lista Vazia \n");
	return 0;
	}
	
		temp = Inicio;
		ant = NULL;
	
	while (temp!=NULL){
		if (temp->chave == valor){
			if (temp == Inicio){
				Inicio = Inicio->prox;
				free(temp);
			return 1;
			}else{
			ant->prox = temp->prox;
			free(temp);
			return 1;
			}
		}else{
			ant = temp;
			temp = temp->prox;
		}
	}
	return 0;
}


void imprime() {
    
    SNo *imp;
    
	    if(Inicio == NULL){
	    	printf("Lista Vazia\n");
		}
	
			imp=Inicio;
	
		while(imp!=NULL){
			printf("%d ", imp->chave);
			imp=imp->prox;
		}
	printf(" Acabou a lista \n\n\n");
}

int main() {
    // sem firula
    insere(20);
    insere(6);
    insere(2);
    insere(30);
    imprime();
    removevalor(6);
    imprime();
    removevalor(30);
    imprime();
    busca(6);
//    if(a == 0)
//      printf("O elemento NAO estah na lista!\n");
//    else if(a == 0)
//    printf("A lista esta vazia!\n");
    
    
    // com firula
    /*while(1){
        printf("Digite a opcao: \n");
        scanf("%d", &opcao);
        switch(opcao != -1) {
            // sai do programa
            case 1: //insere
            scanf("%d",&valor);
            insere(valor);
            break;
            
            case 2: //busca
            scanf("%d",&valor);
            busca(valor);
            break;

            
            case 3: //imprime
            
            case 4: //remove
            
            default:
            printf("Digite uma opcao vahlida!\n");
        }
    }*/
}
