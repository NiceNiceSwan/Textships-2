#include <random>

#include "include/BearLibTerminal.h"
#include "game.h"

std::mt19937_64 random_number_generator((unsigned long long int)time(NULL));

const short int TERMINAL_HIGHEST_CELL_ID_X = 89;
const short int TERMINAL_HIGHEST_CELL_ID_Y = 51;
const short int LEFT_INFO_PANEL_VERTICAL_LINE_ID = 19;
const short int RIGHT_INFO_PANEL_VERTICAL_LINE_ID = 70;
const short int MAP_SIZE_X = 50;
const short int MAP_SIZE_Y = 50;

int main()
{
    terminal_open();
    // terminal_set("window: title='Textships 2', size=90*52, cellsize=12*16; input: filter= [keyboard, mouse];");
    terminal_set("window: title='Textships 2', size=90*52, cellsize=12*12; input: filter= [keyboard, mouse];");

    Game game;
    game.play();

    terminal_close();
}