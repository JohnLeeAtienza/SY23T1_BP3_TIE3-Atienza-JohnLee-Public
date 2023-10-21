#pragma once
#include "GameObject.h"
#include "draw.h"
#include "Scene.h"

class PowerUp : public GameObject
{
public:
    PowerUp(float positionX, float positionY, float directionX, float directionY, float speed);
    void start();
    void update();
    void draw();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
    int speed;
    float directionX;
    float directionY;
};