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

// Lee un entero por linea y vuelve a pedirlo si la entrada no es valida.
bool leerEntero(const char* mensaje, int& valor) {
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            bool valido = true;
            char caracter;
            while (cin.get(caracter) && caracter != '\n') {
                if (caracter != ' ' && caracter != '\t' && caracter != '\r')
                    valido = false;
            }
            if (valido) return true;
            cout << "Entrada invalida. Ingrese un numero entero.\n";
            if (cin.eof()) return false;
        } else {
            if (cin.eof() || cin.bad()) return false;
            cin.clear();
            char caracter;
            while (cin.get(caracter) && caracter != '\n') {}
            cout << "Entrada invalida. Ingrese un numero entero.\n";
            if (cin.eof()) return false;
        }
    }
}

bool cargarCola(Cola& cola, const char* nombre) {
    cout << "\nCola " << nombre << "\n";
    int cantidad = 0;
    do {
        if (!leerEntero("Cantidad de elementos (0 para dejarla vacia): ", cantidad))
            return false;
        if (cantidad < 0) cout << "La cantidad no puede ser negativa.\n";
    } while (cantidad < 0);

    for (int i = 0; i < cantidad; ++i) {
        cout << "Elemento " << i + 1 << " de " << cantidad << "\n";
        int dato = 0;
        if (!leerEntero("Valor entero: ", dato)) return false;
        cola.enqueue(dato);
    }
    return true;
}

int main() {
    Cola a;
    Cola b;
    cout << "Concatenacion de dos colas\n";
    if (!cargarCola(a, "A") || !cargarCola(b, "B")) {
        cout << "\nEntrada finalizada. No se completo la carga de datos.\n";
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
