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

    x = (SCREEN_WIDTH - width) / 2;
    y = SCREEN_HEIGHT - height - 50;
    width = 0;
    height = 0;
    speed = 7;
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
        if (bullets[i]->getPositionY() < 0) {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
            break;
        }
    }

    if (!isAlive) return;

    if (app.keyboard[SDL_SCANCODE_W] && y > 0) {
        y -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_S] && y + height < SCREEN_HEIGHT) {
        y += speed;
    }

    if (app.keyboard[SDL_SCANCODE_A] && x > 0) {
        x -= speed;
    }

    if (app.keyboard[SDL_SCANCODE_D] && x + width < SCREEN_WIDTH) {
        x += speed;
    }

    if (currentReloadTime > 0) {
        currentReloadTime--;
    }

    if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0) {
        SoundManager::playSound(sound);

        // Shooting a single bullet from the center
        Bullet* bullet = new Bullet(x + width / 2, y - 2, 0, -1, 10, Side::PLAYER_SIDE);
        bullets.push_back(bullet);
        getScene()->addGameObject(bullet);
        bullet->start();

        if (isActive) {
            // Shooting two extra bullets from the sides when isActive is true
            int extraBulletOffset = 20; // Adjust the offset as needed
            Bullet* leftBullet = new Bullet(x + width / 2 - extraBulletOffset, y - 2, -1, -1, 10, Side::PLAYER_SIDE);
            Bullet* rightBullet = new Bullet(x + width / 2 + extraBulletOffset, y - 2, 1, -1, 10, Side::PLAYER_SIDE);

            bullets.push_back(leftBullet);
            bullets.push_back(rightBullet);

            getScene()->addGameObject(leftBullet);
            getScene()->addGameObject(rightBullet);

            leftBullet->start();
            rightBullet->start();
        }

        currentReloadTime = reloadTime;
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

bool Player::getIsActive()
{

    return isActive;

}

void Player::setIsActive(bool active)
{

    isActive = active;

}