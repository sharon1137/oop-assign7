#ifndef UNIT_H
#define UNIT_H
struct Vec2{
    int e1;
    int e2;
    int& x(){ return e1;}
    int& y(){ return e2;}
    int& width(){return e1;}
    int& height(){return e2;}
	int x() const { return e1; }
    int y() const { return e2; }
	void setX(int _e1) { e1 = _e1; } 
    void setY(int _e2) { e2 = _e2; }
};

using Position = Vec2;

enum Color {BLACK=0, RED, GREEN, YELLOW, BLUE, PINK, CYAN, WHITE, NOCHANGE};

#endif
