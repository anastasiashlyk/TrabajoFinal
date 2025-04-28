#include <iostream>
#include <fstream>
#include <string>
#include "GSenku.hpp"
#include <thread>
#include <chrono>
using namespace std;




int main(int argc, char* argv[]){
    tpTablero tablero;
    tpMovimientosValidos movsValidos;
    tpListaMovimientos solucion;

    string ficheroTablero = argv[1];
    string ficheroMovimientos = argv[2], ficheroSalida;
    int retardo = atoi(argv[3]);
    if (argc == 5){
        ficheroSalida = argv[4];
    }else{
        ficheroSalida = "solucion.txt";
    }


    if(inicializarTablero(ficheroTablero, tablero)){
        cout << tablero.nfils << ' ' << tablero.ncols << endl;

        for(int i = 0; i < tablero.nfils; i++){
            for(int j =0; j< tablero.ncols; j++){
                cout << tablero.matriz[i][j] << ' ';
            }
            cout << endl;
        }
        cout << ficheroMovimientos << endl << "retardo: "<< retardo << endl;


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

            if(buscaSolucion(tablero, movsValidos, solucion, retardo)==1){
                cout << "eres reina!!!!!!!!!"<< endl;

                
                cout << endl;
                mostrarTablero(tablero);


            }
            escribeListaMovimientos(ficheroSalida, solucion);
        }
        
    }else{
        cerr<<"Error en mostrar el tablero";
    }
}
