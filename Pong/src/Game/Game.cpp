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

namespace Pong {
	/**
	 * @brief Constructor.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	Game::Game()
			:	m_IsRunning( true ),
				m_PlayerScore( 0u ),
				m_EnemyScore( 0u ),
				m_PlayerInput( { false, false } ) {
		m_Window = std::make_unique<sf::RenderWindow>( sf::VideoMode( {
			static_cast<std::uint16_t>( WINDOW_WIDTH ),
			static_cast<std::uint16_t>( WINDOW_HEIGHT ) } ), "Pong" );
		m_Window->setVerticalSyncEnabled( true );

		m_Player = std::make_unique<Pong::PlayerPaddle>();
		m_Enemy = std::make_unique<Pong::EnemyPaddle>();
		m_Ball = std::make_unique<Pong::Ball>();

		m_Player->setPosition( { PADDLE_PADDING, WINDOW_HEIGHT / 2.0f - ( m_Player->getSize().y / 2.0f ) } );
		m_Enemy->setPosition( { WINDOW_WIDTH - PADDLE_PADDING, WINDOW_HEIGHT / 2.0f - ( m_Enemy->getSize().y / 2.0f ) } );
		m_Ball->setPosition( { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f } );

		m_FpsFont = std::make_unique<sf::Font>();
		if ( !m_FpsFont->openFromFile( "C:/Windows/Fonts/arial.ttf" ) ) {
			std::cerr << "Could not load font from file!\n";
		} // if ( !FpsFont.loadFromFile("C:/Windows/Fonts/arial.ttf") )

		m_FpsText = std::make_unique<sf::Text>( *m_FpsFont, "FPS: 0", 16 );
		m_FpsText->setFillColor( sf::Color::White );
		m_FpsText->setOrigin( m_FpsText->getLocalBounds().getCenter() );
		m_FpsText->setPosition( { WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 20.0f } );

		m_PlayerScoreText = std::make_unique<sf::Text>( *m_FpsFont, "0", 32 );
		m_EnemyScoreText = std::make_unique<sf::Text>( *m_FpsFont, "0", 32 );

		m_PlayerScoreText->setFillColor( sf::Color::Green );
		m_PlayerScoreText->setPosition( { WINDOW_WIDTH / 4.0f, 10.0f } );
		m_EnemyScoreText->setFillColor( sf::Color::Red );
		m_EnemyScoreText->setPosition( { WINDOW_WIDTH - WINDOW_WIDTH / 4.0f, 10.0f } );

		m_MiddlePoint = std::make_unique<sf::CircleShape>( 30.0f );
		m_MiddlePoint->setOrigin( { 30.0f, 30.0f } );
		m_MiddlePoint->setOutlineColor( sf::Color::White );
		m_MiddlePoint->setOutlineThickness( 10.0f );
		m_MiddlePoint->setFillColor( sf::Color( 120, 120, 120 ) );
		m_MiddlePoint->setPosition( { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f } );

		m_Lines[0] = sf::RectangleShape( { WINDOW_WIDTH, 10.0f } );
		m_Lines[0].setFillColor( sf::Color::White );
		m_Lines[0].setPosition( { 0.0f, 0.0f } );

		m_Lines[1] = sf::RectangleShape( { WINDOW_WIDTH, 10.0f } );
		m_Lines[1].setFillColor( sf::Color::White );
		m_Lines[1].setPosition( { 0.0f, WINDOW_HEIGHT - 10.0f } );

		m_Lines[2] = sf::RectangleShape( { 10.0f, WINDOW_HEIGHT - 20.0f } );
		m_Lines[2].setFillColor( sf::Color::White );
		m_Lines[2].setPosition( { 0.0f, 10.0f } );

		m_Lines[3] = sf::RectangleShape( { 10.0f, WINDOW_HEIGHT - 20.0f } );
		m_Lines[3].setFillColor( sf::Color::White );
		m_Lines[3].setPosition( { WINDOW_WIDTH - 10.0f, 10.0f } );

		m_Lines[4] = sf::RectangleShape( { 10.0f, WINDOW_HEIGHT - 20.0f } );
		m_Lines[4].setFillColor( sf::Color::White );
		m_Lines[4].setPosition( { WINDOW_WIDTH / 2.0f - 5.0f, 10.0f } );
	} // Game::Game(...)

	/**
	 * @brief Main gameloop.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Game::run() {
		sf::Clock clock;
		while ( m_IsRunning ) {
			sf::Time deltaTime = clock.restart();
			handleUserInput();

			update( deltaTime.asSeconds() );

			render( deltaTime.asSeconds() );
		} // while ( m_IsRunning )
	} // void Game::run(...)

	/**
	 * @brief Handles the user's input.
	 * @author Alunya
	 * @date 04.01.2025
	 */
	void Game::handleUserInput() {
		while ( const std::optional event = m_Window->pollEvent() ) {
			if ( event->is<sf::Event::Closed>() ) {
				m_Window->close();
				m_IsRunning = false;
				break;
			} // if ( event->is<sf::Event::Closed>() )

			if ( event->is<sf::Event::KeyPressed>() ) {
				const auto eventKey = event->getIf<sf::Event::KeyPressed>();
				if ( eventKey->scancode == sf::Keyboard::Scancode::Escape ) {
					m_Window->close();
					m_IsRunning = false;
					break;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::Escape )

				if ( eventKey->scancode == sf::Keyboard::Scancode::W ||
					 eventKey->scancode == sf::Keyboard::Scancode::Up ) {
					m_PlayerInput.Up = true;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

				if ( eventKey->scancode == sf::Keyboard::Scancode::S ||
					 eventKey->scancode == sf::Keyboard::Scancode::Down ) {
					m_PlayerInput.Down = true;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )
			} // if ( event->is<sf::Event::KeyPressed>() )

			if ( event->is<sf::Event::KeyReleased>() ) {
				const auto eventKey = event->getIf<sf::Event::KeyReleased>();

				if ( eventKey->scancode == sf::Keyboard::Scancode::W ||
					 eventKey->scancode == sf::Keyboard::Scancode::Up ) {
					m_PlayerInput.Up = false;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::W || sf::Keyboard::Scancode::Up )

				if ( eventKey->scancode == sf::Keyboard::Scancode::S ||
					 eventKey->scancode == sf::Keyboard::Scancode::Down ) {
					m_PlayerInput.Down = false;
				} // if ( eventKey->scancode == sf::Keyboard::Scancode::S || sf::Keyboard::Scancode::Down )
			} // if ( event->is<sf::Event::KeyReleased>() )
		} // while ( const std::optional event = window.pollEvent() )
	} // void Game::handleUserInput(...)

	/**
	 * @brief Updates the positions of game objects.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Game::update( const float& deltaTime ) {
		// Player movement
		if ( m_PlayerInput.Up ^ m_PlayerInput.Down ) {
			if ( m_PlayerInput.Up ) {
				m_Player->setDirection( { 0, -1 } );
			} // if ( m_PlayerInput.Up )
			else if ( m_PlayerInput.Down ) {
				m_Player->setDirection( { 0, 1 } );
			} // else if ( m_PlayerInput.Down )

			m_Player->move( deltaTime );

			// Collision check for the player's Paddle with the upper and lower window border.
			bool collision = false;
			sf::Vector2f position = m_Player->getPosition();
			if ( position.y < 0.0f ) {
				collision = true;
				position.y = 0.0f;
			} // if ( position.x < 0.0f )
			else if ( position.y + m_Player->getSize().y > WINDOW_HEIGHT ) {
				collision = true;
				position.y = WINDOW_HEIGHT - m_Player->getSize().y;
			} // else if ( position.y > WINDOW_HEIGHT )

			if ( collision ) {
				m_Player->setPosition( position );
			} // if ( collision )

		} // if ( m_PlayerInput.Up ^ m_PlayerInput.Down )

		sf::Vector2f ballPosition = m_Ball->getPosition();

		// Enemy movement
		if ( ballPosition.y < m_Enemy->getPosition().y ) {
			m_Enemy->setDirection( sf::Vector2i( 0, -1 ) );
		} // if ( ballPosition.y < m_Enemy->getPosition().y )
		else if ( ballPosition.y > m_Enemy->getPosition().y + m_Enemy->getSize().y ) {
			m_Enemy->setDirection( sf::Vector2i( 0, 1 ) );
		} // else if ( ballPosition.y > m_Enemy->getPosition().y )
		else {
			m_Enemy->setDirection( sf::Vector2i( 0, 0 ) );
		} // else

		m_Enemy->move( deltaTime );

		// Collision check for the enemy's Paddle with the upper and lower window border.
		bool collision = false;
		sf::Vector2f position = m_Enemy->getPosition();
		if ( position.y < 0.0f ) {
			collision = true;
			position.y = 0.0f;
		} // if ( position.x < 0.0f )
		else if ( position.y + m_Enemy->getSize().y > WINDOW_HEIGHT ) {
			collision = true;
			position.y = WINDOW_HEIGHT - m_Enemy->getSize().y;
		} // else if ( position.y > WINDOW_HEIGHT )

		if ( collision ) {
			m_Enemy->setPosition( position );
		} // if ( collision )

		// Ball movement
		m_Ball->move( deltaTime );

		sf::Vector2f ballDirection = m_Ball->getDirection();
		float ballRadius = m_Ball->getRadius();

		// Ball Collision with upper and lower window borders
		if ( ballPosition.y - ballRadius < 0.0f ) {
			ballPosition.y = 0.0f + ballRadius;
			ballDirection.y *= -1.0f;
			m_Ball->setPosition( ballPosition );
			m_Ball->setDirection( ballDirection );
		} // if ( ballPosition.y - ballRadius < 0.0f )
		else if ( ballPosition.y + ballRadius > WINDOW_HEIGHT ) {
			ballPosition.y = WINDOW_HEIGHT - ballRadius;
			ballDirection.y *= -1.0f;
			m_Ball->setPosition( ballPosition );
			m_Ball->setDirection( ballDirection );
		} // else if ( ballPosition.y + ballRadius > WINDOW_HEIGHT )

		// Ball Collision with left and right window borders
		if ( ballPosition.x - ballRadius < 0.0f ) {
			// Enemy scores
			m_EnemyScore++;
			resetGame();
		} // if ( ballPosition.x - ballRadius < 0.0f )
		else if ( ballPosition.x + ballRadius > WINDOW_WIDTH ) {
			m_PlayerScore++;
			resetGame();
		} // else if ( ballPosition.x + ballRadius > WINDOW_WIDTH )

		sf::Vector2f playerPosition = m_Player->getPosition();
		sf::Vector2f playerSize = m_Player->getSize();

		// Ball Collision with the player's paddle.
		// Closest point of the paddle to the ball's center.
		sf::Vector2f closestPoint;
		closestPoint.x = std::max( playerPosition.x, std::min( ballPosition.x, playerPosition.x + playerSize.x ) );
		closestPoint.y = std::max( playerPosition.y, std::min( ballPosition.y, playerPosition.y + playerSize.y ) );

		sf::Vector2f distanceVector;
		distanceVector.x = ballPosition.x - closestPoint.x;
		distanceVector.y = ballPosition.y - closestPoint.y;

		bool isColliding = distanceVector.lengthSquared() <= ( ballRadius * ballRadius );

		if ( isColliding ) {
			if ( std::abs( distanceVector.x ) > std::abs( distanceVector.y ) ) {
				if ( distanceVector.x > 0.0f ) {
					// Collision from right
					ballDirection.x *= -1.0f;
					ballPosition.x = playerPosition.x + playerSize.x + ballRadius + 0.1f;
				} // if ( distanceVector.x > 0.0f )
				else {
					// Collsion from left
					ballDirection.x *= -1.0f;
					ballPosition.x = playerPosition.x - ballRadius - 0.1f;
				} // else if ( distanceVector.x < 0.0f )
			} // if ( std::abs(distanceVector.x) > std::abs(distanceVector.y) )
			else {
				if ( distanceVector.y > 0.0f ) {
					// Collision from top
					ballDirection.y *= -1.0f;
					ballPosition.y = playerPosition.y + playerSize.y + ballRadius + 0.1f;
				} // if ( distanceVector.y > 0.0f )
				else {
					// Collision from below
					ballDirection.y *= -1.0f;
					ballPosition.y = playerPosition.y - ballRadius - 0.1f;
				} // else if ( distanceVector.y < 0.0f )
			} // else if ( std::abs(distanceVector.x) > std::abs(distanceVector.y) )
			m_Ball->setPosition( ballPosition );
			m_Ball->setDirection( ballDirection );
		} // if ( isColliding )

		sf::Vector2f enemyPosition = m_Enemy->getPosition();
		sf::Vector2f enemySize = m_Enemy->getSize();

		// Ball Collision with the enemy's paddle.
		// Closest point of the paddle to the ball's center.
		closestPoint.x = std::max( enemyPosition.x, std::min( ballPosition.x, enemyPosition.x + enemySize.x ) );
		closestPoint.y = std::max( enemyPosition.y, std::min( ballPosition.y, enemyPosition.y + enemySize.y ) );

		distanceVector.x = ballPosition.x - closestPoint.x;
		distanceVector.y = ballPosition.y - closestPoint.y;

		isColliding = distanceVector.lengthSquared() <= ( ballRadius * ballRadius );

		if ( isColliding ) {
			if ( std::abs( distanceVector.x ) > std::abs( distanceVector.y ) ) {
				if ( distanceVector.x > 0.0f ) {
					// Collision from right
					ballDirection.x *= -1.0f;
					ballPosition.x = enemyPosition.x + ballRadius + 0.1f;
				} // if ( distanceVector.x > 0.0f )
				else {
					// Collsion from left
					ballDirection.x *= -1.0f;
					ballPosition.x = enemyPosition.x - enemySize.x - ballRadius - 0.1f;
				} // else if ( distanceVector.x < 0.0f )
			} // if ( std::abs(distanceVector.x) > std::abs(distanceVector.y) )
			else {
				if ( distanceVector.y > 0.0f ) {
					// Collision from top
					ballDirection.y *= -1.0f;
					ballPosition.y = enemyPosition.y + enemySize.y + ballRadius + 0.1f;
				} // if ( distanceVector.y > 0.0f )
				else {
					// Collision from below
					ballDirection.y *= -1.0f;
					ballPosition.y = enemyPosition.y - ballRadius - 0.1f;
				} // else if ( distanceVector.y < 0.0f )
			} // else if ( std::abs(distanceVector.x) > std::abs(distanceVector.y) )
			m_Ball->setPosition( ballPosition );
			m_Ball->setDirection( ballDirection );
		} // if ( isColliding )
	} // void Game::update(...)

	/**
	 * @brief Renders the game.
	 * @param[in] deltaTime Time since the last frame in seconds.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Game::render( const float& deltaTime ) {
		static float fpsTimer = 0.0f;
		static int frameCount = 0;

		fpsTimer += deltaTime;
		frameCount++;

		if ( fpsTimer >= 1.0f ) {
			float fps = frameCount / fpsTimer;
			m_FpsText->setString( "FPS: " + std::to_string( static_cast<int>( fps ) ) );
			fpsTimer = 0.0f;
			frameCount = 0;
		} // if ( fpsTimer >= 1.0f )

		m_Window->clear( sf::Color( 120, 120, 120 ) );

		m_Window->draw( m_Lines[0] );
		m_Window->draw( m_Lines[1] );
		m_Window->draw( m_Lines[2] );
		m_Window->draw( m_Lines[3] );
		m_Window->draw( m_Lines[4] );
		m_Window->draw( *m_MiddlePoint );

		m_Window->draw( *m_Player );
		m_Window->draw( *m_Enemy );
		m_Window->draw( *m_Ball );
		m_Window->draw( *m_FpsText );
		m_Window->draw( *m_PlayerScoreText );
		m_Window->draw( *m_EnemyScoreText );

		m_Window->display();
	} // void Game::render(...)

	/**
	 * @brief Resets the game to it's initial state.
	 * @author Alunya
	 * @date 05.01.2025
	 */
	void Game::resetGame() {
		m_PlayerScoreText->setString( std::to_string( m_PlayerScore ) );
		m_EnemyScoreText->setString( std::to_string( m_EnemyScore ) );
		m_Player->setPosition( { PADDLE_PADDING, WINDOW_HEIGHT / 2.0f - ( m_Player->getSize().y / 2.0f ) } );
		m_Enemy->setPosition( { WINDOW_WIDTH - PADDLE_PADDING, WINDOW_HEIGHT / 2.0f - ( m_Enemy->getSize().y / 2.0f ) } );
		m_Ball->setPosition( { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f } );
		m_Ball->setRandomDirection();
	} // void Game::resetGame(...)
} // namespace Pong