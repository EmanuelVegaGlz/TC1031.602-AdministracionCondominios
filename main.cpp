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
#include "Administracion.h"
# include <iostream>
# include <string>
# include <vector>
# include <sstream>
using namespace std;

int validaOpcion(int opcion, int min, int max){
    while(opcion < min || opcion > max){
        cout << "Opcion invalida, intente de nuevo: ";
        cin >> opcion;
    }
    return opcion;
}

int main(){
    // Creacion de objetos de tipo Amenidades
    Amenidades* a1 = new Salon();
    Amenidades* a2 = new Alberca();
    Amenidades* a3 = new Gym();

    vector<Amenidades*> instalaciones = {a1, a2, a3};
    

    // Creacion de objetos de tipo Residente
    Residente* r1 = new Residente(100, "Emanuel Vega", "55 1234 5678", 0);
    Residente* r2 = new Residente(22, "Juan Perez", "55 8765 4321", 2000);
    Residente* r3 = new Residente(58, "Maria Lopez", "55 2468 1357", 350);
    Residente* r4 = new Residente(5, "Pedro Sanchez", "55 1357 2468", 85);
    Residente* r5 = new Residente(61, "Ana Garcia", "55 4321 8765", 29000);
    Residente* r6 = new Residente(3, "Luis Hernandez", "55 5678 1234", -2500);
    Residente* r7 = new Residente(9, "Jose Martinez", "55 1234 5678", 0);

    vector<Residente*> propietarios = {r1, r2, r3, r4, r5, r6, r7};

    // Creacion de objetos de tipo Administracion
    Administracion admin = Administracion(instalaciones, propietarios, 0);

    admin.formatoImpresion();

    // Menu para que el usuario pueda interactuar con el programa
    int opcion;

    stringstream menu;
    menu << "\nBienvenido al sistema de administracion del condominio" << endl
         << "Que desea hacer?" << endl
         << "1. Ver los residentes" << endl
         << "2. Dar de alta a un residente" << endl
         << "3. Registrar un pago de un residente" << endl
         << "4. Ver la deuda del condominio" << endl
         << "5. Ver el presupuesto del condominio" << endl
         << "6. Reservar una amenidad" << endl
         << "7. Ver la informacion de un residente" << endl
         << "8. Ver solo las reservaciones de un residente" << endl
         << "9. Ver las amenidades reservadas y los horarios disponibles" << endl;

    cout << menu.str()
         << "\nOpcion: ";
    menu << "10. Salir" << endl << endl
         << "Opcion: ";
    cin >> opcion;

    admin.formatoImpresion();

    opcion = validaOpcion(opcion, 1, 9);

    while(opcion > 0 && opcion < 10){
string prop;
string contact;
        switch(opcion){
            case 1:
                cout << "Como quiere que se despliequen:" << endl
                     << "1. Por numero de casa" << endl
                     << "2. Por saldo a pagar" << endl << endl
                     << "Opcion: ";
                int orden;
                cin >> orden;
                orden = validaOpcion(orden, 1, 2);

                admin.formatoImpresion();

                if(orden == 1){
                    admin.ordenarResidentesCasa();
                    admin.imprimirResidentes();
                } else {
                    admin.ordenarResidentesSaldo();
                    admin.imprimirResidentes();
                }

                break;
            

            case 2:
                cout << "\nDar de alta a un residente" << endl;
                int numCasa;
                float saldo;
                cout << "Numero de casa: ";
                cin >> numCasa;
                cout << "Nombre del propietario: ";
                cin.ignore();
                getline(cin, prop);
                cout << "Contacto: ";
                getline(cin, contact);
                cout << "Saldo: ";
                cin >> saldo;
                admin.agregarResidente(new Residente(numCasa, prop, contact, saldo));

                cout << "Residente agregado con exito!" << endl;

                break;

            case 3:
                cout << "\nRegistrar un pago de un residente" << endl;
                int numCasaPago;
                float pago;
                cout << "Numero de casa: ";
                cin >> numCasaPago;
                cout << "Pago: ";
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
                cout << "Numero de casa: ";
                cin >> numCasaReserva;
                cout << "Amenidad a reservar" << endl
                     << "1. Salon de fiestas" << endl
                     << "2. Alberca" << endl
                     << "3. Gimnasio" << endl
                     << "Otro num. Salir" << endl << endl
                     << "Opcion: ";
                cin >> amenidad;
                if(amenidad > 0 && amenidad < 4){
                    admin.reservarAmenidad(numCasaReserva, amenidad);
                }
                break;
            case 7:
                cout << "\nVer la informacion de un residente" << endl;
                int numCasaInfo;
                cout << "Numero de casa: ";
                cin >> numCasaInfo;
                admin.imprimirResidentes(numCasaInfo);
                break;

            case 8:
                cout << "\nVer solo las reservaciones de un residente" << endl;
                int numCasaReservaciones;
                cout << "Numero de casa: ";
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

    return 0;
};
