#pragma once
#include <KT_Array.h>

#include "SceneBase.h"
float convertRadToDeg(const float& rad);

float convertDegToRad(const float& deg);
class IShapeSFML;

class IGameObject
{
public:
	IGameObject(ISceneBase* scene):m_scene(scene),m_shape(nullptr){}
	virtual ~IGameObject();
	/**
	 * @brief virtual Update
	 * @param float deltatime
	 */
	virtual void Update(const float& deltatime) = 0;
	/**
	 * @brief virtual ProssesInput
	 * @param sf::Event event
	 */
	virtual void ProssesInput(const sf::Event& event) = 0;
	/**
	 * @brief virtual Render
	 */
	virtual void Render() = 0;
	/**
	 * @brief set The Scene Idx
	 * @param idx
	 */
protected:
	ISceneBase* m_scene;
	IShapeSFML* m_shape;
};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(ISceneBase* scene, const float& life) :IGameObject(scene), m_life(life){}
	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;
	void ChangeLife(const float& life) { m_life += life; }
	float getCurrentLife() { return m_life; }
protected:
	float m_life;
};
class NonDestructibleObject : public IGameObject
{
public:
	NonDestructibleObject(ISceneBase* scene) :IGameObject(scene){}
	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;
protected:
};
class IPhysics
{
public:
	virtual ~IPhysics() = default;
};
class AnimateSprite
{
public:
	AnimateSprite(const int& speed, std::initializer_list<std::string> init) :m_speed(speed), m_curentTexture(0)
	{
		for (auto& idx : init)
		{
			m_textureContainer.pushBack(idx);
		}
	}
	void add(std::string toBeAdded)
	{
		m_textureContainer.pushBack(toBeAdded);
	}
	std::string getPath(std::string check)
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
	std::string getPath(const int& idx)
	{
		if (m_textureContainer.Empty())
			throw std::out_of_range("Vector IS Empty");
		if (idx >= m_textureContainer.Size())
			throw std::out_of_range("out of range");
		return m_textureContainer[idx];
	}
	std::string getPath()
	{
		return m_textureContainer[m_curentTexture];
	}
	bool changeReady(const float& timepassed)
	{
		if (timepassed >= m_speed)
			return true;
		return false;
	}
	void NextPath()
	{
		if (m_textureContainer.Empty())
			throw std::out_of_range("Vector IS Empty");
		if (m_curentTexture == m_textureContainer.Size() - 1)
			m_curentTexture = 0;
		else
			++m_curentTexture;
	}
private:
	KT::Vector<std::string> m_textureContainer;
	int m_curentTexture;
	int m_speed;
};
class IShapeSFML
{
public:
	virtual ~IShapeSFML() = default;
	virtual sf::Vector2f getSize() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual float getangle() = 0;
	virtual void setPosition(const sf::Vector2f&) = 0;
	virtual void setSize(const sf::Vector2f&) = 0;
	virtual void setRotation(const float& angle) = 0;
	virtual void setTexture(const sf::Texture& texture) = 0;
};
class RectangleSFML : public IShapeSFML
{
public:
	RectangleSFML(float width, float heignt, sf::Vector2f position, sf::Vector2f Origin) :m_shape(sf::Vector2f(width, heignt))
	{
		m_shape.setPosition(position);
		m_shape.setOrigin(Origin);
	}
	RectangleSFML(float width, float heignt, sf::Vector2f position) :m_shape(sf::Vector2f(width, heignt))
	{
		m_shape.setPosition(position);
		m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
	}
	RectangleSFML(float width, float heignt, ISceneBase* scene) :m_shape(sf::Vector2f(width, heignt))
	{
		m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
		m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
	}
	sf::RectangleShape& getShape()
	{
		return m_shape;
	}
	sf::Vector2f getPosition() override
	{
		return m_shape.getPosition();
	}
	sf::Vector2f getSize() override
	{
		return m_shape.getSize();
	}
	float getangle() override
	{
		return m_shape.getRotation();
	}
	void setTexture(const sf::Texture& texture) override
	{
		m_shape.setTexture(&texture);
	}
	void setPosition(const sf::Vector2f& position) override
	{
		m_shape.setPosition(position);
	}
	void setSize(const sf::Vector2f& size)override
	{
		m_shape.setSize(size);
	}
	void setRotation(const float& angle) override
	{
		m_shape.setRotation(angle);
	}
protected:
	sf::RectangleShape m_shape;
};

class SquareSFML : public RectangleSFML
{
public:
	SquareSFML(float size, sf::Vector2f position, sf::Vector2f Origin) :RectangleSFML(size, size, position, Origin)
	{
		m_shape.setPosition(position);
		m_shape.setOrigin(Origin);
	}
	SquareSFML(float size, sf::Vector2f position) :RectangleSFML(size, size, position)
	{
		m_shape.setPosition(position);
		m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
	}
	SquareSFML(float size, ISceneBase* scene) :RectangleSFML(size, size, scene)
	{
		m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
		m_shape.setOrigin(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
	}
};

class CircleSFML : public IShapeSFML
{
public:
	CircleSFML(float r, sf::Vector2f position, sf::Vector2f Origin) :m_shape(r)
	{
		m_shape.setPosition(sf::Vector2f(position));
		m_shape.setOrigin(Origin);
	}
	CircleSFML(float r, sf::Vector2f position) :m_shape(r)
	{
		m_shape.setPosition(position);
		m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
	}
	CircleSFML(float r, ISceneBase* scene) :m_shape(r)
	{
		m_shape.setPosition(scene->getWindow()->getSize().x / 2, scene->getWindow()->getSize().y / 2);
		m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius() );
	}
	sf::CircleShape& getShape()
	{
		return m_shape;
	}
	sf::Vector2f getPosition() override
	{
		return m_shape.getPosition();
	}
	sf::Vector2f getSize() override
	{
		return sf::Vector2f{ m_shape.getRadius() * 2, m_shape.getRadius()* 2 };
	}
	float getangle() override
	{
		return m_shape.getRotation();
	}
	void setTexture(const sf::Texture& texture) override
	{
		m_shape.setTexture(&texture);
	}
	void setPosition(const sf::Vector2f& position) override
	{
		m_shape.setPosition(position);
	}
	void setSize(const sf::Vector2f& size)override
	{
		if (size.x != size.y)
			throw std::runtime_error("size must be equal");
		m_shape.setRadius(size.x / 2);
	}
	void setRotation(const float& angle) override
	{
		m_shape.setRotation(angle);
	}
protected:
	sf::CircleShape m_shape;
};
