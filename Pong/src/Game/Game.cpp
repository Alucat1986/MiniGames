/**
 * @file Game.cpp
 * @brief Contains the implementation of the Game class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include <SFML/System/Clock.hpp>

#include "Game.hpp"

 // ****************************************************************************************************************** //
 //                                                                                                                    //
 //                                                      CLASSES                                                       //
 //                                                                                                                    //
 // ****************************************************************************************************************** //

namespace Pong
{
	/**
	 * @brief Constructor.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	Game::Game() :
		m_IsRunning(true),
		m_Score(0u),
		m_Lives(3u)
	{
		m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Pong");
		m_Window->setVerticalSyncEnabled(true);

		m_Player = std::make_unique<Pong::PlayerPaddle>();
		m_Enemy = std::make_unique<Pong::EnemyPaddle>();
	} // Game::Game(...)

	/**
	 * @brief Main gameloop.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Game::run()
	{
		sf::Clock clock;
		while ( m_IsRunning )
		{
			sf::Time deltaTime = clock.restart();
			
			render(deltaTime.asSeconds());
		} // while ( m_IsRunning )
	} // void Game::run(...)

	/**
	 * @brief Renders the game.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Game::render(float deltaTime)
	{
		m_Window->clear();

		m_Player->draw();
		m_Enemy->draw();

		m_Window->display();
	} // void Game::render(...)
} // namespace Pong