#include <SFML/Graphics.hpp>
#include <vector>

//g++ -o snk snakeGame.cpp -lsfml-graphics -lsfml-window -lsfml-system

struct SnakeSegment {
    int x, y;
    SnakeSegment(int _x, int _y) : x(_x), y(_y) {}
};

enum class Direction { None, Up, Down, Left, Right };

class SnakeGame {
public:
    SnakeGame() : window(sf::VideoMode(800, 600), "Snake Game"), snake(1, SnakeSegment(10, 10)), direction(Direction::Right) {
        snake[0] = SnakeSegment(10, 10);
        spawnFood();
    }

    void run() {
        sf::Clock clock;
        float timer = 0.0f;
        float delay = 0.1f;

        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            timer += deltaTime;

            handleInput();
            if (timer >= delay) {
                update();
                timer = 0.0f;
            }

            render();
        }
    }

private:
    sf::RenderWindow window;
    std::vector<SnakeSegment> snake;
    Direction direction;
    sf::RectangleShape food;

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (direction != Direction::Down)
                            direction = Direction::Up;
                        break;
                    case sf::Keyboard::Down:
                        if (direction != Direction::Up)
                            direction = Direction::Down;
                        break;
                    case sf::Keyboard::Left:
                        if (direction != Direction::Right)
                            direction = Direction::Left;
                        break;
                    case sf::Keyboard::Right:
                        if (direction != Direction::Left)
                            direction = Direction::Right;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void update() {
        for (int i = snake.size() - 1; i > 0; --i) {
            snake[i].x = snake[i - 1].x;
            snake[i].y = snake[i - 1].y;
        }
        switch (direction) {
            case Direction::Up:
                snake[0].y -= 10;
                break;
            case Direction::Down:
                snake[0].y += 10;
                break;
            case Direction::Left:
                snake[0].x -= 10;
                break;
            case Direction::Right:
                snake[0].x += 10;
                break;
            default:
                break;
        }
        if (snake[0].x < 0 || snake[0].x >= window.getSize().x || snake[0].y < 0 || snake[0].y >= window.getSize().y) {
            window.close();
            return;
        }
        if (snake[0].x == food.getPosition().x && snake[0].y == food.getPosition().y) {
            snake.push_back(SnakeSegment(snake.back().x, snake.back().y));
            spawnFood();
        }
    }

    void render() {
        window.clear();
        for (const auto& segment : snake) {
            sf::RectangleShape shape(sf::Vector2f(10, 10));
            shape.setPosition(segment.x, segment.y);
            shape.setFillColor(sf::Color::Green);
            window.draw(shape);
        }
        window.draw(food);
        window.display();
    }

    void spawnFood() {
        int x = rand() % (window.getSize().x / 10) * 10;
        int y = rand() % (window.getSize().y / 10) * 10;
        food.setSize(sf::Vector2f(10, 10));
        food.setPosition(x, y);
        food.setFillColor(sf::Color::Red);
    }
};

int main() {
    SnakeGame game;
    game.run();
    return 0;
}
