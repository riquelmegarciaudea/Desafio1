#include "bits.h"
#include "tablero.h"
#include "memoria.h"

const int AGREGAR_FILA = 0;
const int ELIMINAR_FILA = 1;
const int AGREGAR_COLUMNA = 2;
const int ELIMINAR_COLUMNA = 3;

static bool casillaDeOrigen(int operacion, int indice, int filaNueva, int columnaNueva,
                            int &filaVieja, int &columnaVieja)
{
    filaVieja = filaNueva;
    columnaVieja = columnaNueva;

    if (operacion == AGREGAR_FILA)
    {
        if (filaNueva == indice)
        {
            return false;
        }
        if (filaNueva > indice)
        {
            filaVieja = filaNueva - 1;
        }
    }
    else if (operacion == ELIMINAR_FILA)
    {
        if (filaNueva >= indice)
        {
            filaVieja = filaNueva + 1;
        }
    }
    else if (operacion == AGREGAR_COLUMNA)
    {
        if (columnaNueva == indice)
        {
            return false;
        }
        if (columnaNueva > indice)
        {
            columnaVieja = columnaNueva - 1;
        }
    }
    else
    {
        if (columnaNueva >= indice)
        {
            columnaVieja = columnaNueva + 1;
        }
    }
    return true;
}

static void limpiarCola(unsigned char *tablero, int bitsValidos, int bytes)
{
    int completos = bitsValidos >> 3;
    int sobrantes = bitsValidos & 7;
    int desde = completos;

    if (sobrantes != 0)
    {
        tablero[completos] = (unsigned char)(tablero[completos] & ((1 << sobrantes) - 1));
        desde = completos + 1;
    }
    for (int i = desde; i < bytes; i++)
    {
        tablero[i] = 0;
    }
}

static unsigned char *redimensionar(unsigned char *tablero, int columnasViejas,
                                    int filasNuevas, int columnasNuevas,
                                    int operacion, int indice)
{
    int casillasNuevas = filasNuevas * columnasNuevas;
    int necesarios = bytesParaFichas(casillasNuevas);
    int reservados = bytesReservadosTablero();
    bool crece = operacion == AGREGAR_FILA || operacion == AGREGAR_COLUMNA;

    bool reservar = false;
    if (crece)
    {
        reservar = necesarios > reservados;
    }
    else
    {
        reservar = necesarios * 100 < reservados * 65;
    }

    unsigned char *destino = tablero;
    if (reservar)
    {
        destino = new unsigned char[necesarios];
        for (int i = 0; i < necesarios; i++)
        {
            destino[i] = 0;
        }
    }

    bool haciaAtras = crece && !reservar;

    for (int k = 0; k < casillasNuevas; k++)
    {
        int q = haciaAtras ? casillasNuevas - 1 - k : k;
        int filaNueva = q / columnasNuevas;
        int columnaNueva = q % columnasNuevas;
        int filaVieja = 0;
        int columnaVieja = 0;
        unsigned char valor = VACIA;

        if (casillaDeOrigen(operacion, indice, filaNueva, columnaNueva, filaVieja, columnaVieja))
        {
            valor = leerFicha(tablero, filaVieja * columnasViejas + columnaVieja);
        }
        else
        {
            valor = fichaAleatoria();
        }
        escribirFicha(destino, q, valor);
    }

    if (reservar)
    {
        liberarTablero(tablero);
        fijarBytesReservados(necesarios);
    }
    else if (!crece)
    {
        limpiarCola(destino, casillasNuevas * BITS_POR_FICHA, reservados);
    }
    return destino;
}

unsigned char *agregarFila(unsigned char *tablero, int &filas, int columnas, int donde)
{
    if (donde < 0 || donde > filas)
    {
        return tablero;
    }
    unsigned char *nuevo = redimensionar(tablero, columnas, filas + 1, columnas, AGREGAR_FILA, donde);
    filas = filas + 1;
    return nuevo;
}

unsigned char *eliminarFila(unsigned char *tablero, int &filas, int columnas, int cual)
{
    if (cual < 0 || cual >= filas)
    {
        return tablero;
    }
    unsigned char *nuevo = redimensionar(tablero, columnas, filas - 1, columnas, ELIMINAR_FILA, cual);
    filas = filas - 1;
    return nuevo;
}

unsigned char *agregarColumna(unsigned char *tablero, int filas, int &columnas, int donde)
{
    if (donde < 0 || donde > columnas)
    {
        return tablero;
    }
    unsigned char *nuevo = redimensionar(tablero, columnas, filas, columnas + 1, AGREGAR_COLUMNA, donde);
    columnas = columnas + 1;
    return nuevo;
}

unsigned char *eliminarColumna(unsigned char *tablero, int filas, int &columnas, int cual)
{
    if (cual < 0 || cual >= columnas)
    {
        return tablero;
    }
    unsigned char *nuevo = redimensionar(tablero, columnas, filas, columnas - 1, ELIMINAR_COLUMNA, cual);
    columnas = columnas - 1;
    return nuevo;
}
