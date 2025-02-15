#include "Game.h"
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
}

void Game::Update(const float& deltatime)
{
	
}

void Game::ProssesInput(const sf::Event& event)
{

}

void Game::Render()
{
	getWindow()->draw(m_Background);
	getWindow()->draw(m_Ship);

}
