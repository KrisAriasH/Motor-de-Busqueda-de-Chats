#ifndef LISTA_G06_10MAYO2021
#define LISTA_G06_10MAYO2021
#include<iostream>
using namespace std;



	/**
	 * Lista.h
	 * @authors Krisly Arias
	 * @version 01
	 * 
	 **/
class Lista {
    friend class Iterador;

    friend ostream& operator<<( ostream& salida, Lista & lista){
        return lista.imprimir(salida);
    }

private:
    class Celda {
    public:
        int elemento;
        Celda * anterior;
        Celda * siguiente;
        Celda(int );
        ~Celda();
    };

    Celda * primera;
    Celda * ultima;
public:
    class Iterador {
        friend class Lista;
    private:
        Celda * actual;
    public:
        Iterador();
        Iterador(Celda *);
        int& operator*();
        Iterador& operator++();
        Iterador operator++(int);
        Iterador& operator--();
        Iterador operator--(int);
        Iterador iteradorInverso(Celda *);
        int operator==(Iterador);
        int operator!=(Iterador);
    };


    Lista(); // -Constructor por Omisión
    Lista(const Lista & );  // Constructor de Copia
    ~Lista();
    int isEmpty();
    Lista & push_back(int);  // encadenamiento de métodos
    ostream& imprimir(ostream&);
    Iterador inverso();
    Celda * getPrimera();
    Celda * getUltima();

    // PROGRAME LOS SIGUIENTES MÉTODOS

    Iterador buscar( int ); // retorna iterador del Celda con valor igual a int

    Lista & borrar( Iterador ); // Borra Celda a la que apunta el iterador

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

    Lista & insertar(Iterador, int );

    // Agrega un valor al inicio
    Lista & push_front( int );

    Iterador begin();
    Iterador end();
};

#endif
