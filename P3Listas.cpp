#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>   

typedef struct _Nodo{
	int dato;
	int dia;
	int mes;
	int anio;
	char descripcion[100];
	struct _Nodo *sig;
}Nodo;

Nodo *crearNodo(int id,  int dia, int mes, int anio, char des[]){
	Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->dato=id;
    nuevo->dia=dia;
    nuevo->mes=mes;
    nuevo->anio=anio;
    strncpy(nuevo->descripcion,des,100);
    nuevo->sig=NULL;
    return nuevo;
}


Nodo *altaNodo(Nodo *top, int id, int dia, int mes, int anio, char descripcion[]){
	Nodo *nuevo, *aux;
    nuevo=crearNodo(id, dia, mes, anio, descripcion);
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
	int valor= contar(cima);;
    Nodo *aux;
    aux=cima;
    int id=1;
    
	if(valor==0){
		printf("No hay eventos guardados");
	}else{
    	while(aux!=NULL){
		    printf("\nId: %d\tFecha: %d/%d/%d\tEvento: %s",id,aux->fecha[0],aux->fecha[1],aux->fecha[2],aux->descripcion);
		    aux=aux->sig;
		    id++;
		}	
	}
}

int disponibilidad(Nodo *top, int dia, int mes, int an){
	Nodo *aux;
	aux=top;
	int id;
	if(top==NULL){
        id=1;
    }else{
   		while(aux!= NULL){
			if(aux->dia==dia && aux->mes==mes && aux->anio==an){
				id=0;
			}
			aux=aux->sig;
		}
	}
	return id;
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
    }else if(pos>1){
		for(int i=1; i<pos-1; i++){
			if(aux->sig==NULL){
				printf("Posicion equivocada");
			}
			aux=aux->sig;
		}
		borrar=aux->sig;
		aux->sig=borrar->sig;
		return top;
	}
}

void guardareventos(Nodo *cima){
	FILE * archivo;
    archivo=fopen("eventos.bin", "wb");
    
    Nodo *aux, *even;
	aux=cima;
	even=NULL;
	
    if(archivo==NULL){
    	printf("ERROR");
	}else{
		while(aux!=NULL){
			even = aux->sig;
			aux->sig=NULL;
			fseek(archivo,0,SEEK_END);
        	fwrite(aux, sizeof(Nodo), 1, archivo);

        	
        	aux->sig=even;
        	even=NULL;
        	aux=aux->sig;
		}		
	}

    fclose(archivo);
    archivo=NULL;
}

Nodo *leerarchivo(Nodo *cima, FILE *archivo){
	size_t valor;
	Nodo *aux, *nuevo;
	if(cima == NULL){
		cima = (Nodo *)malloc(sizeof(Nodo));
		valor=fread(cima, sizeof(Nodo),1,archivo);
		cima->sig=NULL;	
	}else{
		aux=cima;
		nuevo= (Nodo *)malloc(sizeof(Nodo));
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		valor=fread(nuevo, sizeof(Nodo),1,archivo);
		aux->sig=nuevo;
		nuevo->sig=NULL;

	}
	return cima;
}

Nodo *cargareventos(Nodo *cima){
	FILE * archivo;
    archivo=fopen("eventos.bin", "rb");
    if(archivo==NULL){
	}else{
			cima=NULL;
			fseek(archivo,0,SEEK_END);
        	long fileSize=ftell(archivo);
        	rewind(archivo);
        	int eventos = (int)(fileSize/(sizeof(Nodo)));
        	
        	for(int i=0; i<eventos;i++){
        		fseek(archivo,(sizeof(Nodo)*i),SEEK_SET);
        		cima=leerarchivo(cima, archivo);
			}
				
	}
	return cima;
}

int main(){
	int opc, eventos;
	int dia, mes, anio, id;
	char descripcion[100];
	Nodo*top;
	top=NULL;
		
	//top=cargareventos(top);
	
	do{
		printf("\nIngrese la opcion\n1.-Alta de evento\n2.-Baja de evento\n3.-Ver eventos\n4.-Ver cantidad de eventos\n5.-Salir\n");
		scanf("%d",&opc);
		system("cls");
		switch(opc){
			
			case 1:
	 			printf("\n---ALTA EVENTO---");
	 			printf("\nIngrese el dia del evento \n");
	 			scanf("%d", &dia);
	 			printf("Ingrese el mes del evento \n");
	 			scanf("%d", &mes);
	 			printf("Ingrese el año del evento \n");
	 			scanf("%d", &anio);
				id=disponibilidad(top, dia, mes, anio);
	
				if(id>0){
					fflush(stdin);
		   			printf("\nEscribe la descripcion del evento: \n");
		   			gets(descripcion);
					top = altaNodo(top, id, dia, mes, anio, descripcion);
				}else{
					printf("\nFecha no disponible");
				}				
			break;
			
			case 2:
				printf("\n---BAJA EVENTO---");
				verListas(top);
				printf("\nIngresa el ID del evento que desea eliminar\n");
				scanf("%d",&id);
				eventos = contar(top);
				if( id>0 && id<=eventos){
					top = bajaNodo(top, id);
				}else{
					printf("\nPosicion invalida");
				}
			break;
			
			case 3:
				printf("---EVENTOS---");
				verListas(top);
			break;
			
			case 4:
				eventos = contar(top);
				printf("\nEl numero de eventos es: %d", eventos);
			break;	
		}
	}while(opc!=5);
	guardareventos(top);
	return 0;
}
