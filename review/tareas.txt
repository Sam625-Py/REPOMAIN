#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

struct Fecha {
    int dia;
    int mes;
    int año;
};

struct Persona {
    string nombre;
    string apellido;
    string sexo;
    Fecha fechaNacimiento;
    string email;
};

struct Nodo {
    Persona persona;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(const Persona& p) : persona(p), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

bool esFechaMenor(const Fecha& a, const Fecha& b) {
    if (a.año != b.año) return a.año < b.año;
    if (a.mes != b.mes) return a.mes < b.mes;
    return a.dia < b.dia;
}

string fechaToString(const Fecha& fecha) {
    ostringstream oss;
    oss << setw(2) << setfill('0') << fecha.dia << '/'
        << setw(2) << setfill('0') << fecha.mes << '/'
        << setw(4) << setfill('0') << fecha.año;
    return oss.str();
}

// Funciones auxiliares para AVL
int obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int obtenerBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
}

void actualizarAltura(Nodo* nodo) {
    if (nodo) {
        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));
    }
}

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

void mostrarArbol(Nodo* nodo, int espacio = 0, int incremento = 10) {
    if (nodo == nullptr) return;

    espacio += incremento;

    mostrarArbol(nodo->derecho, espacio);

    cout << endl;
    for (int i = incremento; i < espacio; i++) cout << " ";
    cout << fechaToString(nodo->persona.fechaNacimiento) << "\n";

    mostrarArbol(nodo->izquierdo, espacio);
}

Nodo* balancear(Nodo* nodo) {
    actualizarAltura(nodo);
    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
        cout << "Desbalance detectado. Realizando rotacion derecha.\n";
        nodo = rotarDerecha(nodo);
        cout << "Arbol despues de rotacion derecha:\n";
        mostrarArbol(nodo);
        return nodo;
    }

    if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
        cout << "Desbalance detectado. Realizando rotacion izquierda-derecha.\n";
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        cout << "Arbol despues de rotacion izquierda en subarbol izquierdo:\n";
        mostrarArbol(nodo);
        nodo = rotarDerecha(nodo);
        cout << "Arbol despues de rotacion derecha:\n";
        mostrarArbol(nodo);
        return nodo;
    }

    if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
        cout << "Desbalance detectado. Realizando rotacion izquierda.\n";
        nodo = rotarIzquierda(nodo);
        cout << "Arbol despues de rotacion izquierda:\n";
        mostrarArbol(nodo);
        return nodo;
    }

    if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
        cout << "Desbalance detectado. Realizando rotacion derecha-izquierda.\n";
        nodo->derecho = rotarDerecha(nodo->derecho);
        cout << "Arbol despues de rotacion derecha en subarbol derecho:\n";
        mostrarArbol(nodo);
        nodo = rotarIzquierda(nodo);
        cout << "Arbol despues de rotacion izquierda:\n";
        mostrarArbol(nodo);
        return nodo;
    }

    return nodo;
}

Fecha leerFecha() {
    Fecha fecha;
    char separador1, separador2;

    while (true) {
        cout << "Ingrese fecha de nacimiento (DD/MM/AAAA): ";
        string linea;
        getline(cin, linea);
        istringstream iss(linea);

        if (iss >> fecha.dia >> separador1 >> fecha.mes >> separador2 >> fecha.año &&
            separador1 == '/' && separador2 == '/' && fecha.dia >= 1 && fecha.dia <= 31 &&
            fecha.mes >= 1 && fecha.mes <= 12 && fecha.año > 0) {
            break;
        }

        cout << "Formato invalido. Use DD/MM/AAAA.\n";
    }

    return fecha;
}

Persona leerPersona() {
    Persona persona;

    cout << "Ingrese nombre: ";
    getline(cin, persona.nombre);
    cout << "Ingrese apellido: ";
    getline(cin, persona.apellido);
    cout << "Ingrese sexo (M/F/O): ";
    getline(cin, persona.sexo);
    persona.fechaNacimiento = leerFecha();
    cout << "Ingrese email: ";
    getline(cin, persona.email);

    return persona;
}

void mostrarPersona(const Persona& persona) {
    cout << "Nombre: " << persona.nombre << " " << persona.apellido << " | ";
    cout << "Sexo: " << persona.sexo << " | ";
    cout << "Fecha Nac.: " << fechaToString(persona.fechaNacimiento) << " | ";
    cout << "Email: " << persona.email << "\n";
}

Nodo* insertarNodo(Nodo* raiz, const Persona& persona) {
    if (raiz == nullptr) {
        return new Nodo(persona);
    }

    if (esFechaMenor(persona.fechaNacimiento, raiz->persona.fechaNacimiento)) {
        raiz->izquierdo = insertarNodo(raiz->izquierdo, persona);
    } else if (esFechaMenor(raiz->persona.fechaNacimiento, persona.fechaNacimiento)) {
        raiz->derecho = insertarNodo(raiz->derecho, persona);
    } else {
        cout << "Error: ya existe una persona con esa fecha de nacimiento.\n";
        return raiz;
    }

    return balancear(raiz);
}

void recorrerInOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        recorrerInOrden(nodo->izquierdo);
        mostrarPersona(nodo->persona);
        recorrerInOrden(nodo->derecho);
    }
}

void recorrerPreOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        mostrarPersona(nodo->persona);
        recorrerPreOrden(nodo->izquierdo);
        recorrerPreOrden(nodo->derecho);
    }
}

void recorrerPostOrden(Nodo* nodo) {
    if (nodo != nullptr) {
        recorrerPostOrden(nodo->izquierdo);
        recorrerPostOrden(nodo->derecho);
        mostrarPersona(nodo->persona);
    }
}

int contarNodos(Nodo* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
}

Nodo* minimoNodo(Nodo* nodo) {
    if (nodo == nullptr) return nullptr;
    while (nodo->izquierdo != nullptr) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

Nodo* maximoNodo(Nodo* nodo) {
    if (nodo == nullptr) return nullptr;
    while (nodo->derecho != nullptr) {
        nodo = nodo->derecho;
    }
    return nodo;
}

Nodo* eliminarNodo(Nodo* raiz, const Fecha& fecha, bool& eliminado) {
    if (raiz == nullptr) return nullptr;

    if (esFechaMenor(fecha, raiz->persona.fechaNacimiento)) {
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, fecha, eliminado);
    } else if (esFechaMenor(raiz->persona.fechaNacimiento, fecha)) {
        raiz->derecho = eliminarNodo(raiz->derecho, fecha, eliminado);
    } else {
        eliminado = true;

        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            delete raiz;
            return nullptr;
        }

        if (raiz->izquierdo == nullptr) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }

        Nodo* sucesor = minimoNodo(raiz->derecho);
        raiz->persona = sucesor->persona;
        raiz->derecho = eliminarNodo(raiz->derecho, sucesor->persona.fechaNacimiento, eliminado);
    }

    return balancear(raiz);
}

void liberarArbol(Nodo* nodo) {
    if (nodo != nullptr) {
        liberarArbol(nodo->izquierdo);
        liberarArbol(nodo->derecho);
        delete nodo;
    }
}

int leerEntero(const string& prompt) {
    int valor;
    while (true) {
        cout << prompt;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada invalida. Ingrese un numero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Nodo* raiz = nullptr;
    int opcion;

    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar persona\n";
        cout << "2. Mostrar recorrido\n";
        cout << "3. Cantidad de nodos\n";
        cout << "4. Persona con menor fecha (minimo)\n";
        cout << "5. Persona con mayor fecha (maximo)\n";
        cout << "6. Eliminar persona por fecha\n";
        cout << "7. Visualizar arbol\n";
        cout << "8. Salir\n";
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                cout << "\nAgregar nueva persona:\n";
                Persona persona = leerPersona();
                raiz = insertarNodo(raiz, persona);
                cout << "Persona agregada al arbol.\n";
                cout << "Arbol despues de insercion:\n";
                mostrarArbol(raiz);
                break;
            }
            case 2: {
                if (raiz == nullptr) {
                    cout << "El arbol esta vacio.\n";
                    break;
                }
                cout << "\nRecorridos disponibles:\n";
                cout << "1. InOrden\n";
                cout << "2. PreOrden\n";
                cout << "3. PostOrden\n";
                int subopcion = leerEntero("Seleccione recorrido: ");
                cout << "\n";
                if (subopcion == 1) {
                    recorrerInOrden(raiz);
                    cout << "\n";
                } else if (subopcion == 2) {
                    recorrerPreOrden(raiz);
                    cout << "\n";
                } else if (subopcion == 3) {
                    recorrerPostOrden(raiz);
                    cout << "\n";
                } else {
                    cout << "Opcion invalida.\n";
                }
                break;
            }
            case 3: {
                cout << "Cantidad de nodos: " << contarNodos(raiz) << "\n";
                break;
            }
            case 4: {
                Nodo* minimo = minimoNodo(raiz);
                if (minimo != nullptr) {
                    cout << "\nPersona con menor fecha de nacimiento (mas antigua):\n";
                    mostrarPersona(minimo->persona);
                } else {
                    cout << "El arbol esta vacio.\n";
                }
                break;
            }
            case 5: {
                Nodo* maximo = maximoNodo(raiz);
                if (maximo != nullptr) {
                    cout << "\nPersona con mayor fecha de nacimiento (mas reciente):\n";
                    mostrarPersona(maximo->persona);
                } else {
                    cout << "El arbol esta vacio.\n";
                }
                break;
            }
            case 6: {
                if (raiz == nullptr) {
                    cout << "El arbol esta vacio.\n";
                    break;
                }
                cout << "\nEliminar persona por fecha de nacimiento:\n";
                Fecha fecha = leerFecha();
                bool eliminado = false;
                raiz = eliminarNodo(raiz, fecha, eliminado);
                if (eliminado) {
                    cout << "Persona eliminada.\n";
                    cout << "Arbol despues de eliminacion:\n";
                    mostrarArbol(raiz);
                } else {
                    cout << "No se encontro persona con esa fecha.\n";
                }
                break;
            }
            case 7: {
                if (raiz == nullptr) {
                    cout << "El arbol esta vacio.\n";
                } else {
                    cout << "\nVisualizacion del arbol (fechas de nacimiento):\n";
                    mostrarArbol(raiz);
                }
                break;
            }
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (opcion != 8);

    liberarArbol(raiz);
    return 0;
}
