//punteros
#include <iostream>
#include <conio.h>
using namespace std;

//funciones
void punteros(int *dir_num);

//funcion principal
int main(){
    int numero = 20;
    punteros(&numero);
    getch();
    return 0;
}
//desarrollo de funciones
void punteros(int *dir_num){
    
    cout<<"el numero es: "<<*dir_num<<endl;
    cout<<"direccion: "<<dir_num<<endl;

}