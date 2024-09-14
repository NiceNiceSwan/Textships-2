#include "position.h"

#include <cmath>

double Position::distance(Position other_position)
{
    double distance = std::pow(x - other_position.x, 2) + std::pow(y - other_position.y, 2);
    return std::sqrt(distance);
}

double Position::distance(Position position_1, Position position_2)
{
    double distance = std::pow(position_1.x - position_2.x, 2) + std::pow(position_1.y - position_2.y, 2);
    return std::sqrt(distance);
}