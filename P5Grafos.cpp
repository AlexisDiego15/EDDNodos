#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INF 9999

typedef struct _Arcos{
	int final;
	int peso;
	char nom;
	struct _Arcos *der;
}Arco;
typedef struct _Nodo {
    int vertice;
    char nombre;
    struct _Nodo *sig;
    struct _Arcos *sub;
}Nodo;
Nodo *crearNodo(int verti, char n);
Nodo *altaNodo(Nodo *top, int verti, char n);
int encontrar(Nodo *top, char nombre);
Nodo *encontrarb(Nodo *top, int nombre);
Arco *crearArco(int fin, int pes, char n);
void altaArco(Nodo *top, int orig, int fin, int pes, char n);
void lista(Nodo *top);
int contar(Nodo *cima);
void dijkstra(Nodo *vertices, int v, int primero, int ultimo);

int main(){
    Nodo *vertices=NULL;
	char resp='s';
	int vert=1;
	int peso, num_ver, encon, encon2;
	char nombre, nombreb;
	
	printf("---INGRESO DE VERTICES---\n");
	do{
		printf("Ingresa el vertice\n");
		scanf("%c", &nombre);	
		encon=encontrar(vertices, vert);
		if(encon>0){
			printf("Ya hay un vertice llamado asi\n");
		}else{
		    vertices = altaNodo(vertices,vert, nombre);	
		    vert++;
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
		scanf("%c", &nombre);	
		fflush(stdin);
		printf("Ingresa el vertice de llegada\n");
		scanf("%c", &nombreb);
		encon=encontrar(vertices, nombre);
		encon2=encontrar(vertices, nombreb);
		if(nombre==nombreb){
			printf("Introduzca un origen y un final diferente\n");
		}else{
			if(encon>0 && encon2>0){
				printf("Introduzca la ponderacion\n");
				scanf("%d", &peso);
				altaArco(vertices, encon, encon2, peso, nombreb);			
				altaArco(vertices, encon2, encon, peso, nombre);
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
		scanf("%c", &nombre);
		fflush(stdin);
		printf("Ingresa el vertice de llegada\n");
		scanf("%c", &nombreb);	
		encon=encontrar(vertices, nombre);
		encon2=encontrar(vertices, nombreb);
		if(nombre==nombreb){
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

Nodo *crearNodo(int verti, char n){
    Nodo *nuevo;
    nuevo=(Nodo *)malloc(sizeof(Nodo));
    nuevo->vertice=verti;
    nuevo->nombre=n;
    nuevo->sig=NULL;
    nuevo->sub=NULL;
    return nuevo;
}
Nodo *altaNodo(Nodo *top, int verti, char n){
    Nodo *nuevo, *aux;
    nuevo=crearNodo(verti, n);
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
Arco *crearArco(int fin, int pes, char n){
	Arco *tem;
	tem=(Arco *)malloc(sizeof(Arco));
	tem->final=fin;
	tem->peso=pes;
	tem->nom=n;
	tem->der=NULL;
	return tem;
}
void altaArco(Nodo *top, int orig, int fin, int pes, char n){
	Nodo *inicio;
	Arco *aux, *tem;
	
	inicio=encontrarb(top, orig);
	tem=crearArco(fin, pes, n);
	
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
		fprintf(archivob, "%c ->", aux->nombre);
		ady=aux->sub;
		while(ady!=NULL){
			fprintf(archivob, "%c(%d)-", ady->nom, ady->peso);
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
	char nom[v];
	FILE * archivob;
    archivob=fopen("P5MatrizAdy.txt", "a");
	
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
		fprintf(archivob, "%c\t", nom[i]);
	}
	fprintf(archivob, "\n");
	for(int j=0; j<v; j++){
		fprintf(archivob, "%c\t", nom[j]);
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
