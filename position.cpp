#include "position.h"

#include <cmath>

/**
 * @brief Calculates the distance between this objects position and the position passed in as argument
 * 
 * @param other_position position to which distance we're calculating
 * @return the distance between the 2 positions as a double
 */
double Position::distance(Position other_position)
{
    double distance = std::pow(x - other_position.x, 2) + std::pow(y - other_position.y, 2);
    return std::sqrt(distance);
}

/**
 * @brief Calculates the distance between 2 position supplied as arguments.
 * 
 * This is a static function and is available at all times.
 * 
 * @param position_1 position of one of the points
 * @param position_2 position of the other point
 * @return distance between points as a double
 */
double Position::distance(Position position_1, Position position_2)
{
    double distance = std::pow(position_1.x - position_2.x, 2) + std::pow(position_1.y - position_2.y, 2);
    return std::sqrt(distance);
}