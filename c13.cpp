#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

// Estructura
struct producto {
    int codigo;
    string nombre;
    double precio;
    int cant;
};

// Prototipos (Asegúrate de que coincidan con el desarrollo abajo)
void registro(producto *p, int tam);
bool venta(producto *p, int cantidad);
void mostrar(producto *p, int tam);

int main() {
    const int N = 3; // 'const' corregido
    producto inventario[N];
    int opcion, cantVenta, codBusqueda;

    // Ejecutamos el registro
    cout << ".....:::::REGISTRO DE INVENTARIO:::::....." << endl;
    registro(inventario, N);

    system("cls"); // Comillas añadidas

    // Lógica de venta
    cout << "--- SISTEMA DE VENTAS ---" << endl;
    cout << "Ingrese el CODIGO del producto (0 a " << N - 1 << "): ";
    cin >> codBusqueda;
    
    // Validación básica de rango
    if(codBusqueda >= 0 && codBusqueda < N) {
        cout << "Cantidad a vender: ";
        cin >> cantVenta;

        // Pasamos la dirección del producto específico
        if (venta(&inventario[codBusqueda], cantVenta)) {
            cout << "\nVenta realizada con exito!" << endl;
        } else {
            cout << "\nError: Stock insuficiente." << endl;
        }
    } else {
        cout << "\nCodigo no valido." << endl;
    }

    cout << "\nPresione una tecla para ver el reporte final...";
    getch();

    system("cls");
    mostrar(inventario, N);

    getch();
    return 0;
}

// Registro de productos
void registro(producto *p, int tam) {
    for (int i = 0; i < tam; i++) { // Usamos 'tam' en lugar de 'N' para que sea reutilizable
        cout << "Producto [" << i << "]" << endl;
        p[i].codigo = i;
        cout << "NOMBRE: "; cin >> p[i].nombre;
        cout << "PRECIO: "; cin >> p[i].precio;
        cout << "CANTIDAD: "; cin >> p[i].cant;
    }
}

// Ventas (Uso correcto del operador flecha)
bool venta(producto *p, int cantidad) {
    if (p->cant >= cantidad) {
        p->cant -= cantidad;
        return true; // Los paréntesis en return son opcionales
    }
    return false;
}

// Imprimir
void mostrar(producto *p, int tam) {
    cout << "============ INVENTARIO ===========" << endl;
    for (int i = 0; i < tam; i++) {
        cout << "Codigo: " << p[i].codigo << " | Nombre: " << p[i].nombre;
        cout << " | Cantidad: " << p[i].cant;
        
        if (p[i].cant < 3) {
            cout << " <--- [ALERTA: CANTIDAD BAJA]";
        }
        cout << endl;
    }
}