#pragma once
#include <KT_Array.h>

#include "SceneBase.h"
float convertRadToDeg(const float& rad);

float convertDegToRad(const float& deg);
class IShapeSFML;

class IGameObject
{
public:
	IGameObject(ISceneBase* scene) :m_scene(scene), m_shape(nullptr) {}
	virtual ~IGameObject();

	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	IShapeSFML* getShape();

protected:
	ISceneBase* m_scene;
	IShapeSFML* m_shape;
};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(ISceneBase* scene, const float& life);
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
	NonDestructibleObject(ISceneBase* scene);
	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;
};




class GameObject;

class IGameObjectContainer
{
public:
	void _addObject(GameObject*);
	void _removeObject(GameObject*);
	void _toBeRemoveObject(GameObject*);
	void _deferedAddObject(GameObject*);
	void _deferedAddObjects();
	void _cleanObject();
	~IGameObjectContainer();

	virtual ISceneBase* getScene() = 0;

protected:
	KT::Vector<GameObject*> m_allGameObjects;
	KT::Vector<GameObject*> m_toBeRemovedGameObjects;
	KT::Vector<GameObject*> m_toBeAddedGameObjects;
};

class GameObject
{
public:
	GameObject(IGameObjectContainer& owner);
	virtual ~GameObject();


	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	IShapeSFML* getShape();

	void destroy();

	IGameObjectContainer& getOwner() { return m_owner; }

	const IGameObjectContainer& getOwner() const { return m_owner; }

protected:
	IGameObjectContainer& m_owner;
};

class IGameObjectCompound : public GameObject, public IGameObjectContainer
{
public:
	IGameObjectCompound(IGameObjectContainer& owner);
	void Update(const float& deltatime) override;
	void ProssesInput(const sf::Event& event) override;
	void Render() override;
};	
