#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _Nodo{
	char c;
	int dato;
	struct _Nodo *sig;
	struct _Nodo *izq;
	struct _Nodo *der;
}Nodo;

Nodo *crearnodo(int DATO, char dd, Nodo *i, Nodo *d);
Nodo *altapila(Nodo *top, int DATO, char dd, Nodo *i, Nodo *d);
void mergesort(Nodo **top);
Nodo *ordenamiento(Nodo *a, Nodo *b);
void dividir(Nodo *top, Nodo **a, Nodo **b);
Nodo *raices(Nodo *top);
void verpila(Nodo *cima);
void inOrden(Nodo *top);
void preOrden(Nodo *top);
void postOrden(Nodo *top);
Nodo *ultimo(Nodo *top);
void imprimir(char [], int, int); 
void caminorecur(Nodo *top, char [], int, char); 
void recorridos(Nodo *top); 

int main(){
	char c, datochar;
	int n;
    Nodo *top=NULL;
    Nodo *i=NULL;
    Nodo *d=NULL;
    Nodo *ul=NULL;
	FILE * archivo;
    archivo=fopen("arbol.txt", "r");
    
    while((c=getc(archivo))!=EOF){
		if(isdigit(c)==0 && c!=' '){
    		datochar=c;	
		}else if(isdigit(c)!=0){
    		n=(float)(c-48);
    		top=altapila(top, n, datochar, i, d);	
		}
	}
	fclose(archivo);       
	top=raices(top);
	verpila(top);
	ul=ultimo(top);
	inOrden(ul);
	preOrden(ul);
	postOrden(ul);
	recorridos(ul); 	 
    
	return 0;
}


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
	FILE * archivob;
    archivob=fopen("P4Inorder.txt", "a");
    if(top != NULL){
        inOrden (top->izq);
        fprintf(archivob, "%d-%c\n",top->dato, top->c);
        inOrden(top->der);
    }
}
void preOrden(Nodo *top){
	FILE * archivob;
    archivob=fopen("P4Preorder.txt", "a");
    if(top != NULL){
        fprintf(archivob, "%d-%c\n",top->dato, top->c);
        preOrden (top->izq);
        preOrden(top->der);
    }
}
void postOrden(Nodo *top){
	FILE * archivob;
    archivob=fopen("P4Postorder.txt", "a");
    if(top != NULL){
        postOrden (top->izq);
        postOrden(top->der);
        fprintf(archivob,"%d-%c\n",top->dato, top->c);
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

void recorridos(Nodo *top){ 
  char camino[10]; 
  caminorecur(top, camino, 0, '0'); 
} 
  
void caminorecur(Nodo *top, char camino[], int cont, char cam){ 
    
	if(top==NULL) return; 
	
	int valor;
	camino[0] = top->c;
    cont++; 
	camino[cont] = cam;  
    camino[1] =  '|';
 	if (top->izq==NULL && top->der==NULL){ 
    	valor = top->dato;
    	imprimir(camino, cont+1, valor); 	
    }
  	else{ 
    	caminorecur(top->izq, camino, cont, '0'); 
    	caminorecur(top->der, camino, cont, '1'); 
  	} 
} 
  
 
void imprimir(char camino[], int cont, int valor){ 
    int i; 
    FILE * archivob;
    archivob=fopen("P4RecorridosHojas.txt", "a");
  
    fprintf(archivob, "%d ", valor);
    for (i=0; i<cont; i++) { 
    	fprintf(archivob, "%c", camino[i]); 
    } 
    fprintf(archivob, "\n"); 
} 
