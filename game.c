#include "game.h"

#include <locale.h>
#include <stdlib.h>
#include <time.h>
//#include <linux/time.h>

//#include <panel.h>

enum GameState {
    MENU = 1,
    PLAYING = 2
};

enum ColorPairs {
    WHITE_ON_BLACK = 1
};

enum GameFlags {
    FLAG_BOMB = 1,
    FLAG_FLAGGED = 2,
    FLAG_QUESTION = 4,
    FLAG_DISPLAY = 8
};

enum GameState game_state;

WINDOW *game_window;
int game_width;
int game_height;
int bombs;
char *game_data;

WINDOW *game_menu;
int menu_row;
int menu_start_col;

MEVENT mouse_event;
int event;

int modified;

void ms_init_color_pairs(WINDOW *w)
{
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_RED, 1000, 0, 0);
    init_color(31, 500, 500, 500);

    init_pair(5, COLOR_BLUE, 31);
    init_pair(4, COLOR_RED, 31);
    init_pair(3, 31, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, 31);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
}

void ms_init()
{
    setlocale(LC_ALL, "");
    ms_init_color_pairs(stdscr);
    game_menu = stdscr;
    box(game_menu, 0, 0);

    nodelay(game_menu, true);
    nodelay(stdscr, true);

    // Print the title.
    wmove(game_menu, 1, (COLS - 11)/2);
    attron(A_UNDERLINE);
    wprintw(game_menu, "MINESWEEPER");
    attroff(A_UNDERLINE);

    // Print the menu.
    menu_row = (LINES - 3 - 4) / 2 + 1;
    menu_start_col = COLS/2 - 4;
    wmove(game_menu, menu_row, menu_start_col);
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    wprintw(game_menu, "1. EASY");
    wmove(game_menu, menu_row + 1, menu_start_col);
    wprintw(game_menu, "2. MEDIUM");
    wmove(game_menu, menu_row + 2, menu_start_col);
    wprintw(game_menu, "3. HARD");
    wmove(game_menu, menu_row + 3, menu_start_col);
    wprintw(game_menu, "4. EXIT");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    wrefresh(game_menu);
    game_state = MENU;
}

void ms_creategame()
{
    
    game_window = newwin(game_height + 2, game_width + 2, 5, (COLS - (game_width + 2)) / 2);
    nodelay(game_window, true);\
    ms_init_color_pairs(game_window);
    box(game_window, 0, 0);
    for(int i = 0; i < game_width; i++)
    {
        for(int j = 0; j < game_height; j++)
        {
            wmove(game_window, 1 + j, 1 + i);
            //wcolor_set(game_menu, 
            wattron(game_window, COLOR_PAIR(2));
            waddch(game_window, ACS_CKBOARD);
            wattroff(game_window, COLOR_PAIR(2));

            //wprintw(game_menu, "\U00002588");
        }
    }
    game_state = PLAYING;

    // Create the game data.
    game_data = (char*)malloc(sizeof(char) * game_width * game_height);
    if(game_data == NULL)
    {
        endwin();
        fprintf(stderr, "Failed to malloc");
        exit(1);
    }
    for(int i = 0; i < game_width * game_height; i++)
    {
        game_data[i] = 0;
    }
    
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    //unsigned long t = time_current_millis();
    srand(spec.tv_sec);
    for(int i = 0; i < bombs; i++)
    {
        int j = rand() % (game_width * game_height);
        if(game_data[j] == 1)
        {
            i--;
            continue;
        }
        else
        {
            game_data[j] = 1;
        }
    }
    

    // Clear menu.
    menu_row = (LINES - 3 - 4) / 2 + 1;
    wmove(game_menu, menu_row, menu_start_col);
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    wprintw(game_menu, "               ");
    wmove(game_menu, menu_row + 1, menu_start_col);
    wprintw(game_menu, "               ");
    wmove(game_menu, menu_row + 2, menu_start_col);
    wprintw(game_menu, "               ");
    wmove(game_menu, menu_row + 3, menu_start_col);
    wprintw(game_menu, "               ");
    wmove(game_menu, 4, (COLS  - 9) / 2);
    attron(A_UNDERLINE);
    wprintw(game_menu, "EXIT GAME");
    attroff(A_UNDERLINE);
    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));

    // Refresh the menu
    wrefresh(game_menu);
    wrefresh(game_window);
}

void ms_cleangame()
{
    delwin(game_window);
    wmove(game_menu, 4, (COLS  - 9) / 2);
    wprintw(game_menu, "         ");
    redrawwin(game_menu);
    free(game_data);
}

void click_game(int clickx, int clicky)
{
    int location = clicky * game_width + clickx;

    if(location < 0 || location >= game_width * game_height)
    {
        return;
    }

    // Tile is already displayed.
    if(game_data[location] & FLAG_DISPLAY)
    {
        return;
    }

    // Tile is marked for safety.
    if(game_data[location] & (FLAG_FLAGGED | FLAG_QUESTION))
    {
        return;
    }

    // Tile is a bomb.
    if(game_data[location] & FLAG_BOMB)
    {
        
        
        
        for(int i = 0; i < game_width; i++)
        {
            for(int j = 0; j < game_height; j++)
            {
                int l = j * game_width + i;
                if(game_data[l] & FLAG_BOMB)
                {
                    //ms_init_color_pairs();
                    
                    if(game_data[l] & FLAG_FLAGGED)
                    {
                        
                        
                        wmove(game_window, j + 1, i + 1);
                        wattron(game_window, A_BOLD);
                        wattron(game_window, COLOR_PAIR(5));
                        wprintw(game_window, "%c", 'B');
                        wattroff(game_window, COLOR_PAIR(5));
                        wattroff(game_window, A_BOLD);
                    }
                    else
                    {
                        
                        wmove(game_window, j + 1, i + 1);
                        wattron(game_window, COLOR_PAIR(4));
                        wattron(game_window, A_BOLD);
                        wprintw(game_window, "%c", 'B');
                        wattroff(game_window, COLOR_PAIR(4));
                        wattroff(game_window, A_BOLD);
                    }
                }
            }
        }
        attroff(A_BOLD);
        wrefresh(game_window);
        return;
    }

    // Tile is free.
    // Count bombs around tile.
    int bomb_count = 0;
    for(int i = clickx - 1; i <= clickx + 1; i++)
    {
        if(i < 0 || i >= game_width)
        {
            continue;
        }
        for(int j = clicky - 1; j <= clicky + 1; j++)
        {
            if(j < 0 || j >= game_height)
            {
                continue;
            }
            if(game_data[j * game_width + i] & FLAG_BOMB)
            {
                bomb_count++;
            }
        }
    }

    //return;

    // Tile has no nearby bombs. Expand.
    wattron(game_window, A_BOLD);
    game_data[location] |= FLAG_DISPLAY;
    if(bomb_count == 0)
    {
        for(int i = clickx - 1; i <= clickx + 1; i++)
        {
            if(i < 0 || i >= game_width)
            {
                continue;
            }
            for(int j = clicky - 1; j <= clicky + 1; j++)
            {
                if(j < 0 || j >= game_height)
                {
                    continue;
                }
                click_game(i, j);
            }
        }
        
        wattron(game_window, COLOR_PAIR(2));
        wmove(game_window, clicky + 1, clickx + 1);
        waddch(game_window, ' ');
        wattroff(game_window, COLOR_PAIR(2));
    }
    else
    {
        wattron(game_window, COLOR_PAIR(2));
        wmove(game_window, clicky + 1, clickx + 1);
        waddch(game_window, '0' + bomb_count);
        wattroff(game_window, COLOR_PAIR(2));
    }
    wattroff(game_window, A_BOLD);
}

int ms_run()
{

    switch(game_state)
    {
        case MENU:
        {
            event = wgetch(game_menu);
            if(event == KEY_F(1)) return 0;
            if(event == ERR)
            {
                break;
            }
            else if(event == KEY_MOUSE && getmouse(&mouse_event) == OK)
            {
                wmove(game_menu, menu_row + 3, 1);
                if(mouse_event.bstate & BUTTON1_CLICKED)
                {
                    if(mouse_event.y == menu_row + 3)
                    {
                        return 0;
                    }
                    else if(mouse_event.y >= menu_row && mouse_event.y < menu_row + 3)
                    {
                        if(mouse_event.y == menu_row)
                        {
                            game_width = 9;
                            game_height = 9;
                            bombs = 10;
                        }
                        else if(mouse_event.y == menu_row + 1)
                        {
                            game_width = 16;
                            game_height = 16;
                            bombs = 40;
                        }
                        else
                        {
                            game_width = 30;
                            game_height = 16;
                            bombs = 99;
                        }
                        ms_creategame();
                        modified = 1;
                    }
                }
            }
            else
            {
                wmove(game_menu, menu_row + 3, 1);
                wprintw(game_menu, "NO MOUSE EVENT");
            }
            wrefresh(game_menu);
            break;
        }
        case PLAYING:
        {
            event = getch();
            if(event == ERR)
            {
                //event = wgetch(game_window);
            }
            if(event == KEY_F(1)) return 0;
            if(event == ERR)
            {

            }
            else if(event == KEY_MOUSE && getmouse(&mouse_event) == OK)
            {
                
                if(mouse_event.x > game_window->_begx && mouse_event.x <= game_window->_begx + game_width &&
                   mouse_event.y > game_window->_begy && mouse_event.y <= game_window->_begy + game_height)
                {
                    int clickx = mouse_event.x - game_window->_begx - 1;
                    int clicky = mouse_event.y - game_window->_begy - 1;
                    modified = true;
                    wmove(game_menu, LINES - 2, 1);
                    
                    int location = clicky * game_width + clickx;
                    if(mouse_event.bstate & BUTTON3_CLICKED)
                    {
                        if(!(game_data[location] & FLAG_DISPLAY))
                        {
                            wprintw(game_menu, "MOUSE EVENT RIGHT %3d %3d", clickx, clicky);
                            
                            wmove(game_window, clicky + 1, clickx + 1);
                            if(game_data[location] & FLAG_FLAGGED)
                            {
                                game_data[location] ^= FLAG_FLAGGED;
                                game_data[location] |= FLAG_QUESTION;
                                wattron(game_window, COLOR_PAIR(3));
                                waddch(game_window, '?');
                                wattroff(game_window, COLOR_PAIR(3));
                            }
                            else if(game_data[location] & FLAG_QUESTION)
                            {
                                game_data[location] ^= FLAG_QUESTION;
                                wattron(game_window, COLOR_PAIR(2));
                                waddch(game_window, ACS_CKBOARD);
                                wattroff(game_window, COLOR_PAIR(2));
                            }
                            else
                            {
                                game_data[location] |= FLAG_FLAGGED;
                                wattron(game_window, COLOR_PAIR(3));
                                waddch(game_window, 'f');
                                wattroff(game_window, COLOR_PAIR(3));
                            }
                            wrefresh(game_menu);
                            wrefresh(game_window);
                        }
                    }
                    else if(mouse_event.bstate & BUTTON1_CLICKED)
                    {
                        wprintw(game_menu, "MOUSE EVENT LEFT  %3d %3d", clickx, clicky);
                        wrefresh(game_menu);
                        click_game(clickx, clicky);
                    }
                }
                else if(mouse_event.y == 4 && mouse_event.x >= (COLS - 9) / 2 && mouse_event.x < (COLS + 9) / 2)
                {
                    ms_cleangame();
                    ms_init();
                    return 1;
                }
                
            }
            else
            {
                wmove(game_menu, LINES - 2, 1);
                wprintw(game_menu, "BUTTON EVENT %3d                ", event);
                wrefresh(game_menu);
                modified = true;
                //wmove(game_menu, LINES - 2, 1);
                //wprintw(game_menu, "BUTTON EVENT: %d", event);
            }
            if(modified)
            {
                modified = false;
                refresh();
                wrefresh(game_menu);
                wrefresh(game_window);
            }
            
            break;
        }
    }

    return 1;
}