/*relice un programa que lea la entrada estandar de los sigueintes datos de una persona:

    edad: dato de tipo entero
    sexo: dato de tipo caracter
    altura: dato de tipo real 

    tras leer los datos, el programa debe mostrarlos en la salida estandar
*/
#include <iostream>
using namespace std;
int main(){

    int edad;
    char sexo[10];
    float altura;

    cout<<"ingrese edad: "; cin>>edad;
    cout<<"ingrese sexo: "; cin>>sexo;
    cout<<"ingrese altura: "; cin>>altura;

    cout<<"\nedad: "<<edad;
    cout<<"\nsexo: "<<sexo;
    cout<<"\naltura: "<<altura; 


    return 0;

}