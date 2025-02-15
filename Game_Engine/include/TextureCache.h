#pragma once
/*****************************************************************//**
 * \file   TextureCache.h
 * \brief  contain the class TextureCache
 *
 * \author kroktur
 * \date   February 2025
 *********************************************************************/
#include "KT_Vector.h"
#include <string>

namespace sf { class Texture; }

/**
 * @brief class TextureCache
 */
class TextureCache
{
public:
	/**
	 * @brief Constructor take solutionpath
	 * @param std::string execFilePath 
	 */
	TextureCache(const std::string& execFilePath);
	/**
	 * @brief getTexture 
	 * @param std::string filename 
	 * @return sf::Texture&
	 */
	sf::Texture& getTexture(const std::string& filename);
	/**
	 * @brief destructor Cache
	 */
	~TextureCache();

private:
    struct TextureInfo
    {
        sf::Texture* texture;
        std::string path;
    };

    std::string getAbsoluteFilepath(const std::string& filename);

    KT::Vector<TextureInfo> m_allTextureInfos;
    std::string m_execFilePath;
};


