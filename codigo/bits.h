#ifndef BITS_H
#define BITS_H

const int BITS_POR_FICHA = 3;

int bytesParaFichas(int casillas);
int bytesParaMarcas(int casillas);

unsigned char leerFicha(const unsigned char *trama, int posicion);
void escribirFicha(unsigned char *trama, int posicion, unsigned char valor);

bool leerMarca(const unsigned char *marcas, int posicion);
void ponerMarca(unsigned char *marcas, int posicion);
void limpiarMarcas(unsigned char *marcas, int bytes);

#endif
