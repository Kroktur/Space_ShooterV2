#include "Game.h"
//TODO
#include <iostream>

#include "Ship.h"
#include "IGameObject.h"

bool Collision(AABB A, AABB B)
{
	if (A.Amax.x <= B.Amin.x || A.Amin.x >= B.Amax.x || A.Amax.y <= B.Amin.y || A.Amin.y >= B.Amax.y)
		return false;
	else
		return true;
}

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
	new FenceShip(this, m_Background, static_cast<Ship*>(ship));
	new ExternFence(this, m_Background, Position::Down, 5);
	new ExternFence(this, m_Background, Position::Up, 5);
	new ExternFence(this, m_Background, Position::Left, 5);
	new ExternFence(this, m_Background, Position::Right, 5);
	getWindow()->setMouseCursorVisible(false);
}

void Game::Update(const float& deltatime)
{
	for (auto& obj : getChildren())
	{
		obj->Update(deltatime);
	}
	cursor.Update(deltatime);

	//TODO
	//TO REMOVE

	//for (int idx_x = 0; idx_x < m_allGameObject.size(); ++idx_x)
	//{
	//	for (int idx_y = idx_x + 1; idx_y < m_allGameObject.size(); ++idx_y)
	//	{
	//		testColision(m_allGameObject[idx_x], m_allGameObject[idx_y]);
	//	}
	//}


	//std::cout << getFullTree().Size() << std::endl;
	KT::Vector<IComponant*> todelete;
	auto vec = getFullTree();
	for (std::make_signed_t<size_t> i = vec.Size()-1 ; i >= 0; --i)
	{
		for (std::make_signed_t<size_t> y = i - 1; y >= 0; --y)
		{
			if (dynamic_cast<ExternFence*>(vec[i]) != nullptr && dynamic_cast<ClassicBullet*>(vec[y]) != nullptr)
			{
				if (Collision(static_cast<ExternFence*>(vec[i])->GetBoundingBox(), static_cast<IBullet*>(vec[y])->GetBoundingBox()))
				{
					std::cout << "Collision" << std::endl;
					todelete.pushBack( vec[y]);
				}
			}
		/*	if (dynamic_cast<IBullet*>(vec[i]) != nullptr && dynamic_cast<ExternFence*>(vec[y]) != nullptr)
			{
				if (Collision(static_cast<IBullet*>(vec[i])->GetBoundingBox(), static_cast<ExternFence*>(vec[y])->GetBoundingBox()))
				{
					std::cout << "Collision" << std::endl;
				}
			}*/
		}
	}
	for (std::make_signed_t<size_t> i = todelete.Size() - 1; i >= 0; --i)
	{
		delete todelete[i];
	}
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