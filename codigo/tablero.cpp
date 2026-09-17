#include <iostream>
#include <cstdlib>
#include "bits.h"
#include "tablero.h"

using namespace std;

static int bytesReservados = 0;

static const char SIMBOLOS[8] = {'.', 'A', 'B', 'C', 'D', 'E', 'F', '?'};

unsigned char *crearTablero(int filas, int columnas)
{
    int bytes = bytesParaFichas(filas * columnas);
    unsigned char *tablero = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++)
    {
        tablero[i] = 0;
    }
    bytesReservados = bytes;
    return tablero;
}

void liberarTablero(unsigned char *tablero)
{
    delete[] tablero;
}

unsigned char fichaAleatoria()
{
    return (unsigned char)(rand() % TIPOS_DE_FICHA + 1);
}

void llenarAleatorio(unsigned char *tablero, int filas, int columnas)
{
    int casillas = filas * columnas;
    for (int p = 0; p < casillas; p++)
    {
        escribirFicha(tablero, p, fichaAleatoria());
    }
}

unsigned char obtenerFicha(const unsigned char *tablero, int columnas, int fila, int columna)
{
    return leerFicha(tablero, fila * columnas + columna);
}

void ponerFicha(unsigned char *tablero, int columnas, int fila, int columna, unsigned char valor)
{
    escribirFicha(tablero, fila * columnas + columna, valor);
}

void mostrarBinario(const unsigned char *tablero, int filas, int columnas)
{
    int bitsValidos = filas * columnas * BITS_POR_FICHA;

    cout << endl << "tablero en binario (" << bytesReservados << " bytes reservados, "
         << bitsValidos << " bits en uso)" << endl;

    for (int i = 0; i < bytesReservados; i++)
    {
        if (i % 6 == 0)
        {
            if (i > 0)
            {
                cout << endl;
            }
            cout << "  byte ";
            if (i < 10)
            {
                cout << ' ';
            }
            cout << i << ":  ";
        }
        for (int b = 7; b >= 0; b--)
        {
            if (i * 8 + b >= bitsValidos)
            {
                cout << '.';
            }
            else
            {
                cout << ((tablero[i] >> b) & 1);
            }
        }
        cout << ' ';
    }
    cout << endl;
}

void mostrarFichas(const unsigned char *tablero, int filas, int columnas)
{
    cout << endl << "tablero en fichas (" << filas << " x " << columnas << ")" << endl;

    if (filas == 0 || columnas == 0)
    {
        cout << "  el tablero esta vacio" << endl;
        return;
    }

    cout << "     ";
    for (int c = 0; c < columnas; c++)
    {
        if (c < 10)
        {
            cout << ' ';
        }
        cout << c << ' ';
    }
    cout << endl;

    for (int f = 0; f < filas; f++)
    {
        cout << "  ";
        if (f < 10)
        {
            cout << ' ';
        }
        cout << f << ' ';
        for (int c = 0; c < columnas; c++)
        {
            cout << ' ' << SIMBOLOS[obtenerFicha(tablero, columnas, f, c)] << ' ';
        }
        cout << endl;
    }
}

int bytesReservadosTablero()
{
    return bytesReservados;
}

void fijarBytesReservados(int bytes)
{
    bytesReservados = bytes;
}
