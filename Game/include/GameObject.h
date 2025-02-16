#pragma once
#include "IGameObject.h"
#include "SceneBase.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
enum trust
{

	Right = 0
	,Left = 1
	,Up = 2
	,Down = 3
	,Default = 4
};
class Cursor : public NonDestructibleObject
{
public:
	Cursor(ISceneBase* scene):
	NonDestructibleObject(scene)
	, m_crossair(86,scene)
		,m_animate(0,{"Crossair.png","Crossair2.png","Crossair3.png"})
	{
		m_crossair.getShape().setTexture(&m_scene->getTexture()->getTexture(m_animate.getPath()));
		m_crossair.getShape().setPosition(sf::Vector2f{ 50,50 });
		m_crossair.getShape().setOrigin(sf::Vector2f(m_crossair.getShape().getSize().x / 2, m_crossair.getShape().getSize().y / 2));
	}
	void ProssesInput(const sf::Event& event) override{}
	void Update(const float& deltatime) override
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getWindow());
		m_crossair.getShape().setPosition(mousePos.x,mousePos.y);
	}
	void Render() override
	{
		m_scene->getWindow()->draw(m_crossair.getShape());
	}
private:
	AnimateSprite m_animate;
	SquareSFML m_crossair;
};

class MovementInSpace : public IPhysics
{
public:
	MovementInSpace(const float& maxVelority, const float& acceleratrion, const float& deceleration):m_maxVelocity(maxVelority),m_acceleration(acceleratrion),m_deceleration(deceleration){}
	void ExecutePhysics(KT::VectorND<float,4>& velocity)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity[trust::Right] += m_acceleration;
			if (velocity[trust::Right] > m_maxVelocity) velocity[trust::Right] = m_maxVelocity;
		}
		else
		{
			velocity[0] -= m_deceleration;
			if (velocity[0] < 0) velocity[0] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			velocity[trust::Left] += m_acceleration;
			if (velocity[trust::Left] > m_maxVelocity) velocity[trust::Left] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Left] -= m_deceleration;
			if (velocity[trust::Left] < 0) velocity[trust::Left] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			velocity[trust::Up] += m_acceleration;
			if (velocity[trust::Up] > m_maxVelocity) velocity[trust::Up] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Up] -= m_deceleration;
			if (velocity[trust::Up] < 0) velocity[trust::Up] = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			velocity[trust::Down] += m_acceleration;
			if (velocity[trust::Down] > m_maxVelocity) velocity[trust::Down] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Down] -= m_deceleration;
			if (velocity[trust::Down] < 0) velocity[trust::Down] = 0;
		}
	}
	void ExecutePhysics(trust key, KT::VectorND<float, 4>& velocity)
	{
		if (key == trust::Right)
		{
			velocity[trust::Right] += m_acceleration;
			if (velocity[trust::Right] > m_maxVelocity) velocity[trust::Right] = m_maxVelocity;
		}
		else
		{
			velocity[0] -= m_deceleration;
			if (velocity[0] < 0) velocity[0] = 0;
		}
		if (key == trust::Left)
		{
			velocity[trust::Left] += m_acceleration;
			if (velocity[trust::Left] > m_maxVelocity) velocity[trust::Left] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Left] -= m_deceleration;
			if (velocity[trust::Left] < 0) velocity[trust::Left] = 0;
		}
		if (key == trust::Up)
		{
			velocity[trust::Up] += m_acceleration;
			if (velocity[trust::Up] > m_maxVelocity) velocity[trust::Up] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Up] -= m_deceleration;
			if (velocity[trust::Up] < 0) velocity[trust::Up] = 0;
		}
		if (key == trust::Down)
		{
			velocity[trust::Down] += m_acceleration;
			if (velocity[trust::Down] > m_maxVelocity) velocity[trust::Down] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Down] -= m_deceleration;
			if (velocity[trust::Down] < 0) velocity[trust::Down] = 0;
		}
	}
	sf::Vector2f calculPosition(sf::RectangleShape& entity,ISceneBase* scene, KT::VectorND<float, 4>& velocity)
	{
		auto x = velocity[trust::Left] - velocity[trust::Right];
		auto y = velocity[trust::Up] - velocity[trust::Down];
		sf::Vector2f Newposition = { entity.getPosition().x + ((x * scene->getRefreshTime().asSeconds())),entity.getPosition().y + ((y * scene->getRefreshTime().asSeconds())) };
		return Newposition;
	}
	sf::Vector2f calculPosition(sf::CircleShape& entity, ISceneBase* scene, KT::VectorND<float, 4>& velocity)
	{
		auto x = velocity[trust::Left] - velocity[trust::Right];
		auto y = velocity[trust::Up] - velocity[trust::Down];
		sf::Vector2f Newposition = { entity.getPosition().x + ((x * scene->getRefreshTime().asSeconds())),entity.getPosition().y + ((y * scene->getRefreshTime().asSeconds())) };
		return Newposition;
	}
private:
	float m_maxVelocity;
	float m_acceleration;
	float m_deceleration;
};

class Ship : public DestructibleObject
{
public:
	Ship(ISceneBase* scene, sf::RectangleShape* background) :
	DestructibleObject(scene, 10)
	, m_background(background)
	, m_ship(150, scene)
	, m_velocity({0,0,0,0})
	, m_angle(0)
	, m_elapsedTime(0)
	,m_animate(50,{"SpaceHero.png", "SpaceHero2.png"})
		,m_phisics(1500,0.30f,0.30f)
	{

		m_ship.getShape().setTexture(&m_scene->getTexture()->getTexture(m_animate.getPath()));
	}
	void ProssesInput(const sf::Event& event) override
	{
		m_phisics.ExecutePhysics(m_velocity);
		
		physics();
	}
	void physics()
	{
		m_angle = anglecalcul();
	}
	
	void Update(const float& deltatime) override
	{
		m_ship.getShape().setRotation(m_angle);
		m_background->setPosition(m_phisics.calculPosition(*m_background,m_scene,m_velocity));
		m_elapsedTime += deltatime;
		if (m_animate.changeReady(m_elapsedTime)) {
			m_elapsedTime = 0.0f;
			m_animate.NextPath();
			m_ship.getShape().setTexture(&m_scene->getTexture()->getTexture(m_animate.getPath()));
		}
	}
	void Render() override { m_scene->getWindow()->draw(m_ship.getShape()); }

	float anglecalcul()
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getWindow());
		sf::Vector2f shipPos = m_ship.getShape().getPosition();
		float deltaX = mousePos.x - shipPos.x;
		float deltaY = mousePos.y - shipPos.y;
		float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
		return angle;
	}
private:
	sf::RectangleShape* m_background;
	KT::VectorND<float,4> m_velocity;
	float m_angle;
	float m_elapsedTime;


	AnimateSprite m_animate;
	SquareSFML m_ship;
	MovementInSpace m_phisics;
};
