#include "Vec2.h"
#include <cassert>

Vec2::Vec2():x(0),y(0){}
Vec2::Vec2(double x, double y):x(x),y(y){}
Vec2 Vec2::operator+(const Vec2& b) const{ return Vec2(x+b.x, y+b.y); }
Vec2 Vec2::operator-(const Vec2& b) const{ return Vec2(x-b.x, y-b.y); }
double Vec2::operator*(const Vec2& b) const{ return x*b.x+y*b.y; }
Vec2 Vec2::operator*(const double& k) const{ return Vec2(k*x, k*y); }

double Vec2::operator[](const int& i) const{ assert(i==0||i==1); return (i==0?x:y); }

Vec2& Vec2::operator+=(const Vec2& b){ return (*this = *this+b); }
Vec2& Vec2::operator-=(const Vec2& b){ return (*this = *this-b); }
Vec2& Vec2::operator*=(const double& k){ return (*this = *this*k); }

Vec2 Vec2::operator+() const{ return *this; }
Vec2 Vec2::operator-() const{ return Vec2(-x, -y); }

bool Vec2::operator==(const Vec2 &b) const{ return (x==b.x && y==b.y); }
bool Vec2::operator!=(const Vec2 &b) const{ return !(*this==b); }

Vec2 operator*(const double &a, const Vec2 &b){ return b*a; }

void Vec2::test()
{
	Vec2 a(10, 20), b(30, 40);

	//arithematic operators
	assert( a+b == Vec2(40, 60) );
	assert( a-b == Vec2(-20, -20) );
	assert( a*b == 1100 );
	assert( a*-7 == Vec2(-70, -140) );
	assert( -7*a == Vec2(-70, -140) );

	assert( a[0] == 10 );
	assert( a[1] == 20 );
	assert( b[0] == 30 );
	assert( b[1] == 40 );

	//assignment operators
	a += b;
	assert( a.x == 40 );
	assert( a.y == 60 );

	b -= Vec2(20, -30);
	assert( b.x == 10 );
	assert( b.y == 70 );

	a *= 0.1;
	assert( a.x == 4 );
	assert( a.y == 6 );

	//unary operators
	assert( +a == Vec2(4, 6) );
	assert( -a == Vec2(-4, -6) );

	//comparison operators
	assert( a == Vec2(4, 6) );
	assert(a != b);

}