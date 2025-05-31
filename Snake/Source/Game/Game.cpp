/**
 * @file Game.cpp
 * @brief Contains the game class implementation.
 * @author Alunya
 * @date 31.05.2025
 */

#include "Include/Game/Game.hpp"

#include "Include/Graphics/AssetsManager.hpp"
#include "Include/Grid/Grid.hpp"
#include "Include/Snake/Snake.hpp"
#include "Include/Utils/Constants.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

using std::uint16_t, std::int64_t;

/**
 * @brief Constructor.
 * @author Alunya
 * @date 31.05.2025
 */
Game::Game()
        : mIsRunning( true ),
          mDrawGrid( false ),
          mAssetsManager( std::make_unique<AssetsManager>() ),
          mGrid( std::make_unique<Grid>() ),
          mPlayerInput( { .Up = false, .Right = false, .Down = false, .Left = false } ),
          mPlayer( *mAssetsManager ) {
    mWindow =
        std::make_unique<sf::RenderWindow>( sf::VideoMode( { static_cast<uint16_t>( constants::WINDOW_WIDTH ),
                                                             static_cast<uint16_t>( constants::WINDOW_HEIGHT ) } ),
                                            "Snake Clone" );
    mWindow->setVerticalSyncEnabled( true );

    mFpsFont = std::make_unique<sf::Font>( mAssetsManager->getFont( "MainFont" ) );

    mFpsText = std::make_unique<sf::Text>( *mFpsFont, "FPS: 60", 16 );
    mFpsText->setFillColor( sf::Color::White );
    mFpsText->setOrigin( { mFpsText->getLocalBounds().size.x, 0.0f } );
    mFpsText->setPosition( { constants::WINDOW_WIDTH - constants::WINDOW_MARGIN, 1.0f } );
} // Game::Game(...)

/**
 * @brief Main gameloop.
 * @author Alunya
 * @date 14.05.2025
 */
void Game::run() {
    sf::Clock clock;
    while ( mIsRunning ) {
        sf::Time deltaTime = clock.restart();
        handleUserInput();

        update( deltaTime.asSeconds() );

        render( deltaTime.asSeconds() );
    } // while ( m_IsRunning )
} // void Game::run(...)

/**
 * @brief Handles the user's input.
 * @author Alunya
 * @date 31.05.2025
 */
void Game::handleUserInput() {
    while ( const std::optional event = mWindow->pollEvent() ) {
        if ( event->is<sf::Event::Closed>() ) {
            mWindow->close();
            mIsRunning = false;
            break;
        } // if ( event->is<sf::Event::Closed>() )

        if ( event->is<sf::Event::KeyPressed>() ) {
            const auto eventScanCode = event->getIf<sf::Event::KeyPressed>()->scancode;

            switch ( eventScanCode ) {
                case sf::Keyboard::Scancode::Escape:
                    mWindow->close();
                    mIsRunning = false;
                    break;
                case sf::Keyboard::Scancode::W:
                case sf::Keyboard::Scancode::Up:
                    mPlayerInput.Up = true;
                    break;
                case sf::Keyboard::Scancode::D:
                case sf::Keyboard::Scancode::Right:
                    mPlayerInput.Right = true;
                    break;
                case sf::Keyboard::Scancode::S:
                case sf::Keyboard::Scancode::Down:
                    mPlayerInput.Down = true;
                    break;
                case sf::Keyboard::Scancode::A:
                case sf::Keyboard::Scancode::Left:
                    mPlayerInput.Left = true;
                    break;
                case sf::Keyboard::Scancode::G:
                    toggleGridDrawing();
                    break;
                default:
                    std::cout << "Unhandled key pressed: " << static_cast<char>( eventScanCode ) << "\n";
                    break;
            } // switch(eventScanCode)
        } // if ( event->is<sf::Event::KeyPressed>() )

        if ( event->is<sf::Event::KeyReleased>() ) {
            const auto eventScanCode = event->getIf<sf::Event::KeyReleased>()->scancode;

            switch ( eventScanCode ) {
                case sf::Keyboard::Scancode::W:
                case sf::Keyboard::Scancode::Up:
                    mPlayerInput.Up = false;
                    break;
                case sf::Keyboard::Scancode::D:
                case sf::Keyboard::Scancode::Right:
                    mPlayerInput.Right = false;
                    break;
                case sf::Keyboard::Scancode::S:
                case sf::Keyboard::Scancode::Down:
                    mPlayerInput.Down = false;
                    break;
                case sf::Keyboard::Scancode::A:
                case sf::Keyboard::Scancode::Left:
                    mPlayerInput.Left = false;
                    break;
                default:
                    std::cout << "Unhandled key released: " << static_cast<char>( eventScanCode ) << "\n";
                    break;
            } // switch(eventScanCode)
        } // if ( event->is<sf::Event::KeyReleased>() )
    } // while ( const std::optional event = window.pollEvent() )
} // void Game::handleUserInput(...)

/**
 * @brief Updates the positions of game objects.
 * @param[in] deltaTime Time since the last frame in seconds.
 * @author Alunya
 * @date 14.05.2025
 */
void Game::update( const float& deltaTime ) {
    mPlayer.update( deltaTime );
} // void Game::update(...)

/**
 * @brief Renders the game.
 * @param[in] deltaTime Time since the last frame in seconds.
 * @author Alunya
 * @date 25.05.2025
 */
void Game::render( const float& deltaTime ) {
    static float   fpsTimer    = 0.0f;
    static int64_t frameCount  = 0;

    fpsTimer                  += deltaTime;
    frameCount++;

    if ( fpsTimer >= 1.0f ) {
        float fps = frameCount / fpsTimer;
        mFpsText->setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );
        fpsTimer   = 0.0f;
        frameCount = 0;
    } // if ( fpsTimer >= 1.0f )

    mWindow->clear();

    mGrid->draw( *mWindow, mDrawGrid );
    mWindow->draw( *mFpsText );
    mPlayer.draw( *mWindow, *mGrid );

    mWindow->display();
} // void Game::render(...)

/**
 * @brief Resets the game to it's initial state.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::resetGame() {} // void Game::resetGame(...)

/**
 * @brief Toggles the grid drawing state.
 * @author Alunya
 * @date 31.05.2025
 */
void Game::toggleGridDrawing() {
    mDrawGrid = !mDrawGrid;
} // void Game::toggleGridDrawing(...)

} // namespace snake
