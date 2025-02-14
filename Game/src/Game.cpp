#include "Game.h"
// TODO
#include <iostream>
Game::Game(sf::RenderWindow* window, const float& framerate, const std::string& execFilePath): ISceneBase(window,framerate, execFilePath),m_Ship(sf::Vector2f(50,50))
{
	
	m_texture->getTexture("galaxie2.bmp");
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
