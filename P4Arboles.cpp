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


Nodo *crearnodo(int DATO, char dd){
	Nodo *nuevo;
	nuevo=(Nodo *)malloc(sizeof(Nodo));
	nuevo->dato=DATO;
	nuevo->c=dd;
	nuevo->sig=NULL;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	    
	return nuevo;
}

Nodo *altapila(Nodo *top, int DATO, char dd){
    Nodo *nuevo, *aux;
    nuevo=crearnodo(DATO,dd);
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

void dividir(Nodo *top, Nodo **a, Nodo **b ){
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
    int cont=1, nuevoi;
    char nuevoc='$';
    aux=top;
    while(aux!=NULL){
    	if(cont==1){
        	aux1=aux;
        //	printf("entra con 1\n");
		//	printf("%d %c\n", aux1->dato, aux1->c);
        	cont++;
		}
		aux=aux->sig;
		if(cont==2 && aux!=NULL){
        	aux2=aux;
        	nuevoi=(aux1->dato)+(aux2->dato);
    		top=altapila(top, nuevoi, nuevoc);	
    		mergesort(&top);
			//  printf("%d %c\n", nuevoi, nuevoc);
			//	printf("entra con 2\n");
		    //	printf("%d %c\n", aux2->dato, aux2->c);
        	//  nuevo=altaraiz(nuevo, aux1, aux2);
        	cont=1;
			aux=aux->sig;
		}
    }
    return top;
}

void verpila(Nodo *cima){
	FILE * archivob;
    archivob=fopen("resultados.txt", "a");
	Nodo *aux;
	aux=cima;
	while(aux!=NULL){
	    fprintf(archivob,"%d %c \n",aux->dato,aux->c);
	    aux=aux->sig;
	}
	fclose(archivob);
}

Nodo*bajapila(Nodo *cima){
	Nodo * destruir;
	destruir = cima;
    cima=cima->sig;
	free(destruir);
	
    return cima;
}

int main()
{
	char c, datochar;
	int n, cont=0;
    Nodo *top=NULL;
    FILE * archivo;
    archivo=fopen("arbol.txt", "r");
    
    while((c=getc(archivo))!=EOF){
		if(isdigit(c)==0 && c!=' '){
    		cont++;
    		datochar=c;	
		}else if(isdigit(c)!=0){
    		n=(float)(c-48);
    		cont++;	
    		top=altapila(top, n, datochar);	
		}
	}
	fclose(archivo);       

	top=raices(top);
    verpila(top);
	
	return 0;
}

