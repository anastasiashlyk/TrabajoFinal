#include <iostream>
#include <fstream>
#include "GSenku.hpp"
using namespace std;

//Vectores predefinidos para las direcciones X e Y para reduccion de costes (Saetas Reloj)
const int DirFinX[8] = {0,2,2,2,0,-2,-2,-2}; //Posiciones finales
const int DirFinY[8] = {2,2,0,-2,-2,-2,0,2};

const int DirAdyaX[8] = {0,1,1,1,0,-1,-1,-1}; //Posiciones adyacentes
const int DirAdyaY[8] = {1,1,0,-1,-1,-1,0,1};

// FUNCIONES / PROCEDIMIENTOS 

// Pre: true
// Post: lee la configuración y el estado del tablero del fichero de configuración que se le pasa como argumento
//      inicializando tablero y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarTablero(const string nombreFichero, tpTablero &tablero){
  ifstream f;
  f.open(nombreFichero);
  if(!f.is_open()){
    cerr << "Error al abrir el fichero" << endl;
    return false;
  }
  if(!(f >> tablero.nfils >> tablero.ncols)){
    cerr << "Error al leer las dimensiones del tablero" << endl;
    return false;
  }
  if(tablero.nfils<= 0||tablero.ncols<= 0||tablero.nfils>MAXDIM||tablero.ncols>MAXDIM){//NO SE SI HACE FALTA VERIFICAR los MAXDIM
    cerr << "Dimensiones del tablero inválidas" << endl;
    return false;
  }
  char celda;
  int celdasLeidas = 0;
  int totalCeldas = tablero.nfils * tablero.ncols; 
  for (int i = 0; i < tablero.nfils; ++i) {
    for (int j = 0; j < tablero.ncols; ++j) {
      if (!(f >> celda)) {//si la lectura del fichero falla, se devuelve false
        cerr << "Error en la lectura del tablero" << endl;
        return false;
      }
      celdasLeidas++;
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
      f.ignore();
    }
  }
  if (celdasLeidas != totalCeldas) {
    cerr << "Error al leer todo el tablero" << endl;
    return false;
  }
  return true;
}

// Pre: true 
// Post: lee los movimientos válidos del fichero que se le pasa como argumento 
//      inicializando la estructura y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarMovimientosValidos(const string nombreFichero, tpMovimientosValidos &movimientos){
  ifstream f;
  f.open(nombreFichero);
  if(!f.is_open()){
    cerr << "No se ha podido abrir el archivo.";
    return false;
  }
  char c;
  int i = 0;
  while(i<8 && f.get(c)){
    if (c == '+' || c == '-') { // Ignora saltos de línea u otros caracteres
      movimientos.validos[i] = (c == '+');
      i++;
    }
  }
  if(i != 8){
    cerr << "Error: No se leyeron todos los movimientos válidos" << endl;
    return false;
  }
  return true;
}

// Pre: tablero contiene el estado actual de la ejecución de la búsqueda de la solución
// Post: Se ha mostrado el tablero por pantalla
void mostrarTablero(const tpTablero & tablero){
    for(int i = 0; i< tablero.nfils; i++){
        for(int j = 0; j < tablero.ncols; j++){
            if(tablero.matriz[i][j] == NO_USADA){
                cout << "  ";
            }
            else if(tablero.matriz[i][j] == 1){
                cout <<"\033[42m" <<" " << "\033[0m" << " ";
            }
            else if(tablero.matriz[i][j] == 2){
                cout << "\033[41m" <<" " << "\033[0m" << " ";
            }
        }
        cout << endl << endl;
    }
}

//Post: movPosibles contendra una lista de posiciones donde puede moverse la ficha de posicion actual
//el vector de movPosibles contiene todas las posiciones de destino posibles
void rellenarMovimientosPosibles(tpTablero const tablero, tpPosicion const posicionActual, const tpMovimientosValidos &movValidos, tpListaPosiciones &posDestinos, tpListaPosiciones &posIntermedias){
  for(int i = 0; i < 8; i++){
    if(movValidos.validos[i]){
      //calculamos posiciones de destino y intermedia si es la dirrecion permitida
      tpPosicion intermedia, destino;//se pueden utizar variables locales
      intermedia.x = posicionActual.x + DirAdyaX[i];
      intermedia.y = posicionActual.y + DirAdyaY[i];
      destino.x = posicionActual.x + DirFinX[i];
      destino.y = posicionActual.y + DirFinY[i];
      if(intermedia.x >= 0 && intermedia.y >= 0 && destino.x>=0 && destino.y>=0 &&
        intermedia.x < tablero.nfils && intermedia.y < tablero.ncols &&
        destino.x < tablero.nfils && destino.y < tablero.ncols){//comprobamos que este en el rango de matriz 
          
          if(tablero.matriz[intermedia.x][intermedia.y]==OCUPADA && tablero.matriz[destino.x][destino.y]==VACIA){
            posDestinos.posiciones[posDestinos.numPos].x = destino.x;
            posDestinos.posiciones[posDestinos.numPos].y = destino.y;
            posDestinos.numPos++;

            posIntermedias.posiciones[posIntermedias.numPos].x = intermedia.x;
            posIntermedias.posiciones[posIntermedias.numPos].y = intermedia.y;
            posIntermedias.numPos++;
          }
      }
    }
  }
}
//////////////////////////////////////////////////////////
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


// Pre: tablero contiene el estado inicial del que se parte para la búsqueda, 
//      movimientosValidos contiene los movimientos que están permitidos, 
//      solucionParcial contiene la solución actual como lista de movimientos, En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: solucionParcial contendrá la lista de movimientos completa (si no se llega a una solución, estará vacía, numMovs == 0)
//       Devuelve 1 si encuentra solución, -1 si no la encuentra.
int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo){
  tpListaPosiciones ocupadas;//y otra
  rellenarOcupadas(tablero, ocupadas);
  if (ocupadas.numPos == 1){
    return 1;
  }
  for(int i = 0; i < ocupadas.numPos; i++){
    tpListaPosiciones posDestinos, posIntermedias;//aqui igual
    rellenarMovimientosPosibles(tablero, ocupadas.posiciones[i], movValidos, posDestinos, posIntermedias);
    for (int j = 0; j < posDestinos.numPos; j++){
      //hacemos el movimiento
      int x=ocupadas.posiciones[i].x, y=ocupadas.posiciones[i].y, 
          dx=posDestinos.posiciones[j].x, dy=posDestinos.posiciones[j].y,
          mx=posIntermedias.posiciones[j].x, my=posIntermedias.posiciones[j].y;
      tablero.matriz[x][y] = VACIA; // ficha origen
      tablero.matriz[dx][dy] = OCUPADA; // ficha destino
      tablero.matriz[mx][my] = VACIA; // ficha destino
      // Actualizamos la solución y usas lo que has creado, qeu es mejor que volver a buscar en la matriz del tipo de dato
      solucionParcial.movs[solucionParcial.numMovs].origen.x = x;
      solucionParcial.movs[solucionParcial.numMovs].origen.y = y;
      solucionParcial.movs[solucionParcial.numMovs].destino.x = dx;
      solucionParcial.movs[solucionParcial.numMovs].destino.y = dy;
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

// Pre: listaMovimientos contiene la lista de movimientos con la solucion 
// Post: escribe la lista de movimientos en el fichero que se le pasa como argumento siguiendo el 
//      formato especificado en el guión (si está vacía, se escribe un -1 en el fichero)
void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion){
  ofstream f;
  f.open(nombreFichero); 
  if(!f.is_open()){
    cerr << "No se ha podido escribir en el fichero \"" << nombreFichero << "\"." << endl;
  }
    if (solucion.numMovs>0){
      for(int i = 0; i< solucion.numMovs; i++){
        f << solucion.movs[i].origen.x << ','<< solucion.movs[i].origen.y <<':'
        << solucion.movs[i].destino.x << ',' << solucion.movs[i].destino.y << endl;
      }
    }
  else{
    f << "-1";
  }
}
