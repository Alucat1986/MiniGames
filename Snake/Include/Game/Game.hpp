/**
 * @file Game.hpp
 * @brief Contains the game class declaration.
 * @author Alunya
 * @date 14.05.2025
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "Include/Snake/Snake.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cstdint>
#include <memory>

namespace snake {

/**
 * @class Game
 * @brief Manages the main game loop and state of the Pong game.
 * @author Alunya
 * @date 09.02.2025
 *
 * The Game class is responsible for orchestrating the game's lifecycle,
 * including processing input, updating the game state, and rendering the
 * game objects to the screen.
 */
class Game {
public:
    Game();

    void run();

private:
    void handleUserInput();
    void update( const float& deltaTime );
    void render( const float& deltaTime );
    void resetGame();

private:
    struct PlayerInput {
        bool Up;
        bool Right;
        bool Down;
        bool Left;
    }; // struct PlayerInput

    bool        m_IsRunning;
    Snake       m_Player;
    PlayerInput m_PlayerInput;

    std::unique_ptr<sf::RenderWindow> m_Window;

    std::unique_ptr<sf::Font> m_FpsFont;
    std::unique_ptr<sf::Text> m_FpsText;
}; // class Game

} // namespace snake

#endif // #ifndef GAME_HPP
