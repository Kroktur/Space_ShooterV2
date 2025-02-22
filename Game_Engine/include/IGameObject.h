#pragma once
#include "IGameObject.h"
#include "SFML/Graphics.hpp"

float convertRadToDeg(const float& rad);
float convertDegToRad(const float& deg);

class IShapeSFML;
class RootScene;
class ISceneBase;
class IComposite;

class IComponant
{
public:
	IComponant(IComposite* parent );
	virtual ~IComponant();
	 IComponant* getParent();
	 const IComponant* getParent() const;

	virtual void Update(const float& deltatime) = 0;
	virtual void ProssesInput(const sf::Event& event) = 0;
	virtual void Render() = 0;

	 RootScene* getRoot();
	 const RootScene* getRoot() const;

	void setParent(IComposite* parent);
protected:
	
	IComposite* m_parent;
};


class IComposite : public IComponant
{
public:
	friend IComponant;

	IComposite(IComposite* parent );
	~IComposite();

	 void Update(const float& deltatime)override;
	 void ProssesInput(const sf::Event& event)override;
	 void Render()override;
protected:
	std::vector<IComponant*> getChildren();
	const std::vector<IComponant*> getChildren() const;
private:
	void add(IComponant* data);
	void remove(IComponant* data);

	std::vector<IComponant*> m_shildren;
};

class RootScene : public IComposite
{
public:
	RootScene(ISceneBase* scene);

	ISceneBase* getScene();
private:
	ISceneBase* m_scene;
};

class ILeaf : public IComponant
{
public:
	ILeaf(IComposite* parent);

	virtual void Update(const float& deltatime) = 0;
	virtual void ProssesInput(const sf::Event& event) = 0;
	virtual void Render() = 0;
};


class IGameObject 
{
public:
	IGameObject(IComposite* scene);
	virtual ~IGameObject();

	virtual void Update(const float& deltatime) = 0;
	virtual void ProssesInput(const sf::Event& event) = 0;
	virtual void Render() = 0;

	IShapeSFML* getShape();
protected:
	IComposite* m_scene;
	IShapeSFML* m_shape;
};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(IComposite* scene, const float& life);

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
	NonDestructibleObject(IComposite* scene);

	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;
};

