#include <iostream>

using namespace std;

// 1. PROTOTIPOS
int calcularSuma(int a, int b);
void mostrarResultado(int valor);

int main() {
    int num1 = 0, num2 = 0; // Siempre inicializa tus variables

    // Llamamos a la función que hace el cálculo
    // Nota: Aunque num1 y num2 van vacíos, la función los llenará con cin
    int sumafinal = calcularSuma(num1, num2);

    // Pasamos el resultado a la función de salida
    mostrarResultado(sumafinal);

    return 0;
}

// 2. DESARROLLO DE FUNCIONES

int calcularSuma(int a, int b) {
    cout << "Ingrese el primer numero: "; cin >> a;
    cout << "Ingrese el segundo numero: "; cin >> b;

    return a + b; // Retornamos la suma directamente
}

void mostrarResultado(int valor) {
    // Aquí usamos 'valor' porque es el nombre que le dimos al parámetro
    cout << "--------------------------" << endl;
    cout << "El resultado final es: " << valor << endl;
    cout << "--------------------------" << endl;
}