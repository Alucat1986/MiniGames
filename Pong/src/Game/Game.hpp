/**
 * @file Game.hpp
 * @brief Contains the declaration of the Game class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>

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
	}; // class Game
} // namespace Pong

#endif