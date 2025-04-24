#include <iostream>
#include <fstream>
#include <string>
#include "GSenku.hpp"
using namespace std;




int main(int argc, char* argv[]){
    tpTablero tablero;
    tpMovimientosValidos movimientos;
    string ficheroTablero = argv[1];
    string ficheroMovimientos = argv[2];


    if(inicializarTablero(ficheroTablero, tablero)){
        if(inicializarMovimientosValidos(ficheroMovimientos, movimientos)){


        }
    }else{
        cerr<<"Error";
    }
}
