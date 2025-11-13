#include "ship.h"

/**
 * @brief sets the ship up as a destroyer
 * 
 * @param team team to which the ship belongs to
 * @return Ship configured as a destroyer
 */
Ship Ship::Destroyer(int team)
{
    Ship new_ship(team);
    new_ship._name = "Destroyer";
    new_ship._type = Ship_class::destroyer;
    new_ship._hp = 10;
    new_ship._attack = 4;
    new_ship._defense = 1;
    new_ship._range = 4;
    new_ship._probable_detection_range = 10;
    new_ship._certain_detection_range = 8;
    new_ship._movement_range = 7;
    new_ship._remaining_movement = new_ship._movement_range;
    new_ship._team = team;
    return new_ship;
}

/**
 * @brief sets the ship up as a cruiser
 * 
 * @param team team to which the ship belongs to
 * @return Ship configured as a cruiser
 */
Ship Ship::Cruiser(int team)
{
    Ship new_ship(team);
    new_ship._name = "Cruiser";
    new_ship._type = Ship_class::cruiser;
    new_ship._hp = 15;
    new_ship._attack = 7;
    new_ship._defense = 1;
    new_ship._range = 8;
    new_ship._probable_detection_range = 7;
    new_ship._certain_detection_range = 5;
    new_ship._movement_range = 5;
    new_ship._remaining_movement = new_ship._movement_range;
    new_ship._team = team;
    return new_ship;
}

/**
 * @brief sets the ship up as a battleship
 * 
 * @param team team to which the ship belongs to
 * @return Ship configured as a battleship
 */
Ship Ship::Battleship(int team)
{
    Ship new_ship(team);
    new_ship._name = "Battleship";
    new_ship._type = Ship_class::battleship;
    new_ship._hp = 25;
    new_ship._attack = 12;
    new_ship._defense = 1;
    new_ship._range = 12;
    new_ship._probable_detection_range = 5;
    new_ship._certain_detection_range = 3;
    new_ship._movement_range = 3;
    new_ship._remaining_movement = new_ship._movement_range;
    new_ship._team = team;
    return new_ship;
}

/// @brief not implemented right now
/// @return a new ship configured as an aircraft carrier
Ship Ship::Carrier(int team)
{
    Ship new_ship;
    return new_ship;
}

/**
 * @brief not implemented right now
 * 
 * @return Ship configured as a submarine
 */
Ship Ship::Submarine(int team)
{
    Ship new_ship;
    return new_ship;
}

Ship::Ship()
{
    _can_fire = true;
    _visible = false;
}

Ship::Ship(int team)
{
    _can_fire = true;
    _team = team;
    _visible = false;
}

void Ship::refresh_data()
{
    _can_fire = true;
    _remaining_movement = _movement_range;
    _visible = false;
}
