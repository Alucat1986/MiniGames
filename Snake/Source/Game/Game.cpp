/**
 * @file Game.cpp
 * @brief Contains the game class implementation.
 * @author Alunya
 * @date 14.05.2025
 */

#include "Include/Game/Game.hpp"

#include "Include/Utils/Constants.hpp"

#include <SFML/System/Clock.hpp>

#include <iostream>

// ****************************************************************************************************************** //
//                                                                                                                    //
//                                                      CLASSES                                                       //
//                                                                                                                    //
// ****************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 14.05.2025
 */
Game::Game()
        : mIsRunning( true ),
          mPlayerInput( { .Up = false, .Right = false, .Down = false, .Left = false } ) {
    mWindow = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( { static_cast<std::uint16_t>( WINDOW_WIDTH ), static_cast<std::uint16_t>( WINDOW_HEIGHT ) } ),
        "Snake Clone" );
    mWindow->setVerticalSyncEnabled( true );

    mFpsFont = std::make_unique<sf::Font>();
    if ( !mFpsFont->openFromFile( "C:/Windows/Fonts/arial.ttf" ) ) {
        std::cerr << "Could not load font from file!\n";
    } // if ( !FpsFont.loadFromFile("C:/Windows/Fonts/arial.ttf") )

    mFpsText = std::make_unique<sf::Text>( *mFpsFont, "FPS: 0", 16 );
    mFpsText->setFillColor( sf::Color::White );
    mFpsText->setOrigin( mFpsText->getLocalBounds().getCenter() );
    mFpsText->setPosition( { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 20.0f } );
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
 * @date 14.05.2025
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
            if ( eventScanCode == sf::Keyboard::Scancode::Escape ) {
                mWindow->close();
                mIsRunning = false;
                break;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::Escape )

            if ( eventScanCode == sf::Keyboard::Scancode::W || eventScanCode == sf::Keyboard::Scancode::Up ) {
                mPlayerInput.Up = true;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

            if ( eventScanCode == sf::Keyboard::Scancode::D || eventScanCode == sf::Keyboard::Scancode::Right ) {
                mPlayerInput.Right = true;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::D || sf::Keyboard::Scancode::Right )

            if ( eventScanCode == sf::Keyboard::Scancode::S || eventScanCode == sf::Keyboard::Scancode::Down ) {
                mPlayerInput.Down = true;
            } // if ( eventScanCode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )

            if ( eventScanCode == sf::Keyboard::Scancode::A || eventScanCode == sf::Keyboard::Scancode::Left ) {
                mPlayerInput.Left = true;
            } // if ( eventScanCode == sf::Keyboard::Scancode::A || sf::Keyboard::Scancode::Left )
        } // if ( event->is<sf::Event::KeyPressed>() )

        if ( event->is<sf::Event::KeyReleased>() ) {
            const auto eventScanCode = event->getIf<sf::Event::KeyPressed>()->scancode;

            if ( eventScanCode == sf::Keyboard::Scancode::W || eventScanCode == sf::Keyboard::Scancode::Up ) {
                mPlayerInput.Up = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

            if ( eventScanCode == sf::Keyboard::Scancode::D || eventScanCode == sf::Keyboard::Scancode::Right ) {
                mPlayerInput.Right = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::D || sf::Keyboard::Scancode::Right )

            if ( eventScanCode == sf::Keyboard::Scancode::S || eventScanCode == sf::Keyboard::Scancode::Down ) {
                mPlayerInput.Down = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )

            if ( eventScanCode == sf::Keyboard::Scancode::A || eventScanCode == sf::Keyboard::Scancode::Left ) {
                mPlayerInput.Left = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::A || sf::Keyboard::Scancode::Left )
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
 * @date 14.05.2025
 */
void Game::render( const float& deltaTime ) {
    static float fpsTimer    = 0.0f;
    static int   frameCount  = 0;

    fpsTimer                += deltaTime;
    frameCount++;

    if ( fpsTimer >= 1.0f ) {
        float fps = frameCount / fpsTimer;
        mFpsText->setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );
        fpsTimer   = 0.0f;
        frameCount = 0;
    } // if ( fpsTimer >= 1.0f )

    mWindow->clear();

    mWindow->draw( *mFpsText );

    mWindow->display();
} // void Game::render(...)

/**
 * @brief Resets the game to it's initial state.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::resetGame() {} // void Game::resetGame(...)

} // namespace snake
