#include "GameScene.h"
#include "draw.h"

GameScene::GameScene()
{
	backgroundTexture = loadTexture("gfx/background.png");

	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	isActiveTimer = 0;

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

	spawnPowerUp();

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

	for (int i = 0; i < objects.size(); i++) {
		PowerUp* powerUp = dynamic_cast<PowerUp*>(objects[i]);

		if (powerUp != nullptr) {
			int collision = checkCollision(player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(), powerUp->getPositionX(), powerUp->getPositionY(), powerUp->getWidth(), powerUp->getHeight());

			if (collision == 1) {
				despawnPowerUp(powerUp);

				// Set isActive to true when the player collects the power-up
				player->setIsActive(true);

				// Set isActiveTimer to 1800 for 30 seconds (assuming 60 frames per second)
				isActiveTimer = 500; // 60 fps * 30 seconds = 1800 frames

				break;
			}
		}
	}

	// Decrement the isActiveTimer if the player is active
	if (player->getIsActive() && isActiveTimer > 0) {
		isActiveTimer--;
	}
	else {
		// Reset isActive to false when the timer expires
		player->setIsActive(false);
	}

}

void GameScene::spawn()
{
	int initialX = rand() % SCREEN_WIDTH; // Randomize initial X position

	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(initialX, -enemy->getHeight()); // Set initial Y position to be above the screen
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

void GameScene::spawnPowerUp()
{
	if (currentSpawnTimerPowerUp >= spawnTime)
	{
		int initialX = rand() % SCREEN_WIDTH;
		int initialY = -30;

		float directionX = 0;
		float directionY = 1;

		float speed = 3;

		PowerUp* powerUp = new PowerUp(initialX, initialY, directionX, directionY, speed);
		this->addGameObject(powerUp);

		spawnedPowerUps.push_back(powerUp);

		currentSpawnTimerPowerUp = 0;
	}
	else
	{
		currentSpawnTimerPowerUp++;
	}

	for (int i = 0; i < spawnedPowerUps.size(); i++) {
		if (spawnedPowerUps[i]->getPositionY() > SCREEN_HEIGHT) {
			despawnPowerUp(spawnedPowerUps[i]);
		}
	}
}

void GameScene::despawnPowerUp(PowerUp* powerUp)
{

	int index = -1;
	for (int i = 0; i < spawnedPowerUps.size(); i++) {
		if (powerUp == spawnedPowerUps[i]) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete powerUp;
	}

}