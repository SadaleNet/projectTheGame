#include "Color.h"
#include <cassert>

bool Color::calAlpha = false;

Color::Color():r(1.0),g(1.0),b(1.0),a(1.0){}
Color::Color(double r, double g, double b):r(r),g(g),b(b),a(1.0){}
Color::Color(double r, double g, double b, double a):r(r),g(g),b(b),a(a){}

//arithmetic operators
Color Color::operator+(const Color& c) const{ return Color(r+c.r, g+c.g, b+c.b, calAlpha?a+c.a:1.0); }
Color Color::operator-(const Color& c) const{ return Color(r-c.r, g-c.g, b-c.b, calAlpha?a-c.a:1.0); }
Color Color::operator*(const Color& c) const{ return Color(r*c.r, g*c.g, b*c.b, calAlpha?a*c.a:1.0); }
Color Color::operator*(const double& k) const{ return Color(r*k, g*k, b*k, calAlpha?a*k:1.0); }

//assignment operators
Color& Color::operator+=(const Color& c){ return (*this = *this + c); }
Color& Color::operator-=(const Color& c){ return (*this = *this - c); }
Color& Color::operator*=(const Color& c){ return (*this = *this * c); }
Color& Color::operator*=(const double& k){ return (*this = *this * k); }

//unary operators
Color Color::operator+() const{ return *this; }

//comparison operators
bool Color::operator==(const Color &c) const{
	#define COMPARE(_colorComponent) (int(_colorComponent*10000+0.5) == int(c.##_colorComponent*10000+0.5)) //Reduce round off error.
	return ( COMPARE(r) && COMPARE(g) && COMPARE(b) && COMPARE(a) );
}
bool Color::operator!=(const Color &c) const{ return !(*this==c); }

Color operator*(const double &a, const Color &b){ return b*a; }

void Color::test(){
	//arithematic operators test
	calAlpha = false;
	Color a(0.3, 0.4, 0.5, 1.0), b(0.2, 0.4, 0.3, 1.0);

	assert( a+b == Color(0.5, 0.8, 0.8, 1.0) );
	assert( a-b == Color(0.1, 0.0, 0.2, 1.0) );
	assert( a*b == Color(0.06, 0.16, 0.15, 1.0) );
	assert( a*2 == Color(0.6, 0.8, 1.0, 1.0) );
	assert( 2*a == Color(0.6, 0.8, 1.0, 1.0) );

	calAlpha = true;
	assert( a+b == Color(0.5, 0.8, 0.8, 2.0) );
	assert( a-b == Color(0.1, 0.0, 0.2, 0.0) );
	assert( a*b == Color(0.06, 0.16, 0.15, 1.0) );
	assert( 2*a == Color(0.6, 0.8, 1.0, 2.0) );

	calAlpha = false; //set it back to the deault value

	//assignment operators test
	a += b;
	assert( a == Color(0.5, 0.8, 0.8, 1.0) );
	a -= b;
	assert( a == Color(0.3, 0.4, 0.5, 1.0) );
	a *= b;
	assert( a == Color(0.06, 0.16, 0.15, 1.0) );
	a *= 5;
	assert( a == Color(0.3, 0.8, 0.75, 1.0) );

	//unary operator test
	assert( +a == Color(0.3, 0.8, 0.75, 1.0) );

	//comparison operators test
	assert( a == a );
	assert( a != b );

}