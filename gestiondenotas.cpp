#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <limits>
#include <iomanip>

#define MAX_MATERIAS 15
#define MAX_USUARIOS 2

using namespace std;

//estructura
struct config{

    int colorTexto = 15;
    int colorFondo = 1;
    int colorMenu = 14;

};

struct estudiante{

    string nombre;
    float notas[MAX_MATERIAS];

};

//declaraciones
vector<string> listaMaterias;
config miconfig;

//funciones

int leerEnteros(string mensaje);
float leerDecimal(string mensaje);

//funcion principal
int main(){

    


    return 0;
}

//desarrollo de funciones
int leerEnteros(string mensaje){

    int numero;

    while(true){
        cout << mensaje;
        cin >> numero;

        if(cin.fail()){
            cout << "Entrada no valida. Por favor, ingrese un numero entero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return numero;
        }
    }
}//fin de la funcion