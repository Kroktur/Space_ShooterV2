#pragma once
/*****************************************************************//**
 * \file   Game.h
 * \brief  contain the class Game
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include "SceneBase.h"
#include "GameObject.h"
/**
 * @brief Derived ISceneBase  Game
 */
class Game : public ISceneBase
{
public:
	/**
	 * @brief Game Constructor
	 * @param sf::RenderWindow* window
	 * @param float framerate
	 * @param TextureCache* texture
	 */
	Game(sf::RenderWindow* window, const float& framerate, TextureCache* texture);
	/**
	 * @brief default Constructor
	 */
	virtual ~Game()override = default;
	/**
	 * @brief Update Imple
	 * @param float deltatime
	 */
	virtual void Update(const float& deltatime) override;
	/**
	 * @brief ProssesInput Impl
	 * @param sf::event
	 */
	virtual void ProssesInput(const sf::Event& event)override;
	/**
	 *@brief Render Impl
	 */
	virtual void Render() override;

private:
	sf::RectangleShape m_Ship;
	//TODO
	Cursor cursor;
};
