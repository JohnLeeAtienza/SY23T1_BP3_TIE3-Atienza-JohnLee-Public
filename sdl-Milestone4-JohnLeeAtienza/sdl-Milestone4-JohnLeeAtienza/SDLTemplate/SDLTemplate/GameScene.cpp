#include "GameScene.h"
#include "draw.h"

GameScene::GameScene()
{
	backgroundTexture = loadTexture("gfx/background.png");

	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();

	initFonts();
	currentSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++) {

		spawn();

	}
}

void GameScene::draw()
{

	int backgroundScale = 3;
	int backgroundX = 0;
	int backgroundY = 0;
	int backgroundWidth, backgroundHeight;

	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);

	blitScale(backgroundTexture, backgroundX, backgroundY, &backgroundWidth, &backgroundHeight, backgroundScale);

	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false) {

		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER!");

	}

}

void GameScene::update()
{
	Scene::update();

	doSpawnLogic();
	doCollisionLogic();



}

void GameScene::doSpawnLogic()
{

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0) {

		for (int i = 0; i < 3; i++) {

			spawn();
			currentSpawnTimer = spawnTime;

		}
		currentSpawnTimer = spawnTime;
	}

}

void GameScene::doCollisionLogic()
{

	for (int i = 0; i < objects.size(); i++) {

		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL) {

			if (bullet->getSide() == Side::ENEMY_SIDE) {

				int collision = checkCollision(player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(), bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

				if (collision == 1) {

					player->doDeath();
					break;

				}

			}
			else if (bullet->getSide() == Side::PLAYER_SIDE) {

				for (int i = 0; i < spawnedEnemies.size(); i++) {

					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(), bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

					if (collision == 1) {

						despawnEnemy(currentEnemy);
						points++;
						break;

					}

				}

			}

		}

	}

}

void GameScene::spawn()
{

	int initialX = SCREEN_WIDTH;

	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(initialX, 300 + (rand() % 300));
	spawnedEnemies.push_back(enemy);

}

void GameScene::despawnEnemy(Enemy* enemy)
{

	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++) {

		if (enemy == spawnedEnemies[i]) {

			index = i;
			break;

		}

	}

	if (index != -1) {
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		Explosion* explosion = new Explosion(enemy->getPositionX(), enemy->getPositionY());
		this->addGameObject(explosion);
		delete enemy;
	}

}