#ifndef ABSTRACT_GRAPHICAL_LIB_H
#define ABSTRACT_GRAPHICAL_LIB_H

class AbstractGraphicalLib {
public:
    virtual ~AbstractGraphicalLib() {}
    virtual void initialize() = 0;
    virtual void render(int x, int y) = 0;
    virtual bool isKeyPressed(int key) = 0;
};

#endif // ABSTRACT_GRAPHICAL_LIB_H
