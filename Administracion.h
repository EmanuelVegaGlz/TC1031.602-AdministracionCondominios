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
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Administracion{
    private:
        vector<Amenidades*> amenidad;
        vector<Residente*> residente;
        float deudasResidentes;
        float presupuesto;

    public:
        // Constructores
        Administracion();
        Administracion(vector<Amenidades*> amen, vector<Residente*> resi, float pres);

        // Getters
        float getDeudas();
        float getPresupuesto();
        vector<Residente*> getResidentes();

        // Setters
        void setDeudas();

        //Metodos
        void agregarAmenidad(Amenidades* amenidad);
        void agregarResidente(Residente* residente);
        void ordenarResidentesCasa();
        void ordenarResidentesSaldo();

        int busquedaBinaria(int numCasa); 
        int validaBusqueda(int resBusqueda);
        void reservarAmenidad(int numCasa, int iAm);
        void reservarSalon(int numCasa);
        void pagarSaldo(int numCasa, float pago);

        void imprimirAmenidades();
        void imprimirResidentes();
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
    residente = {};
    deudasResidentes = 0;
    presupuesto = 0;
}

/**
 * Constructor con parametros
 *
 * @param vector<Amenidades*> amen
 * @param vector<Residente*> resi
 * @return Objeto de tipo Administracion
 */
Administracion::Administracion(vector<Amenidades*> amen, vector<Residente*> resi, float pres){
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
void Administracion::agregarResidente(Residente* resi){
    ordenarResidentesCasa();
    int nCasa(resi->getNumCasa());
    int casaValida = busquedaBinaria(nCasa);
    while (casaValida != -1){
        cout << "Numero de casa ya registrado, favor de ingresar otro: " << endl;
        cin >> nCasa;
        resi->setNumCasa(nCasa);
        casaValida = busquedaBinaria(nCasa);

    }

    residente.push_back(resi);
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
 * @return vector<Residente*> residente
 */
vector<Residente*> Administracion::getResidentes(){
    return residente;
}

/**
 * Metodo setDeudas
 *
 * @param
 * @return
 */
void Administracion::setDeudas(){
    float aux;
    for (int i = 0; i < residente.size(); i++){
        if (residente[i]->getSaldoAPagar() > 0){
            aux += residente[i]->getSaldoAPagar();   
        }
        deudasResidentes = aux;
    }
}


/**
 * Metodo ordenarResidentesCasa con Selection Sort
 * 
 * @param
 * @return
 */
void Administracion::ordenarResidentesCasa() {
    int pos;
    for (int i = residente.size() - 1; i > 0; i--) {
        pos = 0;
        for (int j = 1; j <= i; j++) {
            if (residente[j]->getNumCasa() > residente[pos]->getNumCasa()) {
                pos = j;
            }
        }
        if (pos != i) {
            Residente* aux = residente[i];
            residente[i] = residente[pos];
            residente[pos] = aux;
        }
    }
}

/**
 * Metodo ordenarResidentesSaldo con Selection Sort
 *
 * @param
 * @return
 */
void Administracion::ordenarResidentesSaldo() {
    int pos;
    for (int i = residente.size() - 1; i > 0; i--) {
        pos = 0;
        for (int j = 1; j <= i; j++) {
            if (residente[j]->getSaldoAPagar() < residente[pos]->getSaldoAPagar()) {
                pos = j;
            }
        }
        if (pos != i) {
            Residente* aux = residente[i];
            residente[i] = residente[pos];
            residente[pos] = aux;
        }
    }
}

/**
 * Metodo busquedaBinaria
 *
 * @param int numCasa
 * @return int i
 */
int Administracion::busquedaBinaria(int numCasa){
    int low = 0;
    int high = residente.size() - 1;
    int mid;

    while (low <= high){
        mid = (low + high) / 2;
        if (residente[mid]->getNumCasa() == numCasa){
            return mid;
        } else if (residente[mid]->getNumCasa() > numCasa){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

/**
 * Metodo validaBusqueda
 *
 * @param int resBusqueda
 * @return int resBusqueda
 */
int Administracion::validaBusqueda(int resBusqueda){
    while (resBusqueda == -1){
        cout << "Numero de casa no encontrado, favor de ingresar otro: " << endl;
        cin >> resBusqueda;
        resBusqueda = busquedaBinaria(resBusqueda);
    }
    return resBusqueda;
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
    ordenarResidentesCasa();
    int iRes = busquedaBinaria(numCasa);
    iRes = validaBusqueda(iRes);

    if (residente[iRes]->getSaldoAPagar() > 0){
        cout << "Favor de pagar el adeudo para reservar" << endl;
    }

    else {
        cout << "Los horarios disponibles de " 
             << amenidad[iAm]->getNombre() << " son: " << endl;
        amenidad[iAm]->horariosDisponibles();

        cout << "Favor de ingresar el numero de asistentes: " << endl;
        int asis;
        cin >> asis;

        cout << "Favor de elegir el indice del horario: " << endl;
        int iHorario;
        cin >> iHorario;

        string reserva = amenidad[iAm]->reservarHorario(iHorario, asis);

        residente[iRes]-> setAmenidadesReservadas(reserva);
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
    int iRes = busquedaBinaria(numCasa);
    iRes = validaBusqueda(iRes);

    residente[iRes]->pagarSaldo(pago);
    deudasResidentes -= pago;
    setDeudas();
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
 * Metodo imprimirResidentes
 *
 * @param
 * @return
 */
void Administracion::imprimirResidentes(){
    cout << "Residentes en el sistema: " << endl << endl
         << "Casa" << "\t" << "Nombre" << "\t" << "\t" << "\t" << "Saldo"
         << "\t" << "Amenidades reservadas" << endl;
    for (int i = 0; i < residente.size(); i++){
        cout << residente[i]->getNumCasa() << "\t" << residente[i]->getNombre()
             << "\t" << "\t" << residente[i]->getSaldoAPagar() << "\t" 
             << residente[i]->getTamAmenidadesReservadas() << endl;
    }
}


/**
 * Metodo imprimirResidente solo los datos de una casa
 *
 * @param int Casa
 * @return
 */
void Administracion::imprimirResidentes(int Casa){
    int iRes = busquedaBinaria(Casa);
    iRes = validaBusqueda(iRes);
    
    cout << "Informacion del residente: " << endl << endl
         << "Numero de casa: " << residente[iRes]->getNumCasa() << endl
         << "Nombre: " << residente[iRes]->getNombre() << endl
         << "Saldo: " << residente[iRes]->getSaldoAPagar() << endl
         << "Amenidades reservadas: " << endl
         << residente[iRes]->getTamAmenidadesReservadas();
    cout << endl;
}

/**
 * Metodo imprimirReservacionesResidente
 *
 * @param int i
 * @return
 */
void Administracion::imprimirReservacionesResidente(int i){
    int iRes = busquedaBinaria(i);
    iRes = validaBusqueda(iRes);
    residente[iRes]->imprimirReservaciones();
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