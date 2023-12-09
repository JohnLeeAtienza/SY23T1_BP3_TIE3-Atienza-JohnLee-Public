#include "Snake.h"
#include "util.h"
#include "input.h"

const int FRAME_RATE = 10;

void Snake::start()
{
    texture = loadTexture("gfx/Snake.png");
    x = 0;
    y = 0;
    width = 0;
    height = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    for (int i = 0; i < INITIAL_BODY_LENGTH; i++) {
        BodyPart part;
        part.x = x - i * (width + BODY_SPACING);
        part.y = y;
        bodyParts.push_back(part);
    }

    directionX = 1;
    directionY = 0;
    isAlive = true;
}

void Snake::update()
{
    if (!isAlive) {
        return;
    }

    static long lastUpdate = SDL_GetTicks();

    if (app.keyboard[SDL_SCANCODE_W] && directionY == 0) {
        directionX = 0;
        directionY = -1;
    }
    else if (app.keyboard[SDL_SCANCODE_S] && directionY == 0) {
        directionX = 0;
        directionY = 1;
    }
    else if (app.keyboard[SDL_SCANCODE_A] && directionX == 0) {
        directionX = -1;
        directionY = 0;
    }
    else if (app.keyboard[SDL_SCANCODE_D] && directionX == 0) {
        directionX = 1;
        directionY = 0;
    }

    long currentTicks = SDL_GetTicks();
    if (currentTicks - lastUpdate >= 1000 / FRAME_RATE) {

        for (int i = bodyParts.size() - 1; i > 0; i--) {
            bodyParts[i] = bodyParts[i - 1];
        }

        bodyParts[0].x = x;
        bodyParts[0].y = y;

        x += directionX * (width + BODY_SPACING);
        y += directionY * (height + BODY_SPACING);

        lastUpdate = currentTicks;
    }
}

void Snake::draw()
{
    if (isAlive) {
        blit(texture, x, y);

        for (const auto& part : bodyParts) {
            blit(texture, part.x, part.y);
        }
    }
}

int Snake::getPositionX()
{
    return x;
}

int Snake::getPositionY()
{
    return y;
}

int Snake::getWidth()
{
    return width;
}

int Snake::getHeight()
{
    return height;
}

bool Snake::getIsAlive()
{
    return isAlive;
}

void Snake::doDeath()
{
    isAlive = false;
}

int Snake::getBodySize()
{
    return bodyParts.size();
}

int Snake::getBodyPartX(int index)
{
    return bodyParts[index].x;
}

int Snake::getBodyPartY(int index)
{
    return bodyParts[index].y;
}

void Snake::addBodySegment()
{
    BodyPart newPart;
    newPart.x = bodyParts.back().x;
    newPart.y = bodyParts.back().y;
    bodyParts.push_back(newPart);
}

void Snake::reset()
{
    x = 0;
    y = 0;
    directionX = 1;
    directionY = 0;
    bodyParts.clear();

    for (int i = 0; i < INITIAL_BODY_LENGTH; i++) {
        BodyPart part;
        part.x = x - i * (width + BODY_SPACING);
        part.y = y;
        bodyParts.push_back(part);
    }

    isAlive = true;
}

