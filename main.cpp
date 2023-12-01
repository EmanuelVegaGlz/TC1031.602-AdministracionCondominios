/*
 * Proyecto final TC1032.TC1031 
 * Programación de estructuras de datos y algoritmos fundamentales
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 *
 * Main
 */

#include "Amenidades.h"
#include "Residente.h"
#include "Arbol.h"
#include "Administracion.h"
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

/**
 * Funcion que valida que la opcion ingresada por el usuario este dentro de los parametros
 * 
 * @param opcion: opcion ingresada por el usuario
 * @param min: valor minimo que puede tener la opcion
 * @param max: valor maximo que puede tener la opcion
 * 
 * @return opcion: opcion validada
 */
int validaOpcion(int opcion, int min, int max){
    while(opcion < min || opcion > max){
        cout << "Opcion invalida, intente de nuevo: ";
        cin >> opcion;
    }
    return opcion;
}

/**
 * Función para combinar dos subarrays del vector res
 * El primer subarray es res[l..m]
 * El segundo subarray es res[m+1..r]
 */
void merge(vector<Residente*> &res, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crear arrays temporales
    vector<Residente*> left(n1);
    vector<Residente*> right(n2);

    // Copiar datos a los arrays temporales left[] y right[]
    for (int i = 0; i < n1; i++)
        left[i] = res[l + i];
    for (int j = 0; j < n2; j++)
        right[j] = res[m + 1 + j];

    // Combinar los arrays temporales de nuevo en res[l..r]
    int i = 0; // Índice inicial del primer subarray
    int j = 0; // Índice inicial del segundo subarray
    int k = l; // Índice inicial del array combinado
    while (i < n1 && j < n2) {
        if (left[i]->getNumCasa() <= right[j]->getNumCasa()) {
            res[k] = left[i];
            i++;
        } else {
            res[k] = right[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes de left[], si hay alguno
    while (i < n1) {
        res[k] = left[i];
        i++;
        k++;
    }

    // Copiar elementos restantes de right[], si hay alguno
    while (j < n2) {
        res[k] = right[j];
        j++;
        k++;
    }
}

/**
 * Función principal que implementa Merge Sort
 * @param res: vector de residentes a ordenar
 * @param l: índice izquierdo
 * @param r: índice derecho
 */
void mergeSortCasa(vector<Residente*> &res, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Ordenar las dos mitades
        mergeSortCasa(res, l, m);
        mergeSortCasa(res, m + 1, r);

        // Combinar las mitades ordenadas
        merge(res, l, m, r);
    }
}

// Función para llamar al Merge Sort
void sortResidentesPorCasa(vector<Residente*> &res) {
    int n = res.size();
    mergeSortCasa(res, 0, n - 1);
}

int main(){
    // Creacion de objetos de tipo Amenidades

    Amenidades* a1 = new Salon();
    Amenidades* a2 = new Alberca();
    Amenidades* a3 = new Gym();

    vector<Amenidades*> instalaciones = {a1, a2, a3};
    

    vector<Residente*> residentesVector;


    ifstream archivoCSV("residentes.csv");
    if (!archivoCSV) {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return 0;
    }

    string linea;
    // Lee y procesa cada línea del archivo CSV (O(N))
    while (getline(archivoCSV, linea)) {
        istringstream ss(linea);
        string campo;
        vector<string> campos;

        // Divide la línea en campos utilizando un delimitador (coma en este caso)
        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() >= 4) {
            try {
                // Convierte los campos necesarios al tipo adecuado
                int numCasa = stoi(campos[0]);
                string propietario = campos[1];
                string contacto = campos[2];
                float saldoAPagar = stof(campos[3]);

                // Crea un objeto Residente con los datos del CSV
                Residente *residente = new Residente(numCasa, propietario, contacto, saldoAPagar);

                // Agrega el objeto Residente al árbol AVL
                residentesVector.push_back(residente);
            } catch (const exception& e) {
                cerr << "Error al procesar línea: " << e.what() << endl;
            }
        }
    }
    archivoCSV.close();
    
    // O(N log N)
    sortResidentesPorCasa(residentesVector);

    // Estrucutra de datos de tipo BST O(N)
    BSTResidente *propietariosArbol = new BSTResidente(residentesVector);

    // Creacion de objetos de tipo Administracion
    Administracion admin = Administracion(instalaciones, propietariosArbol, 0);
    admin.setDeudas();
    admin.formatoImpresion();

    // Menu para que el usuario pueda interactuar con el programa
    int opcion;

    stringstream menu;
    cout << "\nBienvenido al sistema de administracion del condominio" << endl;
    menu << "Que desea hacer?" << endl
         << "1. Ver los residentes" << endl
         << "2. Dar de alta a un residente" << endl
         << "3. Registrar un pago de un residente" << endl
         << "4. Ver la deuda del condominio" << endl
         << "5. Ver el presupuesto del condominio" << endl
         << "6. Reservar una amenidad" << endl
         << "7. Ver la informacion de un residente" << endl
         << "8. Ver solo las reservaciones de un residente" << endl;

    cout << menu.str()
         << "\nOpcion (Solo numero): ";
    menu << "Otro Numero. Salir" << endl << endl
         << "Opcion: (Solo numero): ";
    cin >> opcion;

    admin.formatoImpresion();

    opcion = validaOpcion(opcion, 1, 8);

    while(opcion > 0 && opcion < 9){
string prop;
string contact;
        switch(opcion){
            case 1:
                admin.formatoImpresion();

                    cout << "Residentes en el sistema: " << endl << endl
                    << "Casa" << "\t" << "Nombre" << "\t" << "\t" << "\t" 
                    << "Saldo" << "\t" << "Amenidades reservadas" << endl;
                    cout << admin.ordenarResidentesCasa();

                break;
            

            case 2:
                cout << "\nDar de alta a un residente" << endl;
                int numCasa;
                float saldo;
                cout << "Numero de casa (Solo numero): ";
                cin >> numCasa;
                if (admin.buscarResidente(numCasa)){
                    cout << "Casa ya resgistrada!" << endl;
                    break;
                }
                else{
                    cout << "Nombre del propietario: ";
                    cin.ignore();
                    getline(cin, prop);
                    cout << "Contacto: ";
                    getline(cin, contact);
                    cout << "Saldo (Solo numero): ";
                    cin >> saldo;
                    Residente *nuevoResidente = new Residente(numCasa, prop, contact, saldo);
                    admin.agregarResidente(nuevoResidente);
                    residentesVector.push_back(nuevoResidente);

                    cout << "Residente agregado con exito!" << endl;

                    break;
                }

            case 3:
                cout << "\nRegistrar un pago de un residente" << endl;
                int numCasaPago;
                float pago;
                cout << "Numero de casa (Solo numero): ";
                cin >> numCasaPago;
                cout << "Pago (Solo numero): ";
                cin >> pago;
                admin.pagarSaldo(numCasaPago, pago);
                break;
                
            case 4:
                cout << "\nDeuda del condominio: " << admin.getDeudas() << endl;
                break;
            case 5:
                cout << "\nPresupuesto del condominio: " << admin.getPresupuesto() << endl;
                break;
            case 6:
                cout << "\nReservar una amenidad" << endl;
                int numCasaReserva;
                int amenidad;
                cout << "Numero de casa (Solo numero): ";
                cin >> numCasaReserva;
                cout << "Amenidad a reservar" << endl
                     << "1. Salon de fiestas" << endl
                     << "2. Alberca" << endl
                     << "3. Gimnasio" << endl << endl
                     << "Opcion (Solo numero): ";
                cin >> amenidad;
                validaOpcion(amenidad, 1, 3);
                admin.reservarAmenidad(numCasaReserva, amenidad - 1);
                
                break;
            case 7:
                cout << "\nVer la informacion de un residente" << endl;
                int numCasaInfo;
                cout << "Numero de casa (Solo numero): ";
                cin >> numCasaInfo;
                admin.imprimirResidentes(numCasaInfo);
                break;

            case 8:
                cout << "\nVer solo las reservaciones de un residente" << endl;
                int numCasaReservaciones;
                cout << "Numero de casa (Solo numero): ";
                cin >> numCasaReservaciones;
                admin.imprimirReservacionesResidente(numCasaReservaciones);
                break;
            case 9:
                cout << "\nVer los horarios disponibles de las amenidades" << endl;
                admin.imprimirAmenidades();
                break;
        }
        admin.formatoImpresion();
        cout << menu.str();
        cin >> opcion;
        admin.formatoImpresion();
    }

    // Guarda los datos de los residentes en un archivo CSV

    ofstream archivoSalida("residentes.csv");
    if (!archivoSalida) {
        cerr << "No se pudo abrir el archivo de salida." << endl;
        return 0;
    }

    for (int i = 0; i < residentesVector.size(); i++) {
        Residente *residente = residentesVector[i];
        archivoSalida << residente->getNumCasa() << ","
                      << residente->getPropietario() << ","
                      << residente->getContacto() << ","
                      << residente->getSaldoAPagar() << endl;
    }

    archivoSalida.close();

    return 0;
};