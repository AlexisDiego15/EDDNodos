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

int encontrar(Nodo *top, char nombre){
	Nodo *aux=top;
	Nodo *enc=NULL;
	int cont=1;
	while(aux!=NULL){
		if(nombre==aux->nombre){
			enc=aux;
			return cont;
		}
		else{
			aux=aux->sig;	
			cont++;
		}
	}
	return 0;
}


void dijkstra(Nodo *vertices, int v, int primero, int ultimo){
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
			matriz[j][k]=0;	
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
		
	int mataux[v][v],distancia[v],pred[v], visitado[v];
    int minimo,sigue;
	int j, i;
	for(i=0;i<v;i++)
        for(j=0;j<v;j++)
            if(matriz[i][j]==0)
            	mataux[i][j]=9999;
            else
                mataux[i][j]=matriz[i][j];	


    for(i=0;i<v;i++){
        distancia[i]=mataux[ultimo][i];
        pred[i]=ultimo;
        visitado[i]=0;
    }

	distancia[ultimo]=0;
    visitado[ultimo]=1;
    cont1=1;

    while(cont1<v-1){
        minimo=9999;
        for(i=0;i<v;i++)
            if(distancia[i]<minimo&&!visitado[i]){
                minimo=distancia[i];
                sigue=i;
            }

        visitado[sigue]=1;
        for(i=0;i<v;i++)
            if(!visitado[i])
                if(minimo+mataux[sigue][i]<distancia[i]){
                    distancia[i]=minimo+mataux[sigue][i];
                    pred[i]=sigue;
                }
        cont1++;        
    }

    for(i=0;i<primero;i++)
        if(i!=ultimo){
            if(i == primero-1){
                printf("Distancia del nodo %c a %c = %d", nom[i], nom[ultimo], distancia[i]);
                printf("\nRecorrido = %c", nom[i]);
            }
            j = i;
            do{
                j = pred[j];
                if(i == primero-1) {
                    printf("->%c", nom[j]);
                }
            }while (j != ultimo);
        }
}


int main(){
	//Ya estan bien
	int nodos=0;
	int ponderacion;
	char nombre_in;
	char nombre_fi;
	int aux=1;
	char c;
	int encontrado;
	FILE * archivo;
    int opc=1;
    int inicio;
    int final;
    
	//Cambiar
	Nodo *vertices=NULL;
	Nodo *a;
	Nodo *b;

	archivo=fopen("grafo.txt", "r");
    
    printf("Arcos:\n\n");
    while((c=getc(archivo))!=EOF){
		if(c!='\n' && c!='\t'){
			if(isdigit(c)==0 && aux==1){
	    		nombre_in=c;
				encontrado=encontrar(vertices, nombre_in);
				if(encontrado==0){
					vertices = altaNodo(vertices, nombre_in);	
					nodos++;
				}
								
				a=buscar(vertices, nombre_in);
	    		aux++;
			}else if(isdigit(c)==0 && aux==2){
	    		nombre_fi=c;
				encontrado=encontrar(vertices, nombre_fi);
				if(encontrado==0){
					vertices = altaNodo(vertices, nombre_fi);	
					nodos++;
				}
								
				b=buscar(vertices, nombre_fi);
	    		aux++;
			}else if(isdigit(c)!=0 && aux==3){
	    		ponderacion=(int)(c-48);
				altaArco(a, b, ponderacion);				
				
				printf("De %c a %c son %d\n", nombre_in, nombre_fi, ponderacion);
				aux=1;	
			}
		}
	}
	printf("\nNodos %d", nodos);
	
	while(opc>0 && opc<4){
	
		printf("\nElija una opcion");
		printf("\n[1] Mostrar lista de adyacencia");
		printf("\n[2] Mostrar matriz");
		printf("\n[3] Camino mas corto\n");
		scanf("%d",&opc);
		system("cls");
	
		switch(opc){
			case 1:
				listaAdyacencia(vertices);
			    break;
			
			case 2: 
				matrizAdyacencia(vertices, nodos);
			    break;
			
			case 3:
				printf("---Camino mas corto---");
				fflush(stdin);
				printf("\nEscribe el nodo de inicio\n");
				scanf("%c", &nombre_in);
				inicio=encontrar(vertices, nombre_in);
				fflush(stdin);
				printf("Escribe el nodo de llegada\n");
				scanf("%c", &nombre_fi);
				final=encontrar(vertices, nombre_fi);
				if(inicio>0 && final>0){
					dijkstra(vertices, nodos, inicio, final-1);
				}else{
					printf("No se encontro algun nodo");
				}
		
			    break;
		}
	}
	
	return 0;
}
