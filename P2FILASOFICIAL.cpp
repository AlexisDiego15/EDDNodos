#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct _Nodo{
	char dato;
	struct _Nodo *sig;
}Nodo;

Nodo *crearNodo(char DATO){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->dato=DATO;
    nuevo->sig=NULL;
    return nuevo;
}

Nodo *altaNodo(Nodo *top, char DATO){
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




void verFilas(Nodo *cima){
    Nodo *aux;
    aux=cima;
    while(aux!=NULL){
	        printf("P%c-",aux->dato);
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

int main(){
	int seg=0;
    int num=17;
    char cl;
    Nodo *Fila=NULL;
    Nodo *FilaFA=NULL;
	Nodo *FilaFP=NULL;
	Nodo *FilaFC=NULL;
	Nodo *FilaFNC=NULL;
	srand(time(NULL));
    int fil = 0;
    int a=1;

    do{
    	cl=num+'0';
        num++;
        verFilas(Fila);
        Sleep(2000);
        seg=seg+2;
        system("cls");
        Fila = altaNodo(Fila,cl);
    }while(seg<30);
    
	while(a>0){
	    fil = rand()% (4 + 1 - 1) + 1;
	    cl=Fila[0].dato;
		if(fil==1){
			FilaFA = altaNodo(FilaFA,cl);
		}else if(fil==2){
			FilaFP = altaNodo(FilaFP,cl);		
		}else if(fil==3){
			FilaFC = altaNodo(FilaFC,cl);		
		}else if(fil==4){
			FilaFNC = altaNodo(FilaFNC,cl);		
		}
	    Fila = bajaNodo(Fila);
	 	a=contarFila(Fila);
	}
		printf("\nFila de Atencion: ");
		verFilas(FilaFA);
		printf("\nFila de Prioridad: ");
		verFilas(FilaFP);
		printf("\nFila de Clientes: ");
		verFilas(FilaFC);
		printf("\nFila de No Clientes: ");
		verFilas(FilaFNC);
}




