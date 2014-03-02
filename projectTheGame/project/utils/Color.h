class Color;

#ifndef COLOR_H
#define COLOR_H

/**	@brief	A data structure for storing RGBA color. Supports operators.<br>
			For each color component, 0.0 is the lowest, 1.0 is the highest.
*/
class Color{
public:
	static bool calAlpha; //if false, the resultant alpha value of any operation is 1.0

	double r, g, b, a;
	Color();
	Color(double r, double g, double b);
	Color(double r, double g, double b, double a);

	//arithmetic operators
	Color operator+(const Color& c) const;
	Color operator-(const Color& c) const;
	Color operator*(const Color& c) const;
	Color operator*(const double& k) const;

	//assignment operators
	Color& operator+=(const Color& c);
	Color& operator-=(const Color& c);
	Color& operator*=(const Color& c);
	Color& operator*=(const double& k);

	//unary operators
	Color operator+() const;
	//Color operator-() const; //makes no sense.

	//comparison operators
	/// @return	if the value of this and c are close enough(5 decimal place precision), returns true, false else.
	bool operator==(const Color &c) const;
	bool operator!=(const Color &c) const;

	static void test();
};

::Color operator*(const double &a, const ::Color &b);

#endif