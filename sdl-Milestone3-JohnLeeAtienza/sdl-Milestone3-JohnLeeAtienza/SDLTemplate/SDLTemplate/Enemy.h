#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class GameScene;

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();
    void start();
    void update();
    void draw();
    void setPlayerTarget(Player* player);
    void setPosition(int xPos, int yPos);
    bool isActive() const;

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
    GameScene* scene;
    bool active;

};

