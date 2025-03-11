#include "Game.h"
//TODO
#include <iostream>

#include "Ship.h"
#include "IGameObject.h"
/*****************************************************************//**
 * \file   RandomNumber.cpp
 * \brief  Implementation of RandomNumber.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture) : ISceneBase(window, framerate, texture), cursor(this)
{
	m_Background = new SquareSFML(10000, sf::Vector2f(0, 0));
	m_Background->setTexture(m_texture->getTexture("galaxie4.png"));
	m_view = new sf::View(sf::FloatRect(0, 0, getWindow()->getSize().x, getWindow()->getSize().y));
	
	m_minimap = new sf::View(sf::FloatRect(0, 0, m_Background->getSize().x, m_Background->getSize().y));

	m_minimap->setViewport(sf::FloatRect(0.75f, 0.0f, 0.25f, 0.25f));
	m_minimap->setCenter(0 , 0);
	getWindow()->setMouseCursorVisible(false);
	spawn();
	
	
}

void Game::Update(const float& deltatime)
{

	getWindow()->setView(*m_view);
	cursor.Update(deltatime);
	for (auto& obj : getChildren())
	{
		obj->Update(deltatime);
	}
	
	m_spawner->Spawn();
	auto vec = getFullTree();
	collision.HandleCollision(vec);
	

}

void Game::ProssesInput(const sf::Event& event)
{
	for (auto& obj : getChildren())
	{
		obj->ProssesInput(event);
	}
	cursor.ProssesInput(event);
}

void Game::Render()
{
	getWindow()->draw(static_cast<SquareSFML*>(m_Background)->getShape());
	for (auto& obj : getChildren())
	{
		getWindow()->setView(*m_view);
		obj->Render();
		getWindow()->setView(*m_minimap);
		obj->Render();
	}
	getWindow()->setView(*m_view);
	cursor.Render();
}

void Game::spawn()
{
	auto* ship = new Ship(this, m_Background,m_view);
	new Wall(this, sf::Vector2f(0, 0), sf::Vector2f(10000, 30));
	
	new GameFence(this, m_Background, Position::Down, 5);
	new GameFence(this, m_Background, Position::Up, 5);
	new GameFence(this, m_Background, Position::Left, 5);
	new GameFence(this, m_Background, Position::Right, 5);
	new WorldFence(this, m_Background, Position::Down, 5, 1000);
	new WorldFence(this, m_Background, Position::Up, 5, 1000);
	new WorldFence(this, m_Background, Position::Left, 5, 1000);
	new WorldFence(this, m_Background, Position::Right, 5, 1000);
	m_spawner = new  AsteroidSpawner(this, 20);
}
