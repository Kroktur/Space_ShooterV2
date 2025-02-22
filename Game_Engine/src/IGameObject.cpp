#include "IGameObject.h"
#include "SceneBase.h"
#include "IShape.h"
#include <iostream>
float convertRadToDeg(const float& rad)
{
    return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
    return (deg * 3.14159f) / 180;
}

IGameObject::IGameObject(IComposite* scene):m_scene(scene)
{

}

IGameObject::~IGameObject()
{
    delete m_shape;
	std::cout << "Game Object detruit" << std::endl;
}

IShapeSFML* IGameObject::getShape()
{
    return m_shape;
}



DestructibleObject::DestructibleObject(IComposite* scene, const float& life) :IGameObject(scene), m_life(life)
{
}

NonDestructibleObject::NonDestructibleObject(IComposite* scene) :IGameObject(scene)
{
}


IComponant::IComponant(IComposite* parent) :m_parent(nullptr)
{
	setParent(parent);
}

IComponant::~IComponant()
{
	setParent(nullptr);
}

IComponant* IComponant::getParent()
{
	return m_parent;
}

const IComponant* IComponant::getParent() const
{
	return m_parent;
}


void IComponant::setParent(IComposite* parent)
{
	if (m_parent)
		m_parent->remove(this);

	m_parent = parent;

	if (m_parent)
		m_parent->add(this);
}

RootScene* IComponant::getRoot()
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<RootScene*>(curent);
}

const RootScene* IComponant::getRoot() const
{
	auto* curent = this;
	while (curent->getParent() != nullptr)
	{
		curent = curent->getParent();
	}
	return static_cast<const RootScene*>(curent);
}

IComposite::IComposite(IComposite* parent) : IComponant(parent)
{

}
void IComposite::Update(const float& deltatime)
{
	for (auto& child : m_shildren)
		child->Update(deltatime);
}

void IComposite::ProssesInput(const sf::Event& event)
{
	for (auto& child : m_shildren)
		child->ProssesInput(event);
}


void IComposite::Render()
{
	for (auto& child : m_shildren)
		child->Render();
}


IComposite::~IComposite()
{
	for (std::make_signed_t<size_t> i = m_shildren.size() - 1; i >= 0; --i)
	{
		delete m_shildren[i];
	}
	m_shildren.clear();
}



std::vector<IComponant*> IComposite::getChildren()
{
	return m_shildren;
}

const std::vector<IComponant*> IComposite::getChildren() const
{
	return m_shildren;
}

void IComposite::add(IComponant* data)
{
	m_shildren.push_back(data);
}

void IComposite::remove(IComponant* data)
{
	auto it = std::find(m_shildren.begin(), m_shildren.end(), data);
	if (it == m_shildren.end())
		throw;
	m_shildren.erase(it);
}

RootScene::RootScene(ISceneBase* scene):IComposite(nullptr),m_scene(scene)
{

}

ISceneBase* RootScene::getScene()
{
	return m_scene;
}




ILeaf::ILeaf(IComposite* parent) :IComponant(parent)
{
}


