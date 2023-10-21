#pragma once
#include "GameObject.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"
class Boss :
    public GameObject
{

public:
    Boss();
    ~Boss();
    void start();
    void update();
    void draw();
    void setPlayerTarget(Player* player);
    void setPosition(int x, int y);

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    Player* playerTarget;
    int x;
    int y;
    float directionX;
    float directionY;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;
    std::vector<Bullet*> bullets;

    int hitCount;
};