#include "Ship.h"

#include <iostream>

#include "IGameObject.h"
Ship::Ship(IComposite* scene, IShapeSFML* background, sf::View* view) :
	DestructibleObject(scene, 10)
	,IComposite(scene)
	, m_angle(0)
	, m_elapsedTime(0.2)
	, m_animate({ "SpaceHero.png", "SpaceHero2.png" })
	, m_phisics(new MovementInSpace(250, 1000, 1000))
, m_invisibility(2.5)
,m_view(view)

{
	
	m_shape = new SquareSFML(150, scene->getRoot()->getScene()->GetCenterWindow());

	m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
	new Life(this, this, Color::Blue, m_shape);
	new GameObjectFence(this, m_scene->getRoot()->getScene()->getBackGround(), this);
	m_turrets[0] = new FixTurret(this, m_shape, sf::Vector2f(35, -25), 0.75);
	m_turrets[1] = new FixTurret(this, m_shape, sf::Vector2f(35, 25), -0.75);
	for (auto& turret : m_turrets)
	{
		turret->SetFireRate(0.2f);
		turret->SetOverloadGun(5,30);
		turret->setBullet(0, 0, 10);
	}
}

Ship::~Ship()
{
	delete m_phisics;
}

void Ship::ProssesInput(const sf::Event& event)
{
	 m_strafe = { false,false,false,false };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_strafe[trust::Right] = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_strafe[trust::Left] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_strafe[trust::Up] = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_strafe[trust::Down] = true;
	}
	physics();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (auto& turret : m_turrets)
		{
			turret->Fire();
		}
	}


	
}

void Ship::physics()
{
	m_angle = anglecalcul();
}

void Ship::Update(const float& deltatime)
{
	m_lastPosition = m_shape->getPosition();
	m_view->setCenter(m_shape->getPosition());
	static_cast<MovementInSpace*>(m_phisics)->ExecutePhysics(m_strafe, m_scene->getRoot()->getScene()->getRefreshTime().asSeconds());
	
	m_shape->setPosition(static_cast<MovementInSpace*>(m_phisics)->calculPosition(m_shape, m_scene->getRoot()->getScene(), m_scene->getRoot()->getScene()->getRefreshTime().asSeconds()));
	m_shape->setRotation(m_angle);
	
	if (m_elapsedTime.AutoActionIsReady(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds())) {
		m_animate.ChangeToNextPath();
		m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
	}

	IComposite::Update(deltatime);
	m_invisibility.NextTIck(m_scene->getRoot()->getScene()->getRefreshTime().asSeconds());
}

void Ship::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
	IComposite::Render();
}

AABB Ship::GetBoundingBox()
{
	return m_shape->GetBoundingBox();
}

float Ship::anglecalcul()
{
	sf::Vector2i mousePosWindow = sf::Mouse::getPosition(*m_scene->getRoot()->getScene()->getWindow());
	sf::Vector2f mousePosScene = m_scene->getRoot()->getScene()->getWindow()->mapPixelToCoords(mousePosWindow);
	sf::Vector2f shipPos = m_shape->getPosition();
	float deltaX = mousePosScene.x - shipPos.x;
	float deltaY = mousePosScene.y - shipPos.y;
	float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	return angle;
}

void Ship::HandleCollision(IGameObject* object)
{
	
	if (object->globalGameObjectType() != GameObjectType::DestructibleObject)
		return;
	

	ChangeLife(-1);
}
//IShapeSFML* Ship::getShape()
//{
//	return m_ShipShape;
//}