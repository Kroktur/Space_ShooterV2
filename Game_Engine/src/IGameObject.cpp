#include "IGameObject.h"

float convertRadToDeg(const float& rad)
{
	return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
	return (deg * 3.14159f) / 180;
}

IGameObject::~IGameObject()
{
	delete m_shape;
}

IShapeSFML* IGameObject::getShape()
{
	return m_shape;
}

DestructibleObject::DestructibleObject(ISceneBase* scene, const float& life):IGameObject(scene), m_life(life)
{}

NonDestructibleObject::NonDestructibleObject(ISceneBase* scene):IGameObject(scene)
{}

AnimateSprite::AnimateSprite( std::initializer_list<std::string> init): m_curentTexture(0)
{
	for (auto& idx : init)
	{
		m_textureContainer.pushBack(idx);
	}
}

void AnimateSprite::add(std::string toBeAdded)
{
	m_textureContainer.pushBack(toBeAdded);
}

std::string AnimateSprite::getPath(const std::string& check)
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector IS Empty");
	for (auto& idx : m_textureContainer)
	{
		if (idx == check)
			return idx;
	}
	throw std::runtime_error("Imposible to find path");
}

std::string AnimateSprite::getPath(const int& idx)
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector IS Empty");
	if (idx >= m_textureContainer.Size())
		throw std::out_of_range("out of range");
	return m_textureContainer[idx];
}

std::string AnimateSprite::getCurrentPath()
{
	return m_textureContainer[m_curentTexture];
}

void AnimateSprite::ChangeToNextPath()
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector IS Empty");
	if (m_curentTexture == m_textureContainer.Size() - 1)
		m_curentTexture = 0;
	else
		++m_curentTexture;
}

void AnimateSprite::ChangePath(const int& idx)
{
	if (idx < 0 || idx >= m_textureContainer.Size())
		throw std::runtime_error("out of range");
	m_curentTexture = idx;
 }

void AnimateSprite::ChangeToPreviousPath()
{
	if (m_textureContainer.Empty())
		throw std::out_of_range("Vector IS Empty");
	if (m_curentTexture == 0)
		m_curentTexture = m_textureContainer.Size() - 1;
	else
		--m_curentTexture;
}

RectangleSFML::RectangleSFML(float width, float heignt, sf::Vector2f position, sf::Vector2f Origin):m_shape(sf::Vector2f(width, heignt))
{
	m_shape.setPosition(position);
	m_shape.setOrigin(Origin);
}

RectangleSFML::RectangleSFML(float width, float heignt, sf::Vector2f position):m_shape(sf::Vector2f(width, heignt))
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

RectangleSFML::RectangleSFML(float width, float heignt, ISceneBase* scene):m_shape(sf::Vector2f(width, heignt))
{
	m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

sf::RectangleShape& RectangleSFML::getShape()
{
	return m_shape;
}

sf::Vector2f RectangleSFML::getPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f RectangleSFML::getSize()
{
	return m_shape.getSize();
}

float RectangleSFML::getangle()
{
	return m_shape.getRotation();
}

void RectangleSFML::setTexture(const sf::Texture& texture)
{
	m_shape.setTexture(&texture);
}

void RectangleSFML::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

void RectangleSFML::setSize(const sf::Vector2f& size)
{
	m_shape.setSize(size);
}

void RectangleSFML::setRotation(const float& angle)
{
	m_shape.setRotation(angle);
}

void RectangleSFML::setCenter(sf::Vector2f vec)
{
	m_shape.setOrigin(vec);
}

sf::Vector2f RectangleSFML::getCenter()
{
	return m_shape.getOrigin();
}



SquareSFML::SquareSFML(float size, sf::Vector2f position, sf::Vector2f Origin):RectangleSFML(size, size, position, Origin)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(Origin);
}

SquareSFML::SquareSFML(float size, sf::Vector2f position):RectangleSFML(size, size, position)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

SquareSFML::SquareSFML(float size, ISceneBase* scene):RectangleSFML(size, size, scene)
{
	m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
	m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
}

CircleSFML::CircleSFML(float r, sf::Vector2f position, sf::Vector2f Origin):m_shape(r)
{
	m_shape.setPosition(sf::Vector2f(position));
	m_shape.setOrigin(Origin);
}

CircleSFML::CircleSFML(float r, sf::Vector2f position):m_shape(r)
{
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

CircleSFML::CircleSFML(float r, ISceneBase* scene):m_shape(r)
{
	m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius() );
}

sf::CircleShape& CircleSFML::getShape()
{
	return m_shape;
}

sf::Vector2f CircleSFML::getPosition()
{
	return m_shape.getPosition();
}

sf::Vector2f CircleSFML::getSize()
{
	return sf::Vector2f{ m_shape.getRadius() * 2, m_shape.getRadius()* 2 };
}

float CircleSFML::getangle()
{
	return m_shape.getRotation();
}

void CircleSFML::setTexture(const sf::Texture& texture)
{
	m_shape.setTexture(&texture);
}

void CircleSFML::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

void CircleSFML::setSize(const sf::Vector2f& size)
{
	if (size.x != size.y)
		throw std::runtime_error("size must be equal");
	m_shape.setRadius(size.x / 2);
}

void CircleSFML::setRotation(const float& angle)
{
	m_shape.setRotation(angle);
}

void CircleSFML::setCenter(sf::Vector2f vec )
{
	m_shape.setOrigin(vec);
}
sf::Vector2f CircleSFML::getCenter()
{
	return m_shape.getOrigin();
}