#include "Lista.h"
#include<iostream>
using namespace std;

	/**
	 * Lista.cpp
	 * @brief  Lista utilizada  para manejar los datos
	 * @authors Krisly Arias
	 * @version 01
	 * 
	 **/

Lista::Celda::Celda( int elemento ){
    this->elemento = elemento;
    anterior = 0;     // En C++  es necesario inicializar a nulo ( poner 0 ) a los punteros
    siguiente = 0;
}

Lista::Celda::~Celda(){
    if(siguiente){
        delete siguiente;
    }
}
// METODOS DE LA CLASE ITERADOR

Lista::Iterador::Iterador(){
    actual = 0;
}

Lista::Iterador::Iterador(Celda * actual){
    this->actual = actual;
}

int& Lista::Iterador::operator*(){
    return actual->elemento;
}

Lista::Iterador& Lista::Iterador::operator++(){
    if(actual){
        actual = actual->siguiente;
    }
    return *this;
}

Lista::Iterador Lista::Iterador::iteradorInverso(Celda * ultima){
    Iterador ite;
    if(ultima != 0) {
        ite = ultima;
    }
    return ite;
}
Lista::Iterador& Lista::Iterador::operator--(){//predecremento
    //if(this->actual->anterior != 0 ) {
        Iterador nuevo;
        nuevo.actual = this->actual->anterior;
        this->actual = nuevo.actual;
    return *this;
}

Lista::Iterador Lista::Iterador::operator--(int){//posdeceremento
    Iterador viejo(actual);
    //if(this->actual->anterior != 0){
        --(*this);
    return viejo;
}

Lista::Iterador Lista::Iterador::operator++(int){
    Iterador viejo(actual);
    ++(*this);
    return viejo;
}

int Lista::Iterador::operator==(Iterador otro){
    return this->actual == otro.actual;
}

int Lista::Iterador::operator!=(Iterador otro){
    return ! (*this == otro);
}


// METODOS DE CLASE LISTA
Lista::Lista(){
    primera = 0;
    ultima = 0;
}


Lista::Lista(const Lista & otra){
    primera = 0;
    ultima = 0;
    Celda * actual = otra.primera;
    while(actual){
        this->push_back(actual->elemento);
        actual = actual->siguiente;
    }
}

Lista::~Lista(){
    if(primera){
        delete primera; // destruye la primera Celda si existe valor es !=0
    }
}

int Lista::isEmpty(){
    return !primera;
}

Lista & Lista::push_back( int elemento){
    Celda * nueva = new Celda( elemento );
    if(isEmpty()){
        primera = nueva;
        ultima = nueva;
    }
    else {
        ultima->siguiente = nueva;
        nueva->anterior = ultima;
        ultima = nueva;
    }
    return *this; //encadenamiento
}

ostream& Lista::imprimir(ostream & salida){
    Celda * actual = primera;
    while(actual){
        salida << actual->elemento << " ";
        actual = actual->siguiente;
    }
    return salida;
}

Lista::Iterador Lista::begin(){
    Iterador i( primera );
    return i;
}

Lista::Iterador Lista::end(){
    Iterador i;
    return i;
}

Lista::Iterador Lista::inverso(){
    Lista::Iterador inverso = inverso.iteradorInverso(this->ultima);
    return inverso;
}

Lista::Iterador Lista::buscar(int valor) {
    Iterador iterador;
    if(!this->isEmpty()) {
        iterador = this->begin();
        Iterador fin = this->end();
        while (iterador != fin && *iterador != valor) {
            ++iterador;
        }
    }
    else{
        iterador = this->end();
    }
    return iterador;
} // retorna iterador del Celda con valor igual a int

Lista & Lista::borrar( Iterador borrar ){
    if(!(this->isEmpty()) && borrar != 0){
        if(borrar.actual->elemento == primera->elemento){
           if(primera->siguiente != 0){
               primera = primera->siguiente;
               primera->anterior = 0;
               Celda * matar = borrar.actual;
               borrar = borrar.actual->siguiente;
               matar->siguiente = 0;
               matar->anterior = 0;
               delete matar;
           }
           else {
               primera = 0;
               ultima = 0;
               delete borrar.actual;
           }
        }
        else {
            if (borrar.actual->elemento == ultima->elemento) {
                ultima = ultima->anterior;
                ultima->siguiente = 0;
                Celda * matar = borrar.actual;
                borrar.actual = ultima;
                matar->siguiente = 0;
                matar->anterior = 0;
                delete matar;
            }
            else {
                Iterador anterior = borrar.actual->anterior;
                anterior.actual->siguiente = borrar.actual->siguiente;
                Celda * matar = borrar.actual;
                borrar = anterior.actual->siguiente;
                delete matar;
            }
        }
    }
    return *this;
}// Borra Celda a la que apunta el iterador

// Recibe iterador que apunta a la Celda donde se
// inserta el valor int
// La celda en esa posicion se mueve a la derecha
// Ejemplo: 2 8 7 6
// lista.insertar( buscar(8) , 10 );
// Entonces: 2 10 8 7 6

// NO ES SUSTITUIR:
// Note que no es: Lista::Iterador i = buscar(8);
// *i = 10;
// en este caso sustituye 8 por 10

Lista & Lista::insertar(Iterador posicionDespues, int valor ){
   Celda * meter = new Celda(valor);
   if(this->isEmpty()){
       primera = meter;
       ultima = meter;
   }
   else {
       if (posicionDespues.actual->elemento == primera->elemento) {
            meter->siguiente = primera;
            primera->anterior = meter;
            primera = meter;
       }
       else{
           if(posicionDespues == 0){
               ultima->siguiente = meter;
               meter->anterior = ultima;
               ultima = meter;
           }
           else {
               Iterador anterior = posicionDespues.actual->anterior;
               anterior.actual->siguiente = meter;
               meter->anterior = anterior.actual;
               meter->siguiente = posicionDespues.actual;
               posicionDespues.actual->anterior = meter;
           }
       }
   }
    return *this;
}

Lista::Celda * Lista::getPrimera(){
    Celda * primera;
    if(!isEmpty()) {
        primera = this->primera;
    }
    return primera;
}

Lista::Celda * Lista::getUltima(){
    Celda * ultima;
    if(!isEmpty()) {
        ultima = this->ultima;
    }
    return ultima;
}

// Agrega un valor al inicio
Lista & Lista::push_front( int elemento){
    Celda * nueva = new Celda(elemento);
    if(isEmpty()){
        primera = nueva;
        ultima = nueva;
    }
    else{
        nueva->siguiente = primera;
        primera->anterior = nueva;
        primera = nueva;
    }
    return *this;
}
