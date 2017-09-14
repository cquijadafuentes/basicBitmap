#include <stdio.h>
#include "bitmapG.h"

void mostrarBitmap(bitmapG* bits){
	uint i;
	printf("\t\t*** BITMAP (%u/%u) ***\n", bits->cantidad, bits->capacidad);
	for(i=0; i<bits->containers; i++){
		printf("\t\tbitmap[%u] = %lu\n", i, bits->bitmap[i]);
	}
}

int main(int argc, char *argv[]){
	uint cap, cant, pos, opc = 0;
	ulong cont, res;

	printf("Ingrese la capacidad del bitmap: \n");
	scanf("%u", &cap);
	bitmapG* bits = nuevoBitmap(cap);
	mostrarBitmap(bits);
	
	do{
		printf("***** MENU *****\n");
		printf("0 - Salir\n");
		printf("1 - Insertar\n");
		printf("2 - Consultar\n");
		printf("\nOpción... ");
		scanf("%u", &opc);
		switch(opc){
			case 0:
				printf("Fin del programa...\n");
				break;
			case 1:
				printf("Cantidad de bits a insertar: ");
				scanf("%u", &cant);
				printf("Contenido a insertar: ");
				scanf("%lu", &cont);
				printf("Insertando %u bits de %lu\n", cant, cont);
				if(setBitsAtEnd(bits, cant, cont)){
					printf("Inserción exitosa.\n");
				}else{
					printf("Error, no se han insertado los datos.\n");
				}
				mostrarBitmap(bits);
				break;
			case 2:
				printf("Posición desde la que se desea consultar: ");
				scanf("%u", &pos);
				printf("Cantidad de bits a consultar: ");
				scanf("%u", &cant);
				res = getBits(bits, pos, cant);
				printf("Retorno: %lu\n", res);
				break;
			default:
				printf("Opción no válida\n");
				break;
		}
	}while(opc != 0);

	destuyeBitmap(bits);
	return 0;
}