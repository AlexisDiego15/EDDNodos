#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo
{
int dato;
struct _Nodo *sig;
}Nodo;

Nodo *crearnodo(int DATO){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo ->dato=DATO;
    nuevo->sig=NULL;
return nuevo;
}

Nodo *bajapila(Nodo *top){
    Nodo *borrar;
    borrar=top;
    if(top!=NULL)
        top=top->sig;
        free(borrar);
    return top;
}


Nodo *altapila(Nodo *top, int DATO){
    Nodo *nuevo;
    nuevo=crearnodo(DATO);
    if(top!=NULL)
        nuevo->sig=top;

    return nuevo;
}


void verpila(Nodo *top){
    if(top==NULL){
    	printf("Vacia");
	}else{
		printf("La pila es: ");
		while(top!=NULL){
     		printf("%d ", top->dato);
    		top=top->sig;
		}
	}
}

void *contarpila(Nodo *top){
	Nodo * aux;
	aux = top;
	int c=0;
	while(aux!=NULL){
	    c++;
	    aux=aux->sig;
	}
	printf("\nEl tamano de la pila es %d \n",c);
}

int main()
{
    int opc, numero;
    Nodo *top=NULL;
    do{
    	printf("\nSelecciona la opcion\n1.Alta\n2.Baja\n3.Ver\n4.Tamano\n0.Salir\n");
	    scanf("%d", &opc);

	    if(opc==1){
	        printf("Ingrese un numero\n");
	        scanf("%d",&numero);
	        top = altapila(top,numero);
	    
	    }else if(opc==2){
	    	top = bajapila(top);
	
	    }else if(opc==3){
			verpila(top);
			
	    }else if(opc==4){
			contarpila(top);
	    }
	}while(opc!=0);
    
    return 0;
}

