/**
 * @file Game.hpp
 * @brief Contains the game class declaration.
 * @author Alunya
 * @date 25.05.2025
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "Include/Graphics/AssetsManager.hpp"
#include "Include/Grid/Grid.hpp"
#include "Include/Snake/Snake.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace snake {

/**
 * @class Game
 * @brief Manages the main game loop and state of the Pong game.
 * @author Alunya
 * @date 25.02.2025
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

    bool                              mIsRunning;

    std::unique_ptr<AssetsManager>    mAssetsManager;
    std::unique_ptr<sf::RenderWindow> mWindow;
    std::unique_ptr<Grid>             mGrid;

    Snake                             mPlayer;
    PlayerInput                       mPlayerInput;

    std::unique_ptr<sf::Font>         mFpsFont;
    std::unique_ptr<sf::Text>         mFpsText;
}; // class Game

} // namespace snake

#endif // #ifndef GAME_HPP
