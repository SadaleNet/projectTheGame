/** A class for 3x3 matrix.
For the ease of implementation, this class is ONLY for 3x3 matrix. NOT for 2x3, 3x2, 4x4 etc.
*/
class Mat33;
#ifndef MAT33_H
#define MAT33_H
#include "Vec2.h"

class Mat33{
public:
	double mat[3][3];
	Mat33();
	Mat33(const double[3][3]);

	//arithmetic operators
	Mat33 operator+(const Mat33& b) const;
	Mat33 operator-(const Mat33& b) const;
	/** Matrix multiplication: Mat33*Mat33 */
	Mat33 operator*(const Mat33& b) const;
	/** Matrix multiplication: Mat33*Vec2. Before multiplication, the Vec2 is converted to a vector with three components, and that the last component is 1. */
	Vec2 operator*(const Vec2& b) const;
	/** Scalar multiplication Mat33*k */
	Mat33 operator*(const double& k) const;

	//access operators
	const double* operator[](const int& b) const;
	double* operator[](const int& b);

	//assignment operators
	Mat33& operator+=(const Mat33& b);
	Mat33& operator-=(const Mat33& b);
	Mat33& operator*=(const Mat33& b);
	Mat33& operator*=(const double& k);

	//unary operators
	Mat33 operator+() const;
	Mat33 operator-() const;
	/** Transpose */
	Mat33 operator~() const;

	/** Calculates determinant */
	double det() const;

	//comparison operators
	bool operator==(const Mat33 &b) const;
	bool operator!=(const Mat33 &b) const;

	static void test();
};
/** Scalar operator k*Mat33 */
Mat33 operator*(const double &a, const Mat33 &b);
#endif