#include<stdio.h> 
#include<stdlib.h> 
#define max(a,b) (((a)>(b))?(a):(b))
   
typedef struct _Nodo
{ 
    int dato; 
    struct _Nodo *der;
    struct _Nodo *izq;
}Nodo; 
   
   
Nodo *crearnodo(int valor){
	Nodo *nuevo;
	nuevo=(Nodo *)malloc(sizeof(Nodo));
	nuevo->dato=valor;
	nuevo->izq=nuevo->der = NULL;

	return nuevo;
}
      
Nodo *altaArbol(Nodo *arbol, int valor){ 
	Nodo *nuevo;
	Nodo *raiz;
	
    nuevo = crearnodo(valor);

    if (arbol == NULL){
    	return nuevo; 	
	}else{
		raiz=arbol;
		while(raiz!=NULL){
			if(valor>raiz->dato){
				if(raiz->der==NULL){
					raiz->der=nuevo;
					return arbol;	
				}else{
					raiz=raiz->der;
				}
			}else{
				if(raiz->izq==NULL){
					raiz->izq=nuevo;
					return arbol;
				}else{
					raiz=raiz->izq;
				}
			}
		}
	}
}

void inOrden(Nodo *top){
    if (top != NULL){
        inOrden (top->izq);
        printf(" %d \n",top->dato);
        inOrden(top->der);
    }
}

void preOrden(Nodo *top){
    if (top != NULL){
        printf(" %d \n",top->dato);
        preOrden (top->izq);
        preOrden(top->der);
    }
}

void postOrden(Nodo *top){
    if (top != NULL){
        postOrden (top->izq);
        postOrden(top->der);
        printf(" %d \n",top->dato);
    }
}

int buscar(Nodo *raiz, int dato){
	while(raiz!=NULL){
		if(raiz->dato==dato){
			return 1;
		}if(dato<raiz->dato){
			raiz=raiz->izq;
		}else{
			raiz=raiz->der;
		}
	}
	return 0;
}

int nivel(Nodo *arbol){
	if(arbol==NULL){
		return 0;
	}else{
		return max(nivel(arbol->izq)+1,nivel(arbol->der)+1);
	}
}

Nodo *recorrer(Nodo *top){
	Nodo *aux=top;
	while(aux && aux->izq!=NULL){
		aux=aux->izq;
	}
	return aux;
}


Nodo *bajaArbol(Nodo *arbol, int dato){
	Nodo *aux;

	if(arbol == NULL){
		return arbol;
	}else{
		if(dato<arbol->dato){
            arbol->izq=bajaArbol(arbol->izq, dato);
        }else if(dato>arbol->dato){
            arbol->der=bajaArbol(arbol->der, dato);
        }else{
        	if(arbol->izq==NULL){
        		aux=arbol->der;
        		free(arbol);
        		return aux;				
			}else
			if(arbol->der==NULL){
        		aux=arbol->izq;
        		free(arbol);
        		return aux;
			}
			
			aux=recorrer(arbol->der);
			arbol->dato=aux->dato;
			arbol->der=bajaArbol(arbol->der, aux->dato);
		}
    }
    return arbol;
}


int main() 
{ 
    int opc,dato,orden,busqueda;
    Nodo *top = NULL;
   
   	do{
	printf("\nIngrese la opcion\n1.-Alta\n2.-Baja\n3.-Mostrar\n4.-Altura\n5.-Busqueda\n0.-Salir\n");
	scanf("%d",&opc);
	switch(opc){
		case 1:
			printf("Ingrese el dato a insertar\n");
			scanf("%d",&dato);
			top = altaArbol(top, dato);
		break;
		
		case 2:
			printf("Ingrese el dato a eliminar\n");
			scanf("%d",&dato);
			top = bajaArbol(top, dato);
		break;
		
		case 3:
			printf("\nIngrese el orden deseado:\n1.-inOrden\n2.-preOrden\n3.-postOrden\n");
			scanf("%d",&orden);
				switch(orden){
					case 1:
						inOrden(top);
					break;
					
					case 2:
						preOrden(top);
					break;
	
					case 3:
						postOrden(top);
					break;
				}
		break;
		
		case 4:
			printf("La altura es: %d", nivel(top));
		break;
		
		case 5:
			printf("Ingrese el dato a buscar\n");
			scanf("%d",&dato);
			busqueda=buscar(top, dato);
			if(busqueda==1){
				printf("\nSe encontro\n");
			}else{
				printf("\nNo se encontro\n");
			}
		break;
	}
	}while(opc!=0);
	return 0;
}

