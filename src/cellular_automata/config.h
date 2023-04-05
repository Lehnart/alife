#include <curses.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Langton loop GUI
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define W 720
//#define H 720
//#define CELL_WIDTH 6
//#define STATE_COUNT 8
//#define FRAME_DELAY_MS 50
//#define CA_INITIAL_CONFIG_FILE "res/langton_array.txt"
//#define CA_RULE_FILE "res/langton_rule.txt"
//const static int R[STATE_COUNT] = {0, 192, 0, 0, 192, 192, 0, 192};
//const static int G[STATE_COUNT] = {0, 0, 192, 0, 0, 192, 192, 192};
//const static int B[STATE_COUNT] = {0, 0, 0, 192, 192, 0, 192, 192};
//#define GUI

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Langton loop terminal
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define W 720
//#define H 720
//#define CELL_WIDTH 6
//#define STATE_COUNT 8
//#define FRAME_DELAY_MS 50
//#define CA_INITIAL_CONFIG_FILE "res/langton_array.txt"
//#define CA_RULE_FILE "res/langton_rule.txt"
//const static char chars [STATE_COUNT]= {'#','-','#','x','o','/','#','+'};
//const static Pair pairs [STATE_COUNT]= {
//        {1,COLOR_BLACK, COLOR_BLACK},
//        {2,COLOR_RED, COLOR_BLACK},
//        {3,COLOR_GREEN, COLOR_BLACK},
//        {4,COLOR_BLUE, COLOR_BLACK},
//        {5,COLOR_MAGENTA, COLOR_BLACK},
//        {6,COLOR_YELLOW, COLOR_BLACK},
//        {7,COLOR_CYAN, COLOR_BLACK},
//        {8,COLOR_WHITE, COLOR_BLACK}
//};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Byl loop config GUI
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define W 720
//#define H 720
//#define CELL_WIDTH 6
//#define STATE_COUNT 6
//#define FRAME_DELAY_MS 50
//const static int R[STATE_COUNT] = {0, 192, 0, 0, 192, 192};
//const static int G[STATE_COUNT] = {0, 0, 192, 0, 0, 192};
//const static int B[STATE_COUNT] = {0, 0, 0, 192, 192, 0};
//#define CA_INITIAL_CONFIG_FILE "res/byl_array.txt"
//#define CA_RULE_FILE "res/byl_rule.txt"
//#define GUI

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Byl loop config terminal
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define W 720
#define H 720
#define CELL_WIDTH 6
#define STATE_COUNT 6
#define FRAME_DELAY_MS 50
const static char chars [STATE_COUNT]= {'#','-','#','x','o','/'};
const static Pair pairs [STATE_COUNT]= {
        {1,COLOR_BLACK, COLOR_BLACK},
        {2,COLOR_RED, COLOR_BLACK},
        {3,COLOR_GREEN, COLOR_BLACK},
        {4,COLOR_BLUE, COLOR_BLACK},
        {5,COLOR_MAGENTA, COLOR_BLACK},
        {6,COLOR_YELLOW, COLOR_BLACK},
};
#define CA_INITIAL_CONFIG_FILE "res/byl_array.txt"
#define CA_RULE_FILE "res/byl_rule.txt"