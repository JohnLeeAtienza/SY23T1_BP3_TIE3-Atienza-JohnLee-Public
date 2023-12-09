#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Snake.h"
class Food : public GameObject {
public:
    void start();
    void spawn();
    void draw();
    int getX();
    int getY();
    bool checkCollision(int x, int y, int width, int height);
    bool checkCollisionWithSnake(const Snake& snake);

private:
    int x;
    int y;
    SDL_Texture* texture;
};