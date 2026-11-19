# Ejercicio 38: concatenar dos colas

Hay dos versiones del mismo ejercicio:

- `ejercicio38_struct.cpp`: usa estructuras y funciones.
- `ejercicio38_class.cpp`: usa una clase con sus metodos.

Cada archivo se compila por separado porque tiene su propio `main`.

## Como usarlo

1. Ingresar cuantos datos tendra la cola A.
2. Ingresar los numeros enteros de A.
3. Hacer lo mismo con B.

Si la cantidad es 0, la cola queda vacia. Si es negativa, se vuelve a pedir.
Se deben ingresar numeros enteros. La lectura se hace directamente con `cin`; si falla o faltan datos, el programa termina y libera los nodos.

El programa muestra las colas antes y despues de unirlas. Al final saca los datos de A en el orden en que entraron (FIFO).

## Como se unen

Si B esta vacia, no hay nada que agregar. Si A esta vacia, toma los punteros de B.
Si las dos tienen datos, el ultimo nodo de A se conecta con el primero de B.
Luego se actualiza el final de A y los punteros de B quedan en `nullptr`.

Por ejemplo:

```text
Antes:
A = [1, 2]
B = [3, 4]

Despues:
A = [1, 2, 3, 4]
B = []
```

La concatenacion es O(1) porque solo cambia punteros, sin recorrer las colas.
Los nodos se eliminan con `delete` al sacarlos. En la version con clase, el destructor libera los que queden.

## Compilar

```powershell
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror ejercicio38_struct.cpp -o ejercicio38_struct.exe
./ejercicio38_struct.exe

g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror ejercicio38_class.cpp -o ejercicio38_class.exe
./ejercicio38_class.exe
```

Ambas versiones compilan sin advertencias y se probaron con 9 casos: las cuatro combinaciones de colas vacias o con datos, valores negativos y repetidos, cantidad negativa, datos separados por espacios, texto y entrada incompleta.
