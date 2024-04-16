#include <SFML/Graphics.hpp>
#include "../abstract_graphical_lib.h"

class SFMLWrapper : public AbstractGraphicalLib {
private:
    sf::RenderWindow window;

public:
    void initialize() override {
        window.create(sf::VideoMode(800, 600), "SFML Window");
    }

    void render(int x, int y) override {
        window.clear(sf::Color::Black);
        
        sf::RectangleShape player(sf::Vector2f(50, 50));
        player.setFillColor(sf::Color::White);
        player.setPosition(x, y);
        window.draw(player);
        
        window.display();
    }

    bool isKeyPressed(int key) override {
        switch (key) {
            case sf::Keyboard::Up:
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            case sf::Keyboard::Down:
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            case sf::Keyboard::Left:
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            case sf::Keyboard::Right:
                return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            default:
                return false;
        }
    }
};

extern "C" AbstractGraphicalLib* create() {
    return new SFMLWrapper;
}

extern "C" void destroy(AbstractGraphicalLib* ptr) {
    delete ptr;
}
