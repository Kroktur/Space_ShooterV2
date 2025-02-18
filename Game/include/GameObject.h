#pragma once
#include "IGameObject.h"
#include "SceneBase.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
class Ship;
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
	void ExecutePhysics(KT::VectorND<bool, 4>& isStrafing, KT::VectorND<float, 4>& velocity)
	{
		if (isStrafing[trust::Right] == true)
		{
			velocity[trust::Right] += m_acceleration;
			if (velocity[trust::Right] > m_maxVelocity) velocity[trust::Right] = m_maxVelocity;
		}
		else
		{
			velocity[0] -= m_deceleration;
			if (velocity[0] < 0) velocity[0] = 0;
		}
		if (isStrafing[trust::Left] == true)
		{
			velocity[trust::Left] += m_acceleration;
			if (velocity[trust::Left] > m_maxVelocity) velocity[trust::Left] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Left] -= m_deceleration;
			if (velocity[trust::Left] < 0) velocity[trust::Left] = 0;
		}
		if (isStrafing[trust::Up] == true)
		{
			velocity[trust::Up] += m_acceleration;
			if (velocity[trust::Up] > m_maxVelocity) velocity[trust::Up] = m_maxVelocity;
		}
		else
		{
			velocity[trust::Up] -= m_deceleration;
			if (velocity[trust::Up] < 0) velocity[trust::Up] = 0;
		}
		if (isStrafing[trust::Down] == true)
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


class IFence : public NonDestructibleObject
{
public:

	IFence(ISceneBase* scene ,const sf::Vector2f& Center):NonDestructibleObject(scene),m_center(Center){}
	void ProssesInput(const sf::Event& event) override = 0;
	void Update(const float& deltatime) override = 0;
	void Render() override = 0;
protected:
	sf::Vector2f m_center;
};
class FenceShip : public IFence
{
public:
	friend Ship;
	FenceShip(ISceneBase* scene, const sf::Vector2f& Center, Ship* ship);
	void ProssesInput(const sf::Event& event) override{}
	void Update(const float& deltatime) override;
	void Render() override;

private:
	sf::Vector2f VerifyLimit();
	CircleSFML m_circle;
	Ship* m_ship;
	AnimateSprite m_sprite;
	bool IsInBorder;
};
