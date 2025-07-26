/**
 * @file Snake.cpp
 * @brief Contains the snake class implementation.
 * @author Alunya
 * @date 26.07.2025
 */

#include "Snake.hpp"

#include "../Graphics/AssetsManager.hpp"
#include "../Grid/Grid.hpp"
#include "../Utils/Constants.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include <iostream>
#include <iterator>
#include <list>
#include <memory>

namespace snake {
namespace {
constexpr std::uint32_t INTERVAL = 20;
} // namespace

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @author Alunya
 * @date 09.06.2025
 */
Snake::Snake( const AssetsManager& assetsManager )
        : mDead( false ),
          mGrow( false ),
          mMoveTimeThreshold( 0.3f ),
          mCurrentTimeStamp( 0.0f ),
          mAssetsManager( assetsManager ),
          mSnakeBody( std::make_unique<std::list<SnakePart>>() ) {
    mSnakeBody->emplace_back(
        SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 4,
                   .y         = constants::CELL_ROWS / 2,
                   .direction = Direction::East,
                   .part      = BodyPart::Tail,
                   .animation = Animation( mAssetsManager.texture( "SnakeTail" ), "SnakeTail",
                                           mAssetsManager.textureFrameCount( "SnakeTail" ), INTERVAL ) } );
    mSnakeBody->back().animation.sprite().setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back(
        SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 3,
                   .y         = constants::CELL_ROWS / 2,
                   .direction = Direction::East,
                   .part      = BodyPart::Mid,
                   .animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                           mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL ) } );
    mSnakeBody->back().animation.sprite().setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back(
        SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 2,
                   .y         = constants::CELL_ROWS / 2,
                   .direction = Direction::East,
                   .part      = BodyPart::Mid,
                   .animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                           mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL ) } );
    mSnakeBody->back().animation.sprite().setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back(
        SnakePart{ .x         = ( constants::CELL_COLUMNS / 2 ) - 1,
                   .y         = constants::CELL_ROWS / 2,
                   .direction = Direction::East,
                   .part      = BodyPart::Mid,
                   .animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                           mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL ) } );
    mSnakeBody->back().animation.sprite().setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    mSnakeBody->emplace_back(
        SnakePart{ .x         = constants::CELL_COLUMNS / 2,
                   .y         = constants::CELL_ROWS / 2,
                   .direction = Direction::East,
                   .part      = BodyPart::Head,
                   .animation = Animation( mAssetsManager.texture( "SnakeHead" ), "SnakeHead",
                                           mAssetsManager.textureFrameCount( "SnakeHead" ), INTERVAL ) } );
    mSnakeBody->back().animation.sprite().setTextureRect(
        { { 0, 0 }, { static_cast<int>( constants::CELL_SIZE ), static_cast<int>( constants::CELL_SIZE ) } } );

    rotateBodySprites();
} // Snake::Snake(...)

/**
 * @brief Updates the snakes state.
 * @author Alunya
 * @date 14.06.2025
 * @param[in] deltaTime The time that has passed since the last update had been called.
 *
 * Is called by Game::update(). It moves the snake into the current direction by a cell and then checks if it collides
 * with food, itself or a wall to then either grow in size or die. The deltatime parameter is used to check against the
 * m_MoveTimestamp if it's time to move the snake, default behaviour is that every 0.2ms the snake will move one grid
 * cell into the set current direction.
 */
void Snake::update( const float& deltaTime ) {
    mCurrentTimeStamp += deltaTime;
    /** @todo Either before or after moving find out if we collide or might collide with something and do the
     * corresponding action, aka grow, die or just move. */
    if ( mCurrentTimeStamp >= mMoveTimeThreshold ) {
        move();
        checkForSnakeTurns();
        rotateBodySprites();
        mCurrentTimeStamp -= mMoveTimeThreshold;
    } // if ( mCurrentTimeStamp >= mMoveTimeThreshold )

    for ( auto& bodyPart : *mSnakeBody ) {
        bodyPart.animation.update();
    } // for ( auto& bodyPart : *mSnakeBody )
} // void Snake::update(...)

/**
 * @brief Draws the snake on the given render window.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] window The render window to draw the snake on.
 */
void Snake::draw( sf::RenderWindow& window, const Grid& grid ) const {
    for ( auto& bodyPart : *mSnakeBody ) {
        switch ( bodyPart.part ) {
            case BodyPart::Head:
                bodyPart.animation.sprite().setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
            case BodyPart::Mid:
                bodyPart.animation.sprite().setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
            case BodyPart::Tail:
                bodyPart.animation.sprite().setPosition(
                    grid.getCoordinates( { static_cast<float>( bodyPart.x ), static_cast<float>( bodyPart.y ) } ) );
                break;
        } // switch ( bodyPart.part )
        window.draw( bodyPart.animation.sprite() );
    } // for ( const auto& bodyPart : *mSnakeBody )
} // void draw(...) const

/**
 * @brief To check if the snake is dead or alive.
 * @author Alunya
 * @date 14.05.2025
 *
 * @return true When the snake is dead.
 * @return false When the snake is alive.
 */
bool Snake::isDead() const {
    return mDead;
} // bool Snake::isDead(...) const

/**
 * @brief Sets the direction of the snake.
 * @author Alunya
 * @date 31.05.2025
 * @param[in] newDirection The new direction to set.
 */
void Snake::setDirection( Direction newDirection ) {
    // front(): tail, back(): head
    mSnakeBody->back().direction = newDirection;
} // void Snake::setDirection(...)

// ****************************************************************************************************************** //
//                                                      PRIVATE                                                       //
// ****************************************************************************************************************** //

/**
 * @brief Moves the snake into the current direction.
 * @author Alunya
 * @date 16.05.2025
 *
 * Movement starts from the tail, when the grow flag is set the tail will be skipped to put a new body part right
 * infront of the tail.
 */
void Snake::move() {
    std::list<SnakePart>::iterator snakeIterator = mSnakeBody->begin();
    if ( mGrow ) {
        std::advance( snakeIterator, 1 ); // Should never be mSnakeBody->end(), otherwise something went wrong.
        mSnakeBody->emplace(
            snakeIterator,
            SnakePart{ .x         = snakeIterator->x,
                       .y         = snakeIterator->y,
                       .direction = snakeIterator->direction,
                       .part      = BodyPart::Mid,
                       .animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                               mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL ) } );
        mGrow = false;
    } // if ( mGrow )

    for ( ; snakeIterator != mSnakeBody->end(); std::advance( snakeIterator, 1 ) ) {
        switch ( snakeIterator->direction ) {
            case Direction::North:
                snakeIterator->y--;
                break;
            case Direction::East:
                snakeIterator->x++;
                break;
            case Direction::South:
                snakeIterator->y++;
                break;
            case Direction::West:
                snakeIterator->x--;
                break;
        } // switch ( SnakeIterator->Direction )

        if ( snakeIterator->part == BodyPart::Head ) {
            break;
        } // if ( SnakeIterator->part == BodyPart::Head )

        snakeIterator->direction = std::next( snakeIterator )->direction;
    } // for ( ; SnakeIterator != mSnakeBody->end(); std::next( SnakeIterator ) )
} // void Snake::move(...)

/**
 * @brief Grows the snake by 1 cell.
 * @author Alunya
 * @date 09.06.2025
 */
void Snake::grow() {
    // Probably unnecessary as when the snake reaches it's max length it's about to die anyway.
    if ( mSnakeBody->size() < constants::MAX_CELL_AMOUNT ) {
        mGrow = true;
    } // if ( mSnakeBody->size() < constants::MAX_CELL_AMOUNT)
} // void Snake::grow(...)

/**
 * @brief Kills the snake.
 * @author Alunya
 * @date 16.05.2025
 */
void Snake::die() {
    mDead = true;
} // void Snake::die(...)

/**
 * @brief Rotates the body part sprites to face the current direction.
 * @author Alunya
 * @date 31.05.2025
 */
void Snake::rotateBodySprites() {
    sf::Angle rotation = sf::degrees( 0.0f );
    for ( auto& bodyPart : *mSnakeBody ) {
        switch ( bodyPart.direction ) {
            case Direction::North:
                bodyPart.animation.sprite().setRotation( rotation - sf::degrees( 180.0f ) );
                bodyPart.animation.sprite().setOrigin( { constants::CELL_SIZE, constants::CELL_SIZE } );
                break;
            case Direction::East:
                bodyPart.animation.sprite().setRotation( rotation - sf::degrees( 90.0f ) );
                bodyPart.animation.sprite().setOrigin( { constants::CELL_SIZE, 0.0f } );
                break;
            case Direction::South:
                bodyPart.animation.sprite().setRotation( rotation );
                bodyPart.animation.sprite().setOrigin( { 0.0f, 0.0f } );
                break;
            case Direction::West:
                bodyPart.animation.sprite().setRotation( rotation + sf::degrees( 90.0f ) );
                bodyPart.animation.sprite().setOrigin( { 0.0f, constants::CELL_SIZE } );
                break;
        } // switch ( bodyPart.direction )
    }
} // void Snake::rotateBodySprites(...)

/**
 * @brief Checks if the snake has turns within its body and replaces the actual Sprites.
 * @author Alunya
 * @date 14.06.2025
 */
void Snake::checkForSnakeTurns() {
    auto iterator = mSnakeBody->begin();
    std::advance( iterator, 1 );
    for ( ; iterator != mSnakeBody->end(); std::advance( iterator, 1 ) ) {
        if ( iterator->animation.name() == "SnakeHead" ) {
            break;
        } // if ( iterator->animation.name() == "SnakeHead" )

        switch ( std::prev( iterator )->direction ) {
            case Direction::North:
                switch ( iterator->direction ) {
                    case Direction::East:
                        if ( iterator->animation.name() != "SnakeMidTurnRight" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnRight" ), "SnakeMidTurnRight",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnRight" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnRight" )
                        break;
                    case Direction::North:
                    case Direction::South:
                        if ( iterator->animation.name() != "SnakeMid" ) {
                            iterator->animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                                             mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMid" )
                        break;
                    case Direction::West:
                        if ( iterator->animation.name() != "SnakeMidTurnLeft" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnLeft" ), "SnakeMidTurnLeft",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnLeft" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnLeft" )
                        break;
                } // switch ( iterator->direction )
                break;
            case Direction::East:
                switch ( iterator->direction ) {
                    case Direction::South:
                        if ( iterator->animation.name() != "SnakeMidTurnRight" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnRight" ), "SnakeMidTurnRight",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnRight" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnRight" )
                        break;
                    case Direction::East:
                    case Direction::West:
                        if ( iterator->animation.name() != "SnakeMid" ) {
                            iterator->animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                                             mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMid" )
                        break;
                    case Direction::North:
                        if ( iterator->animation.name() != "SnakeMidTurnLeft" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnLeft" ), "SnakeMidTurnLeft",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnLeft" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnLeft" )
                        break;
                } // switch ( iterator->direction )
                break;
            case Direction::South:
                switch ( iterator->direction ) {
                    case Direction::West:
                        if ( iterator->animation.name() != "SnakeMidTurnRight" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnRight" ), "SnakeMidTurnRight",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnRight" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnRight" )
                        break;
                    case Direction::South:
                    case Direction::North:
                        if ( iterator->animation.name() != "SnakeMid" ) {
                            iterator->animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                                             mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMid" )
                        break;
                    case Direction::East:
                        if ( iterator->animation.name() != "SnakeMidTurnLeft" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnLeft" ), "SnakeMidTurnLeft",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnLeft" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnLeft" )
                        break;
                } // switch ( iterator->direction )
                break;
            case Direction::West:
                switch ( iterator->direction ) {
                    case Direction::North:
                        if ( iterator->animation.name() != "SnakeMidTurnRight" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnRight" ), "SnakeMidTurnRight",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnRight" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnRight" )
                        break;
                    case Direction::East:
                    case Direction::West:
                        if ( iterator->animation.name() != "SnakeMid" ) {
                            iterator->animation = Animation( mAssetsManager.texture( "SnakeMid" ), "SnakeMid",
                                                             mAssetsManager.textureFrameCount( "SnakeMid" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMid" )
                        break;
                    case Direction::South:
                        if ( iterator->animation.name() != "SnakeMidTurnLeft" ) {
                            iterator->animation =
                                Animation( mAssetsManager.texture( "SnakeMidTurnLeft" ), "SnakeMidTurnLeft",
                                           mAssetsManager.textureFrameCount( "SnakeMidTurnLeft" ), INTERVAL );
                        } // if ( iterator->animation.name() != "SnakeMidTurnLeft" )
                        break;
                } // switch ( iterator->direction )
                break;
        } // switch ( iterator->direction )
    } // for ( auto iterator = mSnakeBody->begin(); iterator != mSnakeBody->end();  iterator++ )
} // void Snake::checkForSnakeTurns(...)

// ****************************************************************************************************************** //
//                                                       END                                                          //
// ****************************************************************************************************************** //

} // namespace snake
