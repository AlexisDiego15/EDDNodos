#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//TIPO2

typedef struct _Nodo{
	int dato;
	int alm;
	int mes;
	struct _Nodo *sig;
}Nodo;

Nodo *crearNodo(int DATO, int mes, int alm){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->dato=DATO;
    nuevo->alm=alm;
    nuevo->mes=mes;
    nuevo->sig=NULL;
    return nuevo;
}

Nodo *altaNodo(Nodo *top, int DATO, int mes, int alm){
    Nodo *nuevo, *aux;
    nuevo=crearNodo(DATO, mes, alm);
    if(top==NULL){
        top=nuevo;
    }else{
        aux=top;
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        aux->sig=nuevo;
    }
    return top;
}


Nodo *altapila(Nodo *top, int DATO, int mes, int alm){
	Nodo *nuevo;
    nuevo=crearNodo(DATO, mes, alm);
	if(top!=NULL){
		nuevo->sig=top;
	}

    return nuevo;
}

Nodo *bajaNodo(Nodo *top){
    Nodo *borrar;
    borrar=top;
    int aux;
    if(top==NULL){
        return top;
    }else{
    	top=top->sig;
        free(borrar);
    }

    return top;
}

Nodo *operacionpila(Nodo *cima, Nodo *cima2, Nodo *pil){
    int aux, aux2;
    int m1, alm;
    aux=cima->dato;
    aux2=cima2->dato;
    m1=cima->mes;

    int dat;

    if(aux>aux2){
        alm=1;
        dat=aux2;
    }else{
        alm=2;
        dat=aux;
    }

    pil=altapila(pil, dat, m1, alm);



	return pil;
}


void verFilas(Nodo *cima){
    Nodo *aux;
    aux=cima;
    while(aux!=NULL){
	        printf("\n%d   Mes %d  Almacen   %d",aux->dato, aux->mes,aux->alm);
	        aux=aux->sig;
	}
}

int contarFila(Nodo *cima){
    Nodo * aux;
    aux = cima;
    int a=0;
    while(aux!=NULL){
        a++;
        aux=aux->sig;
    }
    return a;
}

void verpila(Nodo *cima){
	FILE * archivob;
    archivob=fopen("resultados.txt", "a");
	Nodo *aux;
	aux=cima;
	while(aux!=NULL){
	    fprintf(archivob,"\n%d   Mes %d  Almacen   %d",aux->dato, aux->mes,aux->alm);
	    aux=aux->sig;
	}
	fclose(archivob);
}

int main()
{
	char c;
	int n, valor=0;
    Nodo *almacen1=NULL;
    Nodo *almacen2=NULL;
    Nodo *Pila=NULL;
    int mes=1;
    FILE * archivo;
    archivo=fopen("almacen1.txt", "r");
    while((c=getc(archivo))!=EOF){
        if(!isdigit(c)){
            //printf("\nvalor: %d", valor);
            almacen1= altaNodo(almacen1, valor, mes,1);
            valor = 0;
             mes++;
        }else{
            valor *= 10;
            valor += c - '0';
        }

    }
    almacen1= altaNodo(almacen1, valor, mes, 1);
    //printf("\n Ultimo: %d", valor);
	fclose(archivo);

	FILE * archivo2;
    archivo2=fopen("almacen2.txt", "r");
    valor=0;
    mes=1;
    while((c=getc(archivo2))!=EOF){
        if(!isdigit(c)){
            //printf("\nvalor: %d", valor);
            almacen2= altaNodo(almacen2, valor, mes, 2);
            valor = 0;
               mes++;
        }else{
            valor *= 10;
            valor += c - '0';
        }
    }

    almacen2= altaNodo(almacen2, valor, mes, 2);
    //printf("\n Ultimo: %d", valor);
	fclose(archivo);

	printf("\nAlmacen 1 ");
	verFilas(almacen1);
    printf("\nAlmacen2: ");
    verFilas(almacen2);

    int a=1;

    while(a>0){
        Pila = operacionpila(almacen1, almacen2, Pila);
		almacen1=bajaNodo(almacen1);
        almacen2=bajaNodo(almacen2);
        a=contarFila(almacen1);
	}
    printf("\nFINAL ");
	verpila(Pila);

    return 0;
}
