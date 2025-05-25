/**
 * @file AssetsManager.cpp
 * @brief Contains the AssetsManager class implementation.
 * @author Alunya
 * @date 25.05.2025
 */

#include "Include/Graphics/AssetsManager.hpp"

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 25.05.2025
 */
AssetsManager::AssetsManager()
        : mAssetsPath( "Assets/" ),
          mFonts( std::make_unique<std::unordered_map<std::string, sf::Font>>() ),
          mTextures( std::make_unique<std::unordered_map<std::string, sf::Texture>>() ) {
} // AssetManager::AssetManager(...)

} // namespace snake
