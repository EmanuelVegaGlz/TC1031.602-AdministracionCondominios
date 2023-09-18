/*
 * Proyecto final TC1032.TC1031 
 * Programación de estructuras de datos y algoritmos fundamentales
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 *
 * Clase Amenidades  
 */

#ifndef AMENIDADES_H_
#define AMENIDADES_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


class Amenidades{
    protected:
        string nombre;
        vector<string> horarios;
        vector<bool> reservaciones;
        int capacidad;
        vector<int> asistentes;

    public:
        // Constructores
        Amenidades();
        Amenidades(string nom, vector<string> hor);

        // Getters
        string getNombre();
        int getCapacidad();
        int getAsistentes(int i);

        // Setters
        void setNombre(string nombre);

        // Metodos
        void horariosDisponibles();
        void cambioDia();
        int validaHorario(int i);
        int validaCapacidad(int i);
        virtual string reservarHorario(int index, int asis) = 0;
        virtual float getCosto() = 0;
};


/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Amenidades
 */
Amenidades::Amenidades(){
    nombre = "";
    horarios = {};
    reservaciones = {};
    capacidad = 0;
    asistentes = {};
}
/**
 * Constructor con parámetros
 *
 * @param string nombre, vector<string> horarios, int capacidad
 * @return Objeto de tipo Amenidades
 */
Amenidades::Amenidades(string nom, vector<string> hor){
    nombre = nom;
    horarios = hor;
    reservaciones = {};
    capacidad = 0;
    asistentes = {};
}

/**
 * Getter nombre
 *
 * @param
 * @return string nombre
 */
string Amenidades::getNombre(){
    return nombre;
}

/**
 * Getter capacidad
 *
 * @param
 * @return int capacidad
 */
int Amenidades::getCapacidad(){
    return capacidad;
}

/**
 * Getter asistentes
 *
 * @param int i
 * @return int asistentes
 */
int Amenidades::getAsistentes(int i){
    return asistentes[i];
}

/**
 * Setter nombre
 *
 * @param string nombre
 * @return
 */
void Amenidades::setNombre(string nom){
    nombre = nom;
}

/**
 * Método HorariosDisponibles
 *
 * @param
 * @return
 */
void Amenidades::horariosDisponibles(){
    cout << "Horarios disponibles: " << endl;
    for (int i = 0; i < horarios.size(); i++){
        if (reservaciones[i] == false){
            cout << i << ": " << horarios[i] << endl;
        }
    }
}

/**
 * Método CambioDia
 *
 * @param
 * @return
 */
void Amenidades::cambioDia(){
    for (int i = 0; i < reservaciones.size(); i++){
        reservaciones[i] = false;
    }
    asistentes = {};
}

/**
 * Método ValidaHorario
 *
 * @param int i
 * @return int i
 */
int Amenidades::validaHorario(int i){
    while (reservaciones[i] == true && i > horarios.size()){
    cout << "Horario no disponible, favor de eligir otro: " << endl;
    horariosDisponibles();
    cin >> i;
}
return i;
}

/**
 * Método ValidaCapacidad
 *
 * @param int asis
 * @return int asis
 */
int Amenidades::validaCapacidad(int asis){
    while (asis > capacidad){
        cout << "Capacidad exedida, maximo " << capacidad << endl
             << "Favor de intentar de nuevo: " << endl;
        cin >> asis;
    }
    return asis;
}


// clases hijas

class Alberca : public Amenidades{
    protected:
        int temperatura;

    public:
        // Constructores
        Alberca();

        // Getters
        int getTemperatura();

        // Setters
        void setTemperatura(int temperatura);
        string reservarHorario(int index, int asis);
        float getCosto(){return 0;};
};


/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Alberca
 */
Alberca::Alberca(){
    nombre = "Alberca";
    horarios = {"8:00 AM", "9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM",
                "1:00 PM", "2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM",
                "6:00 PM", "7:00 PM", "8:00 PM"};
    reservaciones = {};
    capacidad = 10;
    asistentes = {};
    temperatura = 28;
}


/**
 * Getter temperatura
 *
 * @param
 * @return int temperatura
 */
int Alberca::getTemperatura(){
    return temperatura;
}

/**
 * Setter temperatura
 *
 * @param int temperatura
 * @return
 */
void Alberca::setTemperatura(int temp){
    temperatura = temp;
}

/**
 * Método ReservarHorario
 *
 * @param int index
 * @return
 */
string Alberca::reservarHorario(int index, int asis){
    index = validaHorario(index);
    asis = validaCapacidad(asis);

    asistentes[index] = asis;
    reservaciones[index] = true;

    stringstream detalle;
    detalle << "Amenidad: " << nombre << endl
            << "Horario: " << horarios[index] << endl
            << "Asistentes: " << asistentes[index] << endl
            << "Temperatura del agua: " << temperatura << "°" << endl;
    
    cout << "Reservacion exitosa" << endl;
    return detalle.str();
} 

class Gym : public Amenidades{
    public:
        // Constructores
        Gym();

        string reservarHorario(int index, int asis);
        float getCosto(){return 0;};
};

/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Gym
 */
Gym::Gym(){
    nombre = "Gym";
    horarios = {"6:00 AM", "7:00 AM", "8:00 AM", "9:00 AM", "10:00 AM",
                "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM",
                "4:00 PM", "5:00 PM", "6:00 PM", "7:00 PM", "8:00 PM",
                "9:00 PM", "10:00 PM"};
    reservaciones = {};
    capacidad = 6;
    asistentes = {};
}

/**
 * Método ReservarHorario
 *
 * @param int index
 * @return
 */
string Gym::reservarHorario(int index, int asis){
    index = validaHorario(index);
    asis = validaCapacidad(asis);

    asistentes[index] = asis;
    reservaciones[index] = true;
    
    stringstream detalle;
    detalle << "Amenidad: " << nombre << endl
            << "Horario: " << horarios[index] << endl
            << "Asistentes: " << asistentes[index] << endl;

    cout << "Reservacion exitosa" << endl;

    return detalle.str();
}

class Salon : public Amenidades{
    protected:
        float costo;
        string fecha;

    public:
        // Constructores
        Salon();

        // Getters
        float getCosto();
        string getFecha();

        string reservarHorario(int horaInicio, int asis);
};

/**
 * Constructor por default
 *
 * @param
 * @return Objeto de tipo Salon
 */
Salon::Salon(){
    nombre = "Salon";
    horarios = {"8:00 AM", "9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM",
                "1:00 PM", "2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM",
                "6:00 PM", "7:00 PM", "8:00 PM", "9:00 PM", "10:00 PM"
                "11:00 PM", "12:00 AM"};
    reservaciones = {};
    capacidad = 50;
    asistentes = {};
    costo = 500;
    fecha = "01/01/2021";
}

/**
 * Getter costo
 *
 * @param
 * @return float costo
 */
float Salon::getCosto(){
    return costo;
}

/**
 * Getter fecha
 *
 * @param
 * @return string fecha
 */
string Salon::getFecha(){
    return fecha;
}

/**
 * Método ReservarHorario
 *
 * @param int horaInicio, int fin, int asis, string date
 * @return
 */
string Salon::reservarHorario(int horaInicio, int asis){
    horaInicio = validaHorario(horaInicio);
            cout << "Favor de elegir el indice de la hora de fin: " << endl;
        int fin;
        cin >> fin;
        fin = validaHorario(fin);

        cout << "Favor de ingresar la fecha de la reservacion: " << endl;
        string date;
        getline(cin, date);

    asis = validaCapacidad(asis);

    for (int i = horaInicio; i < fin; i++){
        asistentes[i] = asis;
        reservaciones[i] = true;
    }
    fecha = date;

    stringstream detalle;
    detalle << "Amenidad: " << nombre << endl
            << "Horario: " << horarios[horaInicio] << " - " << horarios[fin] << endl
            << "Asistentes: " << asistentes[horaInicio] << endl
            << "Costo: " << costo << endl
            << "Fecha: " << fecha << endl;

    cout << "Reservacion exitosa" << endl;

    return detalle.str();
}

#endif