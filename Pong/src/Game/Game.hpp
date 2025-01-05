/**
 * @file Game.hpp
 * @brief Contains the declaration of the Game class.
 * @author Alunya
 * @date 04.01.2025
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Ball/Ball.hpp"
#include "Paddles/PlayerPaddle.hpp"
#include "Paddles/EnemyPaddle.hpp"

namespace Pong
{
	/**
	 * @class Game
	 * @brief Manages the main game loop and state of the Pong game.
	 * @author Alunya
	 * @date 04.01.2025
	 *
	 * The Game class is responsible for orchestrating the game's lifecycle,
	 * including processing input, updating the game state, and rendering the
	 * game objects to the screen.
	 */
	class Game
	{
	public:
		Game();
		void run();

	private:
		void handleUserInput();
		void update(const float& deltaTime);
		void render(const float& deltaTime);
		void resetGame();

	private:
		struct PlayerInput
		{
			bool Up;
			bool Down;
		}; // struct PlayerInput

		bool									m_IsRunning;
		std::uint16_t							m_PlayerScore;
		std::uint16_t							m_EnemyScore;
		PlayerInput								m_PlayerInput;

		std::unique_ptr<sf::RenderWindow>		m_Window;
		std::unique_ptr<Pong::PlayerPaddle>		m_Player;
		std::unique_ptr<Pong::EnemyPaddle>		m_Enemy;
		std::unique_ptr<Pong::Ball>				m_Ball;

		std::unique_ptr<sf::Font>				m_FpsFont;
		std::unique_ptr<sf::Text>				m_FpsText;
		std::unique_ptr<sf::Text>				m_PlayerScoreText;
		std::unique_ptr<sf::Text>				m_EnemyScoreText;
	}; // class Game
} // namespace Pong

#endif