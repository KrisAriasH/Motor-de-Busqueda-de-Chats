#include "Celda.h"
#include <iostream>
#include <string>

#include <list>

using namespace std;


/**
	 * Celda.cpp
	 * @brief  Celda utilizada en los arboles para manejar los datos
	 * @authors Krisly Arias
	 * @version 01
	 * 
	 **/

Celda::Celda() {
}

Celda::Celda(string id,string ho,string us,string co) {
    this->id_mensaje=id;
    this->hora=ho;
    this->usuario=us;
    this->contenido=co;
}

Celda::Celda(const Celda & otro) {
    this->id_mensaje=otro.id_mensaje;
    this->hora=otro.hora;
    this->usuario=otro.usuario;
    this->contenido=otro.contenido;
}

Celda & Celda::operator=(const Celda & otro) {
    this->id_mensaje=otro.id_mensaje;
    this->hora=otro.hora;
    this->usuario=otro.usuario;
    this->contenido=otro.contenido;
    return *this;
}

int Celda::operator<(const Celda & otro) {
    return (this->hora<otro.hora);
}

ostream& Celda::imprimir(ostream & salida) {
    salida << " - " <<this->id_mensaje<< " - " <<this->hora<< " - " <<this->usuario<< " - " <<this->contenido<< endl;
    return salida;
}

