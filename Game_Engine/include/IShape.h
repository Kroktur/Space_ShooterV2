#pragma once

#include "SceneBase.h"
class IPhysics
{
public:
	virtual ~IPhysics() = default;
};
class AnimateSprite
{
public:
	AnimateSprite(std::initializer_list<std::string> init);

	void add(std::string toBeAdded);

	std::string getPath(const std::string& check);

	std::string getPath(const int& idx);

	std::string getCurrentPath();

	void ChangeToNextPath();

	void ChangeToPreviousPath();

	void ChangePath(const int& idx);

private:
	KT::Vector<std::string> m_textureContainer;
	int m_curentTexture;
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
	virtual void setCenter(sf::Vector2f) = 0;
	virtual sf::Vector2f getCenter() = 0;
};
class RectangleSFML : public IShapeSFML
{
public:
	RectangleSFML(float width, float heignt, sf::Vector2f position, sf::Vector2f Origin);

	RectangleSFML(float width, float heignt, sf::Vector2f position);

	RectangleSFML(float width, float heignt, ISceneBase* scene);

	sf::Vector2f getPosition() override;

	sf::Vector2f getSize() override;

	float getangle() override;

	void setTexture(const sf::Texture& texture) override;

	void setPosition(const sf::Vector2f& position) override;

	void setSize(const sf::Vector2f& size)override;

	void setRotation(const float& angle) override;

	void setCenter(sf::Vector2f) override;
	sf::Vector2f getCenter() override;

	sf::RectangleShape& getShape();

protected:
	sf::RectangleShape m_shape;
};

class SquareSFML : public RectangleSFML
{
public:
	SquareSFML(float size, sf::Vector2f position, sf::Vector2f Origin);

	SquareSFML(float size, sf::Vector2f position);

	SquareSFML(float size, ISceneBase* scene);
};

class CircleSFML : public IShapeSFML
{
public:
	CircleSFML(float r, sf::Vector2f position, sf::Vector2f Origin);

	CircleSFML(float r, sf::Vector2f position);

	CircleSFML(float r, ISceneBase* scene);

	sf::Vector2f getPosition() override;

	sf::Vector2f getSize() override;

	float getangle() override;

	void setTexture(const sf::Texture& texture) override;

	void setPosition(const sf::Vector2f& position) override;

	void setSize(const sf::Vector2f& size)override;

	void setRotation(const float& angle) override;

	void setCenter(sf::Vector2f) override;
	sf::Vector2f getCenter() override;

	sf::CircleShape& getShape();

protected:
	sf::CircleShape m_shape;
};
class Timer
{
public:
	Timer(const float& timer) :m_TotalTimer(timer), m_CurrentTimer(0) {}
	bool AutoActionIsReady()
	{
		if (m_CurrentTimer >= m_TotalTimer)
		{
			m_CurrentTimer = 0;
			return true;
		}
		++m_CurrentTimer;
		return false;


	}
	bool ActionIsReady()
	{
		if (m_CurrentTimer >= m_TotalTimer)
			return true;
		return false;
	}
	void resetTimer()
	{
		m_CurrentTimer = 0;
	}
	void setNewTimer(const float& timer)
	{
		m_TotalTimer = timer;
	}
	float getTotalTimer()
	{
		return m_TotalTimer;
	}
	float getCurrentTimer()
	{
		return m_CurrentTimer;
	}
	void NextTIck(const float& idx = 1)
	{

		m_CurrentTimer += idx;
		if (m_CurrentTimer >= m_TotalTimer)
			m_CurrentTimer = m_TotalTimer;
	}
	void PreviousTick(const float& idx = 1)
	{
		m_CurrentTimer -= idx;
		if (m_CurrentTimer <= 0)
			m_CurrentTimer = 0;

	}
private:
	float m_TotalTimer;
	float m_CurrentTimer;
};