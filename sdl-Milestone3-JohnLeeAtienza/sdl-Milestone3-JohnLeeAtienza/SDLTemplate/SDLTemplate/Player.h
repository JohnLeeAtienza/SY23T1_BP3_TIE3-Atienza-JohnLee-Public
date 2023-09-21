#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player :  public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
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
    int leftWingBulletCooldown = 30;    
    int rightWingBulletCooldown = 40; 
    int currentLeftWingBulletCooldown = 0;
    int currentRightWingBulletCooldown = 0;
};

