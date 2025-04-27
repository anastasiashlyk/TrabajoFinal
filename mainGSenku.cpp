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
    if (argc == 5){
        ficheroSalida = argv[4];
    }


    if(inicializarTablero(ficheroTablero, tablero)){
        cout << tablero.nfils << ' ' << tablero.ncols << endl;

        for(int i = 0; i < tablero.nfils; i++){
            for(int j =0; j< tablero.ncols; j++){
                cout << tablero.matriz[i][j] << ' ';
            }
            cout << endl;
        }
        cout << ficheroMovimientos << endl;


        if(inicializarMovimientosValidos(ficheroMovimientos, movsValidos)){
            for(int i =0; i < 8; i++){
                if(movsValidos.validos[i]){
                    cout << "1" << ' ';
                }else{
                    cout << "0";
                }
                
            }
            cout << endl;
            mostrarTablero(tablero);

            if(buscaSolucion(tablero, movsValidos, solucion)==1){
                cout << "eres reina!!!!!!!!!"<< endl;

                escribeListaMovimientos("solucion.txt", solucion);


            }
        }
        
    }else{
        cerr<<"Error en mostrar el tablero";
    }
}
