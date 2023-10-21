#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Explosion.h"
#include "PowerUp.h"
#include "Boss.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	float spawnTime;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points;

	SDL_Texture* backgroundTexture;

	void spawnPowerUp();
	void despawnPowerUp(PowerUp* powerUp);

	float currentSpawnTimerPowerUp; 
	std::vector<PowerUp*> spawnedPowerUps;

	int isActiveTimer;

	void spawnBoss();
	void despawnBoss(Boss* boss);
	std::vector<Boss*> spawnedBoss;
	int hitCount;

};