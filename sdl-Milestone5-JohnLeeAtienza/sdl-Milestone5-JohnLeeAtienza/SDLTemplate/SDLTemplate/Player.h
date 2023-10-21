#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "PowerUp.h"
#include <vector>
class Player :
    public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive();
    void doDeath();

    bool getIsActive();

    void setIsActive(bool active);
private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    int x;
    int y;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;
    std::vector<Bullet*> bullets;
    float wingtipBulletCooldown1;
    float wingtipBulletCooldown2;
    bool fireWingtip1Next;
    int wingtipBulletOffsetY1;
    int wingtipBulletOffsetY2;
    bool isAlive;

    bool isActive;
};