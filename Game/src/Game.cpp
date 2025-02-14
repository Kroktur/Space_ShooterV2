#include "Game.h"
// TODO
#include <iostream>
Game::Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture): ISceneBase(window,framerate, texture),m_Ship(sf::Vector2f(50,50))
{
	
	
	if (!texturer.loadFromFile("Debug\\galaxie3.png"))
	{
		std::cout << "ca marche pas " << std::endl;
	}
	m_Background.setTexture(&m_texture->getTexture("C:\\SpaceShooterV2\\Build\\app\\bin\\Debug\\galaxie3.png"));
	m_Ship.setTexture(&m_texture->getTexture("C:\\SpaceShooterV2\\Build\\app\\bin\\Debug\\galaxie3.png"));
	//m_Ship.setTexture(&texturer);
}

void Game::Update(const float& deltatime)
{
	
}

void Game::ProssesInput(const sf::Event& event)
{

}

void Game::Render()
{
	//getWindow()->draw(m_Background);
	getWindow()->draw(m_Ship);

}
