/**
 * @file Game.cpp
 * @brief Contains the implementation of the Game class.
 * @author Alunya
 * @date 04.01.2025
 */

#include <iostream>

#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "../Utils/Constants.hpp"

// ***************************************************************************************************************** //
//                                                                                                                   //
//                                                      CLASSES                                                      //
//                                                                                                                   //
// ***************************************************************************************************************** //

namespace Pong
{
	/**
	 * @brief Constructor.
	 * @author Alunya
	 * @date 04.01.2025
	 */
	Game::Game() :
		m_IsRunning(true),
		m_Score(0u),
		m_Lives(3u),
		m_PlayerInput({ false, false })
	{
		m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Pong");
		m_Window->setVerticalSyncEnabled(true);

		m_Player = std::make_unique<Pong::PlayerPaddle>();
		m_Enemy = std::make_unique<Pong::EnemyPaddle>();
		m_Ball = std::make_unique<Pong::Ball>();

		FpsFont = std::make_unique<sf::Font>();
		if ( !FpsFont->openFromFile("C:/Windows/Fonts/arial.ttf") )
		{
			std::cerr << "Could not load font from file!\n";
		} // if ( !FpsFont.loadFromFile("C:/Windows/Fonts/arial.ttf") )

		FpsText = std::make_unique<sf::Text>(*FpsFont, "FPS: 0", 16);
		FpsText->setFillColor(sf::Color::White);
		sf::Vector2f center = FpsText->getLocalBounds().getCenter();
		FpsText->setOrigin(center);
		FpsText->setPosition({ static_cast<float>(WINDOW_WIDTH / 2.f), static_cast<float>(WINDOW_HEIGHT - 20.f) });
	} // Game::Game(...)

	/**
	 * @brief Main gameloop.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Game::run()
	{
		sf::Clock clock;
		while ( m_IsRunning )
		{
			sf::Time deltaTime = clock.restart();
			handleUserInput();

			update(deltaTime.asSeconds());
			
			render(deltaTime.asSeconds());
		} // while ( m_IsRunning )
	} // void Game::run(...)

	/**
	 * @brief Handles the user's input.
	 * @author Alunya
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
				const auto eventKey = event->getIf<sf::Event::KeyPressed>();
				if ( eventKey->scancode == sf::Keyboard::Scancode::Escape )
				{
					m_Window->close();
					m_IsRunning = false;
					break;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::Escape )

				if ( eventKey->scancode == sf::Keyboard::Scancode::W ||
					 eventKey->scancode == sf::Keyboard::Scancode::Up )
				{
					m_PlayerInput.Up = true;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

				if ( eventKey->scancode == sf::Keyboard::Scancode::S ||
					 eventKey->scancode == sf::Keyboard::Scancode::Down )
				{
					m_PlayerInput.Down = true;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )
			} // if ( event->is<sf::Event::KeyPressed>() )

			if ( event->is<sf::Event::KeyReleased>() )
			{
				const auto eventKey = event->getIf<sf::Event::KeyReleased>();
				
				if ( eventKey->scancode == sf::Keyboard::Scancode::W ||
					eventKey->scancode == sf::Keyboard::Scancode::Up )
				{
					m_PlayerInput.Up = false;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

				if ( eventKey->scancode == sf::Keyboard::Scancode::S ||
					eventKey->scancode == sf::Keyboard::Scancode::Down )
				{
					m_PlayerInput.Down = false;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )
			} // if ( event->is<sf::Event::KeyReleased>() )
		} // while ( const std::optional event = window.pollEvent() )
	} // void Game::handleUserInput(...)

	/**
	 * @brief Updates the positions of game objects.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alunya
	 * @date 04.01.2025
	 */
	void Game::update(const float& deltaTime)
	{
		// Player movement
		if ( m_PlayerInput.Up ^ m_PlayerInput.Down )
		{
			if ( m_PlayerInput.Up )
			{
				m_Player->setDirection({ 0, -1 });
			} // if ( m_PlayerInput.Up )
			else if ( m_PlayerInput.Down )
			{
				m_Player->setDirection({ 0, 1 });
			} // else if ( m_PlayerInput.Down )

			m_Player->move(deltaTime);

			// Collision check for the player's Paddle with the upper and lower window border.
			bool collision = false;
			sf::Vector2f position = m_Player->getPosition();
			if ( position.y < 0 )
			{
				collision = true;
				position.y = 0.f;
			} // if ( position.x < 0 )
			else if ( position.y + m_Player->getSize().y > static_cast<float>(WINDOW_HEIGHT) )
			{
				collision = true;
				position.y = static_cast<float>(WINDOW_HEIGHT - m_Player->getSize().y);
			} // else if ( position.y > WINDOW_HEIGHT )

			if ( collision )
			{
				m_Player->setPosition(position);
			} // if ( collision )
				
		} // if ( m_PlayerInput.Up ^ m_PlayerInput.Down )

		// Enemy movement
		m_Enemy->move(deltaTime);
	} // void Game::update(...)
	/**
	 * @brief Renders the game.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alunya
	 * @date 04.01.2025
	 */
	void Game::render(const float& deltaTime)
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
		m_Window->draw(*m_Ball);
		m_Window->draw(*FpsText);

		m_Window->display();
	} // void Game::render(...)
} // namespace Pong