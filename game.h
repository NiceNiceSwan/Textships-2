#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include "ship.h"
#include "terminal_manager.h"
#include "map_tile.h"

extern std::mt19937_64 random_number_generator;

extern const short int TERMINAL_HIGHEST_CELL_ID_X;
extern const short int TERMINAL_HIGHEST_CELL_ID_Y;
extern const short int LEFT_INFO_PANEL_VERTICAL_LINE_ID;
extern const short int RIGHT_INFO_PANEL_VERTICAL_LINE_ID;
extern const short int MAP_SIZE_X;
extern const short int MAP_SIZE_Y;

class Game
{
private:
    std::vector<std::vector<Ship>> _ships;
    std::vector<std::vector<Map_tile>> _map;
    Terminal_manager _terminal_manager;

    bool _quit_game;

    bool _selected_a_ship;
    Ship* _selected_ship;

    int _player;
public:
    Game();

    bool end_game();
    void play();
    void wait_screen();
    void turn();
    void mouse_input();
    void select_ship(Position map_position, Position mouse_position);
    void move_ship(Position clicked_map_tile);
    void mark_visible_ships();
    void refresh_ships();
    bool hit_a_ship(Ship* target_ship);
    void kill_a_ship(int team_of_dead_ship);
};


#endif