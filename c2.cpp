/*escribe un programa que lea la entrada estandar de dos numeros y muestre en la salida estandar su suma,
resta, multiplicacion y division*/

#include <iostream>

using namespace std;

int main(){

    float num1,num2,sum,res,mult,div;

    cout<<"ingrese el primer numero: ";
    cin>>num1;
    cout<<"ingrese el segundo numero: ";
    cin>>num2;

    sum = num1 + num2;
    res = num1 - num2;
    mult = num1 * num2;
    div = num1 / num2;

    cout<<"\nel resultado de la suma es: "<<sum;
    cout<<"\nel resultado de la resta es: "<<res;
    cout<<"\nel resultado de la multiplicacion es: "<<mult;
    cout<<"\nel resultado de la division es: "<<div;

    return 0;
}