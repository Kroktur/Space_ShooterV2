#include "SceneBase.h"

ISceneBase::ISceneBase(sf::RenderWindow* window, const float& framerate, const std::string& execFilePath) :
m_Window(window)
, m_FefreshTime(sf::seconds(1.f /framerate))
, m_Sceneidx(0)
,m_Background(sf::Vector2f(100,10000))
, m_texture(new TextureCache(execFilePath))
{
	
}

ISceneBase::~ISceneBase()
{
	delete m_texture;
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