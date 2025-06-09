/**
 * @file Animation.hpp
 * @brief Contains the Animation class declaration.
 * @author Alunya
 * @date 09.06.2025
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include <cstdint>
#include <string>

namespace snake {
using std::uint32_t;

/**
 * @class Animation
 * @brief Manages the animations for game objects.
 * @author Alunya
 * @date 09.06.2025
 *
 * The animation class is responsible for handling the animations of game objects.
 */
class Animation {
public:
    Animation( const sf::Texture& texture, const std::string& name, uint32_t frameCount = 1, uint32_t interval = 1 );
    ~Animation() = default;

    void               update();
    sf::Sprite&        sprite();
    const std::string& name() const;

private:
    sf::Sprite  mSprite;
    std::string mName;
    uint32_t    mFrameCount;
    uint32_t    mCurrentFrame;
    uint32_t    mInterval;
    uint32_t    mCurrentIntervalStep;
};

} // namespace snake

#endif // ANIMATION_HPP
