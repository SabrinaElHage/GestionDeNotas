/*comprobar si un numero digitado por el usuario es positivo o negativo*/

#include <iostream>

using namespace std;

int main(){
    int numero;

    cout<<"ingrese un numero: ";
    cin>>numero;

    if(numero >= 0){
        cout<<numero<<" es positivo\n";
    }
    else{
        cout<<numero<<" es negativo\n";
    }

    return 0;
}