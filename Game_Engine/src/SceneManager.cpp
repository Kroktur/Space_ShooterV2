#include "SceneManager.h"
#include "SceneBase.h"
/*****************************************************************//**
 * \file   SceneManager.cpp
 * \brief  Implementation of SceneManager.h
 * 
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
SceneManager::SceneManager(const size_t& width, const size_t& height, const std::string& title, const sfStyle& style) : m_window(new sf::RenderWindow(sf::VideoMode(width, height), title, style)), m_currentScene(nullptr)
{}

SceneManager::~SceneManager()
{
	delete m_window;
	m_window = nullptr;

	for (std::make_signed_t<size_t> idx = m_scene.Size() - 1 ; idx >= 0; --idx)
	{
		delete m_scene[idx];
	}
	m_scene.clear();

}

void SceneManager::Exe()
{
	/**
	 * @brief Gaming loop
	 */
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

		/**
		 * @brief set Scene
		 */
		SetScene(m_currentScene->getSceneIdx());

		/**
		 * @brief clear window
		 */
		m_window->clear();

		/**
		 * @brief event for closing the window
		 */
		while (m_window->pollEvent(m_event)) {
			if (m_event.type == sf::Event::Closed ||
				(m_event.type == sf::Event::KeyPressed && m_event.key.code == sf::Keyboard::Escape)) {
				m_window->close();
			}
		}

		/**
		 * @brief prosses input for the scene
		 */
		m_currentScene->ProssesInput(m_event);

		/**
		 * @brief update while render is late
		 */
		while (m_currentScene->getRefreshTime().asMilliseconds() > 0.0
			&& lag >= m_currentScene->getRefreshTime().asMilliseconds())
		{

			m_currentScene->Update(elapsed);
			lag -= m_currentScene->getRefreshTime().asMilliseconds();
		}
	
		/**
		 * @brief drow everithing
		 */
		m_currentScene->Render();
		m_window->display();
	}


}

void SceneManager::AddScene(ISceneBase* scene)
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

	m_currentScene = m_scene[idx];
}

sf::RenderWindow* SceneManager::getWindow() 
{
	return m_window; 
}
