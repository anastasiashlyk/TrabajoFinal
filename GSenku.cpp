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
  for (int i = 0; i < tablero.nfils; ++i) {
    for (int j = 0; j < tablero.ncols; ++j) {
      //variables que trabajaremos en mod 2 con la intención de apuntar a las posiciones abyacentes a la canica (tocara meterlo como vectores en hpp)
      int RelojX=0;
      int RelojY=1;
      //Valores en dif vect: [0]=(x)0 (y)1, 11, 10, 1-1, 0-1 -1-1 -10 -11 saetas de reloj de los movimientos
      for (int k = 0; k<=8; ++k) {
        if(MovimientosValidos.valido[k])
        //Ahora utilizariamos el vector de las posiciones que apuntan por el reloj para hacer el movimiento de las bolas
        if(//vola se puede mover){
        //entrara si se puede hacer el movimiento para eliminar la bola de enmedio, quitar esa y poner donde toca (modificar la matriz)
        }
        //llama recursiva que volvera a mirar todas las bolas previas y en caso de que el posible movimiento no genere sol valida esta rama fallida seguira.
        
        //al haber fallado desharemos el movimiento previo a la llamada como en el de las reinas, osea las posiciones y de 3 casillsa hay que guardarlas. las variables seguiran guardadas puesto que no pasan por referencia de la funcion al llamarse, aunque su hijo tenga distinto valor dentro de la funcion padre esta seguira teniendo el mismo valor osea por ejemplo la variable donde se guarda la bola movida
        
        
      }
    }
  }
}

//forxfor verificar cada pieza independientemente
  //for verificar cada movimiento de cada pieza
    //if si es valido modificar, solucionParcial y la matriz actual 
//


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
