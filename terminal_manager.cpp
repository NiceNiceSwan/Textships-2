#include <string>
#include <cmath>

#include "terminal_manager.h"
#include "include/BearLibTerminal.h"

Terminal_manager::Terminal_manager()
{
    // _map_background_color = 0xFF'00'30'FF;
    // _movement_area_color = 0xFF'5E'64'A2;
    _map_background_color = color_from_argb(0xFF, 0x00, 0x30, 0xFF);
    _movement_area_color = color_from_argb(0xFF, 0x5E, 0x64, 0xA2);
    _attack_area_color = color_from_argb(0xFF, 0xAF, 0x46, 0x7C);
    _mixed_area_color = color_from_argb(0xFF, 0x83, 0x46, 0xC2);

    _map_display_position_x = LEFT_INFO_PANEL_VERTICAL_LINE_ID + 1;
    _map_display_position_y = 1;

    _left_info_display_position_x = 1;
    _left_info_display_position_y = 1;
    _left_info_display_width = (LEFT_INFO_PANEL_VERTICAL_LINE_ID - 1) - _left_info_display_position_x;
    _left_info_display_height = (TERMINAL_HIGHEST_CELL_ID_Y - 1) - _left_info_display_position_y;

    _right_info_display_position_x = RIGHT_INFO_PANEL_VERTICAL_LINE_ID + 1;
    _right_info_display_position_y = 1;
    _right_info_display_width = TERMINAL_HIGHEST_CELL_ID_X - (RIGHT_INFO_PANEL_VERTICAL_LINE_ID + 1);
    _right_info_display_height = (TERMINAL_HIGHEST_CELL_ID_Y - 1) - _right_info_display_position_y;
}

void Terminal_manager::create_interface()
{
    terminal_put(0, 0, characters::upper_left_box_corner);
    terminal_put(0, TERMINAL_HIGHEST_CELL_ID_Y, characters::lower_left_box_corner);
    for (size_t i = 1; i < TERMINAL_HIGHEST_CELL_ID_X; i++)
    {
        terminal_put(i, 0, characters::horizontal_box_line);
        terminal_put(i, TERMINAL_HIGHEST_CELL_ID_Y, characters::horizontal_box_line);
    }
    terminal_put(TERMINAL_HIGHEST_CELL_ID_X, 0, characters::upper_right_box_corner);
    terminal_put(TERMINAL_HIGHEST_CELL_ID_X, TERMINAL_HIGHEST_CELL_ID_Y, characters::lower_right_box_corner);

    terminal_put(LEFT_INFO_PANEL_VERTICAL_LINE_ID, 0, characters::horizontal_down);
    terminal_put(RIGHT_INFO_PANEL_VERTICAL_LINE_ID, 0, characters::horizontal_down);
    for (size_t i = 1; i < TERMINAL_HIGHEST_CELL_ID_Y; i++)
    {
        terminal_put(0, i, characters::vertical_box_line);
        terminal_put(LEFT_INFO_PANEL_VERTICAL_LINE_ID, i, characters::vertical_box_line);
        terminal_put(RIGHT_INFO_PANEL_VERTICAL_LINE_ID, i, characters::vertical_box_line);
        terminal_put(TERMINAL_HIGHEST_CELL_ID_X, i, characters::vertical_box_line);
    }
    terminal_put(RIGHT_INFO_PANEL_VERTICAL_LINE_ID, TERMINAL_HIGHEST_CELL_ID_Y, horizontal_up);
    terminal_put(LEFT_INFO_PANEL_VERTICAL_LINE_ID, TERMINAL_HIGHEST_CELL_ID_Y, horizontal_up);
    terminal_refresh();
}

void Terminal_manager::begin_turn(int player)
{
    terminal_clear();
    std::string text = "Player's " + std::to_string(player) + " turn";
    terminal_print(37, 24, text.c_str()); // Player's x turn
    text = "Press enter to continue";
    terminal_print(34, 28, text.c_str()); // Press enter to continue
    terminal_refresh();
}

void Terminal_manager::update_map(std::vector<std::vector<Map_tile>> map, int current_player)
{
    terminal_bkcolor(_map_background_color);

    terminal_layer(0);
    terminal_clear_area(_map_display_position_x, _map_display_position_y, MAP_SIZE_X, MAP_SIZE_Y);
    terminal_layer(1);
    terminal_clear_area(_map_display_position_x, _map_display_position_y, MAP_SIZE_X, MAP_SIZE_Y);
    terminal_layer(2);
    terminal_clear_area(_map_display_position_x, _map_display_position_y, MAP_SIZE_X, MAP_SIZE_Y);
    terminal_layer(1);

    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j].ship_is_on_tile() && map[i][j].ship()->visible())
            {
                if (map[i][j].ship()->team() != current_player)
                {
                    terminal_color(0xFFEE2222);
                }
                
                terminal_put(_map_display_position_x + i, _map_display_position_y + j, map[i][j].ship()->type());
                terminal_color(0xFFFFFFFF);
                if (map[i][j].ship()->can_fire() != true)
                {
                    terminal_layer(2);
                    // terminal_composition(TK_ON);

                    terminal_put_ext(_map_display_position_x + i,
                                     _map_display_position_y + j,
                                     0, -2,
                                     characters::circumflex);
                    // terminal_put_ext(_map_display_position_x + i,
                    //                  _map_display_position_y + j,
                    //                  5, 0,
                    //                  0x007C);

                    // terminal_composition(TK_OFF);
                    terminal_layer(1);
                }
                
            }
        }
    }

    terminal_bkcolor(0xFF000000);
    terminal_layer(0);
    terminal_refresh();
}

void Terminal_manager::print_ship_stats(Ship ship, int current_player)
{
    terminal_layer(0);
    terminal_bkcolor(_map_background_color);
    
    terminal_clear_area(_map_display_position_x, _map_display_position_y, MAP_SIZE_X, MAP_SIZE_Y);
    terminal_bkcolor(0xFF000000);
    if (ship.team() == current_player)
    {
        terminal_clear_area(_left_info_display_position_x, _left_info_display_position_y, _left_info_display_width, _left_info_display_height);
    }
    else
    {
        terminal_clear_area(_right_info_display_position_x, _right_info_display_position_y, _right_info_display_width, _right_info_display_height);
    }

    std::string name = ship.name();
    std::string hp = std::to_string(ship.hp());
    std::string attack = std::to_string(ship.attack());
    std::string defense = std::to_string(ship.defense());
    std::string range = std::to_string(ship.range());
    std::string probable_detection_range = std::to_string(ship.probable_detection_range());
    std::string certain_detection_range = std::to_string(ship.certain_detection_range());
    std::string movement = std::to_string(ship.movement_range());
    std::string remaining_movement = std::to_string(ship.remaining_movement());

    std::string output = name + "\n"
                       + hp + " HP\n"
                       + attack + " Attack\n"
                    //    + defense + " Defense\n"
                       + range + " Guns range\n\n"
                    //    + probable_detection_range + " probable detection range\n\n"
                    //    + certain_detection_range + " certain detection range\n\n"
                       + certain_detection_range + " detection range\n\n"
                       + remaining_movement + "/" + movement + " remaining movement";
    if (ship.team() == current_player)
    {
        terminal_print_ext(_left_info_display_position_x, 
                           _left_info_display_position_y, 
                           _left_info_display_width, 
                           _left_info_display_height, 
                           TK_ALIGN_DEFAULT, 
                           output.c_str());
    }
    else
    {
        terminal_print_ext(_right_info_display_position_x, 
                           _right_info_display_position_y, 
                           _right_info_display_width, 
                           _right_info_display_height, 
                           TK_ALIGN_DEFAULT, 
                           output.c_str());
    }
    terminal_refresh();
}

void Terminal_manager::clear_info_tab()
{
    terminal_bkcolor(_map_background_color);
    terminal_clear_area(_map_display_position_x, 
                        _map_display_position_y, 
                        MAP_SIZE_X, 
                        MAP_SIZE_Y);
    terminal_bkcolor(0xFF000000);

    terminal_clear_area(_left_info_display_position_x, 
                        _left_info_display_position_y, 
                        _left_info_display_width, 
                        _left_info_display_height);

    terminal_clear_area(_right_info_display_position_x, 
                        _right_info_display_position_y,
                        _right_info_display_width, 
                        _right_info_display_height);
    
    terminal_refresh();
}

void Terminal_manager::clear_enemy_info()
{
    terminal_bkcolor(_map_background_color);
    terminal_clear_area(_map_display_position_x, 
                        _map_display_position_y, 
                        MAP_SIZE_X, 
                        MAP_SIZE_Y);
    terminal_bkcolor(0xFF000000);

    // terminal_clear_area(_left_info_display_position_x, 
    //                     _left_info_display_position_y, 
    //                     _left_info_display_width, 
    //                     _left_info_display_height);

    terminal_clear_area(_right_info_display_position_x, 
                        _right_info_display_position_y,
                        _right_info_display_width, 
                        _right_info_display_height);
    
    terminal_refresh();
}

void Terminal_manager::show_ship_ranges(Ship ship)
{
    double distance;
    int movement_range = ship.remaining_movement();
    int attack_range = ship.range();
    int radius = std::max(movement_range, attack_range);

    Position area_center = ship.position();
    area_center.x += _map_display_position_x;
    area_center.y += _map_display_position_y;

    Position diameter;
    diameter.x = ((2 * radius) + 1) + area_center.x;
    diameter.y = ((2 * radius) + 1) + area_center.y;

    Position drawing_cursor;
    drawing_cursor.x = std::max(_map_display_position_x, area_center.x - radius);
    drawing_cursor.y = std::max(_map_display_position_y, area_center.y - radius);

    for (; drawing_cursor.x < diameter.x && drawing_cursor.x < RIGHT_INFO_PANEL_VERTICAL_LINE_ID; drawing_cursor.x++)
    {
        for (; drawing_cursor.y < diameter.y && drawing_cursor.y < TERMINAL_HIGHEST_CELL_ID_Y; drawing_cursor.y++)
        {
            distance = std::pow(drawing_cursor.x - area_center.x, 2) + std::pow(drawing_cursor.y - area_center.y, 2);
            distance = std::sqrt(distance);
            if (distance <= movement_range)
            {
                terminal_bkcolor(_movement_area_color);
                terminal_clear_area(drawing_cursor.x, drawing_cursor.y, 1, 1);
            }
            if (distance <= attack_range)
            {
                terminal_bkcolor(_attack_area_color);
                terminal_clear_area(drawing_cursor.x, drawing_cursor.y, 1, 1);
            }
            if (distance <= movement_range && distance <= attack_range)
            {
                terminal_bkcolor(_mixed_area_color);
                terminal_clear_area(drawing_cursor.x, drawing_cursor.y, 1, 1);
            }
            
        }
        drawing_cursor.y = std::max(_map_display_position_y, area_center.y - radius);
    }
    
    terminal_refresh();
    terminal_bkcolor(0xFF000000);
}

void Terminal_manager::underline_ship(Position position)
{
    terminal_bkcolor(_movement_area_color);
    terminal_put(position.x, position.y, characters::underline);
    terminal_bkcolor(0xFF'00'00'00);
    terminal_refresh();
}

void Terminal_manager::overline_ship(Position position)
{
    terminal_layer(2);
    terminal_composition(TK_ON);
    position.x += _map_display_position_x;
    position.y += _map_display_position_y;

    terminal_put_ext(position.x,
                     position.y,
                     0, -2,
                     characters::circumflex);
    // terminal_put_ext(position.x,
    //                  position.y,
    //                  4, -1,
    //                  characters::right_square_bracket);
    // terminal_put_ext(position.x,
    //                  position.y,
    //                  -4, -1,
    //                  characters::left_square_bracket);

    terminal_composition(TK_OFF);
    terminal_layer(1);
    terminal_refresh();
}
