#ifndef _NODOA_
#define _NODOA_

#include <string>
#include <iostream>
#include <list>
#include <iterator>
using namespace std;



	/**
	 * Celda.h 
	 * @authors Krisly Arias
	 * @version 01
	 * 
	 **/

class Celda {
    friend ostream& operator<<( ostream& salida, Celda & n){
        return n.imprimir(salida);
    }
  private:
    string id_mensaje;
    string hora;
    string usuario;
    string contenido;

  public:
    Celda();
    Celda(string,string,string,string);
    Celda(const Celda &);
    Celda & operator=(const Celda &);
    int operator<(const Celda &);
    ostream& imprimir(ostream&);
};

#endif
