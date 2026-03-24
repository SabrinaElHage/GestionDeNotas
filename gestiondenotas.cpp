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
void gotoxi(int x, int y);
void color(int tex, int fon);
void dibujarFondo();

//funcion principal
int main(){

    


    return 0;
}

//desarrollo de funciones

//enteros
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

//decimales
float leerDecimal(string mensaje){

    float numero;

    while(true){
        cout << mensaje;
        cin >> numero;

        if(cin.fail()){
            cout << "Entrada no valida. Por favor, ingrese un numero decimal." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return numero;
        }
    }
}//fin de la funcion

void gotoxi(int x, int y){

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}//fin de la funcion

//colores
void color(int tex, int fon){

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tex + (fon * 16)));

}//fin de la funcion

//fondo
void dibujarFondo(){

    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 80; j++){
            gotoxi(j, i);
            color(miconfig.colorTexto, miconfig.colorFondo);
            cout << " ";
        }
    }

}//fin de la funcion