#include "ISpawner.h"

#include <iostream>

#include "GameObject.h"

void AsteroidSpawner::Spawn()
{
	if (getChildren().Size() >= m_maxEntity)
		return;
	sf::Vector2f size;
	size.x = UseRandomNumber().getRandomNumber(150, 400);
	size.y= UseRandomNumber().getRandomNumber(150, 400);

	float angle = UseRandomNumber().getRandomNumber(0, 360);
	float speed = UseRandomNumber().getRandomNumber(75, 150);
	float life = UseRandomNumber().getRandomNumber(2, 8);




	auto spawn = RandomSpanw::getPosition(m_SpawnZone,m_RestrictedArea, sf::Vector2f( size.x / 2 ,size.y / 2));
	new Asteroid(this, spawn, size, angle, speed, life);
}
