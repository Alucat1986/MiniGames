/**
 * @file main.cpp
 * @brief Contains the main function.
 * @author Alunya
 * @date 14.05.2025
 */

#include "Include/Game/Game.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <optional>

void HelloSFML();

int main() {
    snake::Game game;
    game.run();
} // int main(...)