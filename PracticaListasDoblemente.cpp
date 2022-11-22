#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct _Nodo
{
int dato;
struct _Nodo *sig;
struct _Nodo *ant;
}Nodo;

Nodo *crearNodo(int DATO){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->dato=DATO;
    nuevo->sig=NULL;
    nuevo->ant=NULL;
    
    return nuevo;
}

Nodo *altaNodo(Nodo *top, int DATO){
    Nodo *nuevo, *aux;
    nuevo=crearNodo(DATO);
    if(top==NULL){
        top=nuevo;
    }else{
        aux=top;
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        aux->sig=nuevo;
        nuevo->ant=aux;
    }
    return top;
}
 

void verFila(Nodo *cima){
    Nodo *aux, *ultimo;		
    aux=cima;
    
	printf("Lista de izquierda a derecha\n");
    while(aux!=NULL){
        printf("%d-", aux->dato);
        ultimo=aux;
        aux=aux->sig;
    }
    
    printf("\nLista de derecha a izquierda\n");
	while(ultimo!=NULL){
    	printf("%d-", ultimo->dato);
        ultimo=ultimo->ant;
	}
}

Nodo *dividir(Nodo *top){
	Nodo *a, *b, *temp;
	a=top;
	b=top;
	while(a->sig && a->sig->sig){
		a=a->sig->sig;
		b=b->sig;
	}
	temp=b->sig;
	b->sig=NULL;
	return temp;
}

Nodo *merge(Nodo *primero, Nodo *segundo){
	if(!primero){
		return segundo;
	}
	if(!segundo){
		return primero;
	}
	
	if(primero->dato < segundo->dato){
		primero->sig=merge(primero->sig, segundo);
		primero->sig->ant=primero;
		primero->ant=NULL;
		return primero;		
	}else{
		segundo->sig=merge(primero, segundo->sig);
		segundo->sig->ant=segundo;
		segundo->ant=NULL;
		return segundo;
	}
}

Nodo *mergesort(Nodo *top){
	if(!top || !top->sig){
		return top;
	}
	
	Nodo *segundo = dividir(top);
	
	top=mergesort(top);
	segundo=mergesort(segundo);
	
	return merge(top, segundo);
}


int main()
{
	char c;
    int valor=0;
    Nodo *Fila=NULL;

	FILE * archivo;
    archivo=fopen("practica_3.txt", "r");
    while((c=getc(archivo))!=EOF){
        if(!isdigit(c)){
            Fila = altaNodo(Fila,valor);
    	    valor = 0;
        }else{
            valor *= 10;
            valor += c - '0';
        }
    }
    Fila = altaNodo(Fila,valor);
	fclose(archivo);
	
	printf("Antes de ordenar\n");
    verFila(Fila);
    Fila=mergesort(Fila);
    printf("\n\n\nDespues de ordenar\n");
    verFila(Fila);
    
    return 0;
}
