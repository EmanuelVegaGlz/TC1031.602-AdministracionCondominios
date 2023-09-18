# Programa de Administración de Condominio

#### Proyecto - TC1030.304
#### Profesor: Benjamín Valdés Aguirre
#### Nombre: Emanuel Josué Vega González
#### ID: A01710366

El objetivo de este programa es solucionar un problema en un condominio, lo que se trata de solucionar es tener un sistema en el cual se puedan hacer reservaciones de las amenidades y que las personas que tienen atrasos en pagos de mantenimiento o multas no puedan hacer reservaciones. También el objetivo es darlos de alta conforme se firme el contrato con la nueva administración. Posteriormente en futuros avances se planea incluir temas de gestión de proveedores y de pagos, así como seguimiento de facturas mes a mes. En este avance se incluye solo algunos residentes para ejemplificar el funcionamiento del programa.

## SICT0301: Evalúa los componentes

Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
### Selection Sort

- **Peor Caso**: O(n^2)

### Búsqueda Binaria

- **Peor Caso**: O(log n)

## SICT0302: Toma decisiones

Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

### Selection Sort

Se implementa para ordenar a los residentes por número de casa o por saldo a pagar. A pesar de tener una complejidad temporal considerablemente grande y que se pude considerar como ineficiente en cuento a tiempo de ejecución en grandes estructuras de datos, es adecuado para conjuntos de datos pequeños, como el vector de objetos Residente, que es un atributo de la clase Administracion, porque no tendrá mas de 100 elementos (casas). Adicional a que es fácil de implementar.

### Búsqueda Binaria

Se utiliza para buscar un residente en el vector de residentes, ordenado por número de casa. Este algoritmo es altamente eficiente y adecuado para búsquedas en conjuntos de datos ordenados.


## Explicación del Programa

El programa consta de tres clases principales:

1. **Amenidades**: Representa las amenidades disponibles en el condominio, como un salón de fiestas, una alberca y un gimnasio. Cada amenidad tiene horarios disponibles que los residentes pueden reservar.

2. **Residente**: Representa a un residente del condominio y almacena información como el número de casa, el nombre del propietario, el contacto y el saldo pendiente de pago. 

3. **Administracion**: Es la clase principal que gestiona todas las operaciones relacionadas con el condominio. Permite agregar amenidades, agregar residentes, realizar pagos, reservar amenidades, mostrar la deuda del condominio, ver el presupuesto, ordenar a los residentes y más.

## Funcionalidad

El programa permite a los usuarios realizar las siguientes acciones:

1. Ver la lista de residentes ordenados por número de casa o por saldo a pagar.
2. Agregar un nuevo residente al condominio, el programa pide los datos del residente, si se ingresa un numero de casa ya registrado el programa solicitara otro para poder incluirlo en el “sistema”.
3. Registrar un pago realizado por un residente, se busca la casa y si no se encentra se vuelve a solicitar un input.
4. Ver la deuda total del condominio.
5. Ver el presupuesto del condominio.
6. Reservar una amenidad, como el salón de fiestas, la alberca o el gimnasio.
7. Ver la información detallada de un residente, incluyendo su número de casa, nombre y saldo pendiente.
8. Ver los detalles de las reservaciones realizadas por un residente específico.

## Instrucciones para el Usuario

## Instrucciones
- Descargar los archivos y colocarlos en una misma carpeta.
- En consola ve a la ruta en donde se encuentran los archivos descomprimidos

**Opción 1:**

- Compilar el programa en terminal con: g++ main.cpp -o **programa** (*nombre deseado*)
- Correr el programa en consola con: **programa**.exe

**Opción 2:**

- Compilar el programa en terminal con: g++ main.cpp

- Correr el programa en consola con: a.exe

*Nota: Esto es usando el compilador g++ de MinGW en Windows.*

1. Al iniciar el programa, se mostrará un menú principal con varias opciones numeradas.
2. Ingresa **solo el número** correspondiente a la opción que desea ejecutar y presione Enter.
3. Siga las instrucciones en pantalla para completar la operación seleccionada.
4. El programa proporcionará retroalimentación y resultados de las operaciones realizadas.

## Restricciones para el Usuario

1. Las entradas de datos deben ser válidas y seguir el formato especificado en las instrucciones como el siguiente. *(solo numero)*.
2. No se ingresar valores negativos para el número de casa.
3. El saldo pendiente al ser negativo representa un saldo a favor
4. ingresar solo el tipo de dato que el programa solicita
