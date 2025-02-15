#pragma once
#include "SceneBase.h"
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
	float& getLife() { return m_life; }
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