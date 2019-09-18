#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct alumno{	
	char nombre[50];	char apellido[50];	char escuela[50];	char boleta[10];	};

int main(){
	FILE* puntero_archivo;
	puntero_archivo =  fopen("struct.dat", "w");
	struct alumno datos;

		
		printf("Nombre del alumno: ");
		gets(datos.nombre);
	
		printf("Apellido del alumno: ");
		gets(datos.apellido);	
		
		printf("Escuela del alumno: ");
		gets(datos.escuela);
		
		printf("Boleta del alumno: ");
		gets(datos.boleta);
				
    	fwrite(&datos, sizeof(struct alumno), 1, puntero_archivo);
        
        fclose(puntero_archivo);
        
        FILE*mostrar;
        mostrar=fopen ("struct.dat", "r"); 
        while(fread(&datos, sizeof(struct alumno), 1, mostrar)) {
			printf ("Nombre %s %s\nEscuela %s\nBoleta %s\n", datos.nombre, datos.apellido, datos.escuela, datos.boleta); 
		}        
    	fclose(mostrar);
	return 0;
}
