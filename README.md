# Programa de Administración de Condominio
El objetivo de este programa es solucionar un problema en un condominio, lo que se trata de solucionar es tener un sistema en el cual se puedan hacer reservaciones de las amenidades y que las personas que tienen atrasos en pagos de mantenimiento o multas no puedan hacer reservaciones. También el objetivo es darlos de alta conforme se firme el contrato con la nueva administración. Posteriormente en futuros avances se planea incluir temas de gestión de proveedores y de pagos, así como seguimiento de facturas mes a mes. En este avance se incluye solo algunos residentes para ejemplificar el funcionamiento del programa.
## Análisis de Complejidad de los Algoritmos de Ordenamiento


El programa implementa dos algoritmos de ordenamiento: **Selection Sort** y **Búsqueda Binaria**. A continuación, se proporciona un análisis de complejidad para cada uno de estos algoritmos:

### Selection Sort

- **Peor Caso**: O(n^2)

Se implementa para ordenar a los residentes por número de casa o por saldo a pagar. A pesar de tener una complejidad temporal considerablemente grande y que se pude considerar como ineficiente en cuento a tiempo de ejecución en grandes estructuras de datos, es adecuado para conjuntos de datos pequeños, como el vector de objetos Residente que es un atributo de la clase Administracion, adicional a que es fácil de implementar.

### Búsqueda Binaria

- **Peor Caso**: O(log n)

Se utiliza para buscar un residente en el vector de residentes, ordenado por número de casa. Este algoritmo es altamente eficiente y adecuado para búsquedas en conjuntos de datos ordenados.
