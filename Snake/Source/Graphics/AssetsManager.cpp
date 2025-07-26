/**
 * @file AssetsManager.cpp
 * @brief Contains the AssetsManager class implementation.
 * @author Alunya
 * @date 26.07.2025
 */

#include "AssetsManager.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

namespace snake {
using std::int16_t;

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @author Alunya
 * @date 09.06.2025
 */
AssetsManager::AssetsManager()
        : mAssetsPath( "Assets/assets.txt" ),
          mFonts( std::make_unique<std::unordered_map<std::string, sf::Font>>() ),
          mTextures( std::make_unique<std::unordered_map<std::string, TextureData>>() ) {
    mFonts->reserve( 5 );
    mTextures->reserve( 10 );

    // Since there is barely any assets in this game, I'm just implementing the loading right here.
    std::ifstream fileToRead( mAssetsPath );
    if ( !fileToRead.is_open() ) {
        std::cout << "Failed to open " << mAssetsPath.string() << " ...\n";
        return;
    } // if ( !FileToRead.is_open() )

    std::string line( "" );
    while ( std::getline( fileToRead, line ) ) {
        std::istringstream    stringStream( line );
        std::string           assetType, assetName;
        std::filesystem::path assetPath;
        int16_t               amountOfFrames;
        stringStream >> assetType >> assetPath >> assetName;
        assetPath = "Assets/" / assetPath;

        if ( assetType == "FONT" ) {
            std::cout << "Loading font: " << assetName << " from " << assetPath.string() << "\n";
            mFonts->emplace( assetName, sf::Font( assetPath ) );
        } // if ( assetType == "FONT")
        else if ( assetType == "TEX" ) {
            stringStream >> amountOfFrames;
            std::cout << "Loading texture: " << assetName << " from " << assetPath.string() << " with a framecount of "
                      << amountOfFrames << "\n";
            mTextures->emplace( assetName,
                                TextureData{ .texture = sf::Texture( assetPath ), .frameCount = amountOfFrames } );
        } // else if ( assetType == "TEX" )
    } // while ( std::getline( fileToRead, line) )
} // AssetManager::AssetManager(...)

/**
 * @brief Retrieves a font by its name.
 * @author Alunya
 * @date 09.06.2025
 * @param[in] fontName The name of the font to retrieve.
 * @return sf::Font& A reference to the requested font.
 */
sf::Font& AssetsManager::font( const std::string& fontName ) const {
    return mFonts->at( fontName );
} // sf::Font& AssetsManager::font(... ) const

/**
 * @brief Retrieves a texture by its name.
 * @author Alunya
 * @date 09.06.2025
 * @param[in] textureName The name of the texture to retrieve.
 * @return sf::Texture& A reference to the requested texture.
 */
sf::Texture& AssetsManager::texture( const std::string& textureName ) const {
    return mTextures->at( textureName ).texture;
} // sf::Texture& AssetsManager::texture(...) const

/**
 * @brief Retrieves the frame count of a texture by its name.
 * @author Alunya
 * @date 09.06.2025
 * @param[in] textureName The name of the texture to retrieve the frame count for.
 * @return int16_t The frame count of the requested texture.
 */
int16_t AssetsManager::textureFrameCount( const std::string& textureName ) const {
    return mTextures->at( textureName ).frameCount;
} // int16_t AssetsManager::textureFrameCount(...) const

// ****************************************************************************************************************** //
//                                                       END                                                          //
// ****************************************************************************************************************** //

} // namespace snake
