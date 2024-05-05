cmake_minimum_required(VERSION 3.26)


project(minesweeper
    VERSION 1.0
    DESCRIPTION "A small minesweeper game to get used to ncurses."
    LANGUAGES C)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

find_package(Curses REQUIRED)
find_library(PANEL_LIBRARY panel)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(minesweeper main.c game.c)
add_executable(ptest paneltest.c)
target_link_libraries(minesweeper ${CURSES_LIBRARIES})
target_link_libraries(ptest ${PANEL_LIBRARY} ${CURSES_LIBRARIES})