#pragma once
#include "IGameObject.h"
#include "GameObject.h"
class Ship : public DestructibleObject
{
public:
	friend FenceShip;
	Ship(IGameObjectContainer* scene, IShapeSFML* background);
	~Ship();

	void ProssesInput(const sf::Event& event) override;

	void physics();

	void Update(const float& deltatime) override;
	void Render() override;

	float anglecalcul();

private:
	IShapeSFML* m_background;
	KT::VectorND<float, 4> m_velocity;
	float m_angle;
	Timer m_elapsedTime;
	
	//TODO
	//Modify this with StateMachin
	float cooldown;
	bool m_boost;
	float dashSpeed;
	AnimateSprite m_animate;
	IPhysics* m_phisics;
};