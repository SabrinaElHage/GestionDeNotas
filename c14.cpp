#include <iostream>
#include <conio.h>   // Para _kbhit() y _getch()
#include <windows.h> // Para colores y posicionamiento
#include <vector>    // Para el cuerpo de la serpiente
#include <ctime>     // Para el reloj
#include <cstdlib>   // Para rand() y system()

using namespace std;

// 1. CONFIGURACIÓN
const int ANCHO = 40;
const int ALTO = 20;
int VELOCIDAD = 100; 

enum eDireccion { PAUSA = 0, IZQUIERDA, DERECHA, ARRIBA, ABAJO };
eDireccion dir;

struct Punto {
    int x, y;
};

Punto cabeza;
Punto comida;
vector<Punto> cuerpo;
int puntuacion;
bool juegoTerminado;

// 2. HERRAMIENTAS DE CONSOLA
void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void set_color(int texto, int fondo) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, fondo * 16 + texto);
}

void ocultarCursor() {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

// 3. LÓGICA DEL JUEGO
void Setup() {
    ocultarCursor();
    juegoTerminado = false;
    dir = PAUSA;
    puntuacion = 0;
    cabeza.x = ANCHO / 2;
    cabeza.y = ALTO / 2;
    cuerpo.clear();
    comida.x = rand() % (ANCHO - 2) + 1;
    comida.y = rand() % (ALTO - 2) + 1;
}

void DibujarEscenario() {
    system("cls");
    set_color(15, 2); // Blanco sobre Verde
    for (int i = 0; i < ALTO; i++) {
        for (int j = 0; j < ANCHO; j++) {
            if (i == 0 || i == ALTO - 1 || j == 0 || j == ANCHO - 1) cout << "#";
            else cout << " ";
        }
        cout << endl;
    }
}

// SOLO UNA FUNCIÓN PARA DIBUJAR (LA NUEVA)
void DibujarElementos() {
    static Punto cabezaAnterior = cabeza;

    // 1. Borrar rastro anterior
    set_color(15, 2); 
    if (!cuerpo.empty()) {
        gotoxy(cuerpo.back().x, cuerpo.back().y);
        cout << " ";
    } else {
        gotoxy(cabezaAnterior.x, cabezaAnterior.y);
        cout << " ";
    }

    // 2. DIBUJAR COMIDA (Asterisco blanco)
    set_color(15, 2); 
    gotoxy(comida.x, comida.y);
    cout << "*"; 

    // 3. Dibujar Cuerpo (Amarillo)
    set_color(14, 2); 
    for (size_t i = 0; i < cuerpo.size(); i++) {
        gotoxy(cuerpo[i].x, cuerpo[i].y);
        cout << (char)177;
    }

    // 4. Dibujar Cabeza (Blanco)
    set_color(15, 2);
    gotoxy(cabeza.x, cabeza.y);
    cout << (char)254;

    cabezaAnterior = cabeza;

    // Puntuacion abajo
    set_color(15, 0);
    gotoxy(0, ALTO);
    cout << "Puntuacion: " << puntuacion << "  ";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': case 'A': if (dir != DERECHA)   dir = IZQUIERDA; break;
            case 'd': case 'D': if (dir != IZQUIERDA) dir = DERECHA;   break;
            case 'w': case 'W': if (dir != ABAJO)     dir = ARRIBA;    break;
            case 's': case 'S': if (dir != ARRIBA)    dir = ABAJO;     break;
            case 'x': case 'X': juegoTerminado = true; break;
        }
    }
}

void Logica() {
    if (dir == PAUSA) return;
    Punto prevPos = cabeza;

    switch (dir) {
        case IZQUIERDA: cabeza.x--; break;
        case DERECHA:   cabeza.x++; break;
        case ARRIBA:    cabeza.y--; break;
        case ABAJO:     cabeza.y++; break;
    }

    if (!cuerpo.empty()) {
        for (int i = cuerpo.size() - 1; i > 0; i--) cuerpo[i] = cuerpo[i-1];
        cuerpo[0] = prevPos;
    }

    if (cabeza.x <= 0 || cabeza.x >= ANCHO-1 || cabeza.y <= 0 || cabeza.y >= ALTO-1) 
        juegoTerminado = true;

    for (size_t i = 0; i < cuerpo.size(); i++)
        if (cuerpo[i].x == cabeza.x && cuerpo[i].y == cabeza.y) juegoTerminado = true;

    if (cabeza.x == comida.x && cabeza.y == comida.y) {
        puntuacion += 10;
        cuerpo.insert(cuerpo.begin(), prevPos);
        comida.x = rand() % (ANCHO - 2) + 1;
        comida.y = rand() % (ALTO - 2) + 1;
        if(VELOCIDAD > 40) VELOCIDAD -= 2; // Sube la dificultad
    }
}

// 4. MAIN
int main() {
    srand((unsigned int)time(NULL)); 
    Setup();
    DibujarEscenario();

    while (!juegoTerminado) {
        Input();
        Logica();
        DibujarElementos();
        Sleep(VELOCIDAD);
    }

    system("cls");
    set_color(15, 0);
    cout << "GAME OVER - Puntos: " << puntuacion << endl;
    cout << "Presiona una tecla para salir...";
    _getch();
    return 0;
}



