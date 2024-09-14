#include "game.h"
#include "position.h"



#include "include/BearLibTerminal.h"

Game::Game()
{
    _quit_game = false;
    _player = 0;
    _ships.resize(2);
    _map.resize(MAP_SIZE_X, std::vector<Map_tile>(MAP_SIZE_Y));

    std::uniform_int_distribution<int> player_1_spawn_positions(0, 9);

    // debug positions to test detection and firing
    // std::uniform_int_distribution<int> player_2_spawn_positions(5, 14);

    std::uniform_int_distribution<int> player_2_spawn_positions(40, 49);
    Position position;

    for (size_t i = 0; i < _ships.size(); i++)
    {
        _ships[i].resize(5);
        for (size_t j = 0; j < _ships[i].size(); j++)
        {
            // _ships[i][j].initialize(Ship_class::destroyer, i);
            do
            {
                if (i == 0)
                {
                    position.x = player_1_spawn_positions(random_number_generator);
                    position.y = player_1_spawn_positions(random_number_generator);
                }
                else
                {
                    position.x = player_2_spawn_positions(random_number_generator);
                    position.y = player_2_spawn_positions(random_number_generator);
                }
            } while (_map[position.x][position.y].ship_is_on_tile());
            _ships[i][j].position(position);
            _map[position.x][position.y].ship(_ships[i][j]);
        }
    }

    for (size_t i = 0; i < _ships.size(); i++)
    {
        _ships[i][0].initialize(Ship_class::destroyer, i);
        _ships[i][1].initialize(Ship_class::destroyer, i);
        _ships[i][2].initialize(Ship_class::cruiser, i);
        _ships[i][3].initialize(Ship_class::cruiser, i);
        _ships[i][4].initialize(Ship_class::battleship, i);
    }
    
}

bool Game::end_game()
{
    if (_quit_game)
    {
        return true;
    }
    
    // multithread this bitch >:)
    for (size_t i = 0; i < _ships.size(); i++)
    {
        if (_ships[i].empty())
        {
            return true;
        }
    }
    
    return false;
}

void Game::play()
{
    while (!end_game())
    {
        wait_screen();
        refresh_ships();
        mark_visible_ships();
        turn();
        _player = (_player + 1) % 2;
    }
}

void Game::wait_screen()
{
    _terminal_manager.begin_turn(_player);
    while (true)
    {
        if (terminal_has_input())
        {
            int player_input = terminal_read();
            if (player_input == TK_ENTER || player_input == TK_MOUSE_LEFT)
            {
                break;
            }
            if (player_input == TK_CLOSE)
            {
                _quit_game = true;
                break;
            }
            
        }
    }
}

void Game::turn()
{
    _selected_a_ship = false;
    Position mouse_position;
    _terminal_manager.create_interface();
    _terminal_manager.update_map(_map, _player);
    while (true)
    {
        if (terminal_has_input())
        {
            int player_input = terminal_read();
            if (player_input == TK_MOUSE_LEFT)
            {
                player_input = 0;
                mouse_input();
            }
            if (player_input == TK_ENTER)
            {
                break;
            }
            if (player_input == TK_CLOSE)
            {
                _quit_game = true;
                break;
            }
        }
    }
}

void Game::mouse_input()
{
    Position mouse_position;
    mouse_position.x = terminal_state(TK_MOUSE_X);
    mouse_position.y = terminal_state(TK_MOUSE_Y);
    Position map_tile;
    if (mouse_position.x <= LEFT_INFO_PANEL_VERTICAL_LINE_ID
     || mouse_position.x >= RIGHT_INFO_PANEL_VERTICAL_LINE_ID
     || mouse_position.y <= 0
     || mouse_position.y >= TERMINAL_HIGHEST_CELL_ID_Y)
    {
        // if we're here this means that the mouse click occured outside the map, and so as to not 
        // do any outside of array bounds fuckery we'll just ignore the click
        return;
    }

    map_tile.x = mouse_position.x - (LEFT_INFO_PANEL_VERTICAL_LINE_ID + 1);
    map_tile.y = mouse_position.y - 1;

    if (_map[map_tile.x][map_tile.y].ship_is_on_tile())
    {
        if (_selected_a_ship && _map[map_tile.x][map_tile.y].ship()->team() != _player)
        {
            hit_a_ship(_map[map_tile.x][map_tile.y].ship());
            return;
        }
        
        // if (_map[map_tile.x][map_tile.y].ship()->team() == _player)
        // {
            // select_ship(map_tile, mouse_position);
            // return;
        // }
        
        select_ship(map_tile, mouse_position);
        return;
    }

    if (_selected_a_ship)
    {
        move_ship(map_tile);
    }
    
    _selected_a_ship = false;
    _selected_ship = nullptr;
    _terminal_manager.clear_info_tab();
    _terminal_manager.update_map(_map, _player);
}

void Game::select_ship(Position map_position, Position mouse_position)
{
    Ship* ship = _map[map_position.x][map_position.y].ship();

    if (ship->visible())
    {
        _terminal_manager.print_ship_stats(*ship, _player);
    }

    if (ship->team() == _player)
    {
        // _terminal_manager.show_movement_area(map_position, ship->remaining_movement());
        _terminal_manager.show_ship_ranges(*ship);

        // if (terminal_state(TK_MOUSE_CLICKS) >= 2)
        // {
        //     _terminal_manager.underline_ship(mouse_position);
        //     _selected_a_ship = true;
        //     _selected_ship = ship;
        //     return;
        // }

        _terminal_manager.underline_ship(mouse_position);
        _selected_a_ship = true;
        _selected_ship = ship;
        return;
    }
    _selected_a_ship = false;
    _selected_ship = nullptr;
}

void Game::move_ship(Position clicked_map_tile)
{
    Position ship_position = _selected_ship->position();
    double distance = std::pow(clicked_map_tile.x - ship_position.x, 2) + std::pow(clicked_map_tile.y - ship_position.y, 2);
    distance = std::sqrt(distance);
    if (distance <= _selected_ship->remaining_movement())
    {
        distance = ceil(distance);
        _selected_ship->add_remaining_movement(-distance);
        _selected_ship->position(clicked_map_tile);
        _map[ship_position.x][ship_position.y].clear_tile();
        _map[clicked_map_tile.x][clicked_map_tile.y].ship(_selected_ship);
        _selected_a_ship = false;
        _selected_ship = nullptr;
        _terminal_manager.update_map(_map, _player);
    }
    mark_visible_ships();
    _terminal_manager.update_map(_map, _player);
}

void Game::mark_visible_ships()
{
    Position friendly_ship;
    Position enemy_ship;
    double distance;
    int other_player = (_player + 1) % 2;

    for (size_t i = 0; i < _ships[_player].size(); i++)
    {
        _ships[_player][i].visible(true);
    }
    
    for (size_t i = 0; i < _ships[_player].size(); i++)
    {
        for (size_t j = 0; j < _ships[other_player].size(); j++)
        {
            friendly_ship = _ships[_player][i].position();
            enemy_ship = _ships[other_player][j].position();
            distance = std::pow(friendly_ship.x - enemy_ship.x, 2) + std::pow(friendly_ship.y - enemy_ship.y, 2);
            // TECHNICALLY I could not count the square root of the distance and just raise the detection range 
            // to the power of 2 which would be faster
            // BUT WHY WOULD I DO THAT WHEN THIS PART OF THE CODE IS NOT A BOTTLENECK?
            distance = std::sqrt(distance);
            if (distance <= _ships[_player][i].certain_detection_range())
            {
                _ships[other_player][j].visible(true);
            }
        }
    }
}

void Game::refresh_ships()
{
    for (size_t i = 0; i < _ships.size(); i++)
    {
        for (size_t j = 0; j < _ships[i].size(); j++)
        {
            _ships[i][j].refresh_data();
        }
    }
}

bool Game::hit_a_ship(Ship* target_ship)
{
    if (_selected_ship->can_fire() != true)
    {
        return false;
    }

    Position shooter_position = _selected_ship->position();
    Position target_position = target_ship->position();
    // if (shooter_position.distance(target_position) > _selected_ship->range())
    // {
    //     return false;
    // }
    
    if (Position::distance(shooter_position, target_position) > _selected_ship->range())
    {
        return false;
    }
    

    target_ship->add_hp(-_selected_ship->attack());
    _selected_ship->can_fire(false);
    _terminal_manager.overline_ship(_selected_ship->position());
    _selected_a_ship = false;
    _selected_ship = nullptr;
    _terminal_manager.print_ship_stats(*target_ship, _player);

    if (target_ship->hp() <= 0)
    {
        kill_a_ship(target_ship->team());
        _terminal_manager.update_map(_map, _player);
        _terminal_manager.clear_enemy_info();
        _selected_a_ship = false;
        _selected_ship = nullptr;
        return true;
    }
    return false;
}

void Game::kill_a_ship(int team)
{
    Position ship_position;
    for (int i = 0; i < _ships[team].size(); i++)
    {
        if (_ships[team][i].hp() <= 0)
        {
            ship_position = _ships[team][i].position();
            _map[ship_position.x][ship_position.y].clear_tile();

            _ships[team][i] = _ships[team].back();
            ship_position = _ships[team].back().position();
            _map[ship_position.x][ship_position.y].clear_tile();

            _ships[team].pop_back();
            // _map[ship_position.x][ship_position.y].ship(&_ships[team][i]);
            i--;
        }
    }
    for (size_t i = 0; i < _ships[team].size(); i++)
    {
        ship_position = _ships[team][i].position();
        _map[ship_position.x][ship_position.y].ship(&_ships[team][i]);
    }
    
}
