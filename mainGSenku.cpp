#include <iostream>
#include <fstream>
#include <string>
#include "GSenku.hpp"
using namespace std;

int main(int argc, char* argv[]){
    tpTablero tablero;
    tpMovimientosValidos movsValidos;
    tpListaMovimientos solucion;

    string ficheroTablero = argv[1];
    string ficheroMovimientos = argv[2], ficheroSalida;
    double retardo = atoi(argv[3]);
    if (argc == 5){ficheroSalida = argv[4];}
    if (argc<4||argc>5){cerr<<"Error en la entrada";}

    if(inicializarTablero(ficheroTablero, tablero)){
        if(inicializarMovimientosValidos(ficheroMovimientos, movsValidos)){
            if(buscaSolucion(tablero, movsValidos, solucion,retardo)==1){
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
