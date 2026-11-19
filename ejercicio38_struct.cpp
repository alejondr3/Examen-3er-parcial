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
    if (!cargarCola(a, "A") || !cargarCola(b, "B")) {
        cout << "\nEntrada finalizada. No se completo la carga de datos.\n";
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
