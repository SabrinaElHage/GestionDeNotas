/*escriba un programa que lea tres numeros y determine cual de ellos es el mayor*/

#include <iostream>

using namespace std;

int main(){

    int num1,num2,num3;

    cout<<"ingrese 3 numeros\n"; cin>>num1>>num2>>num3;

    if(num1 >= num2 && num1 >= num3){
        cout<<"el numero mayor es: "<<num1;
    }
    else if(num2 >= num1 && num2 >= num3){
        cout<<"el numero mayor es: "<<num2;
    }
    else{
        cout<<"el numero mayor es: "<<num3;
    }


    return 0;
}