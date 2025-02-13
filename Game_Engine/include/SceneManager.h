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
#include <memory>
#include "KT_Vector.h"

//TODO 
#include <iostream>
using sfStyle = int;

class SceneBase
{
public:
	void Update(const float& deltatime){}
	void ProssesInput(const sf::Event& event){}
	void Render() { std::cout << "a"; }
	void setSceneIdx(int i) { sceneidx = i; }
	int getSceneIdx() { return sceneidx; }
	sf::Time getRefreshTime() { return sf::seconds(1.f / 60); }
private:
	int sceneidx = 0;
};
/**
 * @brief SceneManager is a class that can manage scene
 */
class SceneManager
{
public:
	/**
	 * @brief Constructor
	 * 
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
	void AddScene( SceneBase* scene);
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
	KT::Vector<SceneBase*> m_scene;
	SceneBase* m_currentScene;
	sf::Event m_event;
};
