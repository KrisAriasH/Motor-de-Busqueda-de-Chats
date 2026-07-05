
	/**
	 * Main.cpp
	 * @brief  recibe el archivo json y de consulta y devuelve un menu con opciones de posibles acciones, incluyendo mostrar arboles o *realizar consulta
	 * @authors Krisly Arias
	 * @version 01
	 * 
	 **/
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include <sstream>
#include <locale>
#include <iomanip>
#include <ctime>
#include "json.hpp"

#include <map>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>

#include "Celda.h"

#define ESPERA 20
#define MAX_PALABRAS 100

using json = nlohmann::json;
using namespace std;

set<string> strings;

// Define el árbol A
map<string, set<int>> arbolA;
map<string, set<int>>::iterator iteradorA;
map<string, string> arbolB;
map<int, pair<string,string>> arbolC;
map<int, list<Celda>> arbolCPlus;
map<int, list<Celda>>::iterator iteradorCplus;

fstream archivoAbrir;
string nombreArchivo;
fstream archivoNuevo;

/**
* Método split
*@brief   se utiliza para leer el archivo json
*@param   string
*@return  void
**/
void split (string str) {
    int i = 0;
    int inicio = 0, fin = 0;
    // LImpia el array de palabras
    strings.clear();
    i=0;
    while (i <= str.length()) {
        if (str[i] == ' ' || // Lista de separadores
                str[i] == '.' ||
                str[i] == ',' ||
                str[i] == ';' ||
                i == str.length()) { // Fin del texto
            fin = i;
            string subStr = "";
            subStr.append(str, inicio, fin - inicio);
            if (subStr.length()>0) {
                strings.emplace(subStr);
            }
            inicio = fin + 1;
        }
        i++;
    }
}

/**
* Método menorQue
*@brief   compara dos celdas
*@param   Celda i,Celda j
*@return  bool
**/
bool menorQue (Celda i,Celda j) {
    return (i<j);
}

/**
* Método procesarPalabra
*@brief   navega por los arboles para encontrar la info asociada a la palabra.
*@details recibe la palabra que hay que buscar y la busca en el arbolA etc para adquirir la info, y la imprime en un txt.
*@param   string
*@return  imprime en un nuevo archivo la informacion
**/
void procesarPalabra(string palabra) {
    archivoNuevo << "Consulta: " << palabra << "\n";
    // Busca la palabra en el árbol A
    iteradorA = arbolA.find(palabra);
    archivoNuevo << "Conversaciones: " << set<int>(iteradorA->second).size() << endl;
    for (int i: set<int>(iteradorA->second)) {
        // Busca la conversación e imprime la lista de comentarios
        iteradorCplus = arbolCPlus.find(i);
        if (iteradorCplus != arbolCPlus.end()) {
            archivoNuevo <<  "Conversacion " << iteradorCplus->first  << endl;
            for (Celda i: list<Celda>(iteradorCplus->second)) {
                archivoNuevo << i;
            }
        }
    }
    archivoNuevo << endl;
}

/**
* Método procesarPalabraTiempo
*@brief     procesa las palabras y activa el reloj para calcular cuanto tarda
*@param   string palabra a buscar
*@return void
**/
void procesarPalabraTiempo(string palabra) {
    // Busca la palabra en el árbol A
    iteradorA = arbolA.find(palabra);
    for (int i: set<int>(iteradorA->second)) {
        // Busca la conversación e imprime la lista de comentarios
        iteradorCplus = arbolCPlus.find(i);
        if (iteradorCplus != arbolCPlus.end()) {
            for (Celda i: list<Celda>(iteradorCplus->second)) {
            }
        }
    }
}
/**
* Método medirTiempo
*@brief     calcula el tiempo que toma realizar un dado numero de consultas en las listas
*@param    int cantidad de consultas que se desea hacer
*@return   void, imprime en consola el tiempo
**/
void medirTiempo(int cantidad) {
    auto relojInicio = chrono::steady_clock::now();
    for (int i=0 ; i< cantidad; i++ ) {
        procesarPalabraTiempo("tomorrow");
    }
    auto relojFin = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = relojFin-relojInicio;
    cout << "Tiempo en segundos (" << cantidad << " consultas): " << elapsed_seconds.count() << "s\n";
}
/**
* Método imprimirArbolA
*@brief     imprime todo el contenido del arbol a
*@param    void
*@return   void, imprime en consola
**/
void imprimirArbolA() {
    cout << endl << "Arbol A impreso" << endl;
    for (pair<string, set<int>> elem : arbolA) {
        cout << elem.first << ": " ;
        for (int i: set<int>(elem.second)) {
            cout << ' ' << i;
        }
        cout << endl;
    }
}

/**
* Método imprimirArbolB
*@brief     imprime todo el contenido del arbol b
*@param    void
*@return   void, imprime en consola
**/
void imprimirArbolB() {
    cout << endl << "Arbol B resultante" << endl;
    for (pair<string, string> elem : arbolB) {
        cout << elem.first << " :: " << elem.second << endl;
    }
}
/**
* Método imprimirArbolC
*@brief     imprime todo el contenido del arbol c
*@param    void
*@return   void, imprime en consola
**/
void imprimirArbolC() {
    cout << endl << "Arbol C resultante" << endl;
    for (pair<int,pair<string,string>> elem : arbolC) {
        cout << elem.first << " :: inicio " << elem.second.first << ", fin " << elem.second.second << endl;
    }
}


void imprimirArbolCPlus() {
    cout << endl << "Arbol CPlus resultante" << endl;
    for (pair<int, list<Celda>> elem : arbolCPlus) {
        cout <<  "Conversacion " << elem.first << ":"<<list<Celda>(elem.second).size() << endl;
        for (Celda i: list<Celda>(elem.second)) {
            cout << i << endl;
        }
    }
}

int main() {


    string path = ".";
    string file_name = "Registros";

    json data;
    ifstream file(path + "/" + file_name + ".json");
    file >> data;

    // La primera conversación es 0;
    int id_conv = -1;

    // Se agrega una hora de inicio por defalt
    tm hora_inicio;
    istringstream ss("2020-01-01 00:00:00");
    ss >> get_time(&hora_inicio, "%Y-%m-%d %H:%M:%S");

    // Hora del comentario
    tm hora_comentario;

    string inicioConv = "";
    string finConv = "";

/**
*  separar
*@brief    obtiene datos del doc json
*@param    string .json
*@return   void
**/

    for (auto& x : data.items()) {
        // ********************* Obtiene los valores del comentario
        auto mi_id_conversacion = x.value().at("id");
        auto mi_content = x.value().at("content");
        auto mi_timestamp = string(x.value().at("timestamp")).substr (0,19);
        auto mi_autor = x.value().at("author");
        auto mi_id = mi_autor.at("id");
        auto mi_username = mi_autor.at("username");

/**
*  separarConversas
*@brief    separa los comentarios en conversaciones
*@param    string .json
*@return   void
**/

        // Se obtiene la hora del comentario
        istringstream(mi_timestamp) >> get_time(&hora_comentario, "%Y-%m-%dT%H:%M:%S");

        // Calcula la diferencia en segundos con el comentario anterior
        double segundos_espera=abs(difftime(mktime(&hora_comentario),mktime(&hora_inicio)));

        // Verifica si se tiene hora de inicio de la conversación
        if (inicioConv=="") {
            inicioConv = string(mi_id_conversacion);
        }

        // Si el tiempo entre los comentario es mayor a la ESPERA, se considera una nueva conversación
        if (segundos_espera > ESPERA) {
            // cambio de conversación
            if (id_conv>=0) {
                // En el árbol C se incluye el id de la conversación y el primer comentario con el útlimo de la covnversación.
                arbolC.insert(pair<int,pair<string,string>>(id_conv, make_pair(inicioConv,finConv)));
            }
            id_conv++;

            inicioConv = string(mi_id_conversacion);
            finConv = string(mi_id_conversacion);// Sólo un comentario en la conversación
        } else {
            finConv = string(mi_id_conversacion);
        }

        // ********************* Para cada comentario lo agrega al arbol con la lista de conversaciones

/**
*  arbol C
*@brief    ingresa datos a arbol C
*@param    void
*@return   void
**/

        Celda celda = Celda(mi_id_conversacion,mi_timestamp,mi_username,mi_content);
        // Buscar el id conversación
        iteradorCplus = arbolCPlus.find(id_conv);
        if (iteradorCplus != arbolCPlus.end()) {
            // si lo encuentra, agrega la conversación a la lista
            list<Celda> cActual = list<Celda>(iteradorCplus->second);
            int paso = iteradorCplus->first;
            cActual.push_back(celda);
            cActual.sort(menorQue);
            arbolCPlus.erase(paso);
            arbolCPlus.insert(pair<int,list<Celda>>(paso, cActual));
        } else {
            // si no lo encuentra, lo agrega
            list<Celda> cNueva;
            cNueva.push_back(celda);
            arbolCPlus.insert(pair<int,list<Celda>>(id_conv, cNueva));
            //cout << "Se agrego una conversación " << id_conv <<endl;
        }

        // Actualiza la hora de inicio con la hora del comentario
        hora_inicio=hora_comentario;

        // separar palabras del comentario
        split(string(mi_content));

        // ********************* Procesar el comentario en el árbol A.

/**
*  arbol a
*@brief    ingresa datos a arbol a
*@param    void
*@return   void
**/


        for (string str: strings) {
            // Buscar la palabra
            iteradorA = arbolA.find(str);
            if (iteradorA != arbolA.end()) {
                // si lo encuentra, agrega la conversación a la lista
                set<int> sActual = set<int>(iteradorA->second);
                string paso = iteradorA->first;
                sActual.emplace(id_conv);
                arbolA.erase(paso);
                arbolA.insert(pair<string,set<int>>(paso, sActual));
                } else {
                // si no lo encuentra, lo agrega
                set<int> sNuevo;
                sNuevo.emplace(id_conv);
                arbolA.insert(pair<string,set<int>>(str, sNuevo));
                //   cout << "Se agrego una conversación " << id_conv <<endl;
            }
        }
        // ********************* en el árbol B se incluye la llave de Tiempo+id y almacena el comentario completo.

/**
*  arbol b
*@brief    ingresa datos a arbol b
*@param    void
*@return   void
**/
        arbolB.insert(pair<string, string>(string(mi_timestamp)+string(mi_id_conversacion), mi_content));
    }

    // se incluye la última conversación
    if (id_conv>=0) {
        arbolC.insert(pair<int,pair<string,string>>(id_conv, make_pair(inicioConv,finConv)));
    }

    // *********************  FIN DE LA CONSTRUCCIÓN DE LOS ARBOLES

    // Menú para escoger la opción a seguir
    //*********************************************************


/**
*  menu
*@brief    permite la navegacion en consola
*@param    void
*@return   void
**/
    char seleccion;
    seleccion= 'x';
    while (seleccion!='5') {
        cout<<"\n Menu";
        cout<<"\n========";
        cout<<"\n 0 - Realizar consulta";
        cout<<"\n 1 - Imprimir arbol A";
        cout<<"\n 2 - Imprimir arbol B";
        cout<<"\n 3 - Imprimir arbol C";
        cout<<"\n 4 - Tiempos";
        cout<<"\n 5 - Salir";
        cout<<"\n Escoja la opcion ";
        cin>>seleccion;

        switch(seleccion) {
        case '0' : {
            cout<<"Digite el nombre del archivo: ";
            cin>>nombreArchivo;

            // Enciende el reloj para cronometrar el tiempo
            auto relojInicio = chrono::steady_clock::now();

            // Abre el archivo de entrada
            archivoAbrir.open(nombreArchivo+".txt");
            if (archivoAbrir.is_open()) {
                // Abre el archivo de salida
                archivoNuevo.open(nombreArchivo+"_out.txt",ios::out); //Nombre con el que se llamará el nuevo archivo
                if (archivoNuevo.is_open()) {
                    //Para leerlo palabra por palabra
                    string palabra;
                    while (archivoAbrir >> palabra) {
                        procesarPalabra(palabra);
                    }
                    archivoNuevo.close();
                } else {
                    cout << "No fue posible crear el archivo de salida";
                }
                archivoAbrir.close();
            } else {
                cout << "No fue posible abrir el archivo de entrada";
            }

            // Detiene el reloj y muestra el tiempo
            auto relojFin = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = relojFin-relojInicio;
            cout << "Tiempo en segundos: " << elapsed_seconds.count() << "s\n";
        }
        break;
        case '1' : {
            imprimirArbolA();
        }
        break;
        case '2' : {
            imprimirArbolB();
        }
        break;
        case '3' : {
            imprimirArbolC();
        }
        break;
        case '4' : {
            // Medir los tiempos
            medirTiempo(100);
            medirTiempo(1000);
            medirTiempo(10000);
            medirTiempo(100000);
        }
        break;
        default :
            cout<<"\n Debe digitar la opción del 0 al 5.";
        }
    }
}
