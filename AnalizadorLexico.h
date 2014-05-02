#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

typedef string cadena;
typedef int indice;
typedef string diccionario;
typedef vector < cadena > vector_cadenas;
typedef vector < cadena > palabras_reservadas;

struct AnalizadorLexico{

  // atributos
  palabras_reservadas atrPalabrasReservadas;
  diccionario atrDiccionarioLetras;
  diccionario atrDiccionarioNumerosEnteros;
  diccionario atrDiccionarioNumerosDecimales;
  diccionario atrDiccionarioSimbolos;
  AnalizadorLexico();

  // METODOS 
  void metAnalizador();
  vector_cadenas metSplitCadena (cadena);

  indice metIdentificarAccion (cadena); 
  cadena metEliminaEspaciosBlanco(cadena);

  bool metEsIdentificador (cadena, indice);
  bool metEsInteger (cadena);
  bool metEsBoolean (cadena);
  bool metEsDouble (cadena);
  bool metEsMatrizInteger (cadena);
  bool metEsMatrizBoolean (cadena);
  bool metEsMatrizDouble (cadena);
};

AnalizadorLexico :: AnalizadorLexico(){
  this->atrPalabrasReservadas = {"integer", "boolean", "double", "matint", "matbool", "matdou", "if", "for"};
  this->atrDiccionarioLetras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  this->atrDiccionarioNumerosEnteros = "0123456789";
  this->atrDiccionarioNumerosDecimales = "0123456789.";
  this->atrDiccionarioSimbolos = "_";
}

void AnalizadorLexico :: metAnalizador () {

  ifstream varArchivo ("codigo_fuente.txt"); // leyendo el archivo

  cadena varTempLinea;

  if (varArchivo.is_open()){

    while (getline (varArchivo, varTempLinea)){

      // eliminando espacios en blanco
      cadena varCadenaProceso = this->metEliminaEspaciosBlanco (varTempLinea);

      // verificando fin de cadena
      if (varCadenaProceso.find("!") != varCadenaProceso.size()-1){
	cout << "Error en fin de cadena" << endl;
	break;
      }

      // verificando asignacion
      if (-1 == varCadenaProceso.find("=")){
	cout << "Error no existe asignacion" << endl;
	break;
      } 

      // verificando existe la palabra reservada
      indice varIndicePalabra = this->metIdentificarAccion (varCadenaProceso);
      
      if (-1 == varIndicePalabra){
	cout << "Error en palabra no identificada" << endl;
	break;
      }else{


	// string varCadenaProcesoIdentifica = varCadenaProceso.substr(this->atrPalabrasReservadas[varIndicePalabra].size(), varCadenaProceso.find("=") - this->atrPalabrasReservadas[varIndicePalabra].size());

	string varCadenaProcesoIdentifica = varCadenaProceso.substr(this->atrPalabrasReservadas[varIndicePalabra].size());

	cout << varCadenaProcesoIdentifica << endl;
	
	/**
	 * VERIFICANDO CADA PALABRA
	 * {"integer", "boolean", "double", "matint", "matbool", "matdou", "if", "for"};
	 **/

	switch(varIndicePalabra){
	case 0 :
	  cout << ((this->metEsInteger(varCadenaProcesoIdentifica)) ? "Si es integer" : "No es integer") << endl;
	  break;
	case 1 : 
	  cout << ((this->metEsBoolean(varCadenaProcesoIdentifica)) ? "Si es boolean" : "No es boolean") << endl;
	  break;
	case 2 : 
	  cout << ((this->metEsDouble(varCadenaProcesoIdentifica)) ? "Si es double" : "No es double") << endl;
	  break;
	case 3 : 
	  cout << ((this->metEsMatrizInteger(varCadenaProcesoIdentifica)) ? "Si es matint" : "No es matint") << endl;
	  break;
	case 4 : 
	  cout << ((this->metEsMatrizBoolean(varCadenaProcesoIdentifica)) ? "Si es matint" : "No es matint") << endl;
	  break;
	case 5 : 
	  cout << ((this->metEsMatrizDouble(varCadenaProcesoIdentifica)) ? "Si es matint" : "No es matint") << endl;
	  break;
	case 6 : 
	  cout << "if" << endl; 
	  break;
	case 7 : 
	  cout << "for" << endl; 
	  break;
	}

      }

    }
    varArchivo.close(); // cerrando lectura del archivo

  }else cout << "El archivo es invalido: " << endl; //controlando si no pudo abrir el archivo


}

indice AnalizadorLexico ::  metIdentificarAccion (cadena varCadena){

  for(unsigned int i = 0 ; i != atrPalabrasReservadas.size() ; i++)
    if(varCadena.find(this->atrPalabrasReservadas[i]) == 0) return i;

  return -1;
}

cadena AnalizadorLexico :: metEliminaEspaciosBlanco (cadena varCadena){

  string varRetornaCadena = "";

  for (unsigned int i = 0 ; i < varCadena.size() ; i++){
    if (varCadena[i] != ' ') varRetornaCadena += varCadena[i];
    else continue;
  }

  return varRetornaCadena;

}



vector_cadenas AnalizadorLexico :: metSplitCadena (cadena varCadena) {

  vector_cadenas varVectorPalabras;

  char * varSplitCadena = new char[varCadena.size()];

  for (unsigned int i = 0 ; i < varCadena.size() ; i++)
    varSplitCadena[i] = varCadena[i];

  char * varSplitPalabra;

  varSplitPalabra = strtok (varSplitCadena," ");

  while (varSplitPalabra != NULL){
    varVectorPalabras.push_back(varSplitPalabra);
    varSplitPalabra = strtok (NULL, " \n");
  }

  varVectorPalabras[varVectorPalabras.size()-1].erase(varVectorPalabras[varVectorPalabras.size()-1].size()-1,1);

  return varVectorPalabras;

}

/** estas funciones trabajaran como las expresiones regulares para identificar la gramatica **/

bool AnalizadorLexico :: metEsIdentificador (cadena varCadena, indice varIndiceAsignacion){

  if (this->atrDiccionarioLetras.find(varCadena[0]) == -1){ 
    cout << "error primera letra" << endl;
    return 0;
  }
  else{

    // reconociendo el indentificador
    for (unsigned int i = 0 ; i < varIndiceAsignacion ; i++){    
      if(this->atrDiccionarioLetras.find(varCadena[i]) == -1 && this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1 && this->atrDiccionarioSimbolos.find(varCadena[i]) == -1){
	cout << "error declaraciones" << endl;
	return 0;
      }
    }
  }

  return 1;
}


bool AnalizadorLexico :: metEsInteger (cadena varCadena){
  
  indice varIndiceAsignacion = varCadena.find("=");

  if (this->metEsIdentificador (varCadena, varIndiceAsignacion)){
    // reconociendo valor asignado
    for (unsigned int i = varIndiceAsignacion+1 ; i < varCadena.size()-1 ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error numero asignado" << endl;
	return 0;
      }
    }
  }else return 0;

  return 1;

}
 
bool AnalizadorLexico :: metEsBoolean (cadena varCadena){

  indice varIndiceAsignacion = varCadena.find("=");

  if (this->metEsIdentificador (varCadena, varIndiceAsignacion)){
    // reconociendo valor asignado

    indice varIndiceValor = varIndiceAsignacion+1;
    if (varCadena[varIndiceValor] != '1' && varCadena[varIndiceValor] != '0'){
      cout << "error valor booleano asignado" << endl;
      return 0;
    }

  }else return 0;

  return 1;

}

bool AnalizadorLexico :: metEsDouble (cadena varCadena){

  indice varIndiceAsignacion = varCadena.find("=");

  if (this->metEsIdentificador (varCadena, varIndiceAsignacion)){
    // reconociendo valor asignado
    int varContadorPunto = 0;
    for (unsigned int i = varIndiceAsignacion+1 ; i < varCadena.size()-1 ; i++){
      if (varContadorPunto > 1){
	cout << "error punto flotante mayor a dos" << endl;
	return 0;
      }
      if (varCadena[i] == '.') varContadorPunto ++;

      if(this->atrDiccionarioNumerosDecimales.find(varCadena[i]) == -1){
	cout << "error numero asignado" << endl;
	return 0;
      }
    }
  }else return 0;

  return 1;
}

bool AnalizadorLexico :: metEsMatrizInteger (cadena varCadena){

  indice varIndiceAsignacion = varCadena.find("=");
  indice varIndiceAgrupamientoAbrir = varCadena.find("(");
  indice varIndiceSimboloComa = varCadena.find(",");
  indice varIndiceAgrupamientoCerrar = varCadena.find(")");

  if (this->metEsIdentificador (varCadena, varIndiceAgrupamientoAbrir)){
    // reconociendo valor asignado

    // numero filas
    for (unsigned int i = varIndiceAgrupamientoAbrir+1 ; i < varIndiceSimboloComa ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension filas" << endl;
	return 0;
      }
    }

    // numero columnas
    for (unsigned int i = varIndiceSimboloComa+1 ; i < varIndiceAgrupamientoCerrar ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension columnas" << endl;
	return 0;
      }
    }

    // numero asignado
    for (unsigned int i = varIndiceAsignacion+1 ; i < varCadena.size()-1 ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error numero asignado" << endl;
	return 0;
      }
    }

  }else return 0;

  return 1;
}

bool AnalizadorLexico :: metEsMatrizBoolean (cadena varCadena){

  indice varIndiceAsignacion = varCadena.find("=");
  indice varIndiceAgrupamientoAbrir = varCadena.find("(");
  indice varIndiceSimboloComa = varCadena.find(",");
  indice varIndiceAgrupamientoCerrar = varCadena.find(")");

  if (this->metEsIdentificador (varCadena, varIndiceAgrupamientoAbrir)){
    // reconociendo valor asignado

    // numero filas
    for (unsigned int i = varIndiceAgrupamientoAbrir+1 ; i < varIndiceSimboloComa ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension filas" << endl;
	return 0;
      }
    }

    // numero columnas
    for (unsigned int i = varIndiceSimboloComa+1 ; i < varIndiceAgrupamientoCerrar ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension columnas" << endl;
	return 0;
      }
    }


    // variable asignada
    indice varIndiceValor = varIndiceAsignacion+1;
    if (varCadena[varIndiceValor] != '1' && varCadena[varIndiceValor] != '0'){
      cout << "error valor booleano asignado" << endl;
      return 0;
    }


  }else return 0;

  return 1;
}

bool AnalizadorLexico :: metEsMatrizDouble (cadena varCadena){

  indice varIndiceAsignacion = varCadena.find("=");
  indice varIndiceAgrupamientoAbrir = varCadena.find("(");
  indice varIndiceSimboloComa = varCadena.find(",");
  indice varIndiceAgrupamientoCerrar = varCadena.find(")");

  if (this->metEsIdentificador (varCadena, varIndiceAgrupamientoAbrir)){
    // reconociendo valor asignado

    // numero filas
    for (unsigned int i = varIndiceAgrupamientoAbrir+1 ; i < varIndiceSimboloComa ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension filas" << endl;
	return 0;
      }
    }

    // numero columnas
    for (unsigned int i = varIndiceSimboloComa+1 ; i < varIndiceAgrupamientoCerrar ; i++){
      if(this->atrDiccionarioNumerosEnteros.find(varCadena[i]) == -1){
	cout << "error dimension columnas" << endl;
	return 0;
      }
    }


    // reconociendo valor asignado
    int varContadorPunto = 0;
    for (unsigned int i = varIndiceAsignacion+1 ; i < varCadena.size()-1 ; i++){
      if (varContadorPunto > 1){
	cout << "error punto flotante mayor a dos" << endl;
	return 0;
      }
      if (varCadena[i] == '.') varContadorPunto ++;

      if(this->atrDiccionarioNumerosDecimales.find(varCadena[i]) == -1){
	cout << "error numero asignado" << endl;
	return 0;
      }
    }

  }else return 0;


  return 1;
}
