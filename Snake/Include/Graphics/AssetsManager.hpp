/**
 * @file AssetsManager.hpp
 * @brief Contains the AssetManager class declaration.
 * @author Alunya
 * @date 25.05.2025
 */

#ifndef ASSETSMANAGER_HPP
#define ASSETSMANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace snake {

/**
 * @class AssetsManager
 * @brief Manages the loading and storing of game assets.
 * @author Alunya
 * @date 25.05.2025
 *
 * The assets manager is responsible for loading and storing game assets such as textures and fonts.
 */
class AssetsManager {
public:
    AssetsManager();
    ~AssetsManager() = default;

    sf::Font&    getFont( const std::string& fontName ) const;
    sf::Texture& getTexture( const std::string& textureName ) const;

private:
    std::filesystem::path                                         mAssetsPath;
    std::unique_ptr<std::unordered_map<std::string, sf::Font>>    mFonts;
    std::unique_ptr<std::unordered_map<std::string, sf::Texture>> mTextures;
};

} // namespace snake

#endif // ASSETSMANAGER_HPP
