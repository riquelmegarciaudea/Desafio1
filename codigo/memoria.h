#ifndef MEMORIA_H
#define MEMORIA_H

unsigned char *agregarFila(unsigned char *tablero, int &filas, int columnas, int donde);
unsigned char *eliminarFila(unsigned char *tablero, int &filas, int columnas, int cual);
unsigned char *agregarColumna(unsigned char *tablero, int filas, int &columnas, int donde);
unsigned char *eliminarColumna(unsigned char *tablero, int filas, int &columnas, int cual);

#endif
