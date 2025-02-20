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
	m_Background = new SquareSFML(10000,sf::Vector2f(0,0));
	m_Background->setTexture(m_texture->getTexture("galaxie4.png"));
	m_object.pushBack(new Ship(this, m_Background));
	m_object.pushBack(new FenceShip(this, m_Background, static_cast<Ship*>(m_object[0])));
	m_object.pushBack(new ExternFence(this, m_Background, Position::Down, 5));
	m_object.pushBack(new ExternFence(this, m_Background, Position::Up, 5));
	m_object.pushBack(new ExternFence(this, m_Background, Position::Left , 5));
	m_object.pushBack(new ExternFence(this, m_Background, Position::Right , 5));
	m_object.pushBack(new ExternFence(this, m_object[0]->getShape(), Position::Down, 5));
	m_object.pushBack(new ExternFence(this, m_object[0]->getShape(), Position::Up, 5));
	m_object.pushBack(new ExternFence(this, m_object[0]->getShape(), Position::Left, 5));
	m_object.pushBack(new ExternFence(this, m_object[0]->getShape(), Position::Right, 5));
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
	getWindow()->draw(static_cast<SquareSFML*>(m_Background)->getShape());
	/*getWindow()->draw(m_Ship);*/
	for (auto& obj : m_object)
	{
		obj->Render();
	}
	cursor.Render();
}
