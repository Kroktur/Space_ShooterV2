#pragma once
#include "IGameObject.h"
#include "SceneBase.h"
#include "KT_Math_Algorithm.h"
#include "KT_Array.h"
#include "KT_VectorND.h"
#include "IShape.h"
class Ship;
enum trust
{

	Right = 0
	, Left = 1
	, Up = 2
	, Down = 3
	, Default = 4
};
class Cursor : public NonDestructibleObject ,public ILeaf
{
public:
	Cursor(IComposite* scene);
	void ProssesInput(const sf::Event& event) override;

	void Update(const float& deltatime) override;

	void Render() override;

private:
	AnimateSprite m_animate;
};

class MovementInSpace : public IPhysics
{
public:
	MovementInSpace(const float& maxVelority, const float& acceleratrion, const float& deceleration);
	void ExecutePhysics(KT::VectorND<bool, 4>& isStrafing, KT::VectorND<float, 4>& velocity);

	sf::Vector2f calculPosition(IShapeSFML* entity, ISceneBase* scene, KT::VectorND<float, 4>& velocity);
	float getMaxVelocity()
	{
		return m_maxVelocity;
	}
private:
	float m_maxVelocity;
	float m_acceleration;
	float m_deceleration;
};


class IFence : public NonDestructibleObject , public ILeaf
{
public:

	IFence(IComposite* scene, IShapeSFML* object);
	void ProssesInput(const sf::Event& event) override = 0;
	void Update(const float& deltatime) override = 0;
	void Render() override = 0;
protected:
	IShapeSFML* m_ObjectToProtect;
};
class FenceShip : public IFence
{
public:
	FenceShip(IComposite* scene, IShapeSFML* game_object, Ship* ship);
	void ProssesInput(const sf::Event& event) override {}
	void Update(const float& deltatime) override;
	void Render() override;

private:
	sf::Vector2f VerifyLimit();
	Ship* m_ship;
	AnimateSprite m_sprite;
	Timer m_elapsedTime;
	bool IsInBorder;
};
enum class Position
{
	Left
	, Right
	, Up
	, Down
};
class ExternFence : public IFence
{
public:
	ExternFence(IComposite* scene, IShapeSFML* game_object, Position pos, float BorderSize);
	void ProssesInput(const sf::Event& event) override {}
	void Update(const float& deltatime) override;
	void Render() override;
private:
	sf::Vector2f m_diffposition;
	float m_BorderSize;
};

class ITurret: public IGameObject , public IComposite
{
public:
	ITurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff);
	void ProssesInput(const sf::Event& event) override = 0;
	void Update(const float& deltatime) override = 0;
	void Render() override = 0;
	virtual void Fire() = 0;
	void SetFireRate(const float& fireRate);
	void SetOverloadGun(const float& overload);
protected:
	sf::Vector2f m_positionDiff;
	IShapeSFML* m_gameObject;
	Timer m_fireRate;
	Timer m_coolDown;
	
};

class FixTurret : public  ITurret
{
public:
	FixTurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff,float angle);
	void ProssesInput(const sf::Event& event) override{}
	void Update(const float& deltatime) override;
	void Render() override;
	void Fire() override{}
private:
	float m_angleDiff;
	SquareSFML BaseShape;
};


