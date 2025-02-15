#include "TextureCache.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
/*****************************************************************//**
 * \file   TextureCache.cpp
 * \brief  Implementation of TextureCache.h
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
TextureCache::TextureCache(const std::string& execFilePath) : m_execFilePath(execFilePath)
{}

TextureCache::~TextureCache()
{
    for (auto& textureInfo : m_allTextureInfos)
        delete textureInfo.texture;
    m_allTextureInfos.clear();
}

std::string TextureCache::getAbsoluteFilepath(const std::string& filename)
{
    std::filesystem::path execFilePath(m_execFilePath);
    auto filepath = execFilePath.parent_path().parent_path().parent_path().parent_path().parent_path() / "Re" / std::filesystem::path(filename);
    return filepath.string();
}

sf::Texture& TextureCache::getTexture(const std::string& filename)
{
    std::string path = getAbsoluteFilepath(filename);
    for (size_t idx = 0; idx < m_allTextureInfos.Size(); ++ idx)
    {
        if (m_allTextureInfos[idx].path == path)
            return *m_allTextureInfos[idx].texture;
    }

    TextureInfo ti;
    ti.path = path;
    ti.texture = new sf::Texture;
    ti.texture->loadFromFile(path);
    m_allTextureInfos.pushBack(ti);

    return *ti.texture;
}
