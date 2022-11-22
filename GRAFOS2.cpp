#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _Arcos{
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

Arco *crearArco(Nodo *fin, int pes){
	Arco *tem;
	tem=(Arco *)malloc(sizeof(Arco));
	tem->final=fin;
	tem->peso=pes;
	tem->der=NULL;
	return tem;
}

void altaArco(Nodo *orig, Nodo *fin, int pes){
	Nodo *inicio;
	Arco *aux, *tem;
	
	tem=crearArco(fin, pes);
	
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
		printf("%c---\t", aux->nombre);
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
	int cont=0, y=0, x=0;
	int c;
	Nodo *aux = vertices;
	Nodo *tem = vertices;
	Nodo *aux2;
	Arco *arc;
	int matriz[v][v];
	char nom[v];
	
	while(aux != NULL){
		nom[cont]=aux->nombre;
		cont++;
		aux = aux->sig;
	}
	aux = vertices;
	
	for(int j=0; j<v; j++){
		for(int k=0; k<v; k++){
			matriz[j][k]=0;	
		}
	}

	while(tem!=NULL){
		arc = tem->sub;
		while(arc!=NULL){
			y=0;
			c=arc->final->nombre;
			aux2 = aux;
			while(aux2->nombre != c){
				y++;
				aux2= aux2->sig;
			}	
				matriz[x][y]=arc->peso;		
				arc = arc->der;
		}
		tem = tem->sig;
		x++;
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

Nodo *buscar(Nodo *top, char nombre){
	Nodo *aux=NULL;
	while(top!=NULL){
		if(nombre==top->nombre){
			aux=top;
			return aux;
		}
		else{
			top=top->sig;	
		}
	}
	return aux;
}

int repeticion(Nodo *aux, char nombre){
	while(aux!=NULL){
		if(nombre==aux->nombre){
			return 1;
		}
		else{
			aux=aux->sig;	
		}
	}
	return 0;
}	

int main(){
	int nodos;
	Nodo *vertices=NULL;
	int ponderacion;
	char nombre;
	int c;
	Nodo *a;
	Nodo *b;
	char resp='S';
    
	printf("Ingrese el numero de nodos\n");
	scanf("%d", &nodos);

	for(int i=0; i<nodos; i++){
		fflush(stdin);		
		printf("Ingresa el nombre del nodo %d Debe ser una letra\n", (i+1));
		scanf("%c", &nombre);
		nombre=toupper(nombre);
		c=repeticion(vertices, nombre);
			if(c>0){
				printf("Ya hay un vertice llamado asi\n");
				i--;
			}else{
				vertices = altaNodo(vertices, nombre);	
			}				
	}

	printf("Ingreso de arcos");
	do{
		fflush(stdin);
		printf("\nIngresa el vertice de origen\n");
		scanf("%c", &nombre);
		nombre=toupper(nombre);
		a=buscar(vertices, nombre);
		if(a!=NULL){
			fflush(stdin);
			printf("Ingresa el vertice de llegada\n");
			scanf("%c", &nombre);
			nombre=toupper(nombre);
			b=buscar(vertices, nombre);
			if(b!=NULL){
				printf("Escribe la ponderacion entre %c y %c\n", a->nombre, b->nombre);
				scanf("%d", &ponderacion);
				if(ponderacion>0){
					altaArco(a, b, ponderacion);				
				}
				else{
					printf("No se guardo el arco");
				}
			}
			else{
				printf("No se encontro ese vertice\n");
			}
		}else{
			printf("No se encontro ese vertice\n");
		}
			
		fflush(stdin);
		printf("Desea ingresar otro arco? (S/N)");
		scanf("%c%*c", &resp);
		resp=toupper(resp);
	}while(resp=='S');
				
			
	listaAdyacencia(vertices);
	matrizAdyacencia(vertices, nodos);
	
	return 0;
}
