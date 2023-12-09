#include "GameScene.h"

GameScene::GameScene()
{
    snake = new Snake();
    this->addGameObject(snake);

    fruit = nullptr;
    points = 0;
    highscore = 0;
    gameOver = false;
}

GameScene::~GameScene()
{
    delete snake;

    if (fruit != nullptr) {
        despawnFruit(fruit);
    }
}

void GameScene::start()
{
    Scene::start();

    initFonts();
}

void GameScene::draw()
{
    Scene::draw();

    if (!gameOver) {
        drawText(110, 20, 225, 225, 225, TEXT_CENTER, "POINTS: %03d", points);
        drawText(140, 50, 225, 225, 225, TEXT_CENTER, "HIGHSCORE: %03d", highscore);
    }
    else {
        drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 225, 225, 225, TEXT_CENTER, "GAME OVER! TRY AGAIN!");
        drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, 225, 225, 225, TEXT_CENTER, "'R'");
    }

}

void GameScene::update()
{
    Scene::update();

    if (!gameOver) {
        doCollisionLogic();
        spawnFruit();
    }
    else {
        if (app.keyboard[SDL_SCANCODE_R]) {
            resetGame();
        }
    }
}

void GameScene::spawnFruit()
{
    if (fruit == nullptr) {
        fruit = new Fruit();
        this->addGameObject(fruit);

        fruit->setPosition(rand() % (SCREEN_WIDTH - GLYPH_WIDTH), rand() % (SCREEN_HEIGHT - GLYPH_HEIGHT));
    }
}

void GameScene::despawnFruit(Fruit* fruit)
{
    this->removeGameObject(fruit);
    this->fruit = nullptr;
}

void GameScene::doCollisionLogic()
{
    if (snake->getPositionX() < 0 || snake->getPositionX() >= SCREEN_WIDTH ||
        snake->getPositionY() < 0 || snake->getPositionY() >= SCREEN_HEIGHT) {
        snake->doDeath();
        gameOver = true;
        if (points > highscore) {
            highscore = points;
        }
    }

    for (int i = 1; i < snake->getBodySize(); i++) {
        if (snake->getPositionX() == snake->getBodyPartX(i) && snake->getPositionY() == snake->getBodyPartY(i)) {
            snake->doDeath();
            gameOver = true;
            if (points > highscore) {
                highscore = points;
            }
            break;
        }
    }

    for (int i = 0; i < objects.size(); i++) {
        Fruit* fruitCollision = dynamic_cast<Fruit*>(objects[i]);

        if (fruitCollision != nullptr) {
            int collision = checkCollision(snake->getPositionX(), snake->getPositionY(), snake->getWidth(), snake->getHeight(),
                fruitCollision->getPositionX(), fruitCollision->getPositionY(), fruitCollision->getWidth(), fruitCollision->getHeight());

            if (collision == 1) {

                points += 1;

                snake->addBodySegment();

                despawnFruit(fruitCollision);

                spawnFruit();
                break;
            }
        }
    }
}

void GameScene::resetGame()
{

    points = 0;
    gameOver = false;

    snake->reset();

    despawnFruit(fruit);
    spawnFruit();
}











