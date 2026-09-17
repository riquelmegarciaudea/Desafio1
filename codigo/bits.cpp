#include "bits.h"

int bytesParaFichas(int casillas)
{
    return (casillas * BITS_POR_FICHA + 7) >> 3;
}

int bytesParaMarcas(int casillas)
{
    return (casillas + 7) >> 3;
}

unsigned char leerFicha(const unsigned char *trama, int posicion)
{
    int bit = posicion * BITS_POR_FICHA;
    int indice = bit >> 3;
    int desplazamiento = bit & 7;

    int valor = (trama[indice] >> desplazamiento) & 7;
    if (desplazamiento > 5)
    {
        valor = valor | ((trama[indice + 1] << (8 - desplazamiento)) & 7);
    }
    return (unsigned char)valor;
}

void escribirFicha(unsigned char *trama, int posicion, unsigned char valor)
{
    int bit = posicion * BITS_POR_FICHA;
    int indice = bit >> 3;
    int desplazamiento = bit & 7;
    int limpio = valor & 7;

    trama[indice] = (unsigned char)((trama[indice] & ~(7 << desplazamiento)) | (limpio << desplazamiento));
    if (desplazamiento > 5)
    {
        int arriba = 8 - desplazamiento;
        trama[indice + 1] = (unsigned char)((trama[indice + 1] & ~(7 >> arriba)) | (limpio >> arriba));
    }
}

bool leerMarca(const unsigned char *marcas, int posicion)
{
    return ((marcas[posicion >> 3] >> (posicion & 7)) & 1) == 1;
}

void ponerMarca(unsigned char *marcas, int posicion)
{
    marcas[posicion >> 3] = (unsigned char)(marcas[posicion >> 3] | (1 << (posicion & 7)));
}

void limpiarMarcas(unsigned char *marcas, int bytes)
{
    for (int i = 0; i < bytes; i++)
    {
        marcas[i] = 0;
    }
}
