#include "GameObject.h"
#include "Ship.h"
#include "cmath"
FenceShip::FenceShip(ISceneBase* scene, const sf::Vector2f& Center, Ship* ship):
	IFence(scene, Center)
	, m_ship(ship)
	,m_sprite(0,{"FenceTmp.png"})
	, IsInBorder(false)
{
    m_shape = new CircleSFML(m_scene->getBackgroundSize().x / 2, m_center);
	m_shape->setTexture(m_scene->getTexture()->getTexture(m_sprite.getPath()));
}

void FenceShip::Update(const float& deltatime)
{
    m_shape->setPosition(m_scene->getBackgroundCenter());
	m_ship->m_background->setPosition(VerifyLimit());
}

void FenceShip::Render()
{ m_scene->getWindow()->draw(static_cast<CircleSFML*>(m_shape)->getShape()); }

sf::Vector2f FenceShip::VerifyLimit()
{
   
    sf::Vector2f centreBackground = m_ship->m_background->getPosition();
    sf::Vector2f positionVaisseau = m_ship->m_shape->getPosition(); 

    float dx = positionVaisseau.x - centreBackground.x;
    float dy = positionVaisseau.y - centreBackground.y;
    float distance = dx * dx + dy * dy;
    // be careful the magic value depends on the sprite
    float radius = (m_shape->getSize().x /2 - m_ship->m_shape->getSize().x - 400) * (m_shape->getSize().x / 2 - m_ship->m_shape->getSize().x - 400);
    if (distance > radius ){
        float factor = radius / distance;
        centreBackground.x = positionVaisseau.x - dx * factor;
        centreBackground.y = positionVaisseau.y - dy * factor;
        //  be careful the magic value depends of the deadly speed according to you
        if (m_ship->m_velocity[0] > 1000 || m_ship->m_velocity[1] > 1000 || m_ship->m_velocity[2] > 1000 || m_ship->m_velocity[3] > 1000)
        {
            if (!IsInBorder)
            {
	            IsInBorder = true;
            	m_ship->ChangeLife(-1);
            }
        }
      
    }
    if (distance < (radius - (m_ship->m_shape->getSize().x)*(m_ship->m_shape->getSize().x)))
    {
        IsInBorder = false;
    }


    return centreBackground;
}
Cursor::Cursor(ISceneBase* scene) :
    NonDestructibleObject(scene)
    , m_animate(0, { "Crossair.png","Crossair2.png","Crossair3.png" })
{
    m_shape = new CircleSFML(43, scene);
    m_shape->setTexture(m_scene->getTexture()->getTexture(m_animate.getPath()));

}

void Cursor::ProssesInput(const sf::Event& event)
{}

void Cursor::Update(const float& deltatime)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getWindow());
	m_shape->setPosition(sf::Vector2f( mousePos.x,mousePos.y));
}

void Cursor::Render()
{
	m_scene->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
}
IFence::IFence(ISceneBase* scene, const sf::Vector2f& Center) :NonDestructibleObject(scene), m_center(Center) {}

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
