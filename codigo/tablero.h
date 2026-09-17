#ifndef TABLERO_H
#define TABLERO_H

const unsigned char VACIA = 0;
const int TIPOS_DE_FICHA = 6;

unsigned char *crearTablero(int filas, int columnas);
void liberarTablero(unsigned char *tablero);
unsigned char fichaAleatoria();
void llenarAleatorio(unsigned char *tablero, int filas, int columnas);

unsigned char obtenerFicha(const unsigned char *tablero, int columnas, int fila, int columna);
void ponerFicha(unsigned char *tablero, int columnas, int fila, int columna, unsigned char valor);

void mostrarBinario(const unsigned char *tablero, int filas, int columnas);
void mostrarFichas(const unsigned char *tablero, int filas, int columnas);

int bytesReservadosTablero();
void fijarBytesReservados(int bytes);

#endif
