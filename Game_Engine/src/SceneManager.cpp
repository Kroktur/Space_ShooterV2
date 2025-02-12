#include "SceneManager.h"
/*****************************************************************//**
 * \file   SceneManager.cpp
 * \brief  Implementation of SceneManager.h
 * 
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
SceneManager::SceneManager(const size_t& width, const size_t& height, const std::string& title, const sfStyle& style) : m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, style)), m_currentScene(nullptr)
{}

void SceneManager::Exe()
{

	const sf::Clock clock;
	const sf::Clock spawnClock;
	float previous = clock.getElapsedTime().asSeconds();
	auto lag = 0.0;
	while (m_window->isOpen())
	{
		const float current = clock.getElapsedTime().asMilliseconds();
		const auto elapsed = current - previous;
		previous = current;
		lag += elapsed;
		SetScene(m_currentScene->getSceneIdx());

		m_window->clear();

		m_currentScene->ProssesInput(m_event);

		while (m_currentScene->getRefreshTime().asMilliseconds() > 0.0
			&& lag >= m_currentScene->getRefreshTime().asMilliseconds())
		{

			m_currentScene->Update(elapsed);
			lag -= m_currentScene->getRefreshTime().asMilliseconds();
		}
	
		m_currentScene->Render();
	
		m_window->display();
	}


}

void SceneManager::AddScene(const std::unique_ptr<SceneBase>& scene)
{
	m_scene.pushBack(scene);
	m_scene.back()->setSceneIdx(m_scene.Size() - 1);
	if (m_scene.Size() == 1)
	{
		SetScene(0);
	}
}

void SceneManager::SetScene(const int& idx)
{ 

	m_currentScene = m_scene[idx].get();
}

sf::RenderWindow* SceneManager::getWindow() 
{
	return m_window.get(); 
}
