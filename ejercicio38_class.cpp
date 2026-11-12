#include <iostream>
using namespace std;

class Cola {
private:
    class Nodo {
    public:
        int dato;
        Nodo* siguiente;
        explicit Nodo(int valor) : dato(valor), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* final;

public:
    Cola() : frente(nullptr), final(nullptr) {}

    ~Cola() {
        liberar();
    }

    // Impide copias superficiales que causarian doble liberacion.
    Cola(const Cola&) = delete;
    Cola& operator=(const Cola&) = delete;

    bool vacia() const {
        return frente == nullptr;
    }

    void enqueue(int dato) {
        Nodo* nuevo = new Nodo(dato);
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

    // Equivale a concatenate(A, B) cuando se invoca A.concatenate(B).
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
        cout << "[";
        for (const Nodo* actual = frente; actual != nullptr;
             actual = actual->siguiente) {
            cout << actual->dato;
            if (actual->siguiente != nullptr) cout << ", ";
        }
        cout << "]\n";
    }

    void liberar() {
        int dato = 0;
        while (dequeue(dato)) {}
    }
};

void demostrarCaso(int caso, bool llenarA, bool llenarB) {
    Cola a;
    Cola b;
    if (llenarA) {
        a.enqueue(1);
        a.enqueue(2);
        a.enqueue(3);
    }
    if (llenarB) {
        b.enqueue(4);
        b.enqueue(5);
    }
    cout << "Caso " << caso << "\nAntes:\nA = ";
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
    // Los destructores liberan cualquier nodo restante al salir.
}

int main() {
    demostrarCaso(1, true, true);
    demostrarCaso(2, false, true);
    demostrarCaso(3, true, false);
    demostrarCaso(4, false, false);
    return 0;
}
