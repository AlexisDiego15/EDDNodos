#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct _Nodo
{
float dato;
struct _Nodo *sig;
}Nodo;


Nodo *crearnodo(float DATO){
	Nodo *nuevo;
	nuevo=(Nodo *)malloc(sizeof(Nodo));
	nuevo->dato=DATO;
	nuevo->sig=NULL;
	    
	return nuevo;
}

Nodo *altapila(Nodo *top, float DATO){
	Nodo *nuevo;
    nuevo=crearnodo(DATO);
	if(top!=NULL){
		nuevo->sig=top;
	}
	
    return nuevo;
}

Nodo *operacionpila(Nodo *cima, char sig){
	Nodo * destruir;
	destruir = cima;
	float aux = destruir->dato;
	cima=cima->sig;
	free(destruir);
	
	destruir = cima;
	float auxb = destruir->dato;
	cima=cima->sig;
	free(destruir);
	float res;		
	if(sig=='+'){
		res = (float)aux + auxb;
	}else if(sig=='-'){
		res = (float)auxb - aux;
	}else if(sig=='*'){
		res = (float)aux * auxb;
	}else if(sig=='/'){
		res = (float)auxb / aux;
	}else if(sig=='^'){
		res=(float)pow(auxb, aux);
	}
	//printf("%f ", res);
	cima=altapila(cima, res);
	
	return cima;
}

void verpila(Nodo *cima){
	FILE * archivob;
    archivob=fopen("resultados.txt", "a");
	Nodo *aux;
	aux=cima;
	while(aux!=NULL){
	    fprintf(archivob,"%f\n",aux->dato);
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
	char c;
	int n;
    Nodo *top=NULL;
    FILE * archivo;
    archivo=fopen("practica.txt", "r");
    
    while((c=getc(archivo))!=EOF){
    	if(c!='\n'){
    		if(isdigit(c)!=0){
    			n=(float)(c-48);
				top = altapila(top,n);	
			}else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'){
				top=operacionpila(top, c);
			}
		}else{
			verpila(top);
			top=bajapila(top);	
			printf("\n");
		}
	}
	if((c=getc(archivo))==EOF){
		verpila(top);
		top=bajapila(top);	
	}
	fclose(archivo);       
    return 0;
}

