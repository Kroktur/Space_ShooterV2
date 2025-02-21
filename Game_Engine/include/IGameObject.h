#pragma once
#include <KT_Array.h>
#include "KT_Vector.h"
#include "SFML/Graphics.hpp"
float convertRadToDeg(const float& rad);

float convertDegToRad(const float& deg);
class IShapeSFML;

class ISceneBase;
class IGameObject;

class IGameObjectContainer
{
public:
	void _addObject(IGameObject*);
	void _removeObject(IGameObject*);
	void _toBeRemoveObject(IGameObject*);
	void _deferedAddObject(IGameObject*);
	void _deferedAddObjects();
	void _cleanObject();
	~IGameObjectContainer();

	virtual ISceneBase* getScene() = 0;

protected:
	KT::Vector<IGameObject*> m_allGameObjects;
	KT::Vector<IGameObject*> m_toBeRemovedGameObjects;
	KT::Vector<IGameObject*> m_toBeAddedGameObjects;
};

class IGameObject
{
public:
	IGameObject(IGameObjectContainer* owner);
	virtual ~IGameObject();


	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	IShapeSFML* getShape();

	void destroy();

	IGameObjectContainer* getOwner() { return m_owner; }

	const IGameObjectContainer* getOwner() const { return m_owner; }

protected:
	IGameObjectContainer* m_owner;
	IShapeSFML* m_shape;
};

class IGameObjectCompound : public IGameObject, public IGameObjectContainer
{
public:
	IGameObjectCompound(IGameObjectContainer* owner);
	void Update(const float& deltatime) override;
	void ProssesInput(const sf::Event& event) override;
	void Render() override;
};


//class IGameObject
//{
//public:
//	IGameObject(ISceneBase* scene):m_scene(scene),m_shape(nullptr){}
//	virtual ~IGameObject();
//	
//	virtual void Update(const float& deltatime) = 0;
//
//	virtual void ProssesInput(const sf::Event& event) = 0;
//	
//	virtual void Render() = 0;
//
//	IShapeSFML* getShape();
//
//protected:
//	ISceneBase* m_scene;
//	IShapeSFML* m_shape;
//};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(IGameObjectContainer* scene, const float& life);
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
	NonDestructibleObject(IGameObjectContainer* scene);
	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;
};




