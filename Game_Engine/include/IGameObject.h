#pragma once
#include <KT_Array.h>
#include "SFML/Graphics.hpp"
#include "IGameObject.h"
float convertRadToDeg(const float& rad);

float convertDegToRad(const float& deg);
class IShapeSFML;


class ISceneBase;
class IComposite;
class IComponant
{
public:
	IComponant(IComposite* parent = nullptr);
	virtual ~IComponant();
	virtual ISceneBase* getScene() = 0;
	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	void setParent(IComposite* parent);
private:
	IComposite* m_parent;
};

class IComposite : public IComponant
{
public:
	friend IComponant;
	IComposite(IComposite* parent = nullptr);
	virtual void Update(const float& deltatime)override;

	virtual void ProssesInput(const sf::Event& event)override;

	virtual void Render()override;


	~IComposite();
protected:
	std::vector<IComponant*> getChildren();
	const std::vector<IComponant*> getChildren() const;
private:
	void add(IComponant* data);
	void remove(IComponant* data);
private:
	std::vector<IComponant*> m_shildren;
};
class ILeaf : public IComponant
{
public:
	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	ILeaf(IComposite* parent = nullptr);
};






class IGameObject : public IComposite
{
public:
	IGameObject(IComposite* scene) :IComposite(scene) ,m_scene(scene), m_shape(nullptr) {}
	virtual ~IGameObject();

	virtual void Update(const float& deltatime) = 0;

	virtual void ProssesInput(const sf::Event& event) = 0;

	virtual void Render() = 0;

	IShapeSFML* getShape();
	ISceneBase* getScene() override;

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

