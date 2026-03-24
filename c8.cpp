#include <iostream>
#define N 3

using namespace std;

//funciones
void leerdatos();
void mostrardatos();

//estructura
struct producto{

int codigo;
char nombre[10];
float precio;

};

struct producto dato[N];

//funcion principal
int main(){

    leerdatos();
    mostrardatos();

    return 0;
}

void leerdatos(){

    for(int i = 0; i < N; i++){
    cout<<"ingrese codigo del prducto: "; cin>>dato[i].codigo;

    while((dato[i].codigo < 100) || (dato[i].codigo > 999)){
        cout<<"DATO INVALIDO, INGRESE CODIGO POSITIVO Y DE TRES DIGITOS\n"; cin>>dato[i].codigo;
    }//fin del while

    cout<<"ingrese el nombre del producto: "; cin>>dato[i].nombre;
    
    cout<<"ingrese el precio del producto: "; cin>>dato[i].precio;
    while(dato[i].precio < 0){
        cout<<"EL PRECIO DEBE SER POSITIVO\n"; cin>>dato[i].precio;
    }//fin del while

    }//fin de for

}//fin de la funcion

void mostrardatos(){

    cout<<"\n.............ALMACEN DE PRODUCTOS.............\n";
    cout<<"================================================\n";
    cout<<"lista\t\tcodigo\t\tnombre\t\tprecio\n";
    for(int i = 0; i < N; i++){
        cout<<i<<"\t\t"<<dato[i].codigo<<"\t\t"<<dato[i].nombre<<"\t\t"<<dato[i].precio<<endl;
    }
}