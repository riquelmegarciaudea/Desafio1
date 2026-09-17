#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bits.h"
#include "tablero.h"
#include "memoria.h"
#include "juego.h"

using namespace std;

const int MAXIMO = 30;

int pedirEntero(const char *mensaje, int minimo, int maximo)
{
    int valor = minimo - 1;

    while (valor < minimo || valor > maximo)
    {
        cout << mensaje << " (" << minimo << " a " << maximo << "): ";
        cin >> valor;
        if (!cin)
        {
            if (cin.eof())
            {
                return minimo;
            }
            cin.clear();
            cin.ignore(10000, '\n');
            valor = minimo - 1;
        }
    }
    return valor;
}

void mostrarMenu()
{
    cout << endl;
    cout << "sweet crush" << endl;
    cout << "  1 eliminar ficha" << endl;
    cout << "  2 agregar fila" << endl;
    cout << "  3 eliminar fila" << endl;
    cout << "  4 agregar columna" << endl;
    cout << "  5 eliminar columna" << endl;
    cout << "  6 colocar ficha" << endl;
    cout << "  0 salir" << endl;
}

void mostrarTodo(const unsigned char *tablero, int filas, int columnas)
{
    mostrarBinario(tablero, filas, columnas);
    mostrarFichas(tablero, filas, columnas);
    mostrarEstado(filas, columnas);
}

int main()
{
    srand(time(0));

    int filas = pedirEntero("filas del tablero", 1, MAXIMO);
    int columnas = pedirEntero("columnas del tablero", 1, MAXIMO);

    unsigned char *tablero = crearTablero(filas, columnas);
    llenarAleatorio(tablero, filas, columnas);
    procesarCascadas(tablero, filas, columnas);
    reiniciarEstado();
    mostrarTodo(tablero, filas, columnas);

    int opcion = -1;
    while (opcion != 0)
    {
        mostrarMenu();
        opcion = pedirEntero("opcion", 0, 6);

        switch (opcion)
        {
        case 1:
            if (filas == 0 || columnas == 0)
            {
                cout << "el tablero esta vacio, no hay fichas para eliminar" << endl;
            }
            else
            {
                int fila = pedirEntero("fila", 0, filas - 1);
                int columna = pedirEntero("columna", 0, columnas - 1);
                eliminarFichaJugador(tablero, filas, columnas, fila, columna);
            }
            break;

        case 2:
            if (filas >= MAXIMO)
            {
                cout << "el tablero ya tiene el maximo de filas" << endl;
            }
            else
            {
                int donde = pedirEntero("insertar la fila en la posicion", 0, filas);
                tablero = agregarFila(tablero, filas, columnas, donde);
                revisarTablero(tablero, filas, columnas);
            }
            break;

        case 3:
            if (filas == 0)
            {
                cout << "no hay filas para eliminar" << endl;
            }
            else
            {
                int cual = pedirEntero("fila a eliminar", 0, filas - 1);
                registrarEliminacionEstructural(columnas);
                tablero = eliminarFila(tablero, filas, columnas, cual);
                revisarTablero(tablero, filas, columnas);
            }
            break;

        case 4:
            if (columnas >= MAXIMO)
            {
                cout << "el tablero ya tiene el maximo de columnas" << endl;
            }
            else
            {
                int donde = pedirEntero("insertar la columna en la posicion", 0, columnas);
                tablero = agregarColumna(tablero, filas, columnas, donde);
                revisarTablero(tablero, filas, columnas);
            }
            break;

        case 5:
            if (columnas == 0)
            {
                cout << "no hay columnas para eliminar" << endl;
            }
            else
            {
                int cual = pedirEntero("columna a eliminar", 0, columnas - 1);
                registrarEliminacionEstructural(filas);
                tablero = eliminarColumna(tablero, filas, columnas, cual);
                revisarTablero(tablero, filas, columnas);
            }
            break;

        case 6:
            if (filas == 0 || columnas == 0)
            {
                cout << "el tablero esta vacio" << endl;
            }
            else
            {
                int fila = pedirEntero("fila", 0, filas - 1);
                int columna = pedirEntero("columna", 0, columnas - 1);
                int tipo = pedirEntero("ficha 1=A 2=B 3=C 4=D 5=E 6=F", 1, TIPOS_DE_FICHA);
                ponerFicha(tablero, columnas, fila, columna, (unsigned char)tipo);
            }
            break;

        default:
            break;
        }

        if (opcion != 0)
        {
            mostrarTodo(tablero, filas, columnas);
        }
    }

    liberarTablero(tablero);
    cout << "fin del juego" << endl;
    return 0;
}
