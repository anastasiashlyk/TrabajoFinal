#include <iostream>
#include <fstream>
#include "GSenku.hpp"
using namespace std;

// FUNCIONES / PROCEDIMIENTOS 

// Pre: true
// Post: lee la configuración y el estado del tablero del fichero de configuración que se le pasa como argumento
//      inicializando tablero y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarTablero(const string nombreFichero, tpTablero &tablero){
  ifstream f;
  f.open(nombreFichero);
  if(f.is_open()){
    f >> tablero.nfils;
    f >> tablero.ncols;
    if(tablero.nfils<=0||tablero.ncols<=0||tablero.nfils>MAXDIM||tablero.ncols>MAXDIM){
      cerr << "Entradas de dimensiones del ficheroTablero invalidas" << nombreFichero << endl;
    return false;
    }
    
    getline(f)
    char celda;
    int k=0;
  for (int i = 0; i < tablero.nfils; ++i) {
        for (int j = 0; j < tablero.ncols; ++j) {
          (f>>celda)//comprobar que todas las entradas son validas hasta que se cargue todo el tablero
          switch (celda) {
              case '-':
                tablero.matriz[i][j] = NO_USADA;
                break;
              case 'o':
                tablero.matriz[i][j] = OCUPADA;
                break;
              case 'x':
                tablero.matriz[i][j] = VACIA;
                break;
              default:
                cerr << "Entrada de datos del ficheroTablero invalido " << celda << endl;
                return false;
          }
      }
      return true;
}
  }
cerr << "Error al abrir el fichero" << nombreFichero << endl;
return false;
}

// Pre: true 
// Post: lee los movimientos válidos del fichero que se le pasa como argumento 
//      inicializando la estructura y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarMovimientosValidos(const string nombreFichero, tpMovimientosValidos &movimientos){
    ifstream f(nombreFichero);
    if(f.is_open()){
        char c;
        while(f>>c){
            for(int i=0; i <= 8; i++){
                if (c == '-'){
                    movimientos.validos[i]=false;
                }
                if(c == '+'){
                    movimientos.validos[i]=true;
                }
            }
        }
        return true;
    }else{
        cerr << "No se ha podido abrir el archivo.";
        return false;
    }


}

// Pre: tablero contiene el estado actual de la ejecución de la búsqueda de la solución
// Post: Se ha mostrado el tablero por pantalla
void mostrarTablero(const tpTablero & tablero){
    for(int i = 0; i< tablero.nfils; i++){
        for(int j = 0; j < tablero.ncols; j++){
            if(tablero.matriz[i][j] == 0){
                cout << "  ";
            }
            if(tablero.matriz[i][j] == 1){
                cout <<"\033[42m" <<" " << "\033[0m" << " ";
            }
            if(tablero.matriz[i][j] == 2){
                cout << "\033[41m" <<" " << "\033[0m" << " ";
            }
        }
        cout << endl;
    }
}

// Pre: tablero contiene el estado inicial del que se parte para la búsqueda, 
//      movimientosValidos contiene los movimientos que están permitidos, 
//      solucionParcial contiene la solución actual como lista de movimientos, En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: solucionParcial contendrá la lista de movimientos completa (si no se llega a una solución, estará vacía, numMovs == 0)
//       Devuelve 1 si encuentra solución, -1 si no la encuentra.
int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo=0){
  tpListaPosiciones ocupadas;
  rellenarOcupadas(tablero, ocupadas);

  if (ocupadas.numPos == 1){
    return 1;
  }

  for(int i = 0; i < ocupadas.numPos; i++){
    tpListaPosiciones posDestinos, posIntermedias;
    rellenarMovimientosPosibles(ocupadas.posiciones[i], movValidos, posDestinos, posIntermedias);
    for (int j = 0; j < posDestinos.numPos; j++){
      //hacemos el movimiento
      int x=ocupadas.posiciones[i].x, y=ocupadas.posiciones[i].y, 
          dx=posDestinos.posiciones[j].x, dy=posDestinos.posiciones[j].y,
          mx=posIntermedias.posiciones[j].x, my=posIntermedias.posiciones[j].y;
      
      tablero.matriz[x][y] = VACIA; // ficha origen
      tablero.matriz[dx][dy] = OCUPADA; // ficha destino
      tablero.matriz[mx][my] = VACIA; // ficha destino

      //actualizamos solParcial
      solucionParcial.movs[solucionParcial.numMovs].origen = ocupadas.posiciones[i];
      solucionParcial.movs[solucionParcial.numMovs].destino = posDestinos.posiciones[j];
      solucionParcial.numMovs++;

      if(retardo>0){
        mostrarTablero(tablero);
      }

      if(buscaSolucion(tablero, movValidos, solucionParcial, retardo)==1){
        return 1;
      }
      //desahacemos el mov 
      solucionParcial.numMovs--;
      tablero.matriz[x][y] = OCUPADA; // ficha origen
      tablero.matriz[dx][dy] = VACIA; // ficha destino
      tablero.matriz[mx][my] = OCUPADA; // ficha destino


    }

  }

  return -1;

}


//Post: posiciones contenra una lista de posiciones ocupadas del tablero, indicando tambien el número de posiciones ocupadas
void rellenarOcupadas(tpTablero const tablero, tpListaPosiciones &posiciones){
  for(int i =0; i < tablero.nfils; i++){
    for(int j = 0; j < tablero.ncols; j++){
      if(tablero.matriz[i][j]==OCUPADA){
        posiciones.posiciones[posiciones.numPos].x=i;
        posiciones.posiciones[posiciones.numPos].y=j;
        posiciones.numPos++;
      }
    }
  }
}

//Post: movPosibles contendra una lista de posiciones donde puede moverse la ficha de posicion actual
//el vector de movPosibles contiene todas las posiciones de destino posibles
void rellenarMovimientosPosibles(tpPosicion const posicionActual,  const tpMovimientosValidos &movValidos, tpListaPosiciones &posDestinos, tpListaPosiciones &posIntermedias){
  for(int i = 0; i < 8; i++){
    if(movValidos.validos[i]){
      //calculamos posiciones de destino y intermedia si es la dirrecion permitida
      int x = 0, y = 0;

      switch (i)
      {
        case superiorIzquierda: x = -2; y = -2; break; 
        case superior:          x = -2; y = 0; break; 
        case superiorDerecha:   x = -2; y = 2; break; 
        case izquierda:         x = 0; y = -2; break; 
        case derecha:           x = 0; y = 2; break; 
        case inferiorIzquierda: x = 2; y = -2; break; 
        case inferior:          x = 2; y = 0; break; 
        case inferiorDerecha:   x = 2; y = 2; break; 
      }

      posDestinos.posiciones[posDestinos.numPos].x = posicionActual.x + x;
      posDestinos.posiciones[posDestinos.numPos].y = posicionActual.y + y;
      posDestinos.numPos++;

      posIntermedias.posiciones[posIntermedias.numPos].x = posicionActual.x + x/2;
      posIntermedias.posiciones[posIntermedias.numPos].y = posicionActual.y + y/2;
      posIntermedias.numPos++;

    }
  }
}


// Pre: listaMovimientos contiene la lista de movimientos con la solucion 
// Post: escribe la lista de movimientos en el fichero que se le pasa como argumento siguiendo el 
//      formato especificado en el guión (si está vacía, se escribe un -1 en el fichero)
void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion){
  ofstream f;
  f.open(nombrefichero); 
  if (ListaMovimientos.numMovs>0){
    for(int i = 0; i< ListaMovimientos.numMovs; i++){
      f << ListaMovimientos.movs[i] << endl;
    }
  }
  else{
    f << "-1";
  }
}
