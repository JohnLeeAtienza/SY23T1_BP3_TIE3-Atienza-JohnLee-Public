#pragma once
#include "GameObject.h"
#include "util.h"
#include <vector>
#include "draw.h"

#define INITIAL_BODY_LENGTH 3
#define BODY_SPACING 2

class Snake :
    public GameObject
{
public:
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive();
    void doDeath();
    int getBodySize();
    int getBodyPartX(int index);
    int getBodyPartY(int index);
    void addBodySegment();
    void reset();

private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
    int directionX;
    int directionY;

    struct BodyPart {
        int x;
        int y;
    };

    std::vector<BodyPart> bodyParts;

    bool isAlive;
};

