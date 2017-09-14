/*numero de bits del entero de la maquina*/
#define W 64

#ifndef uint
#define uint unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif

typedef struct GBITMAP{
	ulong * bitmap;		// Arreglos de long para contener el bitmap
	uint capacidad;		// Posibles elementos a almacenar en el bitmap
	uint cantidad;		// Cantidad de bits insertados en el bitmap
	uint containers;
}bitmapG;

bitmapG* nuevoBitmap(uint capacidad);
// Crea la estructura con suficientes capacidad para almacenar los bits requeridos.

void destuyeBitmap(bitmapG * bits);
// Libera la memoria de la estructura, destruyéndo todos sus punteros.

int setBitsAtEnd(bitmapG* bits, uint n, ulong contenido);
// Inserta al final de <bits> los <n> bits finales de <contenido>

int setBitsInPos(bitmapG* bits, uint pos, uint n, ulong contenido);
// Inserta en la posición <pos> del bitmap <bits> los <n> bits desde <contenido>

ulong getBits(bitmapG* bits, uint pos, uint n);
// Retorna los <n> bits almacenados en <bits> desde la posición <pos> en un long sin signo.