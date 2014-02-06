#ifndef COLOR_H
#define COLOR_H

class Color{
public:
	double r, g, b, a;
	Color():r(1.0),g(1.0),b(1.0),a(1.0){}
	Color(double r, double g, double b, double a):r(r),g(g),b(b),a(a){}
};

#endif