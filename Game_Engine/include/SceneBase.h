#pragma once
/*****************************************************************//**
 * \file   SceneBase.h
 * \brief  contain the class SceneBase
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include<string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "KT_Vector.h"
#include "TextureCache.h"
class ISceneBase
{
public:
	ISceneBase(sf::RenderWindow* window , const float& framerate , const std::string& execFilePath);
	virtual ~ISceneBase();
	virtual void Update(const float& deltatime) = 0;
	virtual void ProssesInput(const sf::Event& event) = 0;
	virtual void Render() = 0;
	 void setSceneIdx(int idx);
	 int getSceneIdx();
	 sf::Time getRefreshTime();
	sf::RenderWindow* getWindow();
protected:
	sf::RectangleShape m_Background;
	TextureCache* m_texture;
private:
	int m_Sceneidx;
	sf::RenderWindow* m_Window;
	sf::Time m_FefreshTime;
};