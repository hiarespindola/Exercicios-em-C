#include<stdio.h>
#include<stdlib.h>



// -------------------------------------------------------
// -------------------------------------------------------
// -----------------------RADIX---------------------------
// -------------------------------------------------------
// -------------------------------------------------------




typedef struct Letra {
	char l;
	struct Letra* proxima;
	struct Letra* anterior;
}Letra;

typedef struct String {
	Letra* Inicio;
	Letra* Fim;
}String;


String* CriaString(String *S){
	S = (String*)malloc(sizeof(String));
	S->Inicio = NULL;
	S->Fim = NULL;
	return S;
}


void InsereString (String*S, char c){
	Letra* Novo = (Letra*)malloc(sizeof(Letra));
	Novo->l = c;
	Novo->proxima = NULL;
	if(S->Inicio == NULL){
		S->Inicio = Novo;
		S->Fim = Novo;
		Novo->anterior = NULL;
	}else{
		S->Fim->proxima = Novo;
		Novo->anterior = S->Fim;
		S->Fim = Novo;
	}
}

//Função para criar baldes de cada letra, usando tabela ASCII.
//De 65 à 90, letras maiúsculas. De 97 à 122, letras minúsculas. 
//São 27 baldes, não prioriza maiúscula ou minúscula, pelo fato de que subtrai a posição dela por 64 ou 96, sabendo o número do balde que cairá.
//Exemplo: 65 (letra A) - 64 = 1. Cairá no primeiro balde a letra A. 97 (letra a) - 96 = 1. Cairá no balde 1 a letra a também.
int PosChar(char c){
	int i;
	if( c >= 65 && c <= 90){
		i = (int)c - 64;
	}else if ( c >= 97 && c <= 122){
		i = (int)c - 96;
	}/*else if (c >= 48 && c <= 57){
		i = (int)c - 21;
	}*/
	return i;
}

int TamanhoString(String *S){
	Letra* temp = S->Inicio;
	int i = 0;
	if( temp == NULL){
		return 0;
	}else{
		while ( temp != NULL){
			i++;
			temp = temp->proxima;
		}
		return i;
	}
}

///Função para replicar a string, para que a antiga não se perca na próxima iteração.
void AtribuiString (String *A, String*B){
	Letra* temp = B->Inicio;
	if( B->Inicio != NULL){
		while ( temp != NULL){
			InsereString(A,temp->l);
			temp = temp->proxima;
		}
	}
}

void Remover(String *S){
	Letra* temp = S->Fim;
	if( S->Inicio == S->Fim){
		free(temp);
		S->Inicio = NULL;
		S->Fim = NULL;
	}else{
		S->Fim = temp->anterior;
		free(temp);
	}
}

void RemoveString(String *S){
	Letra* temp;
	if( S->Inicio != NULL){
		while( S->Inicio != NULL){
			Remover(S);
		}
	}
}

void ImprimeString(String *S){
	Letra* temp = S->Inicio;
	if( S->Inicio == NULL){
		printf("Nada aqui!\n");
		return;
	}
	while ( temp != NULL){
		printf("%c",temp->l);
		temp = temp->proxima;
	}
	printf("\n");
}


String** Radix (String** Vetor , int qt){
	int t, p, i, j, M = 0, k;
	int VTemp[27];
	String **VAux = malloc(sizeof(String*)*qt);
	Letra* aux;

//Aqui criamos o vetor para receber os valores
	for (i = 0; i < qt ; i++){
		VAux[i] = CriaString(VAux[i]);
	}

//Aqui vai calcular o tamanho do vetor enquanto for inserindo valores (palavras)
    for ( i = 0; i < qt ; i++){
		t = TamanhoString(Vetor[i]);
		if( t > M){
			M = t;
		}
	}

//Aqui eh o vetor para depois fazer a troca de valores com o modo de somatorio, estamos zerando ele aqui
    for (i = 0; i < M ; i++){
		for ( j = 0; j < 27 ; j++){
			VTemp[j] = 0;
    }

//Aqui eh para caminhar o vetor "normal" e mandar para o balde fazer a somatoria
    for ( j = 0 ; j < qt ; j++){
        aux = Vetor[j]->Fim;
        for ( k = 0 ; k < i ; k++){
            aux = aux->anterior;
            if( aux == NULL){
                break;
            }
        }
        if( aux == NULL){
            p = 0;
        }else{
            p = PosChar(aux->l);
        }
        VTemp[p] = VTemp[p]+1;
    }

//Somatorio dos baldes
    for ( j = 1 ; j < 27 ; j++){
        VTemp[j] = VTemp[j] + VTemp[j-1];
    }
    printf("\n");

//Esse for eh para fazer a volta e realocar os valores no vetor auxiliar
    for ( j = qt-1; j >= 0 ; j--){
        aux = Vetor[j]->Fim;
        for ( k = 0 ; k < i ; k++){
            aux = aux->anterior;
            if( aux == NULL)
                break;
        }

        if( aux == NULL){
            p = 0;
        }else{
            p = PosChar(aux->l);
        }

			AtribuiString(VAux[VTemp[p]-1],Vetor[j]);
			ImprimeString(VAux[VTemp[p]-1]);
			VTemp[p] = VTemp[p] - 1;

    }

    for ( j = 0; j < qt ; j++){
        RemoveString(Vetor[j]);
    }

    for ( j = 0; j < qt ;j++){
        AtribuiString(Vetor[j],VAux[j]);
    }

    for ( j = 0;j < qt ; j++){
        RemoveString(VAux[j]);
    }

    if( i != M-1)
        printf("\n~~~~ * ~~~~ Proxima Iteracao ~~~~ * ~~~~\n");

	}

	return Vetor;

}

// -------------------------------------------------------
// -------------------------------------------------------
// -----------------------COUNTING------------------------
// -------------------------------------------------------
// -------------------------------------------------------

typedef struct SNo{
        int chave;
        struct SNo *proximo;
        struct SNo *anterior;
    }SNo;

typedef struct Fila{
        SNo *Inicio;
        SNo *Fim;
    }Fila;

Fila * criaFila (Fila *F){
        F = malloc (sizeof(Fila));
        F->Inicio = NULL;
        F->Fim = NULL;

        return F;
    }

void InsereFila(Fila *F, int valor){
	SNo* Novo = malloc(sizeof(SNo));
	Novo->chave = valor;
	Novo->proximo = NULL;

	if(F->Inicio == NULL){
		F->Inicio = Novo;
		F->Fim = Novo;
		Novo->anterior = NULL;
	}else{
		F->Fim->proximo = Novo;
		Novo->anterior = F->Fim;
		F->Fim = Novo;
	}
}

void duplicaFila (Fila *F, Fila *F2){
	SNo *temp = F2->Inicio;
	if( F2->Inicio != NULL){
		while ( temp != NULL){
			InsereFila(F,temp->chave);
			temp = temp->proximo;
		}
	}
}

void Remove(Fila *F){
	SNo* temp = F->Fim;
	if( F->Inicio == F->Fim){
		free(temp);
		F->Inicio = NULL;
		F->Fim = NULL;
	}else{
		F->Fim = temp->anterior;
		free(temp);
	}
}

void RemoveFila(Fila *F){
	if( F->Inicio != NULL){
		while( F->Inicio != NULL){
			Remove(F);
		}
	}
}

void ImprimeFila(Fila *F){
	SNo *temp = F->Inicio;
	if( F->Inicio == NULL){
		printf("Nada na fila!\n");
		return;
	}
	while ( temp != NULL){
		printf("%d",temp->chave);
		temp = temp->proximo;
	}
	printf(" ");
}

int TamanhoFila(Fila *F){
	SNo* temp = F->Inicio;
	int i = 0;
	if( temp == NULL){
		return 0;
	}else{
		while ( temp != NULL){
			i++;
			temp = temp->proximo;
		}
		return i;
	}
}

Fila ** countingsort (Fila **Vetor, int qt){
    SNo *temp;
    Fila **Vaux = malloc(sizeof(Fila*)*qt);
    int Vtemp[500];
    int i, t, MA = 0, j, k, posicao;


    for (i = 0; i < qt ; i++){
		Vaux[i] = criaFila(Vaux[i]);
	}

	for ( i = 0; i < qt ; i++){
		t = TamanhoFila(Vetor[i]);
		if( t > MA){
			MA = t;
		}
	}


	for (i = 0; i < MA ; i++){
		for ( j = 0; j < 500 ; j++){
			Vtemp[j] = 0;
    }
 printf(" ~~~~ * ~~~~  HISTOGRAMA  ~~~~ * ~~~~\n");
    for ( j = 0 ; j < qt ; j++){
        temp = Vetor[j]->Fim;
        for ( k = 0 ; k < i ; k++){
            temp = temp->anterior;
            if( temp == NULL){
                break;
            }
        }
    if( temp == NULL){
            posicao = 0;
        }else{
            posicao = temp->chave;
        }
        Vtemp[posicao] = Vtemp[posicao]+1;
     //   printf("Somamos que no balde %d o numero apareceu %d vezes. \n", temp->chave, Vtemp[posicao]);
     printf("B%d: %d > ", temp->chave, Vtemp[posicao]);
    }
    
    	//Apresentacao do somatorio dos baldes. Tem como parametro 20 baldes.
    	printf(" \n~~~~ * ~~~~    CDF    ~~~~ * ~~~~");
    	printf("\n    -> Este somatorio tem como parametro 19 baldes");
        printf("\n");
        for ( j = 0 ; j < 20 ; j++){
        Vtemp[j] = Vtemp[j] + Vtemp[j-1];
        printf("%d ", Vtemp[j]);
    }

        for ( j = qt-1; j >= 0 ; j--){
        temp = Vetor[j]->Fim;
        for ( k = 0 ; k < i ; k++){
            temp = temp->anterior;
            if( temp == NULL)
                break;
        }

        if( temp == NULL){
            posicao = 0;
        }else{
            posicao = temp->chave;
        }


			duplicaFila(Vaux[Vtemp[posicao]-1],Vetor[j]);
		//	ImprimeFila(Vaux[Vtemp[posicao]-1]);
			Vtemp[posicao] = Vtemp[posicao] - 1;

    }

    for ( j = 0; j < qt ; j++){
        RemoveFila(Vetor[j]);
    }

    for ( j = 0; j < qt ;j++){
        duplicaFila(Vetor[j],Vaux[j]);
    }

    for ( j = 0;j < qt ; j++){
        RemoveFila(Vaux[j]);
    }

	}

	return Vetor;

}

// -------------------------------------------------------
// -------------------------------------------------------
// -----------------------FUNC MAIN-----------------------
// -------------------------------------------------------
// -------------------------------------------------------

int main(){

	char c = ' ';
	int qtd,i,esc, n;

	printf("Digite a opcao desejada: \n");
	printf("[1] - para Radix Sort \n[2] - para Counting Sort\n \n");
	scanf("%d", &esc);

	switch(esc){

	case 1:
    printf("\n~~~~ Voce escolheu o Radix Sort! ~~~~");
	printf("\nQuantidade de palavras para ordenar: ");
	scanf("%d",&qtd);
	String **Vetor = malloc(sizeof(String*)*qtd);


	for (i = 0 ; i < qtd ; i++)
		Vetor[i] = CriaString(Vetor[i]);

	fflush(stdin);

	for(i = 0; i < qtd ; i++){
		printf("Insira a %d palavra: ",i+1);
		while ( c != '\n'){
			scanf("%c",&c);
			if( c != '\n')
				InsereString(Vetor[i],c);
		}
		c = ' ';
	}

	Vetor = Radix(Vetor,qtd);

	printf(" \n~~~~ * ~~~~ Iteracao Final ~~~~ * ~~~~\n\n");

	for(i = 0; i<qtd ; i++){
		ImprimeString(Vetor[i]);
	}
	break;

	case 2:
    printf("\n~~~~ Voce escolheu o Counting Sort! ~~~~");
	printf("\nQuantidade de numeros para ordenar: ");
	scanf("%d",&qtd);
	Fila **Vetor2 = malloc(sizeof(Fila*)*qtd);

	//Vetor recebendo a lista.
	for (i = 0 ; i < qtd ; i++)
		Vetor2[i] = criaFila(Vetor2[i]);

	fflush(stdin);

	for(i = 0; i < qtd ; i++){
		printf("Insira o numero que seja menor que 20: ",i+1);
			scanf("%i",&n);
			if(n >= 20 || n == 0){
                printf("Apenas de 1 a 19.\n");
            i--;}else{
           		InsereFila(Vetor2[i],n);
            }
	}
	
		printf(" \n~~~~ * ~~~~ Elementos lidos ~~~~ * ~~~~\n");
	for(i = 0; i<qtd ; i++){
		ImprimeFila(Vetor2[i]);
	}
	printf("\n");


	Vetor2 = countingsort(Vetor2,qtd);

	printf("\n ~~~~ * ~~~~ Vetor Ordenado ~~~~ * ~~~~\n");

	for(i = 0; i<qtd ; i++){
		ImprimeFila(Vetor2[i]);
	}
	break;
	}


	return 0;
}
