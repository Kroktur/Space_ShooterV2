#include "SceneBase.h"
/*****************************************************************//**
 * \file   SceneBase.cpp
 * \brief  Implementation of SceneBase.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
ISceneBase::ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture) :
m_Window(window)
, m_FefreshTime(sf::seconds(1.f /framerate))
, m_Sceneidx(0)
,m_Background(sf::Vector2f(1000,1000))
, m_texture(texture)
{
	m_Background.setTexture(&m_texture->getTexture("galaxie3.png"));
}


void ISceneBase::setSceneIdx(int idx)
{
	m_Sceneidx = idx;
}

int ISceneBase::getSceneIdx()
{
	return m_Sceneidx;
}

sf::Time ISceneBase::getRefreshTime()
{
	return m_FefreshTime;
}

sf::RenderWindow* ISceneBase::getWindow()
{
	return m_Window;
}