/*
 * Proyecto final TC1032.TC1031 
 * Programación de estructuras de datos y algoritmos fundamentales
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 *
 * Clase Administracion
 */

#ifndef ADMINISTRACION_H_
#define ADMINISTRACION_H_

#include "Amenidades.h"
#include "Residente.h"
#include "Arbol.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Administracion{
    private:
        vector<Amenidades*> amenidad;
        BSTResidente *residente;
        float deudasResidentes;
        float presupuesto;

    public:
        // Constructores
        Administracion();
        Administracion(vector<Amenidades*> amen, BSTResidente *resi, float pres);

        // Getters
        float getDeudas();
        float getPresupuesto();
        BSTResidente getResidentes();

        // Setters
        void setDeudas();

        //Metodos
        void agregarAmenidad(Amenidades* amenidad);
        void agregarResidente(Residente* residente);
        string ordenarResidentesCasa();
        void reservarAmenidad(int numCasa, int iAm);
        void pagarSaldo(int numCasa, float pago);
        bool buscarResidente(int numCasa);

        void imprimirAmenidades();
        void imprimirResidentes(int Casa);
        void imprimirReservacionesResidente(int i);
        void formatoImpresion();   
};

/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Administracion
 */
Administracion::Administracion(){
    amenidad = {};
    residente = new BSTResidente();
    deudasResidentes = 0;
    presupuesto = 0;
}

/**
 * Constructor con parametros
 *
 * @param vector<Amenidades*> amen
 * @param AVL<Residente*> resi
 * @return Objeto de tipo Administracion
 */
Administracion::Administracion(vector<Amenidades*> amen, BSTResidente *resi, float pres){
    amenidad = amen;
    residente = resi;
    presupuesto = pres;
    deudasResidentes = 0;
}

/**
 * Metodo agregarAmenidad
 *
 * @param Amenidades* amenidad
 * @return
 */
void Administracion::agregarAmenidad(Amenidades* ameni){
    amenidad.push_back(ameni);
}

/**
 * Metodo agregarResidente
 *
 * @param Residente* residente
 * @return
 */
void Administracion::agregarResidente(Residente * resi){
    residente->add(resi);
}

/**
 * Metodo getDeudas
 *
 * @param
 * @return float deudasResidentes
 */
float Administracion::getDeudas(){
    return deudasResidentes;
}

/**
 * Metodo getPresupuesto
 *
 * @param
 * @return float presupuesto
 */
float Administracion::getPresupuesto(){
    return presupuesto;
}

/**
 * Metodo getResidentes
 *
 * @param
 * @return BSTResidente residente
 */
BSTResidente Administracion::getResidentes(){
    return *residente;
}

/**
 * Metodo setDeudas: Calcula la deudasResidentes, en base a los saldos de cada residente en el AVL
 *
 * @param
 * @return
 */
void Administracion::setDeudas(){
    deudasResidentes = residente->deudasResidentes();
}

/**
 * Metodo ordenarResidentesCasa
 * 
 * @param
 * @return string inorderPorCasa
 */
string Administracion::ordenarResidentesCasa() {
    return residente->inorder();
}


/**
 * Metodo reservarAmenidad
 *
 * @param int numCasa
 * @param int iAm
 * @param int iHorario
 * @param int asis
 * @return
 */
void Administracion::reservarAmenidad(int numCasa, int iAm){
    if(residente->find(numCasa) == false){
        cout << "Numero de casa no encontrado." << endl;
        return;
    }

    Residente * residenteModificado = residente->getResidente(numCasa);
    if (residenteModificado->getSaldoAPagar() > 0){
        cout << "Favor de pagar el adeudo para reservar" << endl;
    }

    else {
        cout << "Los horarios disponibles de " 
             << amenidad[iAm]->getNombre() << " son: " << endl;
        amenidad[iAm]->horariosDisponibles();

        cout << "Favor de ingresar el numero de asistentes (Solo numero): " << endl;
        int asis;
        cin >> asis;

        cout << "Favor de elegir el indice del horario (Solo numero): " << endl;
        int iHorario;
        cin >> iHorario;

        string reserva = amenidad[iAm]->reservarHorario(iHorario, asis);

        residenteModificado-> setAmenidadesReservadas(reserva);
        setDeudas();
    }
}


/**
 * Metodo pagarSaldo
 *
 * @param int numCasa
 * @param float pago
 * @return
 */
void Administracion::pagarSaldo(int numCasa, float pago){
    if(residente->find(numCasa) == false){
        cout << "Numero de casa no encontrado." << endl;
        return;
    }
    Residente * residenteModificado = residente->getResidente(numCasa);
    residenteModificado->pagarSaldo(pago);
    setDeudas();
}

/**
 * Metodo buscarResidente
 *
 * @param int numCasa
 * @return bool
 */
bool Administracion::buscarResidente(int numCasa){
    return residente->find(numCasa);
}

/**
 * Metodo imprimirAmenidades
 *
 * @param
 * @return
 */
void Administracion::imprimirAmenidades(){
    for (int i = 0; i < amenidad.size(); i++){
        cout << i << ". " << amenidad[i]->getNombre() << endl;
    }
}

/**
 * Metodo imprimirResidente solo los datos de una casa
 *
 * @param int Casa
 * @return
 */
void Administracion::imprimirResidentes(int casa){
    if(residente->find(casa) == false){
        cout << "Numero de casa no encontrado." << endl;
        return;
    }

    Residente * residenteModificado = residente->getResidente(casa);
    
    cout << "Informacion del residente: " << endl << endl
         << "Numero de casa: " << residenteModificado->getNumCasa() << endl
         << "Nombre: " << residenteModificado->getNombre() << endl
         << "Saldo: " << residenteModificado->getSaldoAPagar() << endl
         << "Amenidades reservadas: " << endl
         << residenteModificado->getTamAmenidadesReservadas();
    cout << endl;
}

/**
 * Metodo imprimirReservacionesResidente
 *
 * @param int i
 * @return
 */
void Administracion::imprimirReservacionesResidente(int casa){
    if(residente->find(casa) == false){
        cout << "Numero de casa no encontrado." << endl;
        return;
    }

    Residente * residenteModificado = residente->getResidente(casa);
    residenteModificado->imprimirReservaciones();
}

/**
 * Metodo formatoImpresion
 *
 * @param
 * @return
 */
void Administracion::formatoImpresion(){
    cout << "--------------------------------------------------------"<< endl;
    }

#endif