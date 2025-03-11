#pragma once
#include "IGameObject.h"
#include "GameObject.h"
class Ship : public DestructibleObject, public IComposite
{
public:
	
	Ship(IComposite* scene, IShapeSFML* background , sf::View* view);
	~Ship();

	void ProssesInput(const sf::Event& event) override;
	//IShapeSFML* getShape() override;
	void physics();

	void Update(const float& deltatime) override;
	void Render() override;
	AABB GetBoundingBox() override;
	float anglecalcul();
	void HandleCollision(IGameObject* object) override;
	void ChangeLife(const float& life) override
	{
		if (!m_invisibility.ActionIsReady())
			return;

		m_life += life;
		if (m_life <= 0)
			destroy();
		m_invisibility.resetTimer();
	}

private:
	float m_angle;
	Timer m_elapsedTime;
	Timer m_invisibility;
	AnimateSprite m_animate;
	IPhysics* m_phisics;
	KT::Array<ITurret*,2> m_turrets;
	KT::VectorND<bool, 4> m_strafe{ false,false,false,false };
	sf::View* m_view;
	sf::Vector2f m_lastPosition;
};

