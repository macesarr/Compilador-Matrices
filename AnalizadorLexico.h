#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

struct AnalizadorLexico{

  AnalizadorLexico();

  // METODOS 
  void metAnalizador();
  vector <string> metSplitCadena (string);

};

AnalizadorLexico :: AnalizadorLexico(){

}

void AnalizadorLexico :: metAnalizador () {

  ifstream varArchivo ("codigo_fuente.txt"); // leyendo el archivo

  string varTempLinea;

  if (varArchivo.is_open()){

    while (getline (varArchivo, varTempLinea)){

      cout << varTempLinea << endl;

      this -> metSplitCadena (varTempLinea);
      printf("\n");

    }
    varArchivo.close(); // cerrando lectura del archivo

  }else cout << "El archivo es invalido: " << endl; //controlando si no pudo abrir el archivo


}

vector <string> AnalizadorLexico :: metSplitCadena (string varCadena) {

  vector <string> varVectorPalabras;

  // llenando el char * con el string

  char * varSplitCadena = new char[varCadena.size()];
  for (unsigned int i = 0 ; i < varCadena.size() ; i++)
    varSplitCadena[i] = varCadena[i];

  char * varSplitPalabra;

  varSplitPalabra = strtok (varSplitCadena," ");

  while (varSplitPalabra != NULL){
    varVectorPalabras.push_back(varSplitPalabra);
    varSplitPalabra = strtok (NULL, " ");
  }

  vector < string > :: iterator it = varVectorPalabras.begin();

  for (; it != varVectorPalabras.end() ; it++)
    cout << *it << "->";

  return varVectorPalabras;

}


