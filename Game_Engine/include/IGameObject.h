#pragma once
#include <KT_Vector.h>

#include "IGameObject.h"
#include "IGameObject.h"
#include "SFML/Graphics.hpp"

struct AABB
{
	AABB(sf::Vector2f Amin_, sf::Vector2f Amax);
	sf::Vector2f Amin;
	sf::Vector2f Amax;
};


float convertRadToDeg(const float& rad);
float convertDegToRad(const float& deg);

class IShapeSFML;
class RootScene;
class ISceneBase;
class IComposite;
enum class Componant
{
	IComposite
	,ILeaf
	,IGameObject
};


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
	virtual Componant GetComponantType() = 0;
	virtual const Componant GetComponantType() const = 0;
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
	 KT::Vector<IComponant*> getChildren();
	 const KT::Vector<IComponant*> getChildren() const;
	 KT::Vector<IComponant*> getFullTree();
protected:

	//KT::Vector<IComponant*> IterateAllComposite();
	//const KT::Vector<IComponant*> IterateAllComposite() const;

	 Componant GetComponantType() override
	 {
		 return Componant::IComposite;
	 }
	 const Componant GetComponantType() const override
	{
		 return Componant::IComposite;
	}
private:
	void add(IComponant* data);
	void remove(IComponant* data);
	void AddFullTree(KT::Vector<IComponant*>& toAdd, KT::Vector<IComponant*> iterate);
	KT::Vector<IComponant*> m_shildren;
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

	Componant GetComponantType() override
	{
		return Componant::ILeaf;
	}
	const Componant GetComponantType() const override
	{
		return Componant::ILeaf;
	}
};
enum class GameObjectType
{
	DestructibleObject
	,NonDestructibleObject
};

class IGameObject 
{
public:
	IGameObject(IComposite* scene);
	virtual ~IGameObject();

	virtual void Update(const float& deltatime) = 0;
	virtual void ProssesInput(const sf::Event& event) = 0;
	virtual void Render() = 0;
	virtual AABB GetBoundingBox();
	IShapeSFML* getShape();
	virtual GameObjectType globalGameObjectType() = 0;
	virtual void HandleCollision(IGameObject* object){}
	bool NeedDestroy();

	void destroy();
protected:
	
	IComposite* m_scene;
	IShapeSFML* m_shape;
private:
	bool m_needDestroy;
};

class DestructibleObject : public IGameObject
{
public:
	DestructibleObject(IComposite* scene, const float& life);

	void Update(const float& deltatime) override = 0;
	void ProssesInput(const sf::Event& event) override = 0;
	void Render() = 0;

	virtual void ChangeLife(const float& life)
	{
		m_life += life;
		if (m_life <= 0)
			destroy();
	}
	float getCurrentLife() { return m_life; }
	
	 GameObjectType globalGameObjectType() override;
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
	 GameObjectType globalGameObjectType() override;
};

template<typename type , typename type2>
type getOvbj(type2* obj)
{
	return dynamic_cast<type>(obj);
}