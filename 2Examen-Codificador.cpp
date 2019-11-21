#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "mergesort.h"

typedef struct _Tabla{
	char n;
	int bits;
	int frecuencia;
	char camino[10];
	struct _Tabla *sig;
}Tabla;

Tabla *tabla;
    
Nodo *crearnodo(int DATO, char dd, Nodo *i, Nodo *d);
Nodo *altapila(Nodo *top, int DATO, char dd, Nodo *i, Nodo *d, int pos);
int posicion(Nodo *top, int dato);
Nodo *cantidad(Nodo *top, int DATO, char dd, Nodo *i, Nodo *d, int pos);
Nodo *raices(Nodo *top);
Nodo *ultimo(Nodo *top);

void verpila(Nodo *cima);
void preOrden(Nodo *top);

void imprimir(char [], int, int); 
void caminorecur(Nodo *top, char [], int, char); 
void recorridos(Nodo *top); 

void verTabla();
Tabla *crearNT(int, char, char [], int);
void altatabla(int, char, char [], int);
int obbites();
void llenado(char dat, FILE *salida);       	

int main(){
	char c, datochar;
	int n, p, g;
    Nodo *top=NULL;
    Nodo *i=NULL;
    Nodo *d=NULL;
    Nodo *ul=NULL;
 	FILE *archivo, *salidabinaria, *salidacyu;
    archivo=fopen("frase.txt", "r");
    salidacyu=fopen("Salida0y1s.txt", "a");
   
    while((c=getc(archivo))!=EOF){
		datochar=c;
		if(c==' ')
			datochar='*';
		if(c=='á'||c=='Á'||c=='â'||c=='Â'||c=='à'||c=='À')
			datochar='A';
		if(c=='É'||c=='é'||c=='ê'||c=='Ê'||c=='è'||c=='È')
			datochar='E';
     	if(c=='í'||c=='Í'||c=='î'||c=='Î'||c=='ì'||c=='Ì')	
			datochar='I';
		if(c=='ó'||c=='Ó'||c=='ô'||c=='Ô'||c=='ò'||c=='Ò')
			datochar='O';
		if(c=='ú'||c=='Ú'||c=='û'||c=='Û'||c=='ù'||c=='Ù')
			datochar='U';
		
		datochar=toupper(datochar);
	 	p=posicion(top, n);
	  	top=cantidad(top, 1, datochar, i, d, p);	
	}
	fclose(archivo);       
	mergesort(&top);
	top=raices(top);
	verpila(top);
    ul=ultimo(top);
	preOrden(ul);
	recorridos(ul); 	 
	verTabla();
    
	int longitud=obbites();
    int cant;
    printf("Bits: %d\n", longitud);
    
    if(longitud%8==0){
    	cant=longitud/8;
	}else{
		cant=1+(longitud/8);
	}
	printf("Cantidad: %d\n", cant);
	int m=cant*8;
	salidabinaria=fopen("salbin.bin","wb");
	archivo=fopen("frase.txt", "r");
	fprintf(salidabinaria, "%d", cant);
	while((c=getc(archivo))!=EOF){
		if(c==' '){
			datochar='*';
		}else{
			datochar=c;	
		}
		datochar=toupper(datochar);
		llenado(datochar, salidacyu);
	}
	fclose(salidacyu);
	fclose(archivo);
	int contador=0;
	int total = 0;
	char ceros[]={'0','0','0','0','0','0','0','0'};
	char parabyte[8];
	salidacyu=fopen("Salida0y1s.txt", "r");
	while((c=getc(salidacyu))!=EOF){
		if(contador==0){
			memcpy(parabyte,ceros,sizeof(parabyte));
		}
		parabyte[contador]=c;
		contador++;
		
		if(contador==8){
			char* start = &parabyte[0];
			
			while (*start){
			 	total *= 2;
			 	if (*start++ == '1') total += 1;
			}
			fprintf(salidabinaria, "%c", total);
			total=0;
			contador=0;
		}
	}
	char* start = &parabyte[0];
	while (*start){
		total *= 2;
	 	if (*start++ == '1') total += 1;
	}
	fprintf(salidabinaria, "%c", total);
	return 0;
}

void llenado(char dat, FILE *salida){
	Tabla *aux=tabla;
	while(aux!=NULL){
		if(dat==aux->n){
			for(int i=0; i<aux->bits; i++){
				fprintf(salida, "%c", aux->camino[i]);	
			}	
		}
		aux=aux->sig;
	}
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

int posicion(Nodo *top, int dat){
	Nodo *aux;
	aux=top;
	int p=1;
	if(aux==NULL){
		p=1;
	}else{
		while(aux!=NULL){
			if(aux->dato<dat){
			//if(aux->dato<=dat){
				p++;
			}
			aux=aux->sig;
		}
	}
	return p;
}

Nodo *cantidad(Nodo *top, int n, char dd, Nodo *i, Nodo *d, int p){
	Nodo *aux =top;
	int condicion=1;
	if(aux==NULL){
		condicion=1;
	}else{
		while(aux!=NULL){
			if(aux->c==dd){
				aux->dato=aux->dato+1;
				condicion=0;
			}	
			aux=aux->sig;
		}
	}
	if(condicion==1){
		top=altapila(top, n, dd, i, d, p);
	}
	return top;
}

Nodo *altapila(Nodo *top, int DATO, char dd, Nodo *i, Nodo *d, int pos){
    Nodo *nuevo, *aux;
    int cont=1;
    nuevo=crearnodo(DATO,dd,i,d);
    if(pos==1){
		if(top!=NULL){
			nuevo->sig=top;
			return nuevo;
		}
	}else if(pos==0){
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
	}else if(pos>1){
        aux=top;
		while(cont!=pos-1){
			aux=aux->sig;
			cont++;
		}
		nuevo->sig=aux->sig;
		aux->sig=nuevo;
		return top;
	}
}


Nodo *raices(Nodo *top){
    Nodo *aux, *aux1, *aux2;
    int cont=1, nuevoi, nuevochar, pos;
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
        	//nuevochar=((int(aux1->c))+(int(aux2->c)))/2;
        	nuevoc= '#';
			pos=posicion(top, nuevoi);
    		top=altapila(top, nuevoi, nuevoc, aux1, aux2, pos);
        	cont=1;
			aux=aux->sig;
		}
    }
    return top;
}

void verpila(Nodo *cima){
	FILE * archivob;
	int ii, dd;
	char k, l;
    archivob=fopen("ExLista.txt", "a");
	Nodo *aux;
	aux=cima;
	while(aux!=NULL){
		ii=0;
		dd=0;
		k='N';
		l='N';
		if(aux->izq!=NULL){
			ii=aux->izq->dato;
			k=aux->izq->c;
		}
		if(aux->der!=NULL){
			dd=aux->der->dato;
			l=aux->der->c;
		}
		fprintf(archivob,"%d %c\t%d-%c\t %d %c\n",aux->dato,aux->c,ii,k,dd,l);
	      
		aux=aux->sig;
	}
	fclose(archivob);
}

void verTabla(){
	Tabla *aux;
	aux=tabla;
	while(aux!=NULL){
	
	printf("%d %c ", aux->frecuencia, aux->n);				
	for(int i=0; i<(aux->bits); i++){
		printf("%c", aux->camino[i]);
	}
	printf("\n");
	aux=aux->sig;
	}
}

void preOrden(Nodo *top){
	FILE * archivob;
    archivob=fopen("ExPreorder.txt", "a");
    if(top != NULL){
        fprintf(archivob, "%d %c\n",top->dato, top->c);
        preOrden (top->izq);
        preOrden(top->der);
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
    int i, aux; 
    char cam[cont];
    FILE * archivob;
    archivob=fopen("ERecorridosHojas.txt", "a");
    char nombre;
    fprintf(archivob, "%d ", valor);
    for (i=0; i<cont; i++) { 
        nombre=camino[0];
		aux=i;
    	fprintf(archivob, "%c", camino[i]); 
    	while(aux>1 && aux<cont){
	    	cam[i-2]=camino[i];
	    	aux=cont;
		}
    }
    aux=aux-2;
	altatabla(aux, nombre, cam, valor);    
    fprintf(archivob, "\n");
	fclose(archivob);   
} 


void altatabla(int DATO, char dd, char camin[], int valor){
    Tabla *nuevo, *aux;
	nuevo=crearNT(DATO, dd, camin, valor);
	if(tabla==NULL){
        tabla=nuevo;        
    }else{
        aux=tabla;
        while(aux->sig!=NULL){
			aux=aux->sig;
        }
        aux->sig=nuevo;
    }
}

Tabla *crearNT(int DATO, char dd, char camin[], int valor){
	Tabla *nuevo;
	nuevo=(Tabla *)malloc(sizeof(Tabla));
	nuevo->bits=DATO;
	nuevo->n=dd;
	nuevo->frecuencia=valor;
    memcpy(nuevo->camino,camin,strlen(camin)+1);
	nuevo->sig = NULL;
		
	return nuevo;
}

int obbites(){
	Tabla *aux;
	aux=tabla;
	int frec, numer, longitud=0;
	while(aux!=NULL){
		frec=aux->frecuencia;
		numer=aux->bits;
		longitud =(longitud + (frec*numer));
		aux=aux->sig;
	}
	
	return longitud;
}
