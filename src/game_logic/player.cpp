class Player {
private:
    int x;
    int y;

public:
    Player(int initialX, int initialY) : x(initialX), y(initialY) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};
