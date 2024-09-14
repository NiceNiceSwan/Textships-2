#include "ship.h"

void Ship::_destroyer()
{
    _name = "Destroyer";
    _type = Ship_class::destroyer;
    _hp = 10;
    _attack = 4;
    _defense = 1;
    _range = 4;
    _probable_detection_range = 10;
    _certain_detection_range = 8;
    _movement_range = 7;
    _remaining_movement = _movement_range;
}

void Ship::_cruiser()
{
    _name = "Cruiser";
    _type = Ship_class::cruiser;
    _hp = 15;
    _attack = 7;
    _defense = 1;
    _range = 8;
    _probable_detection_range = 7;
    _certain_detection_range = 5;
    _movement_range = 5;
    _remaining_movement = _movement_range;
}

void Ship::_battleship()
{
    _name = "Battleship";
    _type = Ship_class::battleship;
    _hp = 25;
    _attack = 12;
    _defense = 1;
    _range = 12;
    _probable_detection_range = 5;
    _certain_detection_range = 3;
    _movement_range = 3;
    _remaining_movement = _movement_range;
}

void Ship::_carrier()
{

}

void Ship::_submarine()
{

}

Ship::Ship()
{
    
}

void Ship::initialize(Ship_class ship_class)
{
    switch (ship_class)
    {
    case Ship_class::destroyer:
        _destroyer();
        break;
    case Ship_class::cruiser:
        _cruiser();
        break;
    case Ship_class::battleship:
        _battleship();
        break;
    case Ship_class::carrier:
        _carrier();
        break;
    case Ship_class::submarine:
        _submarine();
        break;
    default:
        break;
    }
}

void Ship::initialize(Ship_class ship_class, int team)
{
    _can_fire = true;
    _team = team;
    _visible = false;
    switch (ship_class)
    {
    case Ship_class::destroyer:
        _destroyer();
        break;
    case Ship_class::cruiser:
        _cruiser();
        break;
    case Ship_class::battleship:
        _battleship();
        break;
    case Ship_class::carrier:
        _carrier();
        break;
    case Ship_class::submarine:
        _submarine();
        break;
    default:
        break;
    }
}

void Ship::refresh_data()
{
    _can_fire = true;
    _remaining_movement = _movement_range;
    _visible = false;
}
