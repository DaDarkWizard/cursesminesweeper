#include <ncursesw/ncurses.h>
#include "game.h"

int main()
{
    // Start ncurses mode.
    initscr();
    // Capture all user input.
    raw();
    // Capture mouse input.
    mousemask(ALL_MOUSE_EVENTS, NULL);

    // Hide the cursor.
    curs_set(0);

    // Allow colors.
    start_color();
    

    printw("test");

    // Do not echo cursor text.
    noecho();

    // Capture keypad and fkeys input.
    keypad(stdscr, TRUE);

    // Initialized the program.
    ms_init();

    // Run the minesweeper loop.
    while(ms_run()) {}

    // Exit ncurses mode.
    endwin();

    return 0;
}