#pragma once
#include <KT_Array.h>

#include "SceneBase.h"
float convertRadToDeg(const float& rad);

float convertDegToRad(const float& deg);

class IGameObject
{
public:
	IGameObject(ISceneBase* scene):m_scene(scene){}
	virtual ~IGameObject() = default;
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

class CircleSFML
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
protected:
	sf::CircleShape m_shape;
};
