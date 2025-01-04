/**
 * @file Game.cpp
 * @brief Contains the implementation of the Game class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include <iostream>

#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "../Utils/Constants.hpp"

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

		FpsFont = std::make_unique<sf::Font>();
		if ( !FpsFont->openFromFile("C:/Windows/Fonts/arial.ttf") )
		{
			std::cerr << "Could not load font from file!\n";
		} // if ( !FpsFont.loadFromFile("C:/Windows/Fonts/arial.ttf") )

		FpsText = std::make_unique<sf::Text>(*FpsFont, "FPS: 0", 12);
		FpsText->setFillColor(sf::Color::White);
		sf::Vector2f center = FpsText->getLocalBounds().getCenter();
		FpsText->setOrigin(center);
		FpsText->setPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT - 20.f });
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
			handleUserInput();
			
			render(deltaTime.asSeconds());
		} // while ( m_IsRunning )
	} // void Game::run(...)

	/**
	 * @brief Handles the user's input.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Game::handleUserInput()
	{
		while ( const std::optional event = m_Window->pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
			{
				m_Window->close();
				m_IsRunning = false;
				break;
			} // if ( event->is<sf::Event::Closed>() )

			if ( event->is<sf::Event::KeyPressed>() )
			{
				if ( event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape )
				{
					m_Window->close();
					m_IsRunning = false;
					break;
				} // if ( event->getIf<sf::Event::KeyPressed>()->scancode == sf::Keyboard::Scancode::Escape )
			} // if ( event->is<sf::Event::KeyPressed>() )
		} // while ( const std::optional event = window.pollEvent() )
	} // void Game::handleUserInput(...)

	/**
	 * @brief Renders the game.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alucat1986
	 * @date 04.01.2025
	 */
	void Game::render(float deltaTime)
	{
		static float fpsTimer = 0.f;
		static int frameCount = 0;

		fpsTimer += deltaTime;
		frameCount++;

		if ( fpsTimer >= 1.f )
		{
			float fps = frameCount / fpsTimer;
			FpsText->setString("FPS: " + std::to_string(static_cast<int>(fps)));
			fpsTimer = 0.f;
			frameCount = 0;
		} // if ( fpsTimer >= 1.f )

		m_Window->clear();

		m_Window->draw(*m_Player);
		m_Window->draw(*m_Enemy);
		m_Window->draw(*FpsText);

		m_Window->display();
	} // void Game::render(...)
} // namespace Pong