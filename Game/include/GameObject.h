#pragma once
#include "IGameObject.h"
#include "SceneBase.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
//TODO
#include "iostream"
enum trust
{
	Right = 0
	,Left = 1
	,Up = 2
	,Down = 3
};
struct MyVec2
{
	MyVec2(float x_, float y_) : x(x_), y(y_) {}
	float x;
	float y;
	KT::VectorND<float, 2> getVectorNd()
	{
		data[0] = x;
		data[1] = y;
		return data;
	}
private:
	KT::VectorND<float, 2> data;
};

class Ship : public DestructibleObject
{
public:
	Ship(ISceneBase* scene, sf::RectangleShape* background) :
	DestructibleObject(scene, 10)
	, m_background(background)
	, m_ship(sf::Vector2f(100, 100))
	, m_moove(0, 0)
	, m_velocity({0,0,0,0})
	, m_maxVelocity(1500)
	, m_acceleration(0.30f)
	,m_deceleration(0.30f)
	, m_angle(0)
	, m_elapsedTime(0)
	,m_speed(25)
	{

		m_ship.setOrigin(m_ship.getSize().x / 2, m_ship.getSize().y / 2);
		m_ship.setPosition(m_scene->getWindow()->getSize().x / 2, m_scene->getWindow()->getSize().y / 2);
		m_texturepath.pushBack("SpaceHero.png");
		m_texturepath.pushBack("SpaceHero2.png");
		curenttextureidx = 1;
		m_ship.setTexture(&m_scene->getTexture()->getTexture(m_texturepath[curenttextureidx]));
	}
	void ProssesInput(const sf::Event& event) override
	{
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
				m_velocity[trust::Right] += m_acceleration;
			if (m_velocity[trust::Right] > m_maxVelocity) m_velocity[trust::Right] = m_maxVelocity;
		}
		else
		{
			m_velocity[0] -= m_deceleration;
			if (m_velocity[0] < 0) m_velocity[0] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
		{
			m_velocity[trust::Left] += m_acceleration;
			if (m_velocity[trust::Left] > m_maxVelocity) m_velocity[trust::Left] = m_maxVelocity;
		}
		else 
		{
			m_velocity[trust::Left] -= m_deceleration;
			if (m_velocity[trust::Left] < 0) m_velocity[trust::Left] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
				m_velocity[trust::Up] += m_acceleration;
			if (m_velocity[trust::Up] > m_maxVelocity) m_velocity[trust::Up] = m_maxVelocity;
		}
		else
		{
			m_velocity[trust::Up] -= m_deceleration;
			if (m_velocity[trust::Up] < 0) m_velocity[trust::Up] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
				m_velocity[trust::Down] += m_acceleration;
			if (m_velocity[trust::Down] > m_maxVelocity) m_velocity[trust::Down] = m_maxVelocity;
		}
		else
		{
			m_velocity[trust::Down] -= m_deceleration;
			if (m_velocity[trust::Down] < 0) m_velocity[trust::Down] = 0;
		}
		physics();
	}
	void physics()
	{
		m_angle = anglecalcul();
	}
	sf::Vector2f calculPosition()
	{
		auto x = m_velocity[trust::Left] - m_velocity[trust::Right];
		auto y = m_velocity[trust::Up] - m_velocity[trust::Down];
		sf::Vector2f Newposition = { m_background->getPosition().x +( (x * m_scene->getRefreshTime().asSeconds())),m_background->getPosition().y + ((y * m_scene->getRefreshTime().asSeconds())) };
		return Newposition;
	}
	void changeFrame()
	{
		if (curenttextureidx == m_texturepath.Size() - 1)
			curenttextureidx = 0;
		else
			++curenttextureidx;

	}
	void Update(const float& deltatime) override
	{
		m_ship.setRotation(m_angle);

		m_background->setPosition(calculPosition());
		m_elapsedTime += deltatime;
		if (m_elapsedTime >= m_speed) {
			m_elapsedTime = 0.0f;

			changeFrame();
			m_ship.setTexture(&m_scene->getTexture()->getTexture(m_texturepath[curenttextureidx]));
		}
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
	MyVec2 m_moove;
	KT::VectorND<float,4> m_velocity;
	float m_maxVelocity;
	float m_acceleration;
	float m_deceleration;
	float m_angle;
	KT::Vector<std::string> m_texturepath;
	float curenttextureidx;
	float m_elapsedTime;
	float m_speed;

};
