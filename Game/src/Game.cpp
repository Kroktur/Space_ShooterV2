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
	auto* ship = new Ship(this, m_Background);
	new FenceShip(ship, m_Background, static_cast<Ship*>(ship));
	new GameFence(this, m_Background, Position::Down, 5);
	new GameFence(this, m_Background, Position::Up, 5);
	new GameFence(this, m_Background, Position::Left, 5);
	new GameFence(this, m_Background, Position::Right, 5);
	new WorldFence(this, m_Background, Position::Down, 5 , 1000);
	new WorldFence(this, m_Background, Position::Up, 5 , 1000);
	new WorldFence(this, m_Background, Position::Left, 5, 1000);
	new WorldFence(this, m_Background, Position::Right, 5 , 1000);
	m_spawner = new  AsteroidSpawner(this, 10);
	getWindow()->setMouseCursorVisible(false);


}

void Game::Update(const float& deltatime)
{
	for (auto& obj : getChildren())
	{
		obj->Update(deltatime);
	}
	cursor.Update(deltatime);
	m_spawner->Spawn();
	auto vec = getFullTree();
	collision.HandleCollision(vec);

	std::cout << GetCenterWindow().x << " ; " << GetCenterWindow().y << " Centre Potentiel" << std::endl;

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
	/*getWindow()->draw(m_Ship);*/
	for (auto& obj : getChildren())
	{
		obj->Render();
	}
	cursor.Render();
}