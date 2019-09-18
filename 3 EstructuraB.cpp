#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct tienda{
	int codigo;
	int vendidos;	
	float costo;
	float venta;
	float ganancia;	
};

typedef struct tienda Tiendita;

int main(){
	Tiendita producto [10];
	int total=0;
	do{
		printf("Producto %d:\n", (total+1));

		printf("Ingresa el codigo del producto: ");
		scanf("%d", &producto[total].codigo);
	
		printf("Ingresa el numero de productos vendidos en el mes: ");
		scanf("%d", &producto[total].vendidos);
		
		printf("Ingresa el costo del producto: ");
		scanf("%f", &producto[total].costo);
				
		printf("Ingresa el costo de venta del producto: ");
		scanf("%f", &producto[total].venta);
		
		producto[total].ganancia=(float)producto[total].vendidos * (producto[total].venta - producto[total].costo);
						
		total++;
			
		
	}while(total<=9);
	
	float ganancias=0;
	
	for(int i=0; i<10; i++){
		ganancias = ganancias +(producto[i].ganancia);
	}	
	printf("\nGanancia total del mes: %f", ganancias);
	
	return 0;
}		
