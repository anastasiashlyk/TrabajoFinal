#include <iostream>
#include <fstream>
#include <string>
#include "GSenku.hpp"
#include <time.h>
using namespace std;

int main(int argc, char* argv[]){
    tpTablero tablero;
    tpMovimientosValidos movsValidos;
    tpListaMovimientos solucion;

    string ficheroTablero = argv[1];
    string ficheroMovimientos = argv[2], ficheroSalida;
    double retardo = atoi(argv[3]);
    if (argc == 5){
        ficheroSalida = argv[4];
    }

    if (argc < 4||argc > 5){
        cerr<<"Entrada invalida";
    }
    if(inicializarTablero(ficheroTablero, tablero)){
        if(inicializarMovimientosValidos(ficheroMovimientos, movsValidos)){
            if(cout << buscaSolucion(tablero, movsValidos, solucion, retardo)){
                cout << "eres reina!!!!!!!!!???"<< endl;                
                cout << endl;
            }else{
                cout << "eres peon!!!!!!!!!"<< endl;
            }
            escribeListaMovimientos("solucion.txt", solucion);
        }
    }else{
        cerr<<"Error en mostrar el tablero";
    }
}
