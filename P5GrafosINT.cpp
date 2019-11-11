#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INF 9999

typedef struct _Arcos{
	int final;
	int peso;
	struct _Arcos *der;
}Arco;
typedef struct _Nodo {
    int vertice;
    struct _Nodo *sig;
    struct _Arcos *sub;
}Nodo;
Nodo *crearNodo(int verti);
Nodo *altaNodo(Nodo *top, int verti);
int encontrar(Nodo *top, int nombre);
Nodo *encontrarb(Nodo *top, int nombre);
Arco *crearArco(int fin, int pes);
void altaArco(Nodo *top, int orig, int fin, int pes);
void lista(Nodo *top);
int contar(Nodo *cima);
void dijkstra(Nodo *vertices, int v, int primero, int ultimo);

int main(){
    Nodo *vertices=NULL;
	char resp='s';
	int vert, vertfin;
	int peso, num_ver, encon, encon2;
	
	printf("---INGRESO DE VERTICES---\n");
	do{
		printf("Ingresa el vertice\n");
		scanf("%d", &vert);	
		encon=encontrar(vertices, vert);
		if(encon>0){
			printf("Ya hay un vertice llamado asi\n");
		}else{
		    vertices = altaNodo(vertices,vert);	
		}
		fflush(stdin);
		printf("Desea ingresar otro vertice? (S/N)\n");
		scanf("%c%*c", &resp);
		resp=toupper(resp);
	}while(resp=='S');
	system("cls");
	resp=='s';
	
	printf("---INGRESO DE ARISTAS---\n");
	do{
		fflush(stdin);
		printf("Ingresa el vertice de origen\n");
		scanf("%d", &vert);	
		fflush(stdin);
		printf("Ingresa el vertice de llegada\n");
		scanf("%d", &vertfin);
		encon=encontrar(vertices, vert);
		encon2=encontrar(vertices, vertfin);
		if(vert==vertfin){
			printf("Introduzca un origen y un final diferente\n");
		}else{
			if(encon>0 && encon2>0){
				printf("Introduzca la ponderacion\n");
				scanf("%d", &peso);
				altaArco(vertices, vert, vertfin, peso);			
				altaArco(vertices, vertfin, vert, peso);
			}else{
				printf("No se encontro alguno de los vertices\n");
			}		
		}
		
		fflush(stdin);
		printf("Desea ingresar otra arista? (S/N)");
		scanf("%c%*c", &resp);
		resp=toupper(resp);
	}while(resp=='S');
	system("cls");	
	resp=='s';
	      
    lista(vertices);
	num_ver=contar(vertices);
	
	printf("---CONOCER CAMINO MAS CORTO---\n");
	do{		
		fflush(stdin);
		printf("Ingresa el vertice de origen\n");
		scanf("%d", &vert);
		fflush(stdin);
		printf("Ingresa el vertice de llegada\n");
		scanf("%d", &vertfin);	
		encon=encontrar(vertices, vert);
		encon2=encontrar(vertices, vertfin);
		if(vert==vertfin){
			printf("Introduzca un origen y un final diferente\n");
		}else{
			if(encon>0 && encon2>0){
				dijkstra(vertices, num_ver, encon, encon2-1);
			}else{
				printf("No se encontro alguno de los vertices\n");
			}		
		}
		fflush(stdin);
		printf("\nDesea conocer otro camino? (S/N)");
		scanf("%c%*c", &resp);
		resp=toupper(resp);
	}while(resp=='S');
	return 0;
}

Nodo *crearNodo(int verti){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->vertice=verti;
    nuevo->sig=NULL;
    nuevo->sub=NULL;
    return nuevo;
}
Nodo *altaNodo(Nodo *top, int verti){
    Nodo *nuevo, *aux;
    nuevo=crearNodo(verti);
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
int encontrar(Nodo *top, int nombre){
	Nodo *aux=top;
	Nodo *enc=NULL;
	int cont=1;
	while(aux!=NULL){
		if(nombre==aux->vertice){
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
Nodo *encontrarb(Nodo *top, int nombre){
	Nodo *aux=top;
	Nodo *encontrado=NULL;
	while(aux!=NULL){
		if(nombre==aux->vertice){
			encontrado=aux;
			return encontrado;
		}
		else{
			aux=aux->sig;	
		}
	}
	return encontrado;
}	
Arco *crearArco(int fin, int pes){
	Arco *tem;
	tem=(Arco *)malloc(sizeof(Arco));
	tem->final=fin;
	tem->peso=pes;
	tem->der=NULL;
	return tem;
}
void altaArco(Nodo *top, int orig, int fin, int pes){
	Nodo *inicio;
	Arco *aux, *tem;
	
	inicio=encontrarb(top, orig);
	tem=crearArco(fin, pes);
	
	if(inicio->sub==NULL){
		inicio->sub=tem;
		return;
	}
	aux=inicio->sub;
	while(aux->der!=NULL){
		aux=aux->der;
	}
	aux->der=tem;	

	return;
}
void lista(Nodo *top){
	Nodo *aux=top;
	Arco *ady;
	FILE * archivob;
    archivob=fopen("P5ListaAdy.txt", "a");
  
	fprintf(archivob, "\nLista de Adyacencia\n");
	while(aux!=NULL){
		fprintf(archivob, "%d ->", aux->vertice);
		ady=aux->sub;
		while(ady!=NULL){
			fprintf(archivob, "%d(%d)-", ady->final, ady->peso);
			ady=ady->der;
		}
		fprintf(archivob, "\n");
		aux=aux->sig;
	}
	fclose(archivob);  		
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
void dijkstra(Nodo *vertices, int v, int primero, int ultimo){
	int cont1=0, cont2=0, cont3=0;
	int c;
	Nodo *aux = vertices;
	Nodo *tem = vertices;
	Nodo *aux2;
	Arco *arc;
	int matriz[v][v];
	int fila[v];
	FILE * archivob;
    archivob=fopen("P5MatrizAdy.txt", "a");
	
	while(aux != NULL){
		fila[cont1]=aux->vertice;
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
			c=arc->final;
			aux2 = aux;
			while(aux2->vertice != c){
				cont2++;
				aux2= aux2->sig;
			}	
				matriz[cont3][cont2]=arc->peso;		
				arc = arc->der;
		}
		tem = tem->sig;
		cont3++;
	}
		
	fprintf(archivob, "\nMatriz de Adyacencia\n");
	fprintf(archivob, "*\t");
	for(int i=0; i<v; i++){
		fprintf(archivob, "%d\t", fila[i]);
	}
	fprintf(archivob, "\n");
	for(int j=0; j<v; j++){
		fprintf(archivob, "%d\t", fila[j]);
		for(int k=0; k<v; k++){	
			fprintf(archivob, "%d\t",matriz[j][k]);	
		}
		fprintf(archivob, "\n");
	}
	fclose(archivob);  	
	
	//Dijkstra
	int mataux[v][v],distancia[v],pred[v], visitado[v];
    int minimo,sigue;
	int j, i;
	for(i=0;i<v;i++)
        for(j=0;j<v;j++)
            if(matriz[i][j]==0)
            	mataux[i][j]=INF;
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
        minimo=INF;
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
                printf("Distancia del nodo %d a %d = %d", fila[i], fila[ultimo], distancia[i]);
                printf("\nRecorrido = %d", fila[i]);
            }
            j = i;
            do{
                j = pred[j];
                if(i == primero-1) {
                    printf("->%d", fila[j]);
                }
            }while (j != ultimo);
        }
}
