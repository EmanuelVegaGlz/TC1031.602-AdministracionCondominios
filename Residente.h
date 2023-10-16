/*
 * Proyecto final TC1032.TC1031 
 * Programación de estructuras de datos y algoritmos fundamentales
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 *
 * Clase Residente  
 */

#ifndef RESIDENTE_H
#define RESIDENTE_H

#include "Amenidades.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;



class Residente{

    private:
        int numCasa;
        string propietario;
        string contacto;
        float saldoAPagar;
        vector<string> amenidadesReservadas;

    public:
        // Constructores
        Residente();
        Residente(Residente* r);
        Residente(int num, string prop, string cont, float sal);

        // Getters
        string getNombre();
        int getNumCasa();
        string getPropietario();
        string getContacto();
        float getSaldoAPagar();
        string getAmenidadesReservadas(int i);
        int getTamAmenidadesReservadas();

        // Setters
        void setContacto(string cont);
        void setAmenidadesReservadas(string amenidad);
        void setNumCasa(int num);

        // Metodos
        void pagarSaldo(float pag);
        void hacerCargo(float sal);
        void imprimirReservaciones();
        void imprimirSaldo();
        void imprimirAmenidadesReservadas(int i);

        friend class BSTResidente;
        friend class Node;


};

/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Residente
 */
Residente::Residente(){
    numCasa = 0;
    propietario = "";
    contacto = "";
    saldoAPagar = 0;
    amenidadesReservadas = {};
}

/**
 * Constructor copia
 *
 * @param Residente* r
 * @return Objeto de tipo Residente
 */
Residente::Residente(Residente* r){
    numCasa = r->numCasa;
    propietario = r->propietario;
    contacto = r->contacto;
    saldoAPagar = r->saldoAPagar;
    amenidadesReservadas = r->amenidadesReservadas;
}

/**
 * Constructor con parámetros
 *
 * @param num, prop, cont, sal
 * @return Objeto de tipo Residente
 */
Residente::Residente(int num, string prop, string cont, float sal){
    numCasa = num;
    propietario = prop;
    contacto = cont;
    saldoAPagar = sal;
    amenidadesReservadas = {};
}

/**
 * Getter nombre
 *
 * @param
 * @return string nombre
 */
string Residente::getNombre(){
    return propietario;
}

/**
 * Getter numCasa
 *
 * @param
 * @return int numCasa
 */
int Residente::getNumCasa(){
    return numCasa;
}

/**
 * Getter propietario
 *
 * @param
 * @return string propietario
 */
string Residente::getPropietario(){
    return propietario;
}

/**
 * Getter contacto
 *
 * @param
 * @return string contacto
 */
string Residente::getContacto(){
    return contacto;
}

/**
 * Getter saldo
 *
 * @param
 * @return float saldo
 */
float Residente::getSaldoAPagar(){
    return saldoAPagar;
}

/**
 * Getter amenidadesReservadas
 *
 * @param int i
 * @return string amenidadesReservadas
 */
string Residente::getAmenidadesReservadas(int i){
    return amenidadesReservadas[i];
}

/**
 * Getter tamAmenidadesReservadas
 *
 * @param
 * @return int tamAmenidadesReservadas
 */
int Residente::getTamAmenidadesReservadas(){
    return amenidadesReservadas.size();
}

/**
 * Setter contacto
 *
 * @param string cont
 * @return
 */
void Residente::setContacto(string cont){
    contacto = cont;
}


/**
 * Setter amenidadesReservadas
 *
 * @param string amenidad
 * @return
 */
void Residente::setAmenidadesReservadas(string amenidad){
    amenidadesReservadas.push_back(amenidad);
}

/**
 * Setter numCasa
 *
 * @param int num
 * @return
 */
void Residente::setNumCasa(int num){
    numCasa = num;
}

/**
 * Metodo pagarSaldo
 *
 * @param
 * @return
 */
void Residente::pagarSaldo(float pag){
    saldoAPagar -= pag;
}

/**
 * Metodo hacerCargo
 *
 * @param
 * @return
 */
void Residente::hacerCargo(float sal){
    saldoAPagar += sal;
}

/**
 * Metodo imprimirReservaciones
 *
 * @param
 * @return
 */
void Residente::imprimirReservaciones(){
    for(int i = 0; i < amenidadesReservadas.size(); i++){
        cout << amenidadesReservadas[i] << endl;
    }
}

/**
 * Metodo imprimirSaldo
 *
 * @param
 * @return
 */
void Residente::imprimirSaldo(){
    cout << "Saldo a actual: " << saldoAPagar << endl;
}

/**
 * Metodo imprimirAmenidadesReservadas
 *
 * @param int i
 * @return
 */
void Residente::imprimirAmenidadesReservadas(int i){
    cout << amenidadesReservadas[i] << endl;
}

#endif