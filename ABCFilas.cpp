#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo
{
int dato;
struct _Nodo *sig;
}Nodo;

Nodo *crearNodo(int DATO){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->dato=DATO;
    nuevo->sig=NULL;
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
    }
    return top;
}

Nodo *bajaNodo(Nodo *top){
    Nodo *borrar;
    borrar=top;
    if(top==NULL){
        return top;
    }else{
        top=top->sig;
        free(borrar);
    }
    return top;
}

void verFila(Nodo *cima){
    Nodo *aux;
    aux=cima;
    while(aux!=NULL){
        printf("%d-",aux->dato);
        aux=aux->sig;
    }
}

void *contarFila(Nodo *cima){
    Nodo * aux;
    aux = cima;
    int a=0;
    while(aux!=NULL){
        a++;
        aux=aux->sig;
    }
    printf("\nLa fila tiene %d elementos\n",a);
}

int main()
{
    int opc;
    int num;
    Nodo *Fila=NULL;

    do{
        printf("\n1.Insertar\n2.Borrar\n3.Mostrar\n4.Tamano\n");
        scanf("%d",&opc);
        if(opc==1){
            printf("\nIngrese un numero\n");
            scanf("%d",&num);
            Fila = altaNodo(Fila,num);
        }else if(opc==2){
            Fila = bajaNodo(Fila);
        }else if(opc==3){
            verFila(Fila);
        }else if(opc==4){
            contarFila(Fila);
        }
    }while(opc!=0);

    return 0;
}


