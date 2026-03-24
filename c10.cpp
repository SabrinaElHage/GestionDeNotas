#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Para tablas perfectas
#include <windows.h> // Para colores y limpiar pantalla en Windows

using namespace std;

// === Nivel 1: Estructura de Datos Eficiente ===
struct Producto {
    string codigo;
    string nombre;
    int stock;
    float precio;
};

// === Nivel 2: Funciones de Interfaz (TUI) ===
void configurarConsola() {
    // Fondo Azul oscuro, Letras Blancas brillantes
    system("color 1F");
}

void limpiarPantalla() {
    // En un proyecto real usariamos la API de Windows, 
    // pero system("cls") es mas simple para empezar.
    system("cls");
}

void dibujarBorde(int ancho) {
    cout << "\t";
    for (int i = 0; i < ancho; i++) cout << char(205); // Carácter '═'
    cout << endl;
}

void mostrarEncabezadoApp() {
    limpiarPantalla();
    dibujarBorde(60);
    cout << "\t" << "      SISTEMA DE INVENTARIO PROFESIONAL - ALMACEN MARIO" << endl;
    dibujarBorde(60);
    cout << endl;
}

// === Nivel 3: Lógica del Inventario ===

// Pasamos por REFERENCIA (&) para modificar el vector original sin copiarlo
void registrarProducto(vector<Producto> &inventario) {
    mostrarEncabezadoApp();
    Producto p;
    cout << "\t[ REGISTRAR NUEVO PRODUCTO ]" << endl << endl;
    
    cout << "\tCodigo unico: ";
    cin >> p.codigo;
    cout << "\tNombre del producto: ";
    cin.ignore(); // Limpia el buffer antes de getline
    getline(cin, p.nombre);
    cout << "\tCantidad en stock: ";
    cin >> p.stock;
    cout << "\tPrecio unitario: $";
    cin >> p.precio;

    // Agregamos al vector de forma dinamica
    inventario.push_back(p);
    
    cout << "\n\t" << char(251) << " Producto registrado con exito." << endl;
    cout << "\tPresione Enter para volver...";
    cin.ignore(); cin.get(); // Pausa elegante
}

// Pasamos por REFERENCIA CONSTANTE (const &) para velocidad pura sin riesgos
void mostrarInventario(const vector<Producto> &inventario) {
    mostrarEncabezadoApp();
    cout << "\t[ INVENTARIO ACTUAL ]" << endl << endl;

    // Si está vacío, avisamos
    if (inventario.empty()) {
        cout << "\tEl inventario esta vacio." << endl;
    } else {
        // Encabezado de la Tabla
        cout << "\t" << left << setw(10) << "CODIGO" 
             << setw(25) << "PRODUCTO" 
             << setw(10) << "STOCK" 
             << setw(10) << "PRECIO" << endl;
        cout << "\t";
        for(int i=0; i<55; i++) cout << char(196); // Carácter '─'
        cout << endl;

        // Recorremos el vector
        for (const auto &p : inventario) {
            cout << "\t" << left << setw(10) << p.codigo 
                 << setw(25) << p.nombre 
                 << setw(10) << p.stock 
                 << "$" << fixed << setprecision(2) << p.precio << endl;
        }
    }
    cout << "\n\tPresione Enter para volver...";
    cin.ignore(); cin.get();
}

// === Nivel 4: Menú Principal e Interacción ===
int main() {
    // Configuración inicial de la "App"
    configurarConsola();
    
    // Usamos VECTOR para que el tamaño sea dinamico
    vector<Producto> miInventario; 
    int opcion = 0;

    do {
        mostrarEncabezadoApp();
        cout << "\t1. Registrar Producto" << endl;
        cout << "\t2. Ver Inventario Completo" << endl;
        cout << "\t3. Salir de la Aplicacion" << endl;
        cout << "\n\tSeleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(miInventario); break;
            case 2: mostrarInventario(miInventario); break;
            case 3: 
                mostrarEncabezadoApp();
                cout << "\tGracias por usar la aplicacion. Saliendo..." << endl;
                Sleep(1500); // Pausa de 1.5 segundos antes de cerrar
                break;
            default:
                cout << "\tOpcion invalida. Intente de nuevo." << endl;
                Sleep(1000);
                break;
        }
    } while (opcion != 3);

    return 0;
}