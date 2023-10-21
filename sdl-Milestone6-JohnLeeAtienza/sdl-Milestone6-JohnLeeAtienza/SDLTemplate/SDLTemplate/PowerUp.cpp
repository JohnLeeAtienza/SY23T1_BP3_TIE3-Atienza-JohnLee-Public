#include "PowerUp.h"

PowerUp::PowerUp(float positionX, float positionY, float directionX, float directionY, float speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;

}

void PowerUp::start()
{

	texture = loadTexture("gfx/points.png");

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void PowerUp::update()
{

	x += directionX * speed;
	y += directionY * speed;

}

void PowerUp::draw()
{

	blit(texture, x, y);

}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}