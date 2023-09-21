#include "Player.h"
#include "Scene.h"

Player::~Player()
{
    for (int i = 0; i < bullets.size(); i++)
    {
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
    reloadTime = 10;
    currentReloadTime = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}


void Player::update()
{
    if (app.keyboard[SDL_SCANCODE_W])
    {
        y -= speed;
    }
    if (app.keyboard[SDL_SCANCODE_S])
    {
        y += speed;
    }
    if (app.keyboard[SDL_SCANCODE_A])
    {
        x -= speed;
    }
    if (app.keyboard[SDL_SCANCODE_D])
    {
        x += speed;
    }

    if (currentReloadTime > 0)
        currentReloadTime--;

    if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
    {
        SoundManager::playSound(sound);
        Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
        bullets.push_back(bullet);
        getScene()->addGameObject(bullet);
        bullet->start();

        currentReloadTime = reloadTime;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPositionX() > SCREEN_WIDTH)
        {
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;
            break;
        }
    }

    if (app.keyboard[SDL_SCANCODE_G]) {
        if (currentLeftWingBulletCooldown == 0) {
            SoundManager::playSound(sound);

            Bullet* primaryBullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
            bullets.push_back(primaryBullet);
            getScene()->addGameObject(primaryBullet);
            primaryBullet->start();

            Bullet* leftWingBullet = new Bullet(x + width, y - 2, 1, -0.5, 10);
            bullets.push_back(leftWingBullet);
            getScene()->addGameObject(leftWingBullet);
            leftWingBullet->start();

            currentLeftWingBulletCooldown = leftWingBulletCooldown;
        }

        if (currentRightWingBulletCooldown == 0) {
            SoundManager::playSound(sound);

            Bullet* rightWingBullet = new Bullet(x + width, y - 2 + height, 1, 0.5, 10);  // Adjust the direction as needed
            bullets.push_back(rightWingBullet);
            getScene()->addGameObject(rightWingBullet);
            rightWingBullet->start();

            currentRightWingBulletCooldown = rightWingBulletCooldown;
        }
    }

    if (currentReloadTime > 0)
        currentReloadTime--;

    if (currentLeftWingBulletCooldown > 0)
        currentLeftWingBulletCooldown--;

    if (currentRightWingBulletCooldown > 0)
        currentRightWingBulletCooldown--;
}

void Player::draw()
{
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
