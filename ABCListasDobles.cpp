#include <stdio.h>
#include <stdlib.h>

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
    printf("En orden:\n");
    while(aux!=NULL){
        printf("%d-", aux->dato);
        ultimo=aux;
        aux=aux->sig;
    }
    
    printf("\nDe regreso:\n");
    
    while(ultimo!=NULL){
    	printf("%d-", ultimo->dato);
        ultimo=ultimo->ant;
	}
}

int main()
{
    int opc;
    int num;
    Nodo *Fila=NULL;

    do{
        printf("\n1.Insertar\n3.Mostrar\n");
        scanf("%d",&opc);
        if(opc==1){
            printf("\nIngrese un numero\n");
            scanf("%d",&num);
            Fila = altaNodo(Fila,num);
        }else if(opc==3){
            verFila(Fila);
        }
    }while(opc!=0);

    return 0;
}
