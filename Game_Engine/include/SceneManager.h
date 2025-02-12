#pragma once
#include<string>
#include <SFML/Graphics.hpp>

using sfStyle = int;

class SceneManager
{
public:
	SceneManager(const size_t& width, const size_t& height, const std::string& title, const sfStyle& style)
	{

	}
private:
	sf::RenderWindow m_window;
};
