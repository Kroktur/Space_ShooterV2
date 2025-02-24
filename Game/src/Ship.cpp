#include "Ship.h"
#include "IGameObject.h"
Ship::Ship(IComposite* scene, IShapeSFML* background) :
	DestructibleObject(scene, 10)
	,IComposite(scene)
	, m_background(background)
	, m_velocity({ 0,0,0,0 })
	, m_angle(0)
	, m_elapsedTime(50)
	, m_animate({ "SpaceHero.png", "SpaceHero2.png" })
	, m_phisics(new MovementInSpace(2000, 0.15f, 0.30f))
	, m_boost(false)
	, dashSpeed(0)
	, cooldown(5000)

{
	m_shape = new SquareSFML(150, scene->getRoot()->getScene());
	m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));

	//new FixTurret(this, m_shape, sf::Vector2f(35, -25),0);
	//new FixTurret(this, m_shape, sf::Vector2f(35, 25), 0);
	m_turrets[0] = new FixTurret(scene, m_shape, sf::Vector2f(35, -25), 0.75);
	m_turrets[1] = new FixTurret(scene, m_shape, sf::Vector2f(35, 25), -0.75);
	for (auto& turret : m_turrets)
	{
		turret->SetFireRate(50);
		turret->SetOverloadGun(0,5);
		turret->setBullet(0, 0, 0);
	}
}

Ship::~Ship()
{
	delete m_phisics;
}

void Ship::ProssesInput(const sf::Event& event)
{
	/*static_cast<MovementInSpace*>(m_phisics)->ExecutePhysics(m_velocity);*/
	KT::VectorND<bool, 4> m_strafe{ false,false,false,false };
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (auto& turret : m_turrets)
		{
			turret->Fire();
		}
	}
	static_cast<MovementInSpace*>(m_phisics)->ExecutePhysics(m_strafe, m_velocity);
	physics();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && cooldown >= 5000)
	{
		if (!m_boost)
			m_boost = true;
		cooldown = 0;
	}
	++cooldown;
}

void Ship::physics()
{
	m_angle = anglecalcul();
}

void Ship::Update(const float& deltatime)
{
	m_shape->setRotation(m_angle);
	m_background->setPosition(static_cast<MovementInSpace*>(m_phisics)->calculPosition(m_background, m_scene->getRoot()->getScene(), m_velocity));
	if (m_boost)
	{

		float rad = convertDegToRad(m_angle);
		float dx = std::cos(rad);
		float dy = std::sin(rad);
		float dashSpee1 = 30;
		sf::Vector2f bgMovement;
		bgMovement.x = -dx * dashSpee1;
		bgMovement.y = -dy * dashSpee1;
		m_background->setPosition(bgMovement);
		if (dashSpeed > 1000)
		{
			m_boost = false;
			dashSpeed = 0;
		}
		dashSpeed += dashSpee1;
	}
	if (m_elapsedTime.AutoActionIsReady()) {
		m_animate.ChangeToNextPath();
		m_shape->setTexture(m_scene->getRoot()->getScene()->getTexture()->getTexture(m_animate.getCurrentPath()));
	}
	
	IComposite::Update(deltatime);
}

void Ship::Render()
{
	m_scene->getRoot()->getScene()->getWindow()->draw(static_cast<SquareSFML*>(m_shape)->getShape());
	IComposite::Render();
}

float Ship::anglecalcul()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*m_scene->getRoot()->getScene()->getWindow());
	sf::Vector2f shipPos = m_shape->getPosition();
	float deltaX = mousePos.x - shipPos.x;
	float deltaY = mousePos.y - shipPos.y;
	float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	return angle;
}