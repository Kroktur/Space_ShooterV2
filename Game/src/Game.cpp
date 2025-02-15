#include "Game.h"

#include "IGameObject.h"
#include "GameObject.h"
/*****************************************************************//**
 * \file   RandomNumber.cpp
 * \brief  Implementation of RandomNumber.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture): ISceneBase(window,framerate, texture),m_Ship(sf::Vector2f(50,50))
{
	
	m_Ship.setTexture(&m_texture->getTexture("galaxie3.png"));
	m_Ship.setOrigin(m_Ship.getSize().x / 2, m_Ship.getSize().y / 2);
	m_Ship.setPosition(getWindow()->getSize().x / 2, getWindow()->getSize().y / 2);
	m_object.pushBack(new Ship(this, m_Background));
}

void Game::Update(const float& deltatime)
{
	for (auto& obj : m_object)
	{
		obj->Update(deltatime);
	}
}

void Game::ProssesInput(const sf::Event& event)
{
	for (auto& obj : m_object)
	{
		obj->ProssesInput(event);
	}
}

void Game::Render()
{
	getWindow()->draw(*m_Background);
	/*getWindow()->draw(m_Ship);*/
	for (auto& obj : m_object)
	{
		obj->Render();
	}

}
