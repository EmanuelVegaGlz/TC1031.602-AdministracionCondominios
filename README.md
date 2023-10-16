# Programa de Administración de Condominio

#### Proyecto - TC1030.304
#### Profesor: Benjamín Valdés Aguirre
#### Nombre: Emanuel Josué Vega González
#### ID: A01710366

El objetivo de este programa es solucionar un problema en un condominio, lo que se trata de solucionar es tener un sistema en el cual se puedan hacer reservaciones de las amenidades y que las personas que tienen atrasos en pagos de mantenimiento o multas no puedan hacer reservaciones. Posteriormente en futuros avances se planea incluir temas de gestión de proveedores y de pagos, así como seguimiento de facturas mes a mes. En este avance se incluye un archivo *.csv* en el que se incluyen a los 100 residentes del condominio.
# Competencias
## SICT0301: Evalúa los componentes

**Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.**
#### Selection Sort

- **Peor Caso**: O(n^2)

#### Búsqueda Binaria

- **Peor Caso**: O(log n)

**Hace un análisis de complejidad correcto y completo todas las estructuras de datos y cada uno de sus usos en el programa.**
*La estructura de datos principal se Encuentra en el archivo Árbol.h los encabezados de los métodos están a partir de la línea 234*
#### Constructor BSTResidente():
-	Complejidad de tiempo: O(1)
-	Complejidad de espacio: O(1)
Justificación: Es constante porque solo asigna que root apunta a nulo y no se recorre nada.
#### Constructor BSTResidente(vector<Residente*>):
-	Complejidad de tiempo: O(n * log(n))
-	Complejidad de espacio: O(n * log(n))
Justificación: La creación del árbol se hace al dividir recursivamente un vector ordenado por la mitad para construir un árbol balanceado. Ocurre n*log(n) porque se deben realizar operaciones logarítmicas en cada uno de los nodos del árbol.
#### Destructor ~BSTResidente():
-	Complejidad de tiempo: O(n)
-	Complejidad de espacio: O(1)
Justificación: Se manda a llamar el método *removeAll()*, que tiene que recorrer todo el árbol
#### bool empty() const:
-	Complejidad de tiempo: O(1)
-	Complejidad de espacio: O(1)
Justificación: Solo verifica si root es nulo.
#### void add(Residente*):
-	Complejidad de tiempo: O(log(n))
-	Complejidad de espacio: O(log(n))
Justificación:  Para agregar un residente, se recorre el árbol mediante “sub arboles”, por lo que llegar a las hojas implica un comportamiento logarítmico y que de igual forma en cada recursión se reduce el problema a la mitad (izquierda o derecha).
#### void remove(Residente*):
-	Complejidad de tiempo: O(log(n))
-	Complejidad de espacio:
Justificación: Para encontrar el nodo a eliminar el recorrido en el árbol de igual forma es logarítmico, para después eliminarlo.
#### void removeAll():
-	Complejidad de tiempo: O(n)
-	Complejidad de espacio: O(1)
Justificación: Debe recorrer todo el árbol para eliminar todos los nodos.
#### bool find(int) const:
-	Complejidad de tiempo: O(log(n))
-	Complejidad de espacio: O(log(n))
Justificación: Para verificar si ya se encuentra un residente, implica recorrer el árbol de manera recursiva, haciendo comparaciones, dependiendo si el numero de la casa es mayor o menor es si la siguiente llamada recursiva se va hacia la rama derecha o izquierda reduciendo el problema a la mitad en cada llamada.
#### string inorder() const:
-	Complejidad de tiempo: O(n)
-	Complejidad de espacio: O(n)
Justificación: Recorre todos los nodos del árbol para devolver el string con los datos de todos los residentes en el árbol. 
#### string preorder() const:
-	Complejidad de tiempo: O(n)
-	Complejidad de espacio: O(n)
Justificación: Recorre todos los nodos del árbol para devolver el string con los datos de todos los residentes en el árbol. 
#### float deudasResidentes():
-	Complejidad de tiempo: O(n)
-	Complejidad de espacio: O(n)
Justificación: Para calcular la suma de las deudas de todos los residentes se tiene que recorrer todo el árbol.
#### Residente* getResidente(int numCasa):
-	Complejidad de tiempo: O(log(n))
-	Complejidad de espacio: O(log(n))
Justificación: Buscar un residente por número de casa implica seguir un camino de búsqueda logarítmico en el árbol.

## SICT0302: Toma decisiones

**Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.**

#### Selection Sort

Se implementa para ordenar a los residentes por número de casa o por saldo a pagar. A pesar de tener una complejidad temporal considerablemente grande y que se pude considerar como ineficiente en cuento a tiempo de ejecución en grandes estructuras de datos, es adecuado para conjuntos de datos pequeños, como el vector de objetos Residente, que es un atributo de la clase Administracion, porque no tendrá mas de 100 elementos (casas). Adicional a que es fácil de implementar.

#### Búsqueda Binaria

Se utiliza para buscar un residente en el vector de residentes, ordenado por número de casa. Este algoritmo es altamente eficiente y adecuado para búsquedas en conjuntos de datos ordenados.

**Selecciona una estructura de datos adecuada al problema y lo usa correctamente.**
-	**Ordenación de Datos:** El Árbol de Búsqueda Binaria organiza los datos de forma jerárquica, al crearlo mediante el constructor que recibe un vector, garantiza que no sea un árbol fegenerado lo que permite una organización eficiente por número de casa de los residentes. Esto asegura que los residentes se almacenan en una estructura ordenada, haciendo que acceder a los objetos sea eficiente.
-	**Búsqueda Eficiente:** El BST proporciona un acceso rápido a los residentes mediante su número de casa. La complejidad de búsqueda es O(log(n)), lo que significa que incluso en conjuntos de datos grandes, se pueden buscar residentes de manera eficiente.
-	**Inserción y Eliminación Eficientes:** El BST permite agregar y eliminar residentes de manera eficiente. La complejidad de tiempo para estas operaciones es O(log(n))
-	**Modificar los atributos:** Con el método getResidente aprovecha la propiedad de los BST para buscar residentes por su número de casa de manera eficiente. Y devolver el apuntador al residente para reservar amenidades o pagar saldos.

### SICT0303: Implementa acciones científicas

**Implementa mecanismos para consultar información de las estructuras correctos.**
Se mandan a llamar en el main en las siguientes líneas:
-	139: Se manda a llamar el método ordenarResidentesCasa() de la clase Administracion. Que manda a llamar al método inorder() de la clase BSTResidente.
-	207: Se manda a llamar el método imprimirResidentes () de la clase Administracion. Que manda a llamar a los metodos find() y getResidente() de la clase BSTResidente.
-	215: Se manda a llamar el método imprimirReservacionesResidente() de la clase Administracion. Que manda a llamar al método find() y getResidente() de la clase BSTResidente.
**Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.**
Se incluye el archivo residentes.csv el cual contiene los atributos de 100 residentes, el manejo de este archivo se encuentra de la línea 54 a 93 del main.


# Explicación del Programa

El programa consta de tres clases principales:

1. **Amenidades**: Representa las amenidades disponibles en el condominio, como un salón de fiestas, una alberca y un gimnasio. Cada amenidad tiene horarios disponibles que los residentes pueden reservar.

2. **Residente**: Representa a un residente del condominio y almacena información como el número de casa, el nombre del propietario, el contacto y el saldo pendiente de pago. 

3. **Administracion**: Es la clase principal que gestiona todas las operaciones relacionadas con el condominio. Permite agregar amenidades, agregar residentes, realizar pagos, reservar amenidades, mostrar la deuda del condominio, ver el presupuesto, ordenar a los residentes y más.

# Funcionalidad

El programa permite a los usuarios realizar las siguientes acciones:

1. Ver la lista de residentes ordenados por número de casa.
2. Agregar un nuevo residente al condominio, el programa pide los datos del residente, si se ingresa un numero de casa ya registrado el programa solicitara otro para poder incluirlo en el “sistema”.
3. Registrar un pago realizado por un residente, se busca la casa y si no se encentra se vuelve a solicitar un input.
4. Ver la deuda total del condominio.
5. Ver el presupuesto del condominio.
6. Reservar una amenidad, como el salón de fiestas, la alberca o el gimnasio.
7. Ver la información detallada de un residente, incluyendo su número de casa, nombre y saldo pendiente.
8. Ver los detalles de las reservaciones realizadas por un residente específico.

# Instrucciones para el Usuario

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

# Restricciones para el Usuario

1. Las entradas de datos deben ser válidas y seguir el formato especificado en las instrucciones como el siguiente. *(solo numero)*.
2. No se ingresar valores negativos para el número de casa.
3. El saldo pendiente al ser negativo representa un saldo a favor
4. ingresar solo el tipo de dato que el programa solicita
