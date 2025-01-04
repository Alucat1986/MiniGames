/**
 * @file main.cpp
 * @brief Contains the main function.
 * @author Alucat1986
 * @date 04.01.2025
 */
#include <SFML/Graphics.hpp>

void HelloSFML();

int main() {
	HelloSFML();
}

/**
 * @brief A little test function to see if a window with a green circle is displayed correctly using SFML.
 *
 * @depracated Might be removed in the future.
 */
[[deprecated("Might be removed in the future. Just for testing")]]
void HelloSFML() {
	sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while ( window.isOpen() ) {
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() ) {
				window.close();
				break;
			} // if ( event->is<sf::Event::Closed>() )
		} // while ( const std::optional event = window.pollEvent() )
		window.clear();
		window.draw(shape);
		window.display();
	} // while ( window.isOpen() )
} // HelloSFML()