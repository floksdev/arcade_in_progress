#include <ncurses.h>
#include "../abstract_graphical_lib.h"
#include "../../game_logic/player.h"
#include <iostream>

class NCursesWrapper : public AbstractGraphicalLib {
private:
    Player player;
    bool needsRefresh;

public:
    NCursesWrapper() : player(0, 0), needsRefresh(true) {}

    void initialize() override {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        timeout(0);
        curs_set(0);
    }

    void render(int x, int y) override {
        if (needsRefresh) {
            clear();
            mvprintw(player.getY(), player.getX(), "X");
            refresh();
            needsRefresh = false;
        }
    }

    bool isKeyPressed(int key) override {
        int ch;
        while ((ch = getch()) != ERR) {
            switch (ch) {
                case KEY_UP:
                    player.move(0, -1);
                    needsRefresh = true;
                    break;
                case KEY_DOWN:
                    player.move(0, 1);
                    needsRefresh = true;
                    break;
                case KEY_LEFT:
                    player.move(-1, 0);
                    needsRefresh = true;
                    break;
                case KEY_RIGHT:
                    player.move(1, 0);
                    needsRefresh = true;
                    break;
                default:
                    break;
            }
        }
        return false;
    }


    void flagRefresh() {
        needsRefresh = true;
    }
};

extern "C" AbstractGraphicalLib* create() {
    return new NCursesWrapper;
}

extern "C" void destroy(AbstractGraphicalLib* ptr) {
    delete ptr;
}
