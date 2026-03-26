
// LIBRERIAS
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

// CONSTANTES (Dinámicas para las baterías)
#define MAX_MATERIAS 13
#define MAX_USUARIOS 2 

// ESTRUCTURAS
struct config {
    int colorTexto = 15;
    int colorFondo = 1; 
    int colorMenuPrincipal = 14;
};

struct Estudiante {
    string nombre;
    float notas[MAX_MATERIAS];
};

// PROTOTIPOS DE FUNCIONES
int leerEntero(string mensaje);
float leerDecimal(string mensaje);
void gotoxy(int x, int y);
void color(int tex, int fon);
void dibujarFondo(config &conf);
void guardarDatos(vector<Estudiante>& v, vector<string>& materias, config &conf);
void cargarDatos(vector<Estudiante>& v, vector<string>& materias, config &conf);
void mostrarBaterias(int actual, int maximo, string etiqueta, config &conf);
bool confirmarAccion(string mensaje);
void menuColores(config &conf);
void gestionarMaterias(vector<Estudiante>& alumnos, vector<string>& materias, config &conf);
void configuracion(vector<Estudiante>& v, vector<string>& materias, config &conf);
void mostrarExpediente(Estudiante& e, vector<string>& materias, config &conf);
void ejecutarSistema(vector<Estudiante>& alumnos, vector<string>& listaMaterias, config &miConfig);

// --- FUNCION PRINCIPAL ---
int main() {
    vector<Estudiante> alumnos;
    vector<string> listaMaterias;
    config miConfig;

    cargarDatos(alumnos, listaMaterias, miConfig);
    ejecutarSistema(alumnos, listaMaterias, miConfig);

    return 0;
}

//DESARROLLO DE FUNCIONES
void gestionarMaterias(vector<Estudiante>& alumnos, vector<string>& materias, config &conf) {
    int op;
    do {
        system("cls");
        color(conf.colorMenuPrincipal, 0);
        cout << "========================================" << endl;
        cout << "         GESTION DE ASIGNATURAS         " << endl;
        cout << "========================================" << endl;
        color(conf.colorTexto, 0);
        
        for (int i = 0; i < (int)materias.size(); i++) {
            cout << " [" << i + 1 << "] " << materias[i] << endl;
        }

        color(11, 0);
        cout << "\n1. Agregar Materia\n2. Eliminar Materia\n3. Volver\nOpcion: ";
        op = leerEntero("");

        if (op == 1 && materias.size() < MAX_MATERIAS) {
            string nueva;
            cout << "Nombre de la materia: ";
            cin.ignore(); getline(cin, nueva);
            materias.push_back(nueva);
            // Inicializar nota en 0 para todos los alumnos en esta materia
            for(auto &est : alumnos) est.notas[materias.size()-1] = 0;
        } 
        else if (op == 2 && !materias.empty()) {
            int sel = leerEntero("ID de materia a eliminar: ");
            if (sel >= 1 && sel <= (int)materias.size()) {
                if (confirmarAccion("Borrar '" + materias[sel-1] + "'? (Afectara notas)")) {
                    int idx = sel - 1;
                    // Desplazar las notas de todos los alumnos para mantener orden
                    for (auto &est : alumnos) {
                        for (int i = idx; i < MAX_MATERIAS - 1; i++) {
                            est.notas[i] = est.notas[i+1];
                        }
                        est.notas[MAX_MATERIAS-1] = 0;
                    }
                    materias.erase(materias.begin() + idx);
                }
            }
        }
        guardarDatos(alumnos, materias, conf);
    } while (op != 3);
}

void configuracion(vector<Estudiante>& v, vector<string>& materias, config &conf) {
    int op;
    do {
        system("cls");
        color(conf.colorMenuPrincipal, 0);
        cout << "----------------------------------------" << endl;
        cout << "           PANEL DE CONTROL             " << endl;
        cout << "----------------------------------------" << endl;
        color(conf.colorTexto, 0);
        mostrarBaterias(v.size(), MAX_USUARIOS, "USUARIOS", conf);
        mostrarBaterias(materias.size(), MAX_MATERIAS, "MATERIAS", conf);
        cout << "----------------------------------------" << endl;
        cout << "1. Agregar Usuario\n2. Eliminar Usuario\n3. Gestionar Materias\n4. Colores\n5. Volver\nOpcion: ";
        op = leerEntero("");

        if (op == 1 && v.size() < MAX_USUARIOS) {
            Estudiante nuevo; cout << "Nombre: "; cin.ignore(); getline(cin, nuevo.nombre);
            for(int i=0; i<MAX_MATERIAS; i++) nuevo.notas[i] = 0;
            v.push_back(nuevo);
        } 
        else if (op == 2 && !v.empty()) {
            int sel = leerEntero("ID a borrar: ");
            if (sel >= 1 && sel <= (int)v.size()) {
                if (confirmarAccion("Borrar a " + v[sel-1].nombre + "?")) v.erase(v.begin() + (sel-1));
            }
        }
        else if (op == 3) {
            gestionarMaterias(v, materias, conf); // Integración aquí
        }
        else if (op == 4) menuColores(conf);
        
        guardarDatos(v, materias, conf);
    } while (op != 5);
}

// [EL RESTO DE TUS FUNCIONES SE MANTIENEN IGUAL]
void ejecutarSistema(vector<Estudiante>& alumnos, vector<string>& listaMaterias, config &miConfig) {
    while (true) {
        system("cls");
        color(miConfig.colorMenuPrincipal, 0); 
        cout << "========================================" << endl;
        cout << "            GESTION DE NOTAS           " << endl;
        cout << "========================================" << endl;
        color(miConfig.colorTexto, 0);
        
        for (int i = 0; i < (int)alumnos.size(); i++) {
            cout << " [" << i + 1 << "] " << alumnos[i].nombre << endl;
        }
        
        color(miConfig.colorTexto, 0);
        cout << "\n [" << alumnos.size() + 1 << "] CONFIGURACION PANEL" << endl;
        cout << " [" << alumnos.size() + 2 << "] SALIR DEL SISTEMA" << endl;
        
        color(miConfig.colorTexto, 0); cout << "\n>> Seleccione una opcion: ";
        
        char c = _getch();
        int sel = (c >= '1' && c <= '9') ? (c - '0') : (c == '0' ? 10 : -1);

        if (sel == (int)alumnos.size() + 2) {
            if (confirmarAccion("Desea cerrar el sistema?")) break;
        } 
        else if (sel == (int)alumnos.size() + 1) {
            configuracion(alumnos, listaMaterias, miConfig);
        } 
        else if (sel >= 1 && sel <= (int)alumnos.size()) {
            int idx = sel - 1;
            char tecla;
            do {
                mostrarExpediente(alumnos[idx], listaMaterias, miConfig);
                tecla = toupper(_getch());
                if (tecla == 'S' || tecla == 'M') {
                    int m = leerEntero("\nID Materia: ");
                    if (m >= 1 && m <= (int)listaMaterias.size()) {
                        float n = leerDecimal("Valor de la nota: ");
                        if (confirmarAccion("Desea aplicar este cambio?")) {
                            if (tecla == 'S') alumnos[idx].notas[m-1] += n; 
                            else alumnos[idx].notas[m-1] = n;
                            if(alumnos[idx].notas[m-1] > 100) alumnos[idx].notas[m-1] = 100;
                            guardarDatos(alumnos, listaMaterias, miConfig);
                        }
                    }
                }
            } while (tecla != 'V');
        }
    }
}

void mostrarBaterias(int actual, int maximo, string etiqueta, config &conf) {
    float porcentaje = (actual * 100.0) / maximo;
    int barras = (int)(porcentaje / 10); 
    cout << left << setw(15) << etiqueta << "[";
    for (int i = 0; i < 10; i++) {
        if (i < barras) { color(10, 0); cout << (char)219; } 
        else { color(8, 0); cout << (char)176; }
    }
    color(conf.colorTexto, 0);
    cout << "] " << fixed << setprecision(1) << porcentaje << "% (" << actual << "/" << maximo << ")" << endl;
}

int leerEntero(string mensaje) {
    int numero; 
    while(true) {
        cout << mensaje;
        if (cin >> numero) return numero;
        color(12, 0); cout << "Error: Numero entero invalido." << endl; color(15,0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float leerDecimal(string mensaje) {
    float numero; 
    while(true) {
        cout << mensaje;
        if (cin >> numero) return numero;
        color(12, 0); cout << "Error: Valor numerico invalido." << endl; color(15,0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool confirmarAccion(string mensaje) {
    color(14, 0);
    cout << "\n" << mensaje << " [S/N]: ";
    char res = toupper(_getch());
    color(15, 0);
    return (res == 'S');
}

void gotoxy(int x, int y) {
    COORD coord = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color(int tex, int fon) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tex + (fon * 16)));
}

void dibujarFondo(config &conf) {
    color(conf.colorTexto, conf.colorFondo);
    system("cls");
    for (int y = 0; y < 28; y++) {
        gotoxy(0, y);
        for (int x = 0; x < 80; x++) cout << " ";
    }
}

void menuColores(config &conf) {
    system("cls");
    color(11, 0); cout << "--- PALETA DE COLORES ---" << endl;
    string nombres[] = {"Negro", "Azul\t", "Verde", "Aguamarina", "Rojo\t", "Purpura", "Amarillo", "Blanco", 
                        "Gris\t", "Azul Cielo", "Lima", "Celeste", "rubi", "Rosa", "Oro\t"};
    for(int i=0; i<15; i++) {
        color(i, 0); cout << i << ". " << nombres[i] << "\t\t|"<<"\n";
    }
    color(15, 0);
    cout << "-------------------------" << endl;
    int op = leerEntero("1.Texto / 2.Fondo / 3.Titulo: ");
    int nCol = leerEntero("Numero de color: ");
    if (op == 1) conf.colorTexto = nCol;
    else if (op == 2) conf.colorFondo = nCol;
    else if (op == 3) conf.colorMenuPrincipal = nCol;
}

void mostrarExpediente(Estudiante& e, vector<string>& materias, config &conf) {
    dibujarFondo(conf);
    
    // 1. Marco Exterior (Fijo)
    color(conf.colorMenuPrincipal, conf.colorFondo);
    for(int i = 3; i < 21; i++) {
        gotoxy(2, i);  cout << (char)186; // ║
        gotoxy(78, i); cout << (char)186; // ║
    }
    gotoxy(2, 3);  for(int i=0; i<75; i++) cout << (char)205; // ═
    gotoxy(2, 21); for(int i=0; i<75; i++) cout << (char)205; // ═

    // 2. Encabezado de Estudiante
    gotoxy(5, 4); color(conf.colorTexto, conf.colorFondo);
    cout << "EXPEDIENTE ACADEMICO | ";
    color(14, conf.colorFondo); cout << "ESTUDIANTE: " << e.nombre;
    
    // 3. Cabecera Estilo Excel (Ajustada para nombres largos)
    // ID(4) | ASIGNATURA(30) | ESTADO(11) | NOTA(8) | PUNTOS(10)
    gotoxy(4, 6); color(11, conf.colorFondo);
    cout << " ID |          ASIGNATURA            |  ESTADO   | NOTA % | PUNTOS ";
    gotoxy(4, 7);
    for(int i=0; i<73; i++) cout << (char)196; // ─

    // 4. Renderizado de 9 Casillas Fijas
    for (int i = 0; i < MAX_MATERIAS; i++) {
        int filaY = 8 + i;
        gotoxy(4, filaY);
        
        if (i < (int)materias.size()) {
            // Lógica de color según nota
            if (e.notas[i] >= 50.0) color(10, conf.colorFondo); // Verde
            else color(12, conf.colorFondo); // Rojo

            float nota20 = (e.notas[i] * 20.0) / 100.0;
            
            // ID (4 espacios)
            cout << " " << left << setw(2) << i + 1 << " | ";
            
            // ASIGNATURA: Ahora con 30 espacios (Cabe "Investigación de Operaciones" sobrado)
            string nom = materias[i];
            if(nom.length() > 30) nom = nom.substr(0, 27) + "...";
            cout << left << setw(30) << nom << " | ";
            
            // ESTADO (10 espacios)
            cout << left << setw(9) << (e.notas[i] >= 50.0 ? "APROBADO" : "REPROBADO") << " | ";
            
            // NOTA % (7 espacios)
            cout << right << setw(5) << fixed << setprecision(1) << e.notas[i] << "% | ";
            
            // PUNTOS (8 espacios)
            cout << right << setw(6) << fixed << setprecision(2) << nota20 << " pts";
        } 
        else {
            // Casilla vacía simétrica para mantener la estructura
            color(8, conf.colorFondo);
           
        }
    }

    // 5. Barra de Comandos (Pie de página)
    color(0, 15);
    gotoxy(4, 22); 
    cout << "  [S] SUMAR NOTA | [M] MODIFICAR NOTA | [V] VOLVER AL MENU PRINCIPAL  ";
    color(conf.colorTexto, conf.colorFondo);
}

void guardarDatos(vector<Estudiante>& v, vector<string>& materias, config &conf) {
    ofstream archC("config.dat");
    archC << conf.colorTexto << " " << conf.colorFondo << " " << conf.colorMenuPrincipal << " " << materias.size() << endl;
    for (string m : materias) archC << m << endl;
    archC.close();

    ofstream archU("usuarios.dat");
    archU << v.size() << endl;
    for (auto& e : v) {
        archU << e.nombre << endl;
        for (int i = 0; i < MAX_MATERIAS; i++) archU << e.notas[i] << endl;
    }
    archU.close();
}

void cargarDatos(vector<Estudiante>& v, vector<string>& materias, config &conf) {
    ifstream archC("config.dat");
    if (archC.is_open()) {
        int nM; archC >> conf.colorTexto >> conf.colorFondo >> conf.colorMenuPrincipal >> nM; archC.ignore();
        for (int i = 0; i < nM; i++) { string m; getline(archC, m); materias.push_back(m); }
        archC.close();
    } else { materias = {"Analisis", "Base de Datos", "Programacion"}; }

    ifstream archU("usuarios.dat");
    if (archU.is_open()) {
        int nU; archU >> nU; archU.ignore();
        for (int i = 0; i < nU; i++) {
            Estudiante e; getline(archU, e.nombre);
            for (int j = 0; j < MAX_MATERIAS; j++) archU >> e.notas[j];
            archU.ignore(); v.push_back(e);
        }
        archU.close();
    }
}