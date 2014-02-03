/** A class for vector with 2 components.
For the ease of implementation, this class is not generalized to have arbitrary dimensional components. I believe that it is also easier to use as you can access member with vec2.x and vec2.y
*/

class Vec2;
#ifndef VEC2_H
#define VEC2_H
class Vec2{
public:
	double x, y;
	Vec2();
	Vec2(double x, double y);

	//arithmetic operators
	Vec2 operator+(const Vec2& b) const;
	Vec2 operator-(const Vec2& b) const;
	/** Dot product */
	double operator*(const Vec2& b) const;
	/** Scalar operator v*k */
	Vec2 operator*(const double& k) const;

	//access operator
	double operator[](const int& i) const;

	//assignment operators
	Vec2& operator+=(const Vec2& b);
	Vec2& operator-=(const Vec2& b);
	Vec2& operator*=(const double& k);

	//unary operators
	Vec2 operator+() const;
	Vec2 operator-() const;

	//comparison operators
	bool operator==(const Vec2 &b) const;
	bool operator!=(const Vec2 &b) const;

	static void test();
};
/** Scalar operator k*v */
Vec2 operator*(const double &a, const Vec2 &b);
#endif