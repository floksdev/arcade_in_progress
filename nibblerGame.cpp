#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

struct SnakeSegment {
    int x, y;
    SnakeSegment(int _x, int _y) : x(_x), y(_y) {}
};

struct Obstacle {
    int x, y;
    Obstacle(int _x, int _y) : x(_x), y(_y) {}
};

enum class Direction { None, Up, Down, Left, Right };

class NibblerGame {
public:
    NibblerGame() : window(sf::VideoMode(800, 600), "Nibbler"), snake({ SnakeSegment(10, 10) }), direction(Direction::Right) {
        snakeGrow = false;
        initializeWalls();
        spawnFood();
        spawnObstacles();
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
    std::vector<sf::RectangleShape> walls;
    std::vector<Obstacle> obstacles;
    Direction direction;
    sf::RectangleShape food;
    bool snakeGrow;

    void initializeWalls() {
        sf::RectangleShape wallTop(sf::Vector2f(window.getSize().x, 10));
        wallTop.setPosition(0, 0);
        walls.push_back(wallTop);

        sf::RectangleShape wallBottom(sf::Vector2f(window.getSize().x, 10));
        wallBottom.setPosition(0, window.getSize().y - 10);
        walls.push_back(wallBottom);

        sf::RectangleShape wallLeft(sf::Vector2f(10, window.getSize().y));
        wallLeft.setPosition(0, 0);
        walls.push_back(wallLeft);

        sf::RectangleShape wallRight(sf::Vector2f(10, window.getSize().y));
        wallRight.setPosition(window.getSize().x - 10, 0);
        walls.push_back(wallRight);
    }

    void spawnObstacles() {
        for (int y = 50; y < window.getSize().y - 50; y += 30) {
            for (int x = 50; x < window.getSize().x - 50; x += 30) {
                if ((x >= 140 && x <= 190 && y >= 50 && y <= 150) ||
                    (x >= 250 && x <= 300 && y >= 200 && y <= 350) ||
                    (x >= 420 && x <= 520 && y >= 50 && y <= 150) ||
                    (x >= 520 && x <= 670 && y >= 200 && y <= 350)) {
                    continue;
                }
                obstacles.push_back(Obstacle(x, y));
            }
        }
    }

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
        SnakeSegment head = snake.front();
        SnakeSegment newHead = head;
        switch (direction) {
            case Direction::Up:
                newHead.y -= 10;
                break;
            case Direction::Down:
                newHead.y += 10;
                break;
            case Direction::Left:
                newHead.x -= 10;
                break;
            case Direction::Right:
                newHead.x += 10;
                break;
            default:
                break;
        }
        if (newHead.x < 0 || newHead.x >= window.getSize().x || newHead.y < 0 || newHead.y >= window.getSize().y) {
            window.close();
            return;
        }

        for (size_t i = 1; i < snake.size(); ++i) {
            if (newHead.x == snake[i].x && newHead.y == snake[i].y) {
                window.close();
                return;
            }
        }

        for (const auto& wall : walls) {
            if (newHead.x == wall.getPosition().x && newHead.y == wall.getPosition().y) {
                window.close();
                return;
            }
        }

        for (const auto& obs : obstacles) {
            if (newHead.x == obs.x && newHead.y == obs.y) {
                window.close();
                return;
            }
        }

        snake.insert(snake.begin(), newHead);

        if (snakeGrow) {
            snakeGrow = false;
        } else {
            snake.pop_back();
        }

        if (head.x == food.getPosition().x && head.y == food.getPosition().y) {
            snakeGrow = true;
            spawnFood();
        }
    }

    void render() {
        window.clear();

        for (const auto& wall : walls) {
            window.draw(wall);
        }

        for (const auto& obs : obstacles) {
            sf::RectangleShape obsShape(sf::Vector2f(10, 10));
            obsShape.setPosition(obs.x, obs.y);
            obsShape.setFillColor(sf::Color::Blue);
            window.draw(obsShape);
        }

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
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> disX(0, (window.getSize().x / 10) - 1);
        std::uniform_int_distribution<int> disY(0, (window.getSize().y / 10) - 1);

        int x = disX(gen) * 10;
        int y = disY(gen) * 10;

        food.setSize(sf::Vector2f(10, 10));
        food.setPosition(x, y);
        food.setFillColor(sf::Color::Red);
    }
};

int main() {
    NibblerGame game;
    game.run();
    return 0;
}
