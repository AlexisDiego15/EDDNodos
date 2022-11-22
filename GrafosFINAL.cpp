#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INF 9999

typedef struct _Arcos{
	struct _Nodo *inicio;
    struct _Nodo *final;
	struct _Arcos *der;
	int peso;
}Arco;

typedef struct _Nodo {
    char nombre;
    struct _Nodo *sig;
    struct _Arcos *sub;
}Nodo;

Nodo *crearNodo(char n){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->nombre=n;
    nuevo->sig=NULL;
    nuevo->sub=NULL;
    return nuevo;
}

Nodo *altaNodo(Nodo *top, char n){
    Nodo *nuevo, *aux;
    nuevo=crearNodo(n);
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

Arco *crearArco(Nodo *orig, Nodo *fin, int pes){
	Arco *tem;
	tem=(Arco *)malloc(sizeof(Arco));
	tem->final=fin;
	tem->peso=pes;
	tem->inicio=orig;
	tem->der=NULL;
	return tem;
}

void altaArco(Nodo *orig, Nodo *fin, int pes){
	Nodo *inicio;
	Arco *aux, *tem;
	
	tem=crearArco(orig, fin, pes);
	
	if(orig->sub==NULL){
		orig->sub=tem;
	}else{
		aux=orig->sub;
		while(aux->der!=NULL){
			aux=aux->der;
		}
		aux->der=tem;			
	}

}

void listaAdyacencia(Nodo *top){
	Nodo *aux=top;
	Arco *ady;

	printf("\nLista de Adyacencia\n");
	while(aux!=NULL){
		printf("%c->\t", aux->nombre);
		ady=aux->sub;
		while(ady!=NULL){
			printf("%c(%d)-", ady->final->nombre, ady->peso);
			ady=ady->der;
		}
		printf("\n");
		aux=aux->sig;
	}  		
}

void matrizAdyacencia(Nodo *vertices, int v){
	int cont1=0, cont2=0, cont3=0;
	int c;
	Nodo *aux = vertices;
	Nodo *tem = vertices;
	Nodo *aux2;
	Arco *arc;
	int matriz[v][v];
	char nom[v];
	
	while(aux != NULL){
		nom[cont1]=aux->nombre;
		cont1++;
		aux = aux->sig;
	}
	aux = vertices;
	
	for(int j=0; j<v; j++){
		for(int k=0; k<v; k++){
			matriz[j][k]=INF;	
		}
	}
	while(tem!=NULL){
		arc = tem->sub;
		while(arc!=NULL){
			cont2=0;
			c=arc->final->nombre;
			aux2 = aux;
			while(aux2->nombre != c){
				cont2++;
				aux2= aux2->sig;
			}	
				matriz[cont3][cont2]=arc->peso;		
				arc = arc->der;
		}
		tem = tem->sig;
		cont3++;
	}
		
	printf("\nMatriz de Adyacencia\n");
	printf("*\t");
	for(int i=0; i<v; i++){
		printf("%c\t", nom[i]);
	}
	printf("\n");
	for(int j=0; j<v; j++){
		printf("%c\t", nom[j]);
		for(int k=0; k<v; k++){	
			printf("%d\t",matriz[j][k]);	
		}
		printf("\n");
	}
}

int main(){
	int nodos;
	Nodo *vertices=NULL;
	Nodo *aux=NULL;
	Nodo *rec=NULL;
	
	int peso;
	int n=17;
	char nombre;
	int cont=0;
    
	printf("Ingrese en numero de nodos\n");
	scanf("%d", &nodos);

	do{
		nombre=n+'0';
		printf("El nombre del nodo %d es %c\n", (cont+1),nombre);
		vertices = altaNodo(vertices, nombre);	
		n++;
		cont++;
	}while(nodos!=cont);
	
	rec=vertices;
	aux=vertices;
	           
	printf("\n\n\n");    
	while(aux!=NULL){
		while(rec!=NULL){
			//if(aux->nombre!=rec->nombre){
				fflush(stdin);
				printf("Escribe la ponderacion entre %c y %c. Si no tiene escriba un 0\n", aux->nombre, rec->nombre);
				scanf("%d", &peso);
				if(peso>0){
					altaArco(aux, rec, peso);	
				}
		//	}
			rec=rec->sig;
		}
		rec=vertices;
		aux=aux->sig;
	}	
	
	listaAdyacencia(vertices);
	matrizAdyacencia(vertices, nodos);
	
	return 0;
}
