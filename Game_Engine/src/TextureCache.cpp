#include "Game.h"
#include "TextureCache.h"

#include <SFML/Graphics.hpp>

#include <filesystem>
#include "iostream"
//TextureCache::TextureCache(const std::string& execFilePath) : m_execFilePath(execFilePath)
//{}
//
//TextureCache::~TextureCache()
//{
//    for (auto& textureInfo : m_allTextureInfos)
//        delete textureInfo.texture;
//}
//
//std::string TextureCache::getAbsoluteFilepath(const std::string& filename)
//{
//    std::filesystem::path execFilePath(m_execFilePath);
//    auto filepath = execFilePath.parent_path().parent_path().parent_path().parent_path().parent_path() / "Re" / std::filesystem::path(filename);
//    return filepath.string();
//}
//
//sf::Texture& TextureCache::getTexture(const std::string& filename)
//{
//    std::string path = getAbsoluteFilepath(filename);
//    for (auto& textureInfo : m_allTextureInfos)
//    {
//        if (textureInfo.path == path)
//            return *textureInfo.texture;
//    }
//
//    TextureInfo ti;
//    ti.path = path;
//    ti.texture = new sf::Texture;
//    ti.texture->loadFromFile(path);
//    m_allTextureInfos.push_back(ti);
//
//    return *ti.texture;
//}
sf::Texture& TextureCache::getTexture(const std::string& path)
{
    for (auto& textureinfo : m_allTextureInfos)
    {
        if (textureinfo.path == path)
        {
            return *textureinfo.texture;
        }
    }
    TextureInfo ti;
    ti.path = path;
    ti.texture = new sf::Texture;
    if (!ti.texture->loadFromFile(path))
        std::cout << "error font";
    m_allTextureInfos.push_back(ti);

    return *ti.texture;
}

TextureCache::~TextureCache()
{
    for (auto textureinfo : m_allTextureInfos)
        delete textureinfo.texture;
    m_allTextureInfos.clear();
}