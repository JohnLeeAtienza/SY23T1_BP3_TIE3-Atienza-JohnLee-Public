#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "draw.h"
#include "text.h"
#include "Snake.h"
#include "Fruit.h"

class GameScene :
    public Scene
{
public:
    GameScene();
    ~GameScene();

    void start();
    void draw();
    void update();

private:
    Snake* snake;
    Fruit* fruit;

    int points;
    int highscore;

    bool gameOver;

    void spawnFruit();
    void despawnFruit(Fruit* fruit);
    void doCollisionLogic();

    void resetGame();
};
