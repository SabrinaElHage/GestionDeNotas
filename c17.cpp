#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <limits>
#include <iomanip> // Para tabular la lista de colores

using namespace std;

#define MAX_MATERIAS 15
#define MAX_USUARIOS 10

struct Config {
    int colorTexto = 15;
    int colorFondo = 1; 
    int colorMenuPrincipal = 14; 
};

struct Estudiante {
    string nombre;
    float notas[MAX_MATERIAS];
};

vector<string> listaMaterias;
Config miConfig;

// --- FUNCIONES DE APOYO ---
int leerEntero(string mensaje) {
    int n;
    while (true) {
        cout << mensaje;
        if (cin >> n) return n;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Ingresa un numero valido.\n";
    }
}

float leerFloat(string mensaje) {
    float n;
    while (true) {
        cout << mensaje;
        if (cin >> n) return n;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Ingresa un valor numerico.\n";
    }
}

void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos = {(short)x, (short)y};
    SetConsoleCursorPosition(hCon, dwPos);
}

void color(int t, int f) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, f * 16 + t);
}

void dibujarFondo() {
    color(miConfig.colorTexto, miConfig.colorFondo);
    system("cls");
    for (int y = 0; y < 28; y++) {
        gotoxy(0, y);
        for (int x = 0; x < 80; x++) cout << " ";
    }
}

// --- PERSISTENCIA ---
void guardarUsuarios(vector<Estudiante>& v) {
    ofstream archC("config.dat");
    archC << miConfig.colorTexto << " " << miConfig.colorFondo << " " << miConfig.colorMenuPrincipal << endl;
    archC << listaMaterias.size() << endl;
    for (string m : listaMaterias) archC << m << endl;
    archC.close();

    ofstream archU("usuarios.dat");
    archU << v.size() << endl;
    for (auto& e : v) {
        archU << e.nombre << endl;
        for (int i = 0; i < MAX_MATERIAS; i++) archU << e.notas[i] << endl;
    }
    archU.close();
}

void cargarTodo(vector<Estudiante>& v) {
    ifstream archC("config.dat");
    if (archC.is_open()) {
        archC >> miConfig.colorTexto >> miConfig.colorFondo >> miConfig.colorMenuPrincipal;
        int nM; archC >> nM; archC.ignore();
        for (int i = 0; i < nM; i++) {
            string m; getline(archC, m);
            listaMaterias.push_back(m);
        }
        archC.close();
    } else {
        listaMaterias = {"Analisis", "Base de Datos", "Programacion"};
    }

    ifstream archU("usuarios.dat");
    if (archU.is_open()) {
        int nU; archU >> nU; archU.ignore();
        for (int i = 0; i < nU; i++) {
            Estudiante e;
            getline(archU, e.nombre);
            for (int j = 0; j < MAX_MATERIAS; j++) archU >> e.notas[j];
            archU.ignore();
            v.push_back(e);
        }
        archU.close();
    }
}

// --- MENÚS DE CONFIGURACIÓN ---
void verMemoria(vector<Estudiante>& v) {
    system("cls");
    color(11, 0); cout << "--- ESTADO DE LA MEMORIA DEL SISTEMA ---" << endl << endl;
    color(15, 0);
    cout << "USUARIOS:" << endl;
    cout << "  En uso: " << v.size() << " slots." << endl;
    cout << "  Libres: " << MAX_USUARIOS - v.size() << " slots." << endl;
    float porcU = (v.size() * 100.0) / MAX_USUARIOS;
    cout << "  Carga:  [" << porcU << "%]" << endl << endl;

    cout << "MATERIAS:" << endl;
    cout << "  En uso: " << listaMaterias.size() << " slots." << endl;
    cout << "  Libres: " << MAX_MATERIAS - listaMaterias.size() << " slots." << endl;
    float porcM = (listaMaterias.size() * 100.0) / MAX_MATERIAS;
    cout << "  Carga:  [" << porcM << "%]" << endl << endl;

    cout << "Presione cualquier tecla para volver...";
    _getch();
}

void menuColores() {
    int opC;
    do {
        system("cls");
        color(11, 0); cout << "--- EDITOR DE COLORES ---" << endl;
        color(15, 0);
        cout << "1. Color de Letras (Notas)\n2. Color de Fondo (Notas)\n3. Color Titulo Principal\n4. Volver\n";
        opC = leerEntero("Opcion: ");

        if (opC >= 1 && opC <= 3) {
            system("cls");
            color(14, 0); cout << "PALETA DE COLORES DISPONIBLES:" << endl;
            color(7, 0);
            cout << "--------------------------------------" << endl;
            cout << "0. Negro      | 1. Azul       | 2. Verde" << endl;
            cout << "3. Aguamarina | 4. Rojo       | 5. Purpura" << endl;
            cout << "6. Amarillo   | 7. Blanco     | 8. Gris" << endl;
            cout << "9. Azul Cielo | 10. Lima      | 11. Celeste" << endl;
            cout << "12. Rojo Brill| 13. Rosa      | 14. Oro" << endl;
            cout << "--------------------------------------" << endl;
            int nCol = leerEntero("Seleccione el numero de color: ");
            if (opC == 1) miConfig.colorTexto = nCol;
            else if (opC == 2) miConfig.colorFondo = nCol;
            else miConfig.colorMenuPrincipal = nCol;
        }
    } while (opC != 4);
}

void configuracion(vector<Estudiante>& v) {
    int op;
    do {
        system("cls");
        color(11, 0); cout << "--- PANEL DE CONTROL ---" << endl;
        color(15, 0);
        cout << "1. Agregar Usuario\n2. Eliminar Usuario (Enter)\n3. Gestionar Materias\n4. VER ESTADO DE MEMORIA\n5. Personalizar Colores\n6. Volver\n";
        op = leerEntero("Opcion: ");

        if (op == 1 && v.size() < MAX_USUARIOS) {
            Estudiante nuevo; cout << "Nombre: "; cin.ignore(); getline(cin, nuevo.nombre);
            for(int i=0; i<MAX_MATERIAS; i++) nuevo.notas[i] = 0;
            v.push_back(nuevo);
        } else if (op == 2 && !v.empty()) {
            int sel = leerEntero("Confirme ID de usuario a borrar: ");
            if(sel >= 1 && sel <= (int)v.size()) v.erase(v.begin() + (sel - 1));
        } else if (op == 3) {
            system("cls");
            cout << "1. Agregar Materia\n2. Borrar Materia\nOpcion: ";
            int subm = leerEntero("");
            if(subm == 1 && listaMaterias.size() < MAX_MATERIAS) {
                string nm; cout << "Nombre: "; cin.ignore(); getline(cin, nm);
                listaMaterias.push_back(nm);
            } else if (subm == 2) {
                int idm = leerEntero("ID materia: ");
                if(idm >=1 && idm <= (int)listaMaterias.size()) listaMaterias.erase(listaMaterias.begin() + (idm-1));
            }
        } else if (op == 4) verMemoria(v);
        else if (op == 5) menuColores();
        guardarUsuarios(v);
    } while (op != 6);
}

// --- PANTALLA DE NOTAS ---
void mostrarNotas(Estudiante& e) {
    dibujarFondo();
    gotoxy(10, 2); color(miConfig.colorTexto, miConfig.colorFondo);
    cout << "  EXPEDIENTE: " << e.nombre << "  ";
    for (int i = 0; i < (int)listaMaterias.size(); i++) {
        gotoxy(5, 5 + i); color(miConfig.colorTexto, miConfig.colorFondo);
        cout << i + 1 << ". " << left << setw(20) << listaMaterias[i];
        if (e.notas[i] >= 50) color(10, miConfig.colorFondo); else color(12, miConfig.colorFondo);
        cout <<  e.notas[i] << "%";
    }
    color(11, miConfig.colorFondo);
    gotoxy(5, 22); cout << "[S] Sumar | [M] Modificar | [V] Volver";
}

int main() {
    vector<Estudiante> alumnos;
    cargarTodo(alumnos);

    while (true) {
        system("cls");
        color(miConfig.colorMenuPrincipal, 0); 
        cout << "==== GESTOR ACADEMICO PLUS ====" << endl;
        color(15, 0);
        for (int i = 0; i < (int)alumnos.size(); i++) cout << i + 1 << ". " << alumnos[i].nombre << endl;
        cout << alumnos.size() + 1 << ". CONFIGURACION" << endl;
        cout << alumnos.size() + 2 << ". SALIR" << endl;
        
        color(8, 0); cout << "\n(Presione el numero directamente)" << endl;
        
        char c = _getch(); // LECTURA INSTANTÁNEA
        int sel = c - '0'; // Convertir char a int

        // Ajuste para cuando hay 10 opciones o más (usaríamos otra lógica, pero para 10 slots esto va bien)
        if (c == '0') sel = 10; 

        if (sel == (int)alumnos.size() + 2) {
            cout << "\a\n¿Desea salir del sistema? [S/N]: ";
            char conf = toupper(_getch());
            if (conf == 'S') break;
            else continue;
        }
        
        if (sel == (int)alumnos.size() + 1) { configuracion(alumnos); continue; }
        
        if (sel >= 1 && sel <= (int)alumnos.size()) {
            int idx = sel - 1;
            char t;
            do {
                mostrarNotas(alumnos[idx]);
                t = toupper(_getch());
                if (t == 'S' || t == 'M') {
                    int m = leerEntero("\nID Materia (Enter): ");
                    if (m >= 1 && m <= (int)listaMaterias.size()) {
                        float n = leerFloat("Valor (Enter): ");
                        if (t == 'S') alumnos[idx].notas[m-1] += n; 
                        else alumnos[idx].notas[m-1] = n;
                        if(alumnos[idx].notas[m-1] > 100) alumnos[idx].notas[m-1] = 100;
                        guardarUsuarios(alumnos);
                    }
                }
            } while (t != 'V');
        }
    }
    return 0;
}