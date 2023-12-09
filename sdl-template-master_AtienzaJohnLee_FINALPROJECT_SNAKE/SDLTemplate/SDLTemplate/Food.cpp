#include "Food.h"
#include "draw.h"

void Food::start() {
    texture = loadTexture("gfx/points.png");
    spawn();
}

void Food::spawn() {
    x = rand() % (SCREEN_WIDTH / GLYPH_WIDTH) * GLYPH_WIDTH;
    y = rand() % (SCREEN_HEIGHT / GLYPH_HEIGHT) * GLYPH_HEIGHT;
}

void Food::draw() {
    blit(texture, x, y);
}

int Food::getX() {
    return x;
}

int Food::getY() {
    return y;
}

bool Food::checkCollision(int x, int y, int width, int height) {
    // Check collision with another game object
    return (x < this->x + GLYPH_WIDTH &&
        x + width > this->x &&
        y < this->y + GLYPH_HEIGHT &&
        y + height > this->y);
}

bool Food::checkCollisionWithSnake(const Snake& snake) {
    // Check collision with the entire area occupied by the snake's body
    for (const auto& part : snake.getBodyParts()) {
        if (checkCollision(part.x, part.y, GLYPH_WIDTH, GLYPH_HEIGHT)) {
            return true;
        }
    }
    return false;
}