#include "Explosion.h"
#include "draw.h"
#include <SDL_image.h> 
#include <SDL_timer.h>

Explosion::Explosion(int x, int y) {
    this->x = x;
    this->y = y;
    texture = loadTexture("gfx/explosion.png");
    frameWidth = 64;  
    frameHeight = 64; 
    totalFrames = 16;  
    frameDuration = 3; 
    frameTimer = frameDuration;
    width = frameWidth;
    height = frameHeight;
    currentFrame = 0;
    startTime = SDL_GetTicks(); 
    finished = false;
}

void Explosion::start() {
  
}

void Explosion::update() {
    
    if (!finished) {
        if (--frameTimer <= 0) {
            ++currentFrame;
            if (currentFrame >= totalFrames) {
                currentFrame = 0;
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - startTime >= 100) {
                    finished = true;
                }
            }
            frameTimer = frameDuration;
        }
    }
}

void Explosion::draw() {
    if (!finished && texture != nullptr) {
        int frameX = (currentFrame % (totalFrames / 4)) * frameWidth;
        int frameY = (currentFrame / (totalFrames / 4)) * frameHeight;
        blit(texture, x, y);
    }
}

bool Explosion::isFinished() const {
    return finished;
}
