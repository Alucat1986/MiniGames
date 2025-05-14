/**
 * @file Game.cpp
 * @brief Contains the implementation of the Game class.
 * @author Alunya
 * @date 14.05.2025
 */

#include "Game.hpp"

#include "../Utils/Constants.hpp"

#include <SFML/System/Clock.hpp>

#include <iostream>

//***************************************************************************************************************** //
//                                                                                                                  //
//                                                     CLASSES                                                      //
//                                                                                                                  //
//***************************************************************************************************************** //

namespace snake {

/**
 * @brief Constructor.
 * @author Alunya
 * @date 14.05.2025
 */
Game::Game()
        : m_IsRunning( true ),
          m_PlayerInput( { .Up = false, .Right = false, .Down = false, .Left = false } ) {
    m_Window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode( { static_cast<std::uint16_t>( WINDOW_WIDTH ), static_cast<std::uint16_t>( WINDOW_HEIGHT ) } ),
        "Snake Clone" );
    m_Window->setVerticalSyncEnabled( true );

    m_FpsFont = std::make_unique<sf::Font>();
    if ( !m_FpsFont->openFromFile( "C:/Windows/Fonts/arial.ttf" ) ) {
        std::cerr << "Could not load font from file!\n";
    } // if ( !FpsFont.loadFromFile("C:/Windows/Fonts/arial.ttf") )

    m_FpsText = std::make_unique<sf::Text>( *m_FpsFont, "FPS: 0", 16 );
    m_FpsText->setFillColor( sf::Color::White );
    m_FpsText->setOrigin( m_FpsText->getLocalBounds().getCenter() );
    m_FpsText->setPosition( { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 20.0f } );
} // Game::Game(...)

/**
 * @brief Main gameloop.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::run() {
    sf::Clock clock;
    while ( m_IsRunning ) {
        sf::Time deltaTime = clock.restart();
        handleUserInput();

        update( deltaTime.asSeconds() );

        render( deltaTime.asSeconds() );
    } // while ( m_IsRunning )
} // void Game::run(...)

/**
 * @brief Handles the user's input.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::handleUserInput() {
    while ( const std::optional event = m_Window->pollEvent() ) {
        if ( event->is<sf::Event::Closed>() ) {
            m_Window->close();
            m_IsRunning = false;
            break;
        } // if ( event->is<sf::Event::Closed>() )

        if ( event->is<sf::Event::KeyPressed>() ) {
            const auto eventScanCode = event->getIf<sf::Event::KeyPressed>()->scancode;
            if ( eventScanCode == sf::Keyboard::Scancode::Escape ) {
                m_Window->close();
                m_IsRunning = false;
                break;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::Escape )

            if ( eventScanCode == sf::Keyboard::Scancode::W || eventScanCode == sf::Keyboard::Scancode::Up ) {
                m_PlayerInput.Up = true;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

            if ( eventScanCode == sf::Keyboard::Scancode::D || eventScanCode == sf::Keyboard::Scancode::Right ) {
                m_PlayerInput.Right = true;
            } // if ( eventKey->scancode == sf::Keyboard::Scancode::D || sf::Keyboard::Scancode::Right )

            if ( eventScanCode == sf::Keyboard::Scancode::S || eventScanCode == sf::Keyboard::Scancode::Down ) {
                m_PlayerInput.Down = true;
            } // if ( eventScanCode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )

            if ( eventScanCode == sf::Keyboard::Scancode::A || eventScanCode == sf::Keyboard::Scancode::Left ) {
                m_PlayerInput.Left = true;
            } // if ( eventScanCode == sf::Keyboard::Scancode::A || sf::Keyboard::Scancode::Left )
        } // if ( event->is<sf::Event::KeyPressed>() )

        if ( event->is<sf::Event::KeyReleased>() ) {
            const auto eventScanCode = event->getIf<sf::Event::KeyPressed>()->scancode;

            if ( eventScanCode == sf::Keyboard::Scancode::W || eventScanCode == sf::Keyboard::Scancode::Up ) {
                m_PlayerInput.Up = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

            if ( eventScanCode == sf::Keyboard::Scancode::D || eventScanCode == sf::Keyboard::Scancode::Right ) {
                m_PlayerInput.Right = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::D || sf::Keyboard::Scancode::Right )

            if ( eventScanCode == sf::Keyboard::Scancode::S || eventScanCode == sf::Keyboard::Scancode::Down ) {
                m_PlayerInput.Down = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )

            if ( eventScanCode == sf::Keyboard::Scancode::A || eventScanCode == sf::Keyboard::Scancode::Left ) {
                m_PlayerInput.Left = false;
            } // if ( eventScanCode == sf::Keyboard::Scancode::A || sf::Keyboard::Scancode::Left )
        } // if ( event->is<sf::Event::KeyReleased>() )
    } // while ( const std::optional event = window.pollEvent() )
} // void Game::handleUserInput(...)

/**
 * @brief Updates the positions of game objects.
 * @param[in] deltaTime Time since the last frame in seconds.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::update( const float& deltaTime ) {
    handleUserInput();
    m_Player.update( deltaTime );
} // void Game::update(...)

/**
 * @brief Renders the game.
 * @param[in] deltaTime Time since the last frame in seconds.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::render( const float& deltaTime ) {
    static float fpsTimer    = 0.0f;
    static int   frameCount  = 0;

    fpsTimer                += deltaTime;
    frameCount++;

    if ( fpsTimer >= 1.0f ) {
        float fps = frameCount / fpsTimer;
        m_FpsText->setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );
        fpsTimer   = 0.0f;
        frameCount = 0;
    } // if ( fpsTimer >= 1.0f )

    m_Window->clear();

    m_Window->draw( *m_FpsText );

    m_Window->display();
} // void Game::render(...)

/**
 * @brief Resets the game to it's initial state.
 * @author Alunya
 * @date 09.02.2025
 */
void Game::resetGame() {} // void Game::resetGame(...)

} // namespace snake
