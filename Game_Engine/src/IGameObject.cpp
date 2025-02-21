#include "IGameObject.h"
#include "IShape.h"
float convertRadToDeg(const float& rad)
{
	return (180 * rad) / 3.14159f;
}

float convertDegToRad(const float& deg)
{
	return (deg * 3.14159f) / 180;
}

IGameObject::~IGameObject()
{
	delete m_shape;
}

IShapeSFML* IGameObject::getShape()
{
	return m_shape;
}

DestructibleObject::DestructibleObject(ISceneBase* scene, const float& life):IGameObject(scene), m_life(life)
{}

NonDestructibleObject::NonDestructibleObject(ISceneBase* scene):IGameObject(scene)
{}



IGameObjectContainer::~IGameObjectContainer()
{
    auto allGameObjects = m_allGameObjects;
    for (auto& gameObject : allGameObjects)
        delete gameObject;
}

void IGameObjectContainer::_addObject(GameObject* go)
{
    m_toBeAddedGameObjects.pushBack(go);
}

struct RemoveNonExisitingGameObject : public std::runtime_error
{
    RemoveNonExisitingGameObject() : std::runtime_error("Try to remove non existing Game Object.")
    {
    }
};

void IGameObjectContainer::_removeObject(GameObject* go)
{
    auto it = std::find(m_allGameObjects.begin(), m_allGameObjects.end(), go);
    if (it == m_allGameObjects.end()) // No elem found.
        throw RemoveNonExisitingGameObject();

    m_allGameObjects.erase(it);
}

void IGameObjectContainer::_toBeRemoveObject(GameObject* go)
{
    auto it = std::find(m_toBeRemovedGameObjects.begin(), m_toBeRemovedGameObjects.end(), go);

    if (it != m_toBeRemovedGameObjects.end())
        return;

    m_toBeRemovedGameObjects.pushBack(go);
}

void IGameObjectContainer::_cleanObject()
{
    for (auto& go : m_toBeRemovedGameObjects)
        delete go;

    m_toBeRemovedGameObjects.clear();
}

void IGameObjectContainer::_deferedAddObject(GameObject* go)
{
    m_allGameObjects.pushBack(go);
}

void IGameObjectContainer::_deferedAddObjects()
{
    for (auto& go : m_toBeAddedGameObjects)
        _deferedAddObject(go);

    m_toBeAddedGameObjects.clear();
}




GameObject::GameObject(IGameObjectContainer& owner) : m_owner(owner)
{
    m_owner._addObject(this);
}

GameObject::~GameObject()
{
    m_owner._removeObject(this);
}

void GameObject::destroy()
{
    m_owner._toBeRemoveObject(this);
}

void IGameObjectCompound::Update(const float& deltatime)
{
    for (auto& gameObject : m_allGameObjects)
        gameObject->Update(deltatime);
}

void IGameObjectCompound::ProssesInput(const sf::Event& event)
{
    for (auto& gameObject : m_allGameObjects)
        gameObject->ProssesInput(event);
}

void IGameObjectCompound::Render()
{
    for (auto& gameObject : m_allGameObjects)
        gameObject->Render();
}


