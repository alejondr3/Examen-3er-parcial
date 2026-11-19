#include <iostream>
using namespace std;

class Cola {
private:
    class Nodo {
    public:
        int dato;
        Nodo* siguiente;
    };

    Nodo* frente;
    Nodo* final;

public:
    Cola() {
        frente = nullptr;
        final = nullptr;
    }

    ~Cola() {
        liberar();
    }

    // Evita que dos colas compartan los mismos nodos al copiarlas.
    Cola(const Cola&) = delete;
    Cola& operator=(const Cola&) = delete;

    bool vacia() const {
        return frente == nullptr;
    }

    void enqueue(int dato) {
        Nodo* nuevo = new Nodo;
        nuevo->dato = dato;
        nuevo->siguiente = nullptr;
        if (vacia()) {
            frente = nuevo;
        } else {
            final->siguiente = nuevo;
        }
        final = nuevo;
    }

    bool front(int& dato) const {
        if (vacia()) return false;
        dato = frente->dato;
        return true;
    }

    bool dequeue(int& dato) {
        if (vacia()) return false;
        Nodo* eliminado = frente;
        dato = eliminado->dato;
        frente = eliminado->siguiente;
        if (vacia()) final = nullptr;
        delete eliminado;
        return true;
    }

    // Une el ultimo nodo de esta cola con el primero de B.
    void concatenate(Cola& b) {
        if (this == &b || b.vacia()) return;
        if (vacia()) {
            frente = b.frente;
        } else {
            final->siguiente = b.frente;
        }
        final = b.final;
        b.frente = nullptr;
        b.final = nullptr;
    }

    void mostrar() const {
        const Nodo* aux = frente;
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

    void liberar() {
        int dato = 0;
        while (dequeue(dato)) {}
    }
};

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
        cola.enqueue(dato);
    }
    return true;
}

int main() {
    Cola a;
    Cola b;
    cout << "Concatenacion de dos colas\n";
    if (!cargarCola(a, 'A') || !cargarCola(b, 'B')) {
        cout << "\nNo se completo la carga. Ingrese solamente numeros enteros.\n";
        return 1;
    }
    cout << "\nAntes:\nA = ";
    a.mostrar();
    cout << "B = ";
    b.mostrar();
    a.concatenate(b);
    cout << "Despues de concatenate(A, B):\nA = ";
    a.mostrar();
    cout << "B = ";
    b.mostrar();
    int dato = 0;
    if (a.front(dato)) cout << "Frente de A: " << dato << "\n";
    else cout << "A no tiene frente: esta vacia.\n";
    cout << "Extraccion FIFO de A:";
    while (a.dequeue(dato)) cout << " " << dato;
    cout << "\n\n";
    return 0;
}
