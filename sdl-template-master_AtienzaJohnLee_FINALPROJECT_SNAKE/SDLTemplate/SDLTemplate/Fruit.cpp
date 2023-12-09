#include "Fruit.h"

void Fruit::start()
{
    texture = loadTexture("gfx/points.png");

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Fruit::draw()
{
    blit(texture, x, y);
}

int Fruit::getPositionX()
{
    return x;
}

int Fruit::getPositionY()
{
    return y;
}

int Fruit::getWidth()
{
    return width;
}

int Fruit::getHeight()
{
    return height;
}

void Fruit::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
