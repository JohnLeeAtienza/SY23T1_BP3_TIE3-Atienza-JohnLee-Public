#include "Boss.h"

Boss::Boss()
{
    hitCount = 0;
}

Boss::~Boss()
{
}

void Boss::start()
{

    texture = loadTexture("gfx/4321.png");

    directionX = 1; 
    directionY = 1; 
    width = 0;
    height = 0;
    speed = 2;
    reloadTime = 30;
    currentReloadTime = 0;
    directionChangeTime = (rand() % 300) + 180;
    currentDirectionChangeTime = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
    sound->volume = 64;

}

void Boss::update()
{

    if (y < SCREEN_HEIGHT / 2) {
        y += directionY * speed;
    }
    else {

        if (x <= 0 || x >= SCREEN_WIDTH - width) {
            directionX = -directionX;
        }

        x += directionX * speed;


        float bulletSpawnX = x + (width / 2); 
        float bulletSpawnY = y + (height / 2); 

        if (currentReloadTime > 0) {
            currentReloadTime--;
        }

        if (currentReloadTime == 0) {
            SoundManager::playSound(sound);

            float playerX = playerTarget->getPositionX();
            float playerY = playerTarget->getPositionY();

 
            float dx, dy;
            calcSlope(playerX, playerY, bulletSpawnX, bulletSpawnY, &dx, &dy);


            Bullet* mainBullet = new Bullet(bulletSpawnX, bulletSpawnY, dx, dy, 10, Side::ENEMY_SIDE);
            bullets.push_back(mainBullet);
            getScene()->addGameObject(mainBullet);


            int extraBulletOffset = 20; 
            for (int i = -1; i <= 1; i += 2) {
                Bullet* extraBulletLeft = new Bullet(bulletSpawnX, bulletSpawnY, dx + i * 0.2f, dy, 10, Side::ENEMY_SIDE);
                bullets.push_back(extraBulletLeft);
                getScene()->addGameObject(extraBulletLeft);

                Bullet* extraBulletRight = new Bullet(bulletSpawnX, bulletSpawnY, dx + i * 0.4f, dy, 10, Side::ENEMY_SIDE);
                bullets.push_back(extraBulletRight);
                getScene()->addGameObject(extraBulletRight);
            }

            currentReloadTime = reloadTime;
        }
    }

}

void Boss::draw()
{

    blit(texture, x, y);

}

void Boss::setPlayerTarget(Player* player)
{

    playerTarget = player;

}

void Boss::setPosition(int x, int y)
{

    this->x = x;
    this->y = y;

}

int Boss::getPositionX()
{
    return x;
}

int Boss::getPositionY()
{
    return y;
}

int Boss::getWidth()
{
    return width;
}

int Boss::getHeight()
{
    return height;
}