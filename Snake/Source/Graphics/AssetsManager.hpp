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

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

namespace snake {
using std::int16_t;

/**
 * @class AssetsManager
 * @brief Manages the loading and storing of game assets.
 * @author Alunya
 * @date 09.06.2025
 *
 * The assets manager is responsible for loading and storing game assets such as textures and fonts.
 */
class AssetsManager {
public:
    AssetsManager();
    ~AssetsManager() = default;

    sf::Font&    font( const std::string& fontName ) const;
    sf::Texture& texture( const std::string& textureName ) const;
    int16_t      textureFrameCount( const std::string& textureName ) const;

private:
    struct TextureData {
        sf::Texture texture;
        int16_t     frameCount{ 1 };
    };

    std::filesystem::path                                         mAssetsPath;
    std::unique_ptr<std::unordered_map<std::string, sf::Font>>    mFonts;
    std::unique_ptr<std::unordered_map<std::string, TextureData>> mTextures;
};

} // namespace snake

#endif // ASSETSMANAGER_HPP
