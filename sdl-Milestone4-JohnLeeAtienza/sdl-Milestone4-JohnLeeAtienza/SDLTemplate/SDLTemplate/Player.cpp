#include "Player.h"
#include "Scene.h"
#include "Bullet.h"

Player::~Player()
{

	for (int i = 0; i < bullets.size(); i++) {

		delete bullets[i];

	}
	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 8;
	currentReloadTime = 0;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

	wingtipBulletCooldown1 = 20;
	wingtipBulletCooldown2 = 30;
	fireWingtip1Next = true;
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++) {

		if (bullets[i]->getPositionX() > SCREEN_WIDTH) {

			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}

	}

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_LSHIFT]) {
		speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE]) {
		speed = 2;
	}

	if (app.keyboard[SDL_SCANCODE_W]) {
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S]) {
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A]) {
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D]) {
		x += speed;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	if (wingtipBulletCooldown1 > 0)
		wingtipBulletCooldown1--;

	if (wingtipBulletCooldown2 > 0)
		wingtipBulletCooldown2--;

	int wingtipBulletOffsetY1 = -25;
	int wingtipBulletOffsetY2 = 25;

	if (app.keyboard[SDL_SCANCODE_G]) {
		if (wingtipBulletCooldown1 == 0) {
			SoundManager::playSound(sound);
			Bullet* bullet1 = new Bullet(x + width, y - 2 + height / 2 + wingtipBulletOffsetY1, 1, 0, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet1);
			getScene()->addGameObject(bullet1);
			bullet1->start();
			wingtipBulletCooldown1 = 30;
		}

		if (wingtipBulletCooldown2 == 0) {
			SoundManager::playSound(sound);
			Bullet* bullet2 = new Bullet(x + width, y - 2 + height / 2 + wingtipBulletOffsetY2, 1, 0, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet2);
			getScene()->addGameObject(bullet2);
			bullet2->start();
			wingtipBulletCooldown2 = 30;
		}
	}

}

void Player::draw()
{
	if (!isAlive) return;

	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}