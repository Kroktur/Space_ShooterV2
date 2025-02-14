#pragma once
/*****************************************************************//**
 * \file   SceneManager.h
 * \brief  contain the class SceneManager
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include<string>
#include <SFML/Graphics.hpp>
#include "KT_Vector.h"
#include "TextureCache.h"
class ISceneBase;
using sfStyle = int;
/**
 * @brief SceneManager is a class that can manage scene
 */
class SceneManager
{
public:
	/**
	 * @brief Constructor
	 * \param std::string execFilePath
	 * \param size_t width
	 * \param size_t height
	 * \param std::string title
	 * \param sf::Style / int style
	 */
	SceneManager(const size_t& width, const size_t& height, const std::string& title, const sfStyle& style = sf::Style::Default);
	/**
	 * @brief main function which will contain the gaming loop
	 * 
	 */
	/**
	 * @brief destructor
	 * 
	 */
	~SceneManager();
	void Exe();
	/**
	 * @brief Add A scene to the Manager and auto set the first scene
	 * 
	 * 
	 * \param SceneBase scene
	 */
	void AddScene( ISceneBase* scene);
	/**
	 * @bruef Set The current scene

	 * 
	 * \param int idx
	 */
	void SetScene(const int& idx);
	/**
	 * @brief return a pointer of the window
	 * 
	 * \return sf::RenderWindow* 
	 */
	sf::RenderWindow* getWindow();
private:
	sf::RenderWindow* m_window;
	KT::Vector<ISceneBase*> m_scene;
	ISceneBase* m_currentScene;
	sf::Event m_event;
};
