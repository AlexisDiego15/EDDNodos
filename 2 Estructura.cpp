#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct empleados{	
char nombre[50];	
char apellido[50];	
char sexo[50];	
float sueldo; };

typedef struct empleados Empleado;

int main(){
	Empleado datos[100];
	int total=0;
	char resp, b[10];
	do{
		printf("Empleado %d\n", (total+1));
		
		printf("Nombre del empleado: ");
		gets(datos[total].nombre);
	
		printf("Apellido del empleado: ");
		gets(datos[total].apellido);	
		
		printf("Sexo del empleado: ");
		gets(datos[total].sexo);
		
		printf("Sueldo del empleado: ");
		gets(b);
		
		datos[total].sueldo = atof(b);
		
		printf("\nDesea ingresar otro empleado? (S/N)");
		scanf("%c%*c", &resp);
		
		resp=toupper(resp);
		if(resp=='S'){
			total++;
			continue;
		}
		
	}while(resp=='S');
	
	float menor=datos[0].sueldo;
	float mayor=datos[0].sueldo;
	int auxmen, auxmay;
	
	for(int i=0;i<total;i++)
    {
    	if(menor>datos[i].sueldo){
    		menor=datos[i].sueldo;
    		auxmen=i;
		}
		if(mayor<datos[i].sueldo){
    		mayor=datos[i].sueldo;
    		auxmay=i;
		}	
    }
    printf("El de mayor sueldo es: %s ", datos[auxmay].nombre);
    printf("%s que gana %f", datos[auxmay].apellido, mayor);
    
    printf("\nEl de menor sueldo es: %s ", datos[auxmen].nombre);
    printf("%s que gana %f", datos[auxmen].apellido, menor);
    
	return 0;
}
