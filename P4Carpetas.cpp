#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct _Nodo{
	char descripcion[100];
	struct _Nodo *hijo;
	struct _Nodo *hermano;
}Nodo;

Nodo *sub=NULL;

Nodo *crearNodo(char des[]){
	Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    memcpy(nuevo->descripcion,des,strlen(des)+1);
    nuevo->hijo=NULL;
    nuevo->hermano=NULL;
    
    return nuevo;
}

Nodo *altaNodo(Nodo *top, char descripcion[]){
	Nodo *nuevo, *aux;
    nuevo=crearNodo(descripcion);
    if(top==NULL){
        top=nuevo;
    }else{
    	if(top->hijo==NULL){
    		top->hijo=nuevo;
		}else{
			aux=top->hijo;
				while(aux->hermano!=NULL){
		            aux=aux->hermano;
		        }
        	aux->hermano=nuevo;
    	}
    }
    return top;
}


void Busqueda(Nodo *arbol, char carpeta[]){
	if(arbol!=NULL){
		if(strcmp(carpeta, arbol->descripcion)==0){
				sub=arbol;
		}else{
			Busqueda(arbol->hijo, carpeta);
			Busqueda(arbol->hermano, carpeta);
		}
	}
}

void VerArbol(Nodo *top, int guion){
	int aux=0;
	if(top!=NULL){
		while(aux!=guion){
			printf("---");
			aux++;
		}
		printf("%s\n", top->descripcion);
		VerArbol(top->hijo, guion+1);
		VerArbol(top->hermano, guion);
	}
}


Nodo* eliminarNodo(Nodo* raiz, char carpeta[]){
	Nodo *aux;
	
    if(raiz == NULL){
    	return raiz;
	}else{
		if((strcmp(raiz->descripcion, carpeta) == 0)){
	        free (raiz);
	        raiz = NULL;
	    }else if (raiz->hijo->descripcion && (strcmp(raiz->hijo->descripcion, carpeta) == 0) && raiz->hijo->hermano != NULL){
	        aux = raiz->hijo;
	        raiz->hijo = aux->hermano;
	        free(aux);
	    }else if (raiz->hijo->descripcion && (strcmp(raiz->hijo->descripcion, carpeta) == 0) && raiz->hijo->hermano == NULL){
	        aux = raiz->hijo;
	        free(aux);
	        raiz->hijo = NULL;
	    }else if(raiz->hermano->descripcion && (strcmp(raiz->hermano->descripcion, carpeta) == 0) && raiz->hermano->hermano != NULL){
	        aux = raiz->hermano;
	        raiz->hermano = aux->hermano;
	        free(aux);
	    }else if (raiz->hermano->descripcion && (strcmp(raiz->hermano->descripcion, carpeta) == 0) && raiz->hermano->hermano == NULL){
	        aux = raiz->hermano;
	        free(aux);
	        raiz->hermano = NULL;
	    }else{
	        raiz->hijo = eliminarNodo(raiz->hijo, carpeta);
	        raiz->hermano = eliminarNodo(raiz->hermano, carpeta);
	    }
	    return raiz;
	}
}

int main(){
	Nodo *arbol=NULL;
	char carpeta[100];
	
	fflush(stdin);
	printf("\nIngresa el nombre de la carpeta principal\n");
	gets(carpeta);
	arbol=altaNodo(arbol, carpeta);
	
	int opc=0;
	int foco;
    
	do{
	        	
	sub=NULL;
    printf("\n---Sistema de archivos--- \n");
    printf("[1] Agregar \n");
    printf("[2] Eliminar \n");
    printf("[3] Ver \n");
    printf("[4] Salir \n");
    scanf("%d",&opc);
	system("cls");
    

    switch(opc){
        
		case 1:
        	printf("AGREGAR CARPETA/DIRECTORIO\n");
			fflush(stdin);
			printf("Ingresa el nombre de la carpeta padre\n");
			gets(carpeta);
			Busqueda(arbol, carpeta);
			
			if(sub!=NULL){
				printf("Ingresa el nombre de la carpeta nueva\n");
				gets(carpeta);
				altaNodo(sub, carpeta);
				printf("Se registro\n");
			}else{
				printf("No se encontro esa carpeta padre\n");
			}
			
			
		break;
            
        case 2:
        	printf("ELIMINAR CARPETA/DIRECTORIO\n");
        	
			fflush(stdin);
			printf("Ingresa el nombre de la carpeta para eliminar, si hay dos carpetas iguales se eliminara la primera en ser encontrada\n");
			gets(carpeta);
			Busqueda(arbol, carpeta);
			
			if(sub!=NULL){
				arbol=eliminarNodo(arbol, carpeta);
				printf("Carpeta eliminada\n");
			}else{
				printf("No se encontro esa carpeta\n");
			}
			
			
            break;
            
        case 3:
		  	printf("DIRECTORIO\n");
			VerArbol(arbol, 0);
        	break;
            
        case 4:
            printf("Fin del sistema de archivos");
            exit(-1);
        }
    }
    while(1);
    
return 0;
}
