#include "GameObject.h"
#include "Ship.h"
#include "cmath"
FenceShip::FenceShip(ISceneBase* scene, const sf::Vector2f& Center, Ship* ship):
	IFence(scene, Center)
	, m_ship(ship)
	,m_circle(m_scene->getBackGround()->getSize().x /2,m_center)
	,m_sprite(0,{"FenceTmp.png"})
	, IsInBorder(false)
{
	m_circle.getShape().setTexture(&m_scene->getTexture()->getTexture(m_sprite.getPath()));
}

void FenceShip::Update(const float& deltatime)
{
	m_circle.getShape().setPosition(m_scene->getCenter());
	m_scene->getBackGround()->setPosition(VerifyLimit());
}

void FenceShip::Render()
{ m_scene->getWindow()->draw(m_circle.getShape()); }

sf::Vector2f FenceShip::VerifyLimit()
{
   
    sf::Vector2f centreBackground = m_scene->getBackGround()->getPosition();
    sf::Vector2f positionVaisseau = m_ship->m_ship.getShape().getPosition(); 

    float dx = positionVaisseau.x - centreBackground.x;
    float dy = positionVaisseau.y - centreBackground.y;
    float distance = dx * dx + dy * dy;
    // be careful the magic value depends on the sprite
    float radius = (m_circle.getShape().getRadius() - m_ship->m_ship.getShape().getSize().x - 400) * (m_circle.getShape().getRadius() - m_ship->m_ship.getShape().getSize().x - 400);
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
    if (distance < (radius - (m_ship->m_ship.getShape().getSize().x)*(m_ship->m_ship.getShape().getSize().x)))
    {
        IsInBorder = false;
    }


    return centreBackground;
}
