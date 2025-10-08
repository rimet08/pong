#include <iostream>
#include <raylib.h>

using namespace std;

int main() {

    const int screenWidth = 800;
    const int screenHeight = 600;
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    ins ball_speed_y = 5;
    int ball_radius = 15;

    cout << "Starting the game..." << endl;
    
}

int player_score = 0;
int opponent_score = 0;

class Ball {
    public:
        int x, y;
        int speed_x, speed_y;
        int radius;

        void Draw() {
            DrawCircle(x, y, radius, WHITE);
        }

        void Update() {
            x += speed_x;
            y += speed_y;

            if (y + radius >= GetScreenHeight() || y - radius <=0) { speed_y = *= -1;}
        }
        
            if (x + radius >= GetScreenWidth()) {cpu_score++; ResetBall();}

            if (x - radius <= 0) {player_score++; ResetBall();}

        void ResetBall() {
            x = GetScreenWidth() / 2;
            y = GetScreenHeight() / 2;

            int speed_choices[2] = {-1, 1};
            speed x *= speed_choices[GetRandomValue(0, 1)];
            speed y *= speed_choices[GetRandomValue(0, 1)];
};

class Paddle {
    protected:
        void LimitMovement() {
            if (y <=0) {
                y = 0;
            }
            if (y + height >= GetScreenHeight()) {
                y = GetScreenHeight() - height;
            }
        }
}

public:
    int x, y;
    int width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }
