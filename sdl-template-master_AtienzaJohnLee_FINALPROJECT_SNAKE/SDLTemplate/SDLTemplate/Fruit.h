#pragma once
#include "GameObject.h"
#include "util.h"
#include "draw.h"
#include "Snake.h"

class Fruit :
    public GameObject
{
public:
    void start();
    void draw();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    void setPosition(int x, int y);

private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
};