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
	nuevo->dato=DATO;
	nuevo->sig=NULL;

	return nuevo;
}

Nodo *altaNodo(Nodo *top, int DATO, int pos){
	Nodo *nuevo, *aux;
	int cont=1;
    nuevo=crearnodo(DATO);
	if(pos==1){
		if(top!=NULL){
			nuevo->sig=top;
			return nuevo;
		}
	}else if(pos==0){
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
	}else if(pos>1){
		aux=top;
		while(cont!=pos-1){
			aux=aux->sig;
			cont++;
		}
		nuevo->sig=aux->sig;
		aux->sig=nuevo;
		return top;
	}
}

int contar(Nodo *cima){
    Nodo * aux;
    aux = cima;
    int a=0;
    while(aux!=NULL){
        a++;
        aux=aux->sig;
    }
    return a;
}

void verListas(Nodo *cima){
    Nodo *aux;
    aux=cima;
    while(aux!=NULL){
	        printf(" %d ",aux->dato);
	        aux=aux->sig;
	}
}

Nodo*bajaNodo(Nodo *top, int pos){
	Nodo *aux, *borrar;
	int cont=1;
	aux=top;
	if(pos==1){
		if(top!= NULL){
            top=top->sig;
            free(aux);
        }
        return top;
    }else if(pos==0){
        if(top->sig==NULL){
            free(top);
            return NULL;
        }
        aux=top;
        while(aux->sig->sig!=NULL){
            aux=aux->sig;
        }
        free(aux->sig);
        aux->sig=NULL;
        return top;
	}else if(pos>1){
		for(int i=1; i<pos-1; i++){
			if(aux->sig==NULL){
				printf("Posicion equivocada");
			}
			aux=aux->sig;
		}
		borrar=aux->sig;
		aux->sig=borrar->sig;
		free(borrar);
		
		return top;
	}
}

Nodo *cambiaNodo(Nodo *top, int viejo, int nuevo){
	Nodo *aux;
	aux=top;
	while(aux->sig != NULL){
		if(aux->dato==viejo){
			aux->dato=nuevo;
		}
		aux=aux->sig;
	}
	return top;
}

int main(){
	int opc,dato,pos,tam,nuevo;
	char op;
	Nodo*top;
	top=NULL;
	do{
	//system("cls");
	printf("\nIngrese la opcion\n1.-Alta\n2.-Baja\n3.-Cambio\n4.-Ver Lista\n5.-Tamano\n0.-Salir\n");
	scanf("%d",&opc);
	switch(opc){
		case 1:
			printf("Ingrese el dato\n");
			scanf("%d",&dato);
			printf("Ingrese la posicion\nP.-Primera\nU.-Ultima\nO.-Otra\n");
			scanf("%s",&op);
				switch(op){
					case 'P': case'p':
						top = altaNodo(top, dato,1);
					break;
					case 'U': case'u':
						top = altaNodo(top, dato,0);
					break;
					case 'O': case'o':
						printf("Ingresa la posicion\n");
						scanf("%d",&pos);
						tam = contar(top);
						if(pos<=tam && pos>0){
							top = altaNodo(top, dato, pos);
						}else{
							printf("Posicion invalidada\n");
						}
					break;
				}
		break;
		case 2:
			printf("Ingrese la posicion a eliminar\nP.-Primera\nU.-Ultima\nO.-Otra\n");
			scanf("%s",&op);
				switch(op){
					case 'P': case 'p':
						top = bajaNodo(top, 1);
					break;
					case 'U': case 'u':
						top = bajaNodo(top, 0);
					break;
					case 'O': case 'o':
						printf("Ingresa la posicion\n");
						scanf("%d",&pos);
						tam = contar(top);
						if(pos<=tam && pos>0){
							top = bajaNodo(top, pos);
						}else{
							printf("Posicion invalidada\n");
						}
					break;
				}
		break;
		case 3:
			printf("Escribe el dato que quieres cambiar\n");
			scanf("%d",&dato);
			printf("Escribe el dato nuevo\n");
			scanf("%d",&nuevo);
			top=cambiaNodo(top, dato, nuevo);
		break;
		case 4:
			verListas(top);
		break;
		case 5:
			tam = contar(top);
			printf("\nEl tamano es: %d\n", tam);
		break;
	}
	}while(opc!=0);
	return 0;
}

