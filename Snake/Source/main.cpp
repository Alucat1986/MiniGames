/**
 * @file main.cpp
 * @brief Contains the main function.
 * @author Alunya
 * @date 09.02.2025
 */
#include "Game/Game.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <optional>

void HelloSFML();

int main() {
    // HelloSFML();
    snake::Game game;
    game.run();
}

/**
 * @brief A little test function to see if a window with a green circle is displayed correctly using SFML.
 * @author SFML-Authors
 *
 * @deprecated Might be removed in the future.
 */
[[deprecated( "Might be removed in the future. Just for testing" )]]
void HelloSFML() {
    sf::RenderWindow window( sf::VideoMode( { 200, 200 } ), "SFML works!" );
    sf::CircleShape  shape( 100.f );
    shape.setFillColor( sf::Color::Green );

    while ( window.isOpen() ) {
        while ( const std::optional event = window.pollEvent() ) {
            if ( event->is<sf::Event::Closed>() ) {
                window.close();
                break;
            } // if ( event->is<sf::Event::Closed>() )
        } // while ( const std::optional event = window.pollEvent() )
        window.clear();
        window.draw( shape );
        window.display();
    } // while ( window.isOpen() )
} // HelloSFML()
