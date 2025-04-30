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

    if(inicializarTablero(ficheroTablero, tablero)){
        if(inicializarMovimientosValidos(ficheroMovimientos, movsValidos)){
            if(buscaSolucion(tablero, movsValidos, solucion)==1){
                cout << "eres reina!!!!!!!!!???"<< endl;                
                cout << endl;
                mostrarTablero(tablero);
            }else{
                cout << "eres peon!!!!!!!!!"<< endl;
            }
            escribeListaMovimientos("solucion.txt", solucion);
        }
    }else{
        cerr<<"Error en mostrar el tablero";
    }
}
