/**
 * @file EnemyPaddle.hpp
 * @brief Contains the declaration of the EnemyPaddle class.
 * @author Alunya
 * @date 04.01.2025
 */

#ifndef ENEMYPADDLE_HPP
#define ENEMYPADDLE_HPP

#include "Paddle.hpp"

namespace Pong
{
	/**
	 * @class EnemyPaddle
	 * @brief Represents the paddle controlled by the AI.
	 * @author Alunya
	 * @date 04.01.2025
	 *
	 * The EnemyPaddle class inherits from the Paddle class and adds functionality
	 * specific to the enemy's paddle, such as initialization of it's appearance
	 * and position, as well as a specified movement algorithm to determine where
	 * to move to.
	 */
	class EnemyPaddle : public Paddle
	{
	public:
		EnemyPaddle();
	}; // class EnemyPaddle
} // namespace Pong

#endif