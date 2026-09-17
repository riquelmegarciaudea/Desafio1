#include <iostream>
#include "bits.h"
#include "tablero.h"
#include "juego.h"

using namespace std;

static int eliminaciones = 0;
static int fichasEliminadas = 0;
static int combinaciones = 0;
static int cascadas = 0;
static long puntaje = 0;

int detectarCombinaciones(const unsigned char *tablero, int filas, int columnas, unsigned char *marcas)
{
    int encontradas = 0;

    for (int f = 0; f < filas; f++)
    {
        int c = 0;
        while (c < columnas)
        {
            unsigned char actual = obtenerFicha(tablero, columnas, f, c);
            if (actual == VACIA)
            {
                c = c + 1;
                continue;
            }
            int largo = 1;
            while (c + largo < columnas && obtenerFicha(tablero, columnas, f, c + largo) == actual)
            {
                largo = largo + 1;
            }
            if (largo >= 3)
            {
                for (int i = 0; i < largo; i++)
                {
                    ponerMarca(marcas, f * columnas + c + i);
                }
                encontradas = encontradas + 1;
            }
            c = c + largo;
        }
    }

    for (int c = 0; c < columnas; c++)
    {
        int f = 0;
        while (f < filas)
        {
            unsigned char actual = obtenerFicha(tablero, columnas, f, c);
            if (actual == VACIA)
            {
                f = f + 1;
                continue;
            }
            int largo = 1;
            while (f + largo < filas && obtenerFicha(tablero, columnas, f + largo, c) == actual)
            {
                largo = largo + 1;
            }
            if (largo >= 3)
            {
                for (int i = 0; i < largo; i++)
                {
                    ponerMarca(marcas, (f + i) * columnas + c);
                }
                encontradas = encontradas + 1;
            }
            f = f + largo;
        }
    }

    return encontradas;
}

int eliminarMarcadas(unsigned char *tablero, int filas, int columnas, const unsigned char *marcas)
{
    int casillas = filas * columnas;
    int eliminadas = 0;

    for (int p = 0; p < casillas; p++)
    {
        if (leerMarca(marcas, p))
        {
            escribirFicha(tablero, p, VACIA);
            eliminadas = eliminadas + 1;
        }
    }
    return eliminadas;
}

void aplicarGravedad(unsigned char *tablero, int filas, int columnas)
{
    for (int c = 0; c < columnas; c++)
    {
        int destino = filas - 1;
        for (int origen = filas - 1; origen >= 0; origen--)
        {
            unsigned char ficha = obtenerFicha(tablero, columnas, origen, c);
            if (ficha != VACIA)
            {
                if (origen != destino)
                {
                    ponerFicha(tablero, columnas, destino, c, ficha);
                    ponerFicha(tablero, columnas, origen, c, VACIA);
                }
                destino = destino - 1;
            }
        }
    }
}

void rellenarVacias(unsigned char *tablero, int filas, int columnas)
{
    int casillas = filas * columnas;

    for (int p = 0; p < casillas; p++)
    {
        if (leerFicha(tablero, p) == VACIA)
        {
            escribirFicha(tablero, p, fichaAleatoria());
        }
    }
}

int procesarCascadas(unsigned char *tablero, int filas, int columnas)
{
    int bytes = bytesParaMarcas(filas * columnas);
    unsigned char *marcas = new unsigned char[bytes];
    int vueltas = 0;
    bool seguir = true;

    while (seguir)
    {
        limpiarMarcas(marcas, bytes);
        int encontradas = detectarCombinaciones(tablero, filas, columnas, marcas);

        if (encontradas == 0)
        {
            seguir = false;
        }
        else
        {
            vueltas = vueltas + 1;
            int quitadas = eliminarMarcadas(tablero, filas, columnas, marcas);
            combinaciones = combinaciones + encontradas;
            fichasEliminadas = fichasEliminadas + quitadas;
            puntaje = puntaje + 10L * quitadas * vueltas;
            aplicarGravedad(tablero, filas, columnas);
            rellenarVacias(tablero, filas, columnas);
        }
    }

    delete[] marcas;
    return vueltas;
}

void eliminarFichaJugador(unsigned char *tablero, int filas, int columnas, int fila, int columna)
{
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
    {
        return;
    }

    ponerFicha(tablero, columnas, fila, columna, VACIA);
    eliminaciones = eliminaciones + 1;
    fichasEliminadas = fichasEliminadas + 1;

    aplicarGravedad(tablero, filas, columnas);
    rellenarVacias(tablero, filas, columnas);
    cascadas = procesarCascadas(tablero, filas, columnas);
}

void registrarEliminacionEstructural(int fichasQuitadas)
{
    eliminaciones = eliminaciones + 1;
    fichasEliminadas = fichasEliminadas + fichasQuitadas;
}

void revisarTablero(unsigned char *tablero, int filas, int columnas)
{
    cascadas = procesarCascadas(tablero, filas, columnas);
}

void reiniciarEstado()
{
    eliminaciones = 0;
    fichasEliminadas = 0;
    combinaciones = 0;
    cascadas = 0;
    puntaje = 0;
}

void mostrarEstado(int filas, int columnas)
{
    cout << endl << "estado del juego" << endl;
    cout << "  dimensiones actuales = " << filas << " x " << columnas << endl;
    cout << "  memoria reservada =" << bytesReservadosTablero() << " bytes" << endl;
    cout << "  eliminaciones del usuario = " << eliminaciones << endl;
    cout << "  fichas eliminadas en total = " << fichasEliminadas << endl;
    cout << "  combinaciones detectadas = " << combinaciones << endl;
    cout << "  cascadas de esta jugada = " << cascadas << endl;
    cout << "  puntaje = " << puntaje << endl;
}
