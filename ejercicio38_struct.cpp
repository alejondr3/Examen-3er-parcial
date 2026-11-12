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
    Nodo* nuevo = new Nodo{dato, nullptr};
    if (vacia(cola)) {
        cola.front = nuevo;
    } else {
        cola.rear->siguiente = nuevo;
    }
    cola.rear = nuevo;
}

// Devuelve false si no existe un elemento. No modifica dato en ese caso.
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

// Transfiere la propiedad de los nodos de B a A en O(1).
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
    cout << "[";
    for (const Nodo* actual = cola.front; actual != nullptr;
         actual = actual->siguiente) {
        cout << actual->dato;
        if (actual->siguiente != nullptr) cout << ", ";
    }
    cout << "]\n";
}

void liberar(Cola& cola) {
    int dato = 0;
    while (dequeue(cola, dato)) {}
}

void demostrarCaso(int caso, bool llenarA, bool llenarB) {
    Cola a;
    Cola b;
    inicializar(a);
    inicializar(b);
    if (llenarA) {
        enqueue(a, 1);
        enqueue(a, 2);
        enqueue(a, 3);
    }
    if (llenarB) {
        enqueue(b, 4);
        enqueue(b, 5);
    }
    cout << "Caso " << caso << "\nAntes:\nA = ";
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
}

int main() {
    demostrarCaso(1, true, true);
    demostrarCaso(2, false, true);
    demostrarCaso(3, true, false);
    demostrarCaso(4, false, false);
    return 0;
}
