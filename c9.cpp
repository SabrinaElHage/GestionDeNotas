#include <iostream>
#include <string>

using namespace std;

// Función 1: Entrada (Usa '&' para modificar las variables originales directamente)
void pedir(string &n, float &p) {
    cout << "Producto y Precio: ";
    cin >> n >> p;
}

// Función 2: Cálculo (Usa 'const &' para no copiar el texto, es lo más rápido)
float aplicarDescuento(const string &n, float p, float desc = 0.10) {
    cout << "Aplicando descuento a: " << n << endl;
    return p * (1 - desc);
}

int main() {
    string nombre;
    float precio;

    pedir(nombre, precio);
    
    // Mostramos el resultado llamando a la función directamente en el cout
    cout << "Precio final: $" << aplicarDescuento(nombre, precio) << endl;

    return 0;
}