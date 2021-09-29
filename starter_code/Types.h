#ifndef COSC_ASSIGN_TWO_TYPES
#define COSC_ASSIGN_TWO_TYPES

#include <math.h>

//the max amount of rows or coulumns the board can be
#define BOARD_MAX_SIZE          26
#define QWIRKLE_POINTS          6

//Maximum amount of tiles that can be in the bag
#define MAXIMUM_TILES           72
#define MAX_HAND_SIZE           6

#define DUPLICATES              2
#define MAX_PLAYERS             2
//regex for player name
#define NAME_REGEX              "[A-Z]+"
//regex for when a player uses the place command
#define PLACE_REGEX             "place [Y,G,R,O,P,B]{1}[1-6]{1} at [A-Z]{1}[0-9]{1,2}"
//regex for when a player uses the replace command
#define REPLACE_REGEX           "replace [Y,G,R,O,P,B]{1}[1-6]{1}"
//reegex for when a aplayer uses the save command
#define SAVE_REGEX              "save [A-Za-z0-9]+"
//regex for the format of the file
#define FILE_FORMAT_REGEX       "[A-Z]+\n[0-9]+\n([Y,G,R,O,P,B]{1}[1-6]{1},)*([Y,G,R,O,P,B]{1}[1-6]{1})*\n([A-Z]+)\n([0-9]+)\n(([Y,G,R,O,P,B]{1}[1-6]{1},){0,5}([Y,G,R,O,P,B]{1}[1-6]{1}))\n([0-9]+,[0-9]+)\n([Y,G,R,O,P,B]{1}[1-6]{1}@[A-Z]{1}[0-9]{1,2}, )*([Y,G,R,O,P,B]{1}[1-6]{1}@[A-Z]{1}[0-9]{1,2})*\n(([Y,G,R,O,P,B]{1}[1-6]{1},)|([Y,G,R,O,P,B]{1}[1-6]{1}))*\n([A-Z]+)"
#define COL_ROW_START           0
#define COL_ROW_END             25
#define FILE_EXTENSION          ".save"
//separator characters used in file parsing
#define FILE_TILE_SEPARATOR ','
#define FILE_TILE_POSITION_SEPARATOR '@'


#endif // COSC_ASSIGN_TWO_TYPES