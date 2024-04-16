#include "player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

class Game {
private:
    Player player;

public:
    Game() : player(0, 0) {}

    void handleInput(bool keys[]) {
        int dx = 0, dy = 0;
        if (keys[sf::Keyboard::Up]) dy -= 5;
        if (keys[sf::Keyboard::Down]) dy += 5;
        if (keys[sf::Keyboard::Left]) dx -= 5;
        if (keys[sf::Keyboard::Right]) dx += 5;
        player.move(dx, dy);
    }

    int getPlayerX() const {
        return player.getX();
    }

    int getPlayerY() const {
        return player.getY();
    }
};
