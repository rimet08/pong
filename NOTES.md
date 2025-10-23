# Pong Game - Technical Notes

## Overview
This is a C++ implementation of the classic Pong arcade game using the Raylib graphics library. The game features a player-controlled paddle, an AI-controlled opponent paddle, and a bouncing ball with score tracking.

## Project Structure
- **Language**: C++
- **Graphics Library**: Raylib
- **Tutorial Source**: [YouTube Tutorial](https://www.youtube.com/watch?v=VLJlTaFvHo4)
- **Inspiration**: [Cpp-Pong-Game-Raylib Repository](https://github.com/educ8s/Cpp-Pong-Game-Raylib)

## Code Structure Analysis

### 1. Headers and Includes
```cpp
#include <iostream>
#include <raylib.h>
using namespace std;
```
- **iostream**: For console output (debugging)
- **raylib.h**: Main graphics and game engine library
- **using namespace std**: Allows direct use of cout, endl without std:: prefix

### 2. Game Variables
```cpp
const int screenWidth = 800;
const int screenHeight = 600;
int player_score = 0;
int opponent_score = 0;
```
- **Screen dimensions**: 800x600 pixels (4:3 aspect ratio)
- **Score tracking**: Global variables for both players

### 3. Ball Class
The `Ball` class represents the game ball with position, velocity, and behavior:

#### Properties:
- `int x, y`: Ball position coordinates
- `int speed_x, speed_y`: Velocity in pixels per frame
- `int radius`: Ball size (15 pixels)

#### Methods:
- **Draw()**: Renders the ball as a white circle using `DrawCircle()`
- **Update()**: Handles ball movement and collision detection
  - Moves ball by adding speed to position
  - Bounces off top/bottom walls by reversing `speed_y`
  - Detects scoring when ball exits left/right sides
  - Calls `ResetBall()` when a point is scored

- **ResetBall()**: Centers ball and randomizes initial direction
  - Places ball at screen center
  - Randomly chooses horizontal and vertical directions

### 4. Paddle Class (Base Class)
The `Paddle` class provides common functionality for both player and AI paddles:

#### Properties:
- `int x, y`: Paddle position
- `int width, height`: Paddle dimensions
- `int speed`: Movement speed in pixels per frame

#### Methods:
- **Draw()**: Renders paddle as a rounded white rectangle
- **Update()**: Handles player input (UP/DOWN arrow keys)
- **LimitMovement()** (protected): Prevents paddle from moving off-screen

### 5. CpuPaddle Class (Inheritance)
Extends `Paddle` for AI-controlled opponent:

#### AI Logic:
- Compares paddle center with ball Y position
- Moves towards ball to intercept
- Uses same speed and movement limitations as player

### 6. Game Loop Structure (Incomplete)
The current `main()` function is incomplete and contains syntax errors:
- Two `main()` functions defined
- Missing game initialization
- Missing main game loop
- No Raylib window setup

## Current Issues in Code

### Syntax Errors:
1. **Line 12**: `ins ball_speed_y = 5;` should be `int ball_speed_y = 5;`
2. **Line 34**: `speed_y = *= -1;` should be `speed_y *= -1;`
3. **Line 37**: `cpu_score++` should be `opponent_score++` (variable name mismatch)
4. **Line 44-45**: Missing underscore in variable names (`speed_x`, `speed_y`)
5. **Line 103**: `screeinWidth` should be `screenWidth`

### Structural Issues:
1. **Incomplete main function**: Missing Raylib initialization and game loop
2. **Missing collision detection**: No ball-paddle collision implemented
3. **Unused variables**: Initial ball variables in main are not used
4. **Class structure**: Ball, Paddle objects declared but not properly initialized

## How the Game Should Work

### Game Flow:
1. **Initialization**:
   - Initialize Raylib window (800x600)
   - Set target FPS (usually 60)
   - Initialize ball and paddle objects

2. **Main Game Loop**:
   - Check for window close event
   - Update game objects (ball, paddles)
   - Check collisions (ball-paddle, ball-walls)
   - Draw all objects
   - Display scores

3. **Game Mechanics**:
   - Player controls left paddle with UP/DOWN arrows
   - AI controls right paddle automatically
   - Ball bounces off paddles and walls
   - Points scored when ball exits left/right sides
   - Game continues indefinitely until window closed

### Missing Components for Complete Game:
1. **Raylib initialization**: `InitWindow()`, `SetTargetFPS()`
2. **Main game loop**: `while (!WindowShouldClose())`
3. **Ball-paddle collision detection**
4. **Proper object initialization**
5. **Score display**: `DrawText()` for showing scores
6. **Game state management**: Start screen, pause, etc.

## Raylib Functions Used:
- `DrawCircle()`: Renders ball
- `DrawRectangleRounded()`: Renders paddles
- `GetScreenWidth()`, `GetScreenHeight()`: Screen dimensions
- `IsKeyDown()`: Input detection
- `GetRandomValue()`: Random number generation

## Game Physics:
- **Simple velocity-based movement**: Position += velocity each frame
- **Basic collision**: Reverse velocity component on wall hit
- **AI behavior**: Simple tracking algorithm following ball Y position

This implementation follows classic Pong mechanics with modern C++ and graphics library approach.