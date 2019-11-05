#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct _Nodo{
	char c;
	int dato;
	struct _Nodo *sig;
	struct _Nodo *izq;
	struct _Nodo *der;
}Nodo;


Nodo *crearnodo(int DATO, char dd, Nodo *i, Nodo *d){
	Nodo *nuevo;
	nuevo=(Nodo *)malloc(sizeof(Nodo));
	nuevo->dato=DATO;
	nuevo->c=dd;
	nuevo->sig = NULL;
	nuevo->izq = i;
	nuevo->der = d;
	    
	return nuevo;
}

Nodo *altapila(Nodo *top, int DATO, char dd, Nodo *i, Nodo *d){
    Nodo *nuevo, *aux;
    nuevo=crearnodo(DATO,dd,i,d);
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

Nodo *raices(Nodo *top){
    Nodo *aux, *aux1, *aux2;
    int cont=1, nuevoi, nuevochar;
    char nuevoc;
    aux=top;
    while(aux!=NULL){
    	if(cont==1){
        	aux1=aux;
        	cont++;
		}
		aux=aux->sig;
		if(cont==2 && aux!=NULL){
        	aux2=aux;
        	nuevoi=(aux1->dato)+(aux2->dato);
        	nuevochar=((int(aux1->c))+(int(aux2->c)))/2;
        	nuevoc= nuevochar;
    		top=altapila(top, nuevoi, nuevoc, aux1, aux2);
			mergesort(&top);
        	cont=1;
			aux=aux->sig;
		}
    }
    return top;
}

void verpila(Nodo *cima){
	FILE * archivob;
	int ii, dd;
    archivob=fopen("P4Lista.txt", "a");
	Nodo *aux;
	aux=cima;
	while(aux!=NULL){
		ii=0;
		dd=0;
		if(aux->izq!=NULL){
			ii=aux->izq->dato;
		}
		if(aux->der!=NULL){
			dd=aux->der->dato;
		}
		fprintf(archivob,"%d %c %d %d \n",aux->dato,aux->c,ii,dd);
	      
		aux=aux->sig;
	}
	fclose(archivob);
}

void inOrden(Nodo *top){
    if(top != NULL){
        inOrden (top->izq);
        printf("-%d %c-",top->dato, top->c);
        inOrden(top->der);
    }
}

void preOrden(Nodo *top){
    if(top != NULL){
        printf("-%d %c-",top->dato, top->c);
        preOrden (top->izq);
        preOrden(top->der);
    }
}

void postOrden(Nodo *top){
    if(top != NULL){
        postOrden (top->izq);
        postOrden(top->der);
        printf("-%d %c-",top->dato, top->c);
    }
}

Nodo *ultimo(Nodo *top){
	Nodo *ul;
	ul=top;
	if(ul==NULL){
		return (NULL);
	}
	if(ul->sig==NULL){
		return top;
	}
	
	return ultimo(top->sig);
}

void printArray(char [], int); 
void printPathsRecur(Nodo *top, char [], int, char); 
void printPaths(Nodo *top); 
  
void printPaths(Nodo *top)  
{ 
  char path[100]; 
  printPathsRecur(top, path, 0, '0'); 
} 
  
void printPathsRecur(Nodo *top, char path[], int pathLen, char cam){ 
    
	if(top==NULL) return; 
	int valor = top->dato; 
    path[0] = top->c;
    pathLen++; 
	path[pathLen] = cam;  
    path[1] =  '-';
 	if (top->izq==NULL && top->der==NULL){ 
    	printArray(path, pathLen+1); 
    }
  	else{ 
    	printPathsRecur(top->izq, path, pathLen, '0'); 
    	printPathsRecur(top->der, path, pathLen, '1'); 
  	} 
} 
  
 
void printArray(char ints[], int len){ 
  int i; 
  for (i=0; i<len; i++) { 
    printf("%c", ints[i]); 
  } 
  printf("\n"); 
}  

int main()
{
	char c, datochar;
	int n, cont=0;
    Nodo *top=NULL;
    Nodo *i=NULL;
    Nodo *d=NULL;
    Nodo *ul=NULL;
	FILE * archivo;
    archivo=fopen("arbol.txt", "r");
    
    while((c=getc(archivo))!=EOF){
		if(isdigit(c)==0 && c!=' '){
    		cont++;
    		datochar=c;	
		}else if(isdigit(c)!=0){
    		n=(float)(c-48);
    		cont++;	
    		top=altapila(top, n, datochar, i, d);	
		}
	}
	fclose(archivo);       
	top=raices(top);
	verpila(top);
	
	ul=ultimo(top);
	
	printf("\nInorden\n");
	inOrden(ul);
	printf("\nPreorden\n");
	preOrden(ul);
	printf("\nPostorden\n");
	postOrden(ul);
	printf("\nCaminos\n");
	printPaths(ul); 	 
    
	return 0;
}

