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
	m_Ship.setOrigin(m_Ship.getSize().x / 2, m_Ship.getSize().y / 2);
	m_Ship.setPosition(getWindow()->getSize().x / 2, getWindow()->getSize().y / 2);
}

void Game::Update(const float& deltatime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_Background.move(sf::Vector2f(-5.f, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_Background.move(sf::Vector2f(5.f, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_Background.move(sf::Vector2f(0, -5.f));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		m_Background.move(sf::Vector2f(0, 5.f));
}

void Game::ProssesInput(const sf::Event& event)
{

}

void Game::Render()
{
	getWindow()->draw(m_Background);
	getWindow()->draw(m_Ship);

}
