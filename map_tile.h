#ifndef MAP_TILE_H
#define MAP_TILE_H

// #include "position.h"
#include "ship.h"

class Map_tile
{
private:
    // Position _position;
    bool _ship_is_on_tile;
    Ship* _ship_on_tile;
public:
    Map_tile();
    // Map_tile(Position position);
    // Map_tile(int position_x, int position_y);

    // setters
    // void position(Position position) { _position = position; };
    // void position(int position_x, int position_y) { _position.x = position_x; _position.y = position_y; };
    void ship(Ship& ship) { _ship_on_tile = &ship; _ship_is_on_tile = true; };
    void ship(Ship* ship) { _ship_on_tile = ship; _ship_is_on_tile = true; };

    // getters
    // Position position() { return _position; };
    Ship* ship() { return _ship_on_tile; };
    bool ship_is_on_tile() { return _ship_is_on_tile; };

    // simple functions
    void clear_tile() { _ship_is_on_tile = false; _ship_on_tile = nullptr; };
};


#endif