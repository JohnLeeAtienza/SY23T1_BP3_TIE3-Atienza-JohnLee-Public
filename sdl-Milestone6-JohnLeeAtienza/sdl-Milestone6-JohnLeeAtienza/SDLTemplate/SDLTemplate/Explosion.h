#pragma once
#include "GameObject.h"
#include <SDL.h>

class Explosion : public GameObject {
public:
    Explosion(int x, int y);
    void start();
    void update();
    void draw();
    bool isFinished() const;
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;
    int currentFrame;
    int totalFrames;
    int frameWidth;
    int frameHeight;
    int frameDuration;
    int frameTimer;
    Uint32 startTime;
    bool finished;
};
