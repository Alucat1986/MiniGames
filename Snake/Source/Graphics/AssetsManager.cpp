/**
 * @file AssetsManager.cpp
 * @brief Contains the AssetsManager class implementation.
 * @author Alunya
 * @date 25.05.2025
 */

#include "Include/Graphics/AssetsManager.hpp"

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

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      PUBLIC                                                        //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

using std::int16_t;

/**
 * @brief Constructor.
 * @author Alunya
 * @date 25.05.2025
 */
AssetsManager::AssetsManager()
        : mAssetsPath( "Assets/assets.txt" ),
          mFonts( std::make_unique<std::unordered_map<std::string, sf::Font>>() ),
          mTextures( std::make_unique<std::unordered_map<std::string, sf::Texture>>() ) {
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
        int16_t               frameCount;
        stringStream >> assetType >> assetPath >> assetName;
        assetPath = "Assets/" / assetPath;

        if ( assetType == "FONT" ) {
            std::cout << "Loading font: " << assetName << " from " << assetPath.string() << "\n";
            mFonts->emplace( assetName, sf::Font( assetPath ) );
        } // if ( assetType == "FONT")
        else if ( assetType == "TEX" ) {
            stringStream >> frameCount; /** @todo Gotta do something with this information. */
            std::cout << "Loading texture: " << assetName << " from " << assetPath.string() << " with a framecount of "
                      << frameCount << "\n";
            mTextures->emplace( assetName, sf::Texture( assetPath ) );
        } // else if ( assetType == "TEX" )
    } // while ( std::getline( fileToRead, line) )
} // AssetManager::AssetManager(...)

/**
 * @brief Retrieves a font by its name.
 * @author Alunya
 * @date 25.05.2025
 * @param[in] fontName The name of the font to retrieve.
 * @return sf::Font& A reference to the requested font.
 */
sf::Font& AssetsManager::getFont( const std::string& fontName ) const {
    return mFonts->at( fontName );
} // sf::Font& AssetsManager::getFont( const std::string& fontName )

/**
 * @brief Retrieves a texture by its name.
 * @author Alunya
 * @date 25.05.2025
 * @param[in] textureName The name of the texture to retrieve.
 * @return sf::Texture& A reference to the requested texture.
 */
sf::Texture& AssetsManager::getTexture( const std::string& textureName ) const {
    return mTextures->at( textureName );
} // sf::Texture& AssetsManager::getTexture( const std::string& textureName ) const

} // namespace snake
