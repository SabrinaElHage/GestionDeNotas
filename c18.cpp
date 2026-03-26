#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <time.h>

using namespace std;

#define ANCHO 40
#define ALTO 20

enum TipoSerpiente { COMUN, FANTASMA, GUERRERO };

enum eDireccion { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Jugador {
    int dinero = 0;
    int vidas = 3;
    int velocidad = 100;
    TipoSerpiente tipo = COMUN;
    int nivelActual = 1;
    int colorCuerpo = 10;
};

struct Obstaculo { int x, y; };
struct Enemigo { int x, y; bool vivo; };

bool gameOver;
int x, y, frutaX, frutaY, score;
int nCola;
int colaX[100], colaY[100];
eDireccion dir;

vector<Obstaculo> obstaculos;
vector<Enemigo> enemigos;
vector<pair<int,int>> balas;
vector<eDireccion> balasDir;

bool habilidadActiva = false;
time_t inicioHabilidad = 0;
time_t ultimaVezUsada = 0;
bool nivelCompletado = false;
bool nivelTimeout = false;
int tickCount = 0;

void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hCon, dwPos);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void guardarDatos(Jugador &j) {
    ofstream archivo("savegame.txt");
    if (archivo.is_open()) {
        archivo << j.dinero << " " << j.vidas << " " << j.velocidad << " " << (int)j.tipo << " " << j.nivelActual << " " << j.colorCuerpo << "\n";
    }
}

void cargarDatos(Jugador &j) {
    ifstream archivo("savegame.txt");
    if (archivo.is_open()) {
        int tipoInt;
        archivo >> j.dinero >> j.vidas >> j.velocidad >> tipoInt >> j.nivelActual >> j.colorCuerpo;
        if (!archivo.fail()) j.tipo = (TipoSerpiente)tipoInt;
    }
}

void agregarObstaculo(int x, int y) {
    obstaculos.push_back({x, y});
}

bool enObstaculo(int px, int py) {
    for (auto &o : obstaculos) if (o.x == px && o.y == py) return true;
    return false;
}

void crearFruta() {
    int intentos = 0;
    do {
        frutaX = rand() % (ANCHO - 2) + 1;
        frutaY = rand() % (ALTO - 2) + 1;
        intentos++;
        if (intentos > 1000) {
            frutaX = -1;
            frutaY = -1;
            break;
        }
    } while ((frutaX != -1 && frutaY != -1) && (enObstaculo(frutaX, frutaY) || (frutaX == x && frutaY == y)));
}

void prepararNivel(Jugador &j) {
    obstaculos.clear();
    enemigos.clear();
    balas.clear();
    balasDir.clear();

    if (j.nivelActual == 1) {
        for (int i = 8; i < 32; i++) if (i % 2 == 0) agregarObstaculo(i, 5);
        for (int i = 5; i < 15; i++) if (i % 2 == 0) agregarObstaculo(15, i);
    } else if (j.nivelActual == 2) {
        for (int i = 4; i < 36; i++) if (i % 3 == 0) agregarObstaculo(i, 8);
        for (int i = 2; i < 12; i++) agregarObstaculo(25, i);
        enemigos.push_back({10, 3, true});
        enemigos.push_back({30, 16, true});
    } else if (j.nivelActual == 3) {
        for (int i = 2; i < 38; i += 2) agregarObstaculo(i, 10);
        for (int i = 2; i < 17; i += 2) agregarObstaculo(20, i);
        for (int i = 5; i < 15; i += 3) agregarObstaculo(5, i);
        enemigos.push_back({7, 3, true});
        enemigos.push_back({32, 3, true});
        enemigos.push_back({20, 16, true});
    }

    x = ANCHO / 2;
    y = ALTO / 2;
    dir = STOP;
    nCola = 0;
    score = 0;
    habilidadActiva = false;
    inicioHabilidad = 0;
    crearFruta();
}

void Setup(Jugador &j) {
    gameOver = false;
    nivelCompletado = false;
    nivelTimeout = false;
    tickCount = 0;
    prepararNivel(j);
}

void dibujarNivel(Jugador &j) {
    gotoxy(0, 0); // Regresa al inicio sin borrar todo (evita parpadeo)
    setColor(11);
    for (int i = 0; i < ANCHO + 2; i++) cout << "#";
    cout << endl;

    for (int fila = 0; fila < ALTO; fila++) {
        setColor(11);
        cout << "#"; // Lado izquierdo
        for (int col = 1; col <= ANCHO; col++) {
            bool impreso = false;
            
            // Lógica de dibujo de cabeza, cola, fruta, etc. (se mantiene igual)
            if (x == col && y == fila) {
                setColor(10);
                if (j.tipo == COMUN) cout << "O";
                else if (j.tipo == FANTASMA) cout << "F";
                else cout << "G";
                impreso = true;
            }
            // ... (aquí va el resto de tus validaciones de cola, obstáculos y enemigos) ...

            if (!impreso) {
                if (frutaX == col && frutaY == fila) { setColor(12); cout << "@"; }
                else cout << " ";
            }
        }
        setColor(11);
        cout << "#" << "      " << endl; // Los espacios extra limpian basura visual a la derecha
    }

    setColor(11);
    for (int i = 0; i < ANCHO + 2; i++) cout << "#";
    cout << "\n";
    
    // Limpieza de las líneas de información para que no se traslapen
    setColor(7);
    cout << "NIVEL: " << j.nivelActual << "  DINERO: $" << j.dinero << "  VIDAS: " << j.vidas << "  SCORE: " << score << "          \n";
    cout << "VELOCIDAD: " << j.velocidad << "ms  SERPIENTE: " << (j.tipo == COMUN ? "COMUN" : (j.tipo == FANTASMA ? "FANTASMA" : "GUERRERO")) << "          \n";
    cout << "HABILIDAD: ";
    if (habilidadActiva) cout << "ACTIVA (" << (5 - (int)difftime(time(0), inicioHabilidad)) << "s)      \n";
    else cout << "Disponible          \n";
    cout << "Controles: w/a/s/d, 1-2 Habilidad, Espacio Disparo, Q Salir          \n";
}
void generarBala(Jugador &j) {
    if (j.tipo != GUERRERO || !habilidadActiva) return;
    if (dir == STOP) return;
    int bx = x, by = y;
    eDireccion d = dir;
    if (d == LEFT) bx--;
    if (d == RIGHT) bx++;
    if (d == UP) by--;
    if (d == DOWN) by++;
    if (bx <= 0 || bx > ANCHO || by < 0 || by >= ALTO) return;
    balas.emplace_back(bx, by);
    balasDir.push_back(d);
}

void movimientoEnemigos() {
    for (auto &e : enemigos) {
        if (!e.vivo) continue;
        int dx = 0, dy = 0;
        if (e.x < x) dx = 1;
        else if (e.x > x) dx = -1;
        if (e.y < y) dy = 1;
        else if (e.y > y) dy = -1;

        int nx = e.x + dx;
        int ny = e.y + dy;
        if (nx > 0 && nx <= ANCHO && ny >= 0 && ny < ALTO && !enObstaculo(nx, ny)) {
            e.x = nx;
            e.y = ny;
        }
    }
}

void calcularLogica(Jugador &j) {
    if (habilidadActiva && difftime(time(0), inicioHabilidad) > 5) {
        habilidadActiva = false;
    }

    if (_kbhit()) {
        char c = _getch();
        if (c == 'a' && dir != RIGHT) dir = LEFT;
        if (c == 'd' && dir != LEFT) dir = RIGHT;
        if (c == 'w' && dir != DOWN) dir = UP;
        if (c == 's' && dir != UP) dir = DOWN;
        if (c == '1' && j.tipo == FANTASMA && difftime(time(0), ultimaVezUsada) > 60) {
            habilidadActiva = true;
            inicioHabilidad = time(0);
            ultimaVezUsada = time(0);
        }
        if (c == '2' && j.tipo == GUERRERO && difftime(time(0), ultimaVezUsada) > 60) {
            habilidadActiva = true;
            inicioHabilidad = time(0);
            ultimaVezUsada = time(0);
        }
        if (c == ' ') generarBala(j);
        if (c == 'q' || c == 'Q' || c == 27) {
            gameOver = true;
            nivelCompletado = false;
        }
    }

    int prevX = colaX[0];
    int prevY = colaY[0];
    int prev2X, prev2Y;
    colaX[0] = x;
    colaY[0] = y;
    for (int i = 1; i < nCola; i++) {
        prev2X = colaX[i];
        prev2Y = colaY[i];
        colaX[i] = prevX;
        colaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (dir == LEFT) x--;
    if (dir == RIGHT) x++;
    if (dir == UP) y--;
    if (dir == DOWN) y++;

    bool golpe = false;

    if (x <= 0 || x > ANCHO || y < 0 || y >= ALTO) {
        if (habilidadActiva) {
            if (x <= 0) x = ANCHO;
            if (x > ANCHO) x = 1;
            if (y < 0) y = ALTO - 1;
            if (y >= ALTO) y = 0;
        } else {
            golpe = true;
        }
    }

    if (!habilidadActiva && enObstaculo(x, y)) golpe = true;

    for (auto &e : enemigos) {
        if (e.vivo && e.x == x && e.y == y) golpe = true;
    }

    if (golpe) {
        j.vidas--;
        if (j.vidas <= 0) {
            gameOver = true;
            return;
        }
        prepararNivel(j);
        return;
    }

    for (int i = 0; i < nCola; i++) {
        if (colaX[i] == x && colaY[i] == y) {
            j.vidas--;
            if (j.vidas <= 0) {
                gameOver = true;
                return;
            }
            prepararNivel(j);
            return;
        }
    }

    if (x == frutaX && y == frutaY) {
        j.dinero += 10;
        score += 5;
        nCola++;
        crearFruta();
    }

    for (int i = (int)balas.size()-1; i >= 0; i--) {
        if (balasDir[i] == LEFT) balas[i].first--;
        if (balasDir[i] == RIGHT) balas[i].first++;
        if (balasDir[i] == UP) balas[i].second--;
        if (balasDir[i] == DOWN) balas[i].second++;

        bool fuera = balas[i].first <= 0 || balas[i].first > ANCHO || balas[i].second < 0 || balas[i].second >= ALTO;
        if (fuera) {
            balas.erase(balas.begin() + i);
            balasDir.erase(balasDir.begin() + i);
            continue;
        }

        bool impact = false;
        for (auto &e : enemigos) {
            if (e.vivo && e.x == balas[i].first && e.y == balas[i].second) {
                e.vivo = false;
                impact = true;
                j.dinero += 20;
                score += 20;
                break;
            }
        }

        if (impact) {
            balas.erase(balas.begin() + i);
            balasDir.erase(balasDir.begin() + i);
            continue;
        }
    }

    if (j.nivelActual >= 2) movimientoEnemigos();

    if (j.nivelActual == 1 && score >= 40) {
        nivelCompletado = true;
        gameOver = true;
    } else if (j.nivelActual == 2 && score >= 80) {
        nivelCompletado = true;
        gameOver = true;
    } else if (j.nivelActual == 3 && score >= 130) {
        nivelCompletado = true;
        gameOver = true;
    }

    tickCount++;
    if (tickCount >= 12000) {  // timeout aprox. 10-12 min según velocidad
        nivelTimeout = true;
        gameOver = true;
    }
}

void MenuBanco(Jugador &j) {
    system("cls");
    cout << "=== TIENDA DE COLORES ===\n";
    cout << "Dinero actual: $" << j.dinero << "\n";
    cout << "1. Azul ($50)\n2. Rojo ($50)\n3. Cyan ($50)\n4. Verde (gratis)\n5. Volver\n";
    char op = _getch();
    if (op == '1' && j.dinero >= 50) { j.colorCuerpo = 9; j.dinero -= 50; }
    if (op == '2' && j.dinero >= 50) { j.colorCuerpo = 12; j.dinero -= 50; }
    if (op == '3' && j.dinero >= 50) { j.colorCuerpo = 11; j.dinero -= 50; }
    if (op == '4') j.colorCuerpo = 10;
    guardarDatos(j);
}

void MenuVelocidad(Jugador &j) {
    system("cls");
    cout << "=== AJUSTAR VELOCIDAD ===\n";
    cout << "1. Lento\n2. Medio\n3. Rapido\n";
    char op = _getch();
    if (op == '1') j.velocidad = 150;
    if (op == '2') j.velocidad = 80;
    if (op == '3') j.velocidad = 30;
}

void MenuNiveles(Jugador &j) {
    system("cls");
    cout << "=== SELECCIONAR NIVEL ===\n";
    cout << "1. Nivel 1\n2. Nivel 2\n3. Nivel 3\n";
    char op = _getch();
    if (op >= '1' && op <= '3') {
        j.nivelActual = op - '0';
    }
}

int main() {
    srand(time(0));
    Jugador player;
    cargarDatos(player);

    while (true) {
        system("cls");
        setColor(10);
        cout << "   _____ _   _          _  ________ \n";
        cout << "  / ____| \\ | |   /\\   | |/ /  ____|\n";
        cout << " | (___ |  \\| |  /  \\  | ' /| |__   \n";
        cout << "  \\___ \\| . ` | / /\\ \\ |  < |  __|  \n";
        cout << "  ____) | |\\  |/ ____ \\| . \\| |____ \n";
        cout << " |_____/|_| \\_/_/    \\_\\_|\\_\\______|\n\n";

        setColor(7);
        cout << "1. JUGAR NIVEL " << player.nivelActual << "\n";
        cout << "2. NIVELES\n";
        cout << "3. SERPIENTES\n";
        cout << "4. BANCO/TIENDA\n";
        cout << "5. VELOCIDAD\n";
        cout << "6. SALIR\n";

        char opcion = _getch();
        if (opcion == '1') {
            Setup(player);
            nivelCompletado = false;
            while (!gameOver) {
                dibujarNivel(player);
                calcularLogica(player);
                Sleep(player.velocidad);
            }
            guardarDatos(player);
            if (nivelCompletado) {
                system("cls");
                cout << "\n¡Nivel " << player.nivelActual << " completado! Presiona una tecla...";
                _getch();
                if (player.nivelActual < 3) player.nivelActual++;
                gameOver = false;
                nivelCompletado = false;
            } else if (nivelTimeout) {
                system("cls");
                cout << "\nTiempo de nivel agotado, regresando al menu... Presiona una tecla...";
                _getch();
                gameOver = false;
                nivelTimeout = false;
            } else if (player.vidas > 0) {
                system("cls");
                cout << "\nTe golpearon y perdiste vida. Presiona una tecla para regresar a menu...";
                _getch();
                gameOver = false;
            } else {
                system("cls");
                cout << "\nGame Over. Fin del juego. Presiona una tecla...";
                _getch();
                player.vidas = 3;
                player.nivelActual = 1;
                player.dinero = 0;
                guardarDatos(player);
                gameOver = false;
            }
        }
        else if (opcion == '2') {
            MenuNiveles(player);
        }
        else if (opcion == '3') {
            system("cls");
            cout << "1. COMUN (OOO)\n2. FANTASMA (1)\n3. GUERRERO (2 + disparo)\n";
            char opS = _getch();
            if (opS == '1') player.tipo = COMUN;
            if (opS == '2') player.tipo = FANTASMA;
            if (opS == '3') player.tipo = GUERRERO;
            guardarDatos(player);
        }
        else if (opcion == '4') MenuBanco(player);
        else if (opcion == '5') MenuVelocidad(player);
        else if (opcion == '6') break;
    }

    return 0;
}
 
