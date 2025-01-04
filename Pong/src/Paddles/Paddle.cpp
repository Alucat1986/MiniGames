/**
 * @file Paddle.cpp
 * @brief Contains the implementation of the Paddle class.
 * @author Alucat1986
 * @date 04.01.2025
 */

#include "Paddle.hpp"

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
	Paddle::Paddle()
	{
		setSize({ 10.f, 50.f });
	} // Paddle::Paddle(...)
} // namespace Pong