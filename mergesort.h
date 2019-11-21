#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _Nodo{
	char c;
	int dato;
	struct _Nodo *sig;
	struct _Nodo *izq;
	struct _Nodo *der;
}Nodo;

void mergesort(Nodo **top);
Nodo *ordenamiento(Nodo *a, Nodo *b);
void dividir(Nodo *top, Nodo **a, Nodo **b);

void mergesort(Nodo **top){
	Nodo *aux = *top;
	Nodo *a, *b;
	
	if((aux==NULL)||(aux->sig==NULL)){
		return;
	}
	
	dividir(aux, &a, &b);
	
	mergesort(&a);
	mergesort(&b);
	
	*top=ordenamiento(a, b);
}
void dividir(Nodo *top, Nodo **a, Nodo **b){
	Nodo *dos, *uno;
	uno=top;
	dos=top->sig;
	
	while(dos != NULL){
		dos = dos->sig;
		if(dos != NULL){
			uno=uno->sig;
			dos=dos->sig;
		}
	}
	
	*a=top;
	*b=uno->sig;
	uno->sig=NULL;	
}
Nodo *ordenamiento(Nodo *a, Nodo *b){
	Nodo *resultado = NULL;
	
	if(a==NULL){
		return b;
	}else if(b==NULL){
		return a;
	}
	
	if(a->dato <= b->dato){
		resultado = a;
		resultado->sig=ordenamiento(a->sig, b);
	}else{
		resultado = b;
		resultado->sig=ordenamiento(a, b->sig);
	}
	return resultado;
}

