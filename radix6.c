#include<stdio.h>
#include<stdlib.h>

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


int PosChar(char c){
	int i;
	if( c >= 65 && c <= 90){
		i = (int)c - 64;
	}else if ( c >= 97 && c <= 122){
		i = (int)c - 96;
	}/*else if (c >= 48 && c <= 57){
		i = (int)c - 21;
	}*/
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
	int t, p, i, j, M = 0, x = 0, k;
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

//Aqui eh o vetor para depois fazer a troca de valores com o modo de somatorio
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
        printf("~~~~ * ~~~~ Proxima Iteracao ~~~~ * ~~~~\n");

	}

	return Vetor;

}



int main(){

	char c = ' ';
	int qtd,i;
	printf("Quantidade de Palavras: ");
	scanf("%d",&qtd);
	String **Vetor = malloc(sizeof(String*)*qtd);


	for (i = 0 ; i < qtd ; i++)
		Vetor[i] = CriaString(Vetor[i]);

	fflush(stdin);

	for(i = 0; i < qtd ; i++){
		printf("Insira a %d Palavra: ",i+1);
		while ( c != '\n'){
			scanf("%c",&c);
			if( c != '\n')
			InsereString(Vetor[i],c);
		}
		c = ' ';
	}

	Vetor = Radix(Vetor,qtd);

	printf(" ~~~~ * ~~~~ Iteracao Final ~~~~ * ~~~~\n");

	for(i = 0; i<qtd ; i++){
		ImprimeString(Vetor[i]);
	}


	return 0;
}
