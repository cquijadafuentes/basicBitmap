#include <stdio.h>
#include <stdlib.h>
#include "bitmapG.h"

bitmapG* nuevoBitmap(uint capacidad){
	bitmapG* bits = (bitmapG *) malloc(sizeof(bitmapG));
	if(bits == NULL){
		printf("No se ha podido reservar memoria.\n");
		return NULL;
	}
	uint containers = (capacidad - 1) / W;
	if(containers*W < capacidad){
		containers++;
	}
	bits->bitmap = (ulong *) malloc(sizeof(ulong)*containers);
	if(bits->bitmap == NULL){
		printf("No se ha podido reservar memoria.\n");
		destuyeBitmap(bits);
		return NULL;
	}
	bits->containers = containers;
	uint i;
	for(i=0; i<containers; i++){
		bits->bitmap[i] = 0;
	}
	bits->capacidad = capacidad;
	bits->cantidad = 0;
	return bits;
}

void destuyeBitmap(bitmapG * bits){
	if(bits != NULL){
		if(bits->bitmap != NULL){
			free(bits->bitmap);
		}
		free(bits);
	}
	bits = NULL;
}

int setBitsAtEnd(bitmapG* bits, uint n, ulong contenido){
	// **** VALIDACIONES ****
	// Comprueba que bits existe.
	if(bits == NULL){
		printf("bitmap enviado es puntero a nulo\n");
		return 0;
	}
	// Comprueba que <n> es correcto en base a la capacidad del ulong
	if(n > sizeof(ulong)*8){
		printf("Error! La cantidad de bits indicados no corresponde.\n");
		return 0;
	}
	// Comprueba que hay espacio suficiente en <bits> para almacenar <contenido>
	if(bits->cantidad + n > bits->capacidad){
		printf("No hay capacidad suficiente en el bitmap\n");
		return 0;
	}

	// Limpiar contenido..
	ulong mascara = (1 << n) - 1;
	if(n == W){
		mascara = -1;
	}
	contenido = contenido & mascara;

	// **** OPERACIÓN ****
	uint sobrante = W - (bits->cantidad % W);
	uint posicion = bits->cantidad / W;
	ulong auxiliar;
	if(sobrante >= n){
		// Se inserta en el ulong actual de bitmap
		uint desplazamiento = bits->cantidad % W;
		mascara = contenido << desplazamiento;
		auxiliar = bits->bitmap[posicion] | mascara;
		bits->bitmap[posicion] = auxiliar;
	}else{
		// Se debe dividir antes de insertarlo
		// Operando primera parte
		mascara = contenido << (W - sobrante);
		auxiliar = bits->bitmap[posicion] | mascara;
		bits->bitmap[posicion] = auxiliar;
		// Operando segunda parte
		posicion++;
		mascara = contenido >> sobrante;
		auxiliar = bits->bitmap[posicion] | mascara;
		bits->bitmap[posicion] = auxiliar;
	}
	bits->cantidad += n;

	return 1;
}

ulong getBits(bitmapG* bits, uint pos, uint n){
	// Validaciones
	if(pos + n > bits->cantidad){
		printf("Los bits solicitados salen del rango almacenado.\n");
		return 0;
	}
	if(n > sizeof(ulong)*8){
		printf("No es posible extraer más de %lu bits.\n", sizeof(ulong)*8);
		return 0;
	}

	// Operación
	ulong retorno = 0;
	uint inicio = pos;
	uint fin = pos + n - 1;
	uint cInicio = inicio / W;
	uint cFin = fin / W;
	ulong mascara;
	uint desplazamiento;
	if(cInicio == cFin){
		// Retorno está en un container
		mascara = (1 << n) - 1;
		desplazamiento = pos % W;
		mascara = mascara << desplazamiento;
		retorno = bits->bitmap[cInicio] & mascara;
		retorno = retorno >> desplazamiento;
	}else{
		// Retorno está en dos containers
		ulong auxiliar1, auxiliar2;
		desplazamiento = pos % W;
		mascara = ((1 << n) - 1) << desplazamiento;
		auxiliar1 = mascara & bits->bitmap[cInicio];
		auxiliar1 = auxiliar1 >> desplazamiento;
		
		desplazamiento = (pos + n) % W;
		mascara = (1 << desplazamiento) - 1;
		auxiliar2 = mascara & bits->bitmap[cFin];
		desplazamiento = (W - (pos % W));
		auxiliar2 = auxiliar2 << desplazamiento;
		retorno = auxiliar2 | auxiliar1;
	}

	return retorno;
}