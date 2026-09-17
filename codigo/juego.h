#ifndef JUEGO_H
#define JUEGO_H

int detectarCombinaciones(const unsigned char *tablero, int filas, int columnas, unsigned char *marcas);
int eliminarMarcadas(unsigned char *tablero, int filas, int columnas, const unsigned char *marcas);
void aplicarGravedad(unsigned char *tablero, int filas, int columnas);
void rellenarVacias(unsigned char *tablero, int filas, int columnas);
int procesarCascadas(unsigned char *tablero, int filas, int columnas);

void eliminarFichaJugador(unsigned char *tablero, int filas, int columnas, int fila, int columna);
void registrarEliminacionEstructural(int fichasQuitadas);
void revisarTablero(unsigned char *tablero, int filas, int columnas);

void reiniciarEstado();
void mostrarEstado(int filas, int columnas);

#endif
