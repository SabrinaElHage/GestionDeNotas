/*esciba un programa que calcule las soluciones de una ecuacion de segundo grado de la forma
ax^2 + bx c = 0 usando la formula general*/

#include <iostream>
#include <math.h>
using namespace std;

int main(){

    float a,b,c,resultado1 = 0, resultado2 = 0;

    cout<<"ingrese el valor de a: "; cin>>a;
    cout<<"ingrese el valor de b: "; cin>>b;
    cout<<"ingrese el valor de c: "; cin>>c;

    resultado1 = (-b + sqrt(pow(b,2) - 4*a*c))/(2*a);
    resultado2 = (-b - sqrt(pow(b,2) - 4*a*c))/(2*a);

    cout<<"\nel resultado de la ecuacion cuadratica es: "<<endl;
    cout<<"\nx1 = "<<resultado1<<endl; 
    cout<<"\nx2 = "<<resultado2<<endl;

    return 0;
}