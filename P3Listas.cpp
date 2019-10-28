#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct _Nodo{
	int dato;
	int fecha[3];
	char descripcion[100];
	struct _Nodo *sig;
}Evento;

Evento *crearNodo(int id,  int dia, int mes, int anio, char des[]){
	Evento *nuevo;
    nuevo=(Evento *)malloc(sizeof(Evento));
    nuevo->dato=id;
    nuevo->fecha[0]=dia;
    nuevo->fecha[1]=mes;
    nuevo->fecha[2]=anio;
    memcpy(nuevo->descripcion,des,strlen(des)+1);
    nuevo->sig=NULL;
    return nuevo;
}


Evento *altaNodo(Evento *top, int id, int dia, int mes, int anio, char descripcion[]){
	Evento *nuevo, *aux;
    nuevo=crearNodo(id, dia, mes, anio, descripcion);
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

int contar(Evento *cima){
    Evento * aux;
    aux = cima;
    int a=0;
    while(aux!=NULL){
        a++;
        aux=aux->sig;
    }
    return a;
}

void verListas(Evento *cima){
	int valor= contar(cima);
    Evento *aux;
    aux=cima;
    int id=1;

	if(valor==0){
		printf("\nNo hay eventos guardados\n");
	}else{
    	while(aux!=NULL){
		     //printf("\nId: %d\tFecha: %d/%d/%d\tEvento: %s",id,aux->fecha[0],aux->fecha[1],aux->fecha[2],aux->descripcion);
            printf("\nId: %d\tFecha: %d/%d/%d\tCapacidad: %d\tEvento: %s",id,aux->fecha[0],aux->fecha[1],aux->fecha[2],aux->dato,aux->descripcion);
		    aux=aux->sig;
		    id++;
		}
	}
}

int disponibilidad(Evento *top, int dia, int mes, int an){
	Evento *aux;
	aux=top;
	int id=2;
	if(top==NULL){
        id=1;
    }else{
   		while(aux!= NULL){
			if(aux->fecha[0]==dia && aux->fecha[1]==mes && aux->fecha[2]==an){
				id=0;
			}
			aux=aux->sig;
		}
		if(id>1){
			aux=top;
			while(aux->sig!=NULL){
				aux=aux->sig;
				id=aux->dato;
				id++;
			}
		}
	}
	return id;
}

Evento *bajaNodo(Evento *top, int pos){
	Evento *aux, *borrar;
	int cont=1, i;
	aux=top;
	if(pos==1){
		if(top!= NULL){
            top=top->sig;
            free(aux);
        }
        return top;
    }else if(pos>1){
		for(i=1; i<pos-1; i++){
			if(aux->sig==NULL){
				printf("Posicion equivocada");
			}
			aux=aux->sig;
		}
		borrar=aux->sig;
		aux->sig=borrar->sig;
		return top;
	}
}

Evento *bajaNodofe(Evento *top, int dia, int mes, int an){
	Evento *aux;
	aux=top;
	int pos=1;
   		while(aux!= NULL){
			if(aux->fecha[0]==dia && aux->fecha[1]==mes && aux->fecha[2]==an){
                top = bajaNodo(top, pos);
			}else{
                pos++;
			}
			aux=aux->sig;
		}

		return top;
}


void guardareventos(Evento *cima){
	FILE * archivo;
    archivo=fopen("eventos.bin", "wb");

    Evento *aux, *even;
	aux=cima;
	even=NULL;

    if(archivo==NULL){
    	printf("ERROR");
	}else{
		while(aux!=NULL){
			even = aux->sig;
			aux->sig=NULL;
			fseek(archivo,0,SEEK_END);
        	fwrite(aux, sizeof(Evento), 1, archivo);


        	aux->sig=even;
        	even=NULL;
        	aux=aux->sig;
		}
	}

    fclose(archivo);
    archivo=NULL;
}

Evento *leerarchivo(Evento *cima, FILE *archivo){
	size_t valor;
	Evento *aux, *nuevo;
	if(cima == NULL){
		cima = (Evento *)malloc(sizeof(Evento));
		valor=fread(cima, sizeof(Evento),1,archivo);
		cima->sig=NULL;
	}else{
		aux=cima;
		nuevo= (Evento *)malloc(sizeof(Evento));
		while(aux->sig!=NULL){
			aux=aux->sig;
		}
		valor=fread(nuevo, sizeof(Evento),1,archivo);
		aux->sig=nuevo;
		nuevo->sig=NULL;

	}
	return cima;
}

Evento *cargareventos(Evento *cima){
	FILE * archivo;
	int i;
    archivo=fopen("eventos.bin", "rb");
    if(archivo==NULL){
	}else{
			cima=NULL;
			fseek(archivo,0,SEEK_END);
        	long fileSize=ftell(archivo);
        	rewind(archivo);
        	int eventos = (int)(fileSize/(sizeof(Evento)));

        	for(i=0; i<eventos;i++){
        		fseek(archivo,(sizeof(Evento)*i),SEEK_SET);
        		cima=leerarchivo(cima, archivo);
			}

	}
	return cima;
}

int fechavalida(int d, int m, int a){
	int valido=0;
	if(m>0 && m<13){
		if(m==1 || m==3 || m==5 || m==7 || m==8||m==10||m==12){
			if(d>0 && d<32 ){
				valido=1;
			}
		}else if(m==4 || m==6 || m==9 || m==11){
			if(d>0 && d<31 ){
				valido=1;
			}
		}else if(m==2){
			if(d>0 && d<29){
				valido=1;
			}
			if(a%4==0 && d>0 && d<30){
				valido=1;
			}
		}
	}
	return valido;
}

int main(){
	int opc, eventos;
	int dia, mes, anio, id, cap, borr;
	int f_correcta;
	char descripcion[100];
	Evento*top;
	top=NULL;

	top=cargareventos(top);

	do{
		printf("\nIngrese la opcion\n1.-Alta de evento\n2.-Baja de evento\n3.-Ver eventos\n4.-Ver cantidad de eventos\n5.-Salir\n");
		scanf("%d",&opc);
		system("cls");
		switch(opc){

			case 1:
	 			printf("\n---ALTA EVENTO---");
	 			printf("\nIngrese el dia del evento (DD) \n");
	 			scanf("%d", &dia);
	 			printf("Ingrese el mes del evento (MM) \n");
	 			scanf("%d", &mes);
	 			printf("Ingrese el año del evento (AAAA) \n");
	 			scanf("%d", &anio);
	 			printf("Ingrese la capacidad del evento (Numero de personas)\n");
	 			scanf("%d", &cap);
	 			f_correcta=fechavalida(dia, mes, anio);
	 			if(f_correcta>0){
	 				id=disponibilidad(top, dia, mes, anio);
					if(id>0){
						fflush(stdin);
		   				printf("\nEscribe la descripcion del evento: \n");
		   				gets(descripcion);

						top = altaNodo(top, cap, dia, mes, anio, descripcion);
						//top = altaNodo(top, id, dia, mes, anio, descripcion);
					}else{
						printf("\nFecha ocupada");
					}
				}else{
					printf("\nEscribe una fecha valida\n");
				}
			break;

			case 2:
				printf("\n---BAJA EVENTO---");
				verListas(top);

				printf("\nIngresa la opcion para eliminar\n1.Por ID\n2.Por fecha\n");
                scanf("%d",&borr);
				if(borr==1){
                    printf("\nIngresa el ID del evento que desea eliminar\n");
                    scanf("%d",&id);
                    eventos = contar(top);
                    if( id>0 && id<=eventos){
                        top = bajaNodo(top, id);
                    }else{
                        printf("\nPosicion invalida");
                    }
				}else if(borr==2){
                    printf("\nIngrese el dia del evento (DD) \n");
                    scanf("%d", &dia);
                    printf("Ingrese el mes del evento (MM) \n");
                    scanf("%d", &mes);
                    printf("Ingrese el año del evento (AAAA) \n");
                    scanf("%d", &anio);
                    top = bajaNodofe(top, dia, mes,anio);
				}/*else if(borr=3){
                    fflush(stdin);
		   			printf("\nEscribe la descripcion del evento: \n");
		   			gets(descripcion);

                    top = bajaNododes(top, descripcion);

				}*/
			break;

			case 3:
				printf("---EVENTOS---");
				verListas(top);
			break;

			case 4:
				eventos = contar(top);
				printf("\nEl numero de eventos es: %d\n", eventos);
			break;
		}
	}while(opc!=5);
	guardareventos(top);
	return 0;
}
