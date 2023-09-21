#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;

	// Delete all the spawned enemies
	for (Enemy* enemy : spawnedEnemies)
	{
		delete enemy;
	}
	spawnedEnemies.clear();
}

void GameScene::start()
{
	Scene::start();
	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 2; i++)
	{
		Enemy* enemy = new Enemy();
		this->addGameObject(enemy);
		enemy->setPlayerTarget(player);
		enemy->setPosition(SCREEN_WIDTH - 100, 300 + (rand() % 300));
		spawnedEnemies.push_back(enemy);
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();


	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			spawn();
			currentSpawnTimer = spawnTime;
		}
	}
}

void GameScene::spawn()
{
	for (int i = 0; i < 2; i++)
	{
		Enemy* enemy = new Enemy();
		this->addGameObject(enemy);
		enemy->setPlayerTarget(player);

		enemy->setPosition(SCREEN_WIDTH + 100, 300 + (rand() % 300));
		spawnedEnemies.push_back(enemy);
	}
}
