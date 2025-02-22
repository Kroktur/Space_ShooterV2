#include "SceneBase.h"
#include "IGameObject.h"
#include"IShape.h"
/*****************************************************************//**
 * \file   SceneBase.cpp
 * \brief  Implementation of SceneBase.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
ISceneBase::ISceneBase(sf::RenderWindow* window, const float& framerate, TextureCache* texture) :
RootScene(this),
m_Window(window)
, m_FefreshTime(sf::seconds(1.f /framerate))
, m_Sceneidx(0)
,m_Background(nullptr)
, m_texture(texture)
{

}

ISceneBase::~ISceneBase()
{
	delete m_Background;
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

sf::Vector2f ISceneBase::getBackgroundCenter()
{ return m_Background->getCenter(); }

sf::Vector2f ISceneBase::getBackgroundSize()
{ return m_Background->getSize(); }

