#pragma once


#include <iostream>

#include "IGameObject.h"
#include "RandomNumber.h"
#include "SceneBase.h"


class ISpawner : public IComposite
{
public:
	ISpawner(IComposite* scene , const size_t& maxEntity):IComposite(scene) , m_Scene(scene), m_maxEntity(maxEntity), m_SpawnZone(sf::Vector2f(0, 0), sf::Vector2f(0, 0)), m_RestrictedArea(sf::Vector2f(0, 0), sf::Vector2f(0, 0))
	{
		m_SpawnZone.Pmin = scene->getRoot()->getScene()->getLeftTopCorner();
		m_SpawnZone.Pmax = (scene->getRoot()->getScene()->getRightBotomCorner());

		m_RestrictedArea.Pmin.x = scene->getRoot()->getScene()->GetCenterWindow().x - scene->getRoot()->getScene()->getWindow()->getSize().x / 2;
		m_RestrictedArea.Pmin.y = scene->getRoot()->getScene()->GetCenterWindow().y - scene->getRoot()->getScene()->getWindow()->getSize().y / 2;
		m_RestrictedArea.Pmax.x = scene->getRoot()->getScene()->GetCenterWindow().x + scene->getRoot()->getScene()->getWindow()->getSize().x / 2;
		m_RestrictedArea.Pmax.y = scene->getRoot()->getScene()->GetCenterWindow().y + scene->getRoot()->getScene()->getWindow()->getSize().y / 2;


	}
	void ProssesInput(const sf::Event& event) override{}
	void Render() override
	{
		IComposite::Render();
	}
	void Update(const float& deltatime) override
	{
		m_RestrictedArea.Pmin.x = m_Scene->getRoot()->getScene()->GetCenterWindow().x - m_Scene->getRoot()->getScene()->getWindow()->getSize().x / 2;
		m_RestrictedArea.Pmin.y = m_Scene->getRoot()->getScene()->GetCenterWindow().y - m_Scene->getRoot()->getScene()->getWindow()->getSize().y / 2;
		m_RestrictedArea.Pmax.x = m_Scene->getRoot()->getScene()->GetCenterWindow().x + m_Scene->getRoot()->getScene()->getWindow()->getSize().x / 2;
		m_RestrictedArea.Pmax.y = m_Scene->getRoot()->getScene()->GetCenterWindow().y + m_Scene->getRoot()->getScene()->getWindow()->getSize().y / 2;

		std::cout << getChildren().Size();
		IComposite::Update(deltatime);
	}
	virtual void Spawn() = 0;


protected:
	IComposite* m_Scene;
	size_t m_maxEntity;
	Vec2 m_SpawnZone;
	Vec2 m_RestrictedArea;

};


class AsteroidSpawner : public ISpawner
{
public:
	AsteroidSpawner(IComposite* scene, const size_t& maxEntity):ISpawner(scene, maxEntity){}
	void Spawn() override;
};