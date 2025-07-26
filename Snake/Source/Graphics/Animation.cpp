/**
 * @file Animation.cpp
 * @brief Contains the Animation class implementation.
 * @author Alunya
 * @date 26.07.2025
 */

#include "Animation.hpp"

#include "../Utils/Constants.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cstdint>
#include <string>

namespace snake {
using std::uint32_t;

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @author Alunya
 * @date 09.06.2025
 * @param[in] texture The texture to use for the animation sprite.
 * @param[in] name The name of the animation.
 * @param[in] frameCount The number of frames in the animation.
 * @param[in] interval The frame interval between animation frames.
 */
Animation::Animation( const sf::Texture& texture, const std::string& name, uint32_t frameCount, uint32_t interval )
        : mSprite( texture ),
          mName( name ),
          mFrameCount( frameCount ),
          mCurrentFrame( 0 ),
          mInterval( interval ),
          mCurrentIntervalStep( 1 ) {
    mSprite.setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );
} // Animation::Animation(...)

/**
 * @brief Updates the animation frame.
 * @author Alunya
 * @date 09.06.2025
 */
void Animation::update() {
    if ( mFrameCount == 1 ) {
        return;
    } // if ( mFrameCount == 1 )

    mCurrentIntervalStep++;
    if ( mCurrentIntervalStep >= mInterval ) {
        mCurrentIntervalStep = 1;
        mCurrentFrame++;
        if ( mCurrentFrame >= mFrameCount ) {
            mCurrentFrame = 0;
        } // if ( mCurrentFrame >= mFrameCount )

        mSprite.setTextureRect(
            { { static_cast<int>( mCurrentFrame * constants::CELL_SIZE ), 0 },
              { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );
    } // if ( mCurrentIntervalStep >= mInterval )
} // void Animation::update(...)

/**
 * @brief Returns the current sprite of the animation.
 * @author Alunya
 * @date 09.06.2025
 * @return A const reference to the current sprite of the animation.
 */
sf::Sprite& Animation::sprite() {
    return mSprite;
} // sf::Sprite& Animation::sprite(...) const

/**
 * @brief Returns the name of the animation.
 * @author Alunya
 * @date 09.06.2025
 * @return A const reference to the name of the animation.
 */
const std::string& Animation::name() const {
    return mName;
} // std::string& Animation::name(...) const

// ****************************************************************************************************************** //
//                                                       END                                                          //
// ****************************************************************************************************************** //

} // namespace snake
