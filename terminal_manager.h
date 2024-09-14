#ifndef TERMINAL_MANAGER_H
#define TERMINAL_MANAGER_H

#include <vector>
#include <cstdint>

#include "map_tile.h"
#include "ship.h"
#include "position.h"

extern const short int TERMINAL_HIGHEST_CELL_ID_X;
extern const short int TERMINAL_HIGHEST_CELL_ID_Y;
extern const short int LEFT_INFO_PANEL_VERTICAL_LINE_ID;
extern const short int RIGHT_INFO_PANEL_VERTICAL_LINE_ID;
extern const short int MAP_SIZE_X;
extern const short int MAP_SIZE_Y;

enum characters
{
    left_square_bracket = 0x005B,
    right_square_bracket = 0x005D,
    circumflex = 0x005E,
    underline = 0x005F,
    overline = 0x203E,
    horizontal_box_line = 0x2500,
    vertical_box_line = 0x2502,
    upper_left_box_corner = 0x250C,
    upper_right_box_corner = 0x2510,
    lower_left_box_corner = 0x2514,
    lower_right_box_corner = 0x2518,
    vertical_right = 0x251C,
    vertical_left = 0x2524,
    horizontal_down = 0x252C,
    horizontal_up = 0x2534,
    vertical_horizontal = 0x253C
};

class Terminal_manager
{
private:
    uint32_t _map_background_color;
    uint32_t _movement_area_color;
    uint32_t _attack_area_color;
    uint32_t _mixed_area_color;

    int _map_display_position_x;
    int _map_display_position_y;

    int _left_info_display_position_x;
    int _left_info_display_position_y;
    int _left_info_display_width;
    int _left_info_display_height;

    int _right_info_display_position_x;
    int _right_info_display_position_y;
    int _right_info_display_width;
    int _right_info_display_height;
public:
    Terminal_manager();

    void create_interface();
    void begin_turn(int player);
    void update_map(std::vector<std::vector<Map_tile>> map, int current_player);
    void print_ship_stats(Ship ship, int current_player);
    // void print_ship_stats(Ship* ship, int current_player);
    void clear_info_tab();
    void clear_enemy_info();
    void show_ship_ranges(Ship ship);
    void underline_ship(Position position);
    void overline_ship(Position position);
};


#endif