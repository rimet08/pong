# Analýza kódu - Pong Game v C++

## Přehled projektu
Tento projekt implementuje klasickou hru Pong v jazyce C++ s využitím grafické knihovny Raylib. Hra obsahuje míček, dvě pálky (hráč a AI) a základní systém skóre.

## Struktura kódu

### 1. Knihovny a závislosti
```cpp
#include <iostream>
#include <raylib.h>
using namespace std;
```

**Použité knihovny:**
- **`iostream`**: Standardní knihovna C++ pro vstup a výstup (konzole)
- **`raylib.h`**: Moderní C knihovna pro vývoj 2D/3D her
  - Poskytuje funkce pro grafiku, zvuk, input handling
  - Multiplatformní (Windows, macOS, Linux, Web)
  - Jednoduchá API pro začátečníky

**Proč Raylib:**
- Lehká a rychlá knihovna
- Jednoduché API pro základní herní funkce
- Dobře dokumentovaná
- Vhodná pro učení game developmentu

### 2. Globální proměnné

```cpp
int player_score = 0;
int opponent_score = 0;
```

**Účel:** Uchovávají aktuální skóre obou hráčů
**Umístění:** Globální scope pro snadný přístup z celého programu
**Alternativa:** Mohly by být součástí herní třídy nebo struktury

### 3. Třída Ball (Míček)

#### Vlastnosti (atributy)
```cpp
class Ball {
    public:
        int x, y;              // Pozice na obrazovce (pixely)
        int speed_x, speed_y;  // Rychlost pohybu (pixely/frame)
        int radius;            // Poloměr míčku (pixely)
```

**Design rozhodnutí:**
- **Public atributy**: Umožňuje přímý přístup k vlastnostem
- **int typy**: Dostačující přesnost pro pixelové pozice
- **Separátní speed_x/speed_y**: Nezávislý pohyb v obou osách

#### Metoda Draw()
```cpp
void Draw() {
    DrawCircle(x, y, radius, WHITE);
}
```

**Funkcionalita:**
- Vykresluje míček jako bílý kruh
- Používá Raylib funkci `DrawCircle()`
- **Parametry**: pozice (x,y), poloměr, barva

**Proč takto:**
- Encapsulace: míček sám zodpovídá za své vykreslení
- Jednoduché API Raylib
- Separace logiky od vykreslování

#### Metoda Update()
```cpp
void Update() {
    x += speed_x;
    y += speed_y;
    
    if (y + radius >= GetScreenHeight() || y - radius <= 0) { 
        speed_y *= -1;
    }
}
```

**Logika pohybu:**
1. **Aktualizace pozice**: Přičte rychlost k aktuální pozici
2. **Kolize detekce**: Kontroluje srážku s horní/dolní stěnou
3. **Odraz**: Obrací vertikální rychlost (speed_y *= -1)

**Fyzika:**
- Jednoduchý lineární pohyb
- Perfektně elastický odraz (bez ztráty energie)
- Konstantní rychlost

#### Metoda ResetBall() - Problémy v implementaci
```cpp
void ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    
    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
}
```

**Účel:** Reset míčku po gólu do středu s náhodným směrem

**Problémy v kódu:**
```cpp
// CHYBA: Tento kód je mimo funkci!
if (x + radius >= GetScreenWidth()) {cpu_score++; ResetBall();}
if (x - radius <= 0) {player_score++; ResetBall();}
```

### 4. Třída Paddle (Pálka hráče)

#### Vlastnosti
```cpp
class Paddle {
    protected:
        void LimitMovement() { /* omezení pohybu */ }
        
    public:
        int x, y;           // Pozice pálky
        int width, height;  // Rozměry pálky
        int speed;          // Rychlost pohybu
```

**Design patterns:**
- **Protected metoda**: `LimitMovement()` dostupná jen pro třídu a potomky
- **Public atributy**: Přímý přístup k vlastnostem
- **Enkapsulace**: Logika omezení pohybu je skrytá

#### Metoda Draw()
```cpp
void Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
}
```

**Vizuální design:**
- **Zaoblený obdélník**: Modernější vzhled než klasický obdélník
- **Parametr 0.8**: Míra zaoblení rohů
- **Rectangle struct**: Raylib struktura pro definici obdélníku

#### Metoda Update()
```cpp
void Update() {
    if (IsKeyDown(KEY_UP)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y += speed;
    }
    LimitMovement();
}
```

**Input handling:**
- **`IsKeyDown()`**: Raylib funkce pro detekci stisknutých kláves
- **Kontinuální pohyb**: Reaguje na držení klávesy
- **Bezpečnost**: Volá `LimitMovement()` pro omezení pohybu

#### Metoda LimitMovement()
```cpp
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
```

**Boundary checking:**
- Zabraňuje pálce opustit obrazovku
- Kontroluje horní hranici (y <= 0)
- Kontroluje dolní hranici (y + výška >= výška obrazovky)

### 5. Třída CpuPaddle (AI pálka)

```cpp
class CpuPaddle : public Paddle {
    public:
        void Update(int ball_y) {
            if (y + height / 2 > ball_y) {
                y = y - speed;
            }
            if (y + height / 2 <= ball_y) {
                y = y + speed;
            }
            LimitMovement();
        }
};
```

**Dědičnost:**
- **Extends Paddle**: Získává všechny vlastnosti a metody
- **Override Update()**: Vlastní implementace pohybu

**AI algoritmus:**
1. **Sledování míčku**: Přijímá pozici míčku jako parametr
2. **Centrování**: Snaží se dostat střed pálky (y + height/2) na úroveň míčku
3. **Jednoduchá logika**: Pohyb nahoru/dolů podle polohy míčku

**Charakteristiky AI:**
- **Predictable**: Vždy sleduje míček
- **Perfect tracking**: Bez zpoždění nebo chyb
- **Obtížnost**: Závislá na rychlosti pálky

### 6. Main funkce - Inicializace

```cpp
int main() {
    std::cout << "Starting the game" << std::endl;
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);
    
    // Inicializace míčku
    ball.radius = 15;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 5;
    ball.speed_y = 5;
    
    // Inicializace hráčovy pálky
    player.width = 20;
    player.height = 100;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
}
```

**Konfigurace okna:**
- **Rozlišení**: 800x600 pixelů (4:3 aspect ratio)
- **FPS**: 60 snímků za sekundu
- **Název**: "Pong Game"

**Inicializace objektů:**
- **Míček**: Střed obrazovky, rychlost 5 pixelů/frame
- **Hráčova pálka**: Pravý okraj obrazovky, vertikálně vycentrovaná

## Identifikované problémy

### 1. Syntaktické chyby
```cpp
// CHYBA:
ins ball_speed_y = 5;  // Should be: int ball_speed_y = 5;

// CHYBA:
speed_y = *= -1;       // Should be: speed_y *= -1;

// CHYBA:
speed x *= ...         // Should be: speed_x *= ...
```

### 2. Strukturální problémy
- **Duplikovaný main()**: Funkce main() je definovaná dvakrát
- **Kód mimo funkce**: Detekce gólů není uvnitř žádné funkce
- **Neukončená implementace**: Chybí herní smyčka

### 3. Chybějící funkcionalita
- **Game loop**: Hlavní herní cyklus (while(!WindowShouldClose()))
- **Kolize detekce**: Srážky míčku s pálkami
- **CPU pálka inicializace**: Nastavení rozměrů a pozice
- **Clear screen**: Vymazání obrazovky mezi framy
- **Window closing**: Ukončení okna

### 4. Logické problémy
- **Nekonzistentní proměnné**: cpu_score vs opponent_score
- **Magická čísla**: Hardcoded hodnoty bez konstant
- **Chybějící validace**: Kontrola hranic a inicializace

## Doporučené vylepšení

### 1. Oprava struktury kódu
```cpp
// Přidat konstanty
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_SPEED = 5;
const int PADDLE_SPEED = 6;

// Kompletní game loop
while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Update logic
    ball.Update();
    player.Update();
    cpu.Update(ball.y);
    
    // Draw objects
    ball.Draw();
    player.Draw();
    cpu.Draw();
    
    EndDrawing();
}
```

### 2. Přidání kolize detekce
```cpp
bool CheckCollision(Ball ball, Paddle paddle) {
    return (ball.x - ball.radius <= paddle.x + paddle.width &&
            ball.x + ball.radius >= paddle.x &&
            ball.y - ball.radius <= paddle.y + paddle.height &&
            ball.y + ball.radius >= paddle.y);
}
```

### 3. Vylepšení AI
```cpp
class CpuPaddle : public Paddle {
private:
    float difficulty = 0.8f;  // 0.0 = easy, 1.0 = impossible
    
public:
    void Update(int ball_y) {
        int target_y = ball_y - height / 2;
        int diff = target_y - y;
        
        // Apply difficulty (slower reaction)
        y += (int)(diff * difficulty);
        
        LimitMovement();
    }
};
```

## Závěr

Kód představuje solidní základ pro Pong hru s objektově orientovaným designem. Obsahuje správnou strukturu tříd a základní herní logiku, ale potřebuje dokončení implementace a opravu syntaktických chyb. Architektura je škálovatelná a umožňuje snadné přidání nových funkcí jako zvukové efekty, menu nebo power-ups.

**Klady:**
- Čistý OOP design
- Správné použití dědičnosti
- Modulární struktura
- Použití moderní knihovny (Raylib)

**Zápory:**
- Syntaktické chyby
- Neukončená implementace
- Chybějící error handling
- Nedostatečné komentáře v kódu