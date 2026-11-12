# Ejercicio 38: concatenación O(1) de colas enlazadas

Solución en C++ del ejercicio 38, página 41 del práctico. Cada programa usa únicamente `#include <iostream>` y `using namespace std;`.

- `ejercicio38_struct.cpp`: modelo procedural con `struct Nodo`, `struct Cola` y funciones externas.
- `ejercicio38_class.cpp`: modelo con `class Cola`, nodos y punteros privados, constructor, destructor y métodos públicos.

Cada archivo es un programa independiente con su propio `main`. Se deben compilar por separado. Al ejecutarlos muestran los cuatro casos del enunciado y extraen los elementos en orden FIFO. Para cambiar los ejemplos, modificar las llamadas a `enqueue` en `demostrarCaso`.

## Compilar y ejecutar

Con GCC/MinGW, desde la carpeta del repositorio:

```powershell
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror ejercicio38_struct.cpp -o ejercicio38_struct.exe
./ejercicio38_struct.exe

g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror ejercicio38_class.cpp -o ejercicio38_class.exe
./ejercicio38_class.exe
```

## Modelo con struct

```text
Nodo
  dato: int
  siguiente: Nodo*

Cola
  front: Nodo*  --> primer nodo
  rear: Nodo*   --> último nodo

Funciones externas:
  inicializar(cola), vacia(cola), enqueue(cola, dato)
  front(cola, dato), dequeue(cola, dato)
  concatenate(a, b), mostrar(cola), liberar(cola)
```

Inicializar cada cola antes de usarla y llamar a `liberar` al terminar. No copiar una `Cola` mediante asignación ni pasarla por valor: los punteros son propietarios de sus nodos. Las funciones reciben referencias para operar sobre la cola original.

## Modelo con class

```text
Cola
  privados:
    Nodo { dato: int, siguiente: Nodo* }
    frente: Nodo*  --> equivale a front
    final: Nodo*   --> equivale a rear
  públicos:
    Cola(), ~Cola(), vacia()
    enqueue(dato), front(dato), dequeue(dato)
    concatenate(b), mostrar(), liberar()
```

Se usa `frente` como nombre del puntero para permitir que el método se llame `front`. El constructor crea una cola vacía y el destructor libera todos los nodos restantes. Las copias están deshabilitadas para evitar que dos objetos intenten liberar los mismos nodos.

## Operaciones

`enqueue` agrega al final. `front` consulta el primer valor sin retirarlo. `dequeue` retira el primer nodo y devuelve su valor. Estas dos últimas devuelven `false` si la cola está vacía y conservan el valor del argumento de salida; así no se confunde un dato válido, como `-1`, con un error.

En struct se llama `concatenate(a, b)`; en class, `a.concatenate(b)`. La operación transfiere los nodos de B a A:

1. Si A y B son la misma cola, no hace cambios para evitar un ciclo.
2. Si B está vacía, no hace cambios.
3. Si A está vacía, su frente pasa a apuntar al frente de B.
4. Si A tiene nodos, el siguiente de su último nodo apunta al frente de B.
5. El final de A pasa a ser el final de B y ambos punteros de B quedan en `nullptr`.

No se recorren, copian, crean ni eliminan nodos durante la concatenación.

## Diagramas de memoria

Caso normal, antes:

```text
A.front --> [1|*] --> [2|*] --> [3|null] <-- A.rear
B.front --> [4|*] --> [5|null]           <-- B.rear
```

Estado intermedio: se ejecutó `A.rear->siguiente = B.front`. B aún conserva sus punteros; este es un estado transitorio dentro de la función:

```text
A.front --> [1|*] --> [2|*] --> [3|*] --> [4|*] --> [5|null]
                              ^          ^          ^
                            A.rear     B.front    B.rear
```

Después de actualizar el final de A y anular los punteros de B:

```text
A.front --> [1|*] --> [2|*] --> [3|*] --> [4|*] --> [5|null] <-- A.rear
B.front = nullptr
B.rear  = nullptr
```

Caso borde: A vacía y B con un nodo:

```text
Antes:   A.front = A.rear = nullptr
         B.front --> [7|null] <-- B.rear

Después: A.front --> [7|null] <-- A.rear
         B.front = B.rear = nullptr
```

En este caso se cambian ambos extremos de A; no se accede al antiguo `A.rear`, que es nulo. En class los mismos dibujos se interpretan con `frente` y `final`.

## Invariantes y memoria

- Una cola está vacía si y solo si ambos extremos son `nullptr`.
- En una cola no vacía, el final apunta al último nodo y su `siguiente` es `nullptr`.
- Con un único nodo, ambos extremos apuntan al mismo nodo.
- Cada nodo pertenece a una sola cola al terminar cada operación.
- Al retirar el último nodo también se anula el puntero al final.
- Cada `enqueue` reserva un nodo. Cada `dequeue` libera exactamente el nodo retirado.
- Tras concatenar, A es propietaria de todos los nodos transferidos. Anular B evita accesos compartidos y dobles liberaciones.
- `liberar` es iterativa y puede repetirse sobre una cola vacía. En class también la invoca el destructor.

## Complejidad

| Operación | Tiempo | Memoria auxiliar |
|---|---|---|
| Inicializar / constructor | O(1) | O(1) |
| vacia / front | O(1) | O(1) |
| enqueue | O(1) | O(1), con un nodo nuevo |
| dequeue | O(1) | O(1) |
| concatenate | O(1) | O(1), sin reservas |
| mostrar | O(n) | O(1) |
| liberar / destructor | O(n) | O(1) |

La cola completa ocupa O(n) memoria. Mostrar el resultado tarda O(n), aunque concatenar tarda O(1).

## Evidencia de verificación

Verificado con GCC 15.1.0, C++11 y `-Wall -Wextra -Wpedantic -Werror`: ambos programas compilan sin errores ni advertencias y producen salidas idénticas.

| Caso | A después | B después |
|---|---|---|
| A=[1,2,3], B=[4,5] | [1,2,3,4,5] | [] |
| A=[], B=[4,5] | [4,5] | [] |
| A=[1,2,3], B=[] | [1,2,3] | [] |
| A=[], B=[] | [] | [] |

Pruebas adicionales automatizadas realizadas durante la preparación:

- Consultar y extraer en vacío devuelve `false` sin cambiar el argumento de salida.
- Valores negativos, cero y repetidos conservan su orden.
- Reutilizar A y B después de vaciarlas o transferir sus nodos funciona correctamente.
- Autoconcatenar una cola vacía o de un nodo conserva su estado.
- Concatenaciones sucesivas después de una extracción parcial conservan FIFO.
- Transferir y extraer 10.000 nodos conserva la secuencia completa.
- Un contador de reservas y liberaciones comprobó que `concatenate` no ejecuta ninguna de ellas. Cada versión terminó con 10.022 reservas y 10.022 liberaciones, sin fallos en las comprobaciones. También se comprobó la liberación automática de nodos restantes por el destructor de class.

## Respuestas para la defensa

**¿Qué punteros permiten O(1)?** El final de A y ambos extremos de B permiten conectar las colas sin buscar el último nodo.

**¿Qué ocurre con rear si A está vacía?** Se asigna el final de B al final de A, y también se transfiere el frente de B.

**¿Por qué se anulan los punteros de B?** Porque sus nodos ahora pertenecen a A. B debe quedar vacía y poder reutilizarse o destruirse de forma segura.
