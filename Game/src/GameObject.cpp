#include "GameObject.h"
#include "Ship.h"
#include "cmath"
#include <iostream>
FenceShip::FenceShip(IComposite* scene, IShapeSFML* game_object, Ship* ship) :
	IFence(scene, game_object)
	, m_ship(ship)
	, m_sprite({ "FenceTmp.png","FenceTmp2.png" })
	, IsInBorder(false)
	, m_elapsedTime(50)
{
	m_shape = new CircleSFML(m_ObjectToProtect->getSize().x / 2, m_ObjectToProtect->getCenter());
	m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_sprite.getCurrentPath()));
}

void FenceShip::Update(const float& deltatime)
{
	m_shape->setPosition(m_ObjectToProtect->getPosition());
	m_ship->m_background->setPosition(VerifyLimit());
	if (m_elapsedTime.AutoActionIsReady())
	{
		m_sprite.ChangeToNextPath();
		m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_sprite.getCurrentPath()));
	}
}

void FenceShip::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<CircleSFML*>(m_shape)->getShape());
}

sf::Vector2f FenceShip::VerifyLimit()
{

	sf::Vector2f centreBackground = m_ObjectToProtect->getPosition();
	sf::Vector2f positionVaisseau = m_ship->m_shape->getPosition();

	float dx = positionVaisseau.x - centreBackground.x;
	float dy = positionVaisseau.y - centreBackground.y;
	float distance = dx * dx + dy * dy;
	float Border = 2 * (m_shape->getSize().x / 30);
	float malocity = static_cast<MovementInSpace*>(m_ship->m_phisics)->getMaxVelocity();
	float radius = (m_shape->getSize().x / 2 - m_ship->m_shape->getSize().x - Border) * (m_shape->getSize().x / 2 - m_ship->m_shape->getSize().x - Border);
	if (distance > radius) {
		float factor = radius / distance;
		centreBackground.x = positionVaisseau.x - dx * factor;
		centreBackground.y = positionVaisseau.y - dy * factor;
		if (m_ship->m_velocity[0] > malocity / 2 || m_ship->m_velocity[1] > malocity / 2 || m_ship->m_velocity[2] > malocity / 2 || m_ship->m_velocity[3] > malocity / 2)
		{
			if (!IsInBorder)
			{
				IsInBorder = true;
				m_ship->ChangeLife(-1);
			}
		}

	}
	if (distance < (radius - (m_ship->m_shape->getSize().x) * (m_ship->m_shape->getSize().x)))
	{
		IsInBorder = false;
	}


	return centreBackground;
}

ExternFence::ExternFence(IComposite* scene, IShapeSFML* game_object, Position pos, float BorderSize) :IFence(scene, game_object), m_diffposition(0, 0), m_BorderSize(BorderSize)
{
	m_shape = new RectangleSFML(m_ObjectToProtect->getSize().x, m_ObjectToProtect->getSize().y, game_object->getCenter());
	switch (pos)
	{
	case Position::Up:
	{
		m_shape->setSize(sf::Vector2f(m_ObjectToProtect->getSize().x, m_BorderSize));
		m_diffposition.x = 0;
		m_diffposition.y = -(m_ObjectToProtect->getSize().y / 2 - m_BorderSize / 2);
		break;
	}
	case Position::Down:
	{
		m_shape->setSize(sf::Vector2f(m_ObjectToProtect->getSize().x, m_BorderSize));
		m_diffposition.x = 0;
		m_diffposition.y = m_ObjectToProtect->getSize().y / 2 + m_BorderSize / 2;
		break;
	}
	case Position::Left:
	{
		m_shape->setSize(sf::Vector2f(m_BorderSize, m_ObjectToProtect->getSize().x));
		m_diffposition.x = -(m_ObjectToProtect->getSize().y / 2 - m_BorderSize / 2);
		m_diffposition.y = 0;
		break;
	}
	case Position::Right:
	{
		m_shape->setSize(sf::Vector2f(m_BorderSize, m_ObjectToProtect->getSize().x));
		m_diffposition.x = +(m_ObjectToProtect->getSize().y / 2 - m_BorderSize / 2);
		m_diffposition.y = 0;
		break;
	}

	}
	m_shape->setCenter(sf::Vector2f(m_shape->getSize().x / 2, m_shape->getSize().y / 2));
}

void ExternFence::Update(const float& deltatime)
{
	m_shape->setPosition(sf::Vector2f(m_ObjectToProtect->getPosition().x + m_diffposition.x, m_ObjectToProtect->getPosition().y + m_diffposition.y));
}

void ExternFence::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<RectangleSFML*>(m_shape)->getShape());
}

ITurret::ITurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff): IGameObject(scene),IComposite(scene),m_positionDiff(positiondiff),m_gameObject(game_object),m_fireRate(15),m_coolDown(0)
{
	
}

void ITurret::SetFireRate(const float& fireRate)
{
	m_fireRate.setNewTimer(fireRate);
	
}

void ITurret::SetOverloadGun(const float& overload)
{
	m_coolDown.setNewTimer(overload);
}


FixTurret::FixTurret(IComposite* scene, IShapeSFML* game_object, sf::Vector2f& positiondiff, float angle) : ITurret(scene, game_object, positiondiff),m_angleDiff(angle),BaseShape(10, m_gameObject->getPosition())
{
	m_shape = new SquareSFML(10, m_gameObject->getPosition());
}

 void FixTurret::Update(const float& deltatime)
{
	 sf::Vector2f gamePos = m_gameObject->getPosition();

	 float angleRad = m_gameObject->getangle() * (3.14159265f / 180.0f);

	 sf::Vector2f rotatedOffset(
		 m_positionDiff.x * cos(angleRad) - m_positionDiff.y * sin(angleRad),
		 m_positionDiff.x * sin(angleRad) + m_positionDiff.y * cos(angleRad)
	 );

	 BaseShape.setPosition(gamePos + rotatedOffset);
	 BaseShape.setRotation(m_gameObject->getangle());

	 m_shape->setPosition(BaseShape.getPosition());
	 m_shape->setRotation(m_gameObject->getangle() + m_angleDiff);
}

void FixTurret::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
}

Cursor::Cursor(IComposite* scene) :
	NonDestructibleObject(scene)
,ILeaf(scene)
	, m_animate({ "Crossair.png","Crossair2.png","Crossair3.png" })
{
	m_shape = new CircleSFML(43, scene->getRoot()->getScene());
	m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));

}

void Cursor::ProssesInput(const sf::Event& event)
{
}

void Cursor::Update(const float& deltatime)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getRoot()->getScene()->getWindow());
	m_shape->setPosition(sf::Vector2f(mousePos.x, mousePos.y));
}

void Cursor::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
}
IFence::IFence(IComposite* scene, IShapeSFML* object) :NonDestructibleObject(scene),  ILeaf(scene), m_ObjectToProtect(object) {}

MovementInSpace::MovementInSpace(const float& maxVelority, const float& acceleratrion, const float& deceleration) :m_maxVelocity(maxVelority), m_acceleration(acceleratrion), m_deceleration(deceleration) {}

void MovementInSpace::ExecutePhysics(KT::VectorND<bool, 4>& isStrafing, KT::VectorND<float, 4>& velocity)
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

sf::Vector2f MovementInSpace::calculPosition(IShapeSFML* entity, ISceneBase* scene, KT::VectorND<float, 4>& velocity)
{
	auto x = velocity[trust::Left] - velocity[trust::Right];
	auto y = velocity[trust::Up] - velocity[trust::Down];
	sf::Vector2f Newposition = { entity->getPosition().x + ((x * scene->getRefreshTime().asSeconds())),entity->getPosition().y + ((y * scene->getRefreshTime().asSeconds())) };
	return Newposition;
}