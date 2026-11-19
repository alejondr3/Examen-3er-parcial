#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Cola {
    Nodo* front;
    Nodo* rear;
};

void inicializar(Cola& cola) {
    cola.front = nullptr;
    cola.rear = nullptr;
}

bool vacia(const Cola& cola) {
    return cola.front == nullptr;
}

void enqueue(Cola& cola, int dato) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = dato;
    nuevo->siguiente = nullptr;
    if (vacia(cola)) {
        cola.front = nuevo;
    } else {
        cola.rear->siguiente = nuevo;
    }
    cola.rear = nuevo;
}

// Consulta el primer dato sin sacarlo.
bool front(const Cola& cola, int& dato) {
    if (vacia(cola)) return false;
    dato = cola.front->dato;
    return true;
}

bool dequeue(Cola& cola, int& dato) {
    if (vacia(cola)) return false;
    Nodo* eliminado = cola.front;
    dato = eliminado->dato;
    cola.front = eliminado->siguiente;
    if (vacia(cola)) cola.rear = nullptr;
    delete eliminado;
    return true;
}

// Une el ultimo nodo de A con el primero de B.
void concatenate(Cola& a, Cola& b) {
    if (&a == &b || vacia(b)) return;
    if (vacia(a)) {
        a.front = b.front;
    } else {
        a.rear->siguiente = b.front;
    }
    a.rear = b.rear;
    b.front = nullptr;
    b.rear = nullptr;
}

void mostrar(const Cola& cola) {
    const Nodo* aux = cola.front;
    cout << "[";
    while (aux != nullptr) {
        cout << aux->dato;
        if (aux->siguiente != nullptr) {
            cout << ", ";
        }
        aux = aux->siguiente;
    }
    cout << "]\n";
}

void liberar(Cola& cola) {
    int dato = 0;
    while (dequeue(cola, dato)) {}
}

// Primero se pide la cantidad y despues cada dato.
bool cargarCola(Cola& cola, char nombre) {
    int cantidad;
    int dato;

    cout << "\nCola " << nombre << "\n";
    do {
        cout << "Cantidad de elementos (0 para dejarla vacia): ";
        if (!(cin >> cantidad)) {
            return false;
        }
        if (cantidad < 0) {
            cout << "La cantidad no puede ser negativa.\n";
        }
    } while (cantidad < 0);

    for (int i = 0; i < cantidad; i++) {
        cout << "Dato " << i + 1 << ": ";
        if (!(cin >> dato)) {
            return false;
        }
        enqueue(cola, dato);
    }
    return true;
}

int main() {
    Cola a;
    Cola b;
    inicializar(a);
    inicializar(b);
    cout << "Concatenacion de dos colas\n";
    if (!cargarCola(a, 'A') || !cargarCola(b, 'B')) {
        cout << "\nNo se completo la carga. Ingrese solamente numeros enteros.\n";
        liberar(a);
        liberar(b);
        return 1;
    }
    cout << "\nAntes:\nA = ";
    mostrar(a);
    cout << "B = ";
    mostrar(b);
    concatenate(a, b);
    cout << "Despues de concatenate(A, B):\nA = ";
    mostrar(a);
    cout << "B = ";
    mostrar(b);
    int dato = 0;
    if (front(a, dato)) cout << "Frente de A: " << dato << "\n";
    else cout << "A no tiene frente: esta vacia.\n";
    cout << "Extraccion FIFO de A:";
    while (dequeue(a, dato)) cout << " " << dato;
    cout << "\n\n";
    liberar(a);
    liberar(b);
    return 0;
}
