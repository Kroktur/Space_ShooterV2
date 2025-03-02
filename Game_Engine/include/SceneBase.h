#pragma once
/*****************************************************************//**
 * \file   SceneBase.h
 * \brief  contain the class SceneBase
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "IGameObject.h"

class IShapeSFML;
#include "TextureCache.h"
/**
 * @brief  class ISceneBase Interaface of Scene
 */
class ISceneBase : public RootScene
{
public:
	/**
	 * @brief Constructor
	 * @param sf::RenderWindow* window
	 * @param float framerate
	 * @param TextureCache* texture
	 */
	ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture);
	/**
	 * @brief default destructor
	 */
	virtual ~ISceneBase();
	/**
	 * @brief virtual Update
	 * @param float deltatime
	 */
	virtual void Update(const float& deltatime) = 0;
	/**
	 * @brief virtual ProssesInput
	 * @param sf::Event event
	 */
	virtual void ProssesInput(const sf::Event& event) = 0;
	/**
	 * @brief virtual Render
	 */
	virtual void Render() = 0;
	/**
	 * @brief set The Scene Idx
	 * @param idx
	 */
	void setSceneIdx(int idx);
	/**
	 * @brief get the scene idx
	 * @return int
	 */
	int getSceneIdx();
	/**
	 * @get the framerate
	 * @return sf::Time
	 */
	sf::Time getRefreshTime();
	/**
	 *  @brief  get the window
	 * @return sf::RenderWindow*
	 */
	sf::RenderWindow* getWindow();
	/**
	 * @brief  return the textureCache
	 * @return textureCache*
	 */
	sf::Vector2f getBackgroundCenter();
	sf::Vector2f getBackgroundSize();
	sf::Vector2f getLeftTopCorner();
	sf::Vector2f getRightBotomCorner();
	sf::Vector2f GetCenterWindow();
	TextureCache* getTexture() { return m_texture; }



protected:
	IShapeSFML* m_Background;
	TextureCache* m_texture;
private:
	int m_Sceneidx;
	sf::RenderWindow* m_Window;
	sf::Time m_FefreshTime;
};
