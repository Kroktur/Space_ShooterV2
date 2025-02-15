#pragma once
#include "IGameObject.h"
#include "SceneBase.h"
class Ship : public DestructibleObject
{
public:
	Ship(ISceneBase* scene,sf::RectangleShape* background):DestructibleObject(scene,10), m_background(background),m_ship(sf::Vector2f(100,100)), moove(0,0)
	{
		m_ship.setOrigin(m_ship.getSize().x / 2, m_ship.getSize().y / 2);
		m_ship.setPosition(m_scene->getWindow()->getSize().x / 2, m_scene->getWindow()->getSize().y / 2);
		m_ship.setTexture(&m_scene->getTexture()->getTexture("SpaceHero.png"));
	}
	void ProssesInput(const sf::Event& event) override
	{
		moove = { 0,0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moove += { -5.f, 0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			moove += { 5.f,0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moove += { 0, -5.f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			moove += { 0, 5.f };
	}
	void Update(const float& deltatime) override
	{
		m_ship.setRotation(anglecalcul());
		m_background->move(moove);
	
	}
	void Render() override { m_scene->getWindow()->draw(m_ship); }
	float anglecalcul()
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getWindow());
		sf::Vector2f shipPos = m_ship.getPosition();
		float deltaX = mousePos.x - shipPos.x;
		float deltaY = mousePos.y - shipPos.y;
		float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
		return angle;
	}
private:
	sf::RectangleShape* m_background;
	sf::RectangleShape m_ship;
	sf::Vector2f moove;
};