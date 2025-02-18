#include "Game.h"
#include "Ship.h"
#include "IGameObject.h"
/*****************************************************************//**
 * \file   RandomNumber.cpp
 * \brief  Implementation of RandomNumber.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture): ISceneBase(window,framerate, texture),cursor(this)
{
	m_Background->setSize(sf::Vector2f(10000, 10000));
	m_Background->setOrigin(m_Background->getSize().x / 2, m_Background->getSize().y / 2);
	m_Background->setTexture(&m_texture->getTexture("galaxie3.png"));
	m_object.pushBack(new Ship(this, m_Background));
	m_object.pushBack(new FenceShip(this, m_Background->getOrigin(), static_cast<Ship*>(m_object[0])));
	getWindow()->setMouseCursorVisible(false);
}

void Game::Update(const float& deltatime)
{ 
	for (auto& obj : m_object)
	{
		obj->Update(deltatime);
	}
	cursor.Update(deltatime);
}

void Game::ProssesInput(const sf::Event& event)
{
	for (auto& obj : m_object)
	{
		obj->ProssesInput(event);
	}
	cursor.ProssesInput(event);
}

void Game::Render()
{
	getWindow()->draw(*m_Background);
	/*getWindow()->draw(m_Ship);*/
	for (auto& obj : m_object)
	{
		obj->Render();
	}
	cursor.Render();
}
