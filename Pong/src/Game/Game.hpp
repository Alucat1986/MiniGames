/**
 * @file Game.hpp
 * @brief Contains the declaration of the Game class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Paddles/PlayerPaddle.hpp"
#include "Paddles/EnemyPaddle.hpp"

namespace Pong
{
	class Game
	{
	public:
		Game();
		void run();

	private:
		void handleUserInput();
		void render(float deltaTime);

	private:
		bool									m_IsRunning;
		std::uint16_t							m_Score;
		std::uint16_t							m_Lives;

		std::unique_ptr<sf::RenderWindow>		m_Window;
		std::unique_ptr<Pong::PlayerPaddle>		m_Player;
		std::unique_ptr<Pong::EnemyPaddle>		m_Enemy;

		std::unique_ptr<sf::Font>				FpsFont;
		std::unique_ptr<sf::Text>				FpsText;
	}; // class Game
} // namespace Pong

#endif