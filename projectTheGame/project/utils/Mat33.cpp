#include "Mat33.h"
#include "Vec2.h"
#include <cassert>

#define EACH_ELEMENT(_mat)\
	for(int i=0;i<3;i++)\
		for(int j=0;j<3;j++)\
			_mat[i][j]

Mat33::Mat33(){
	EACH_ELEMENT(this->mat) = 0;
}

Mat33::Mat33(const double b[3][3]){
	EACH_ELEMENT(this->mat) = b[i][j];
}

Mat33 Mat33::operator+(const Mat33& b) const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = this->mat[i][j]+b.mat[i][j];
	return ret;
}

Mat33 Mat33::operator-(const Mat33& b) const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = this->mat[i][j]-b.mat[i][j];
	return ret;
}

/** Matrix multiplication: Mat33*Mat33 */
Mat33 Mat33::operator*(const Mat33& b) const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = this->mat[i][0]*b.mat[0][j]+this->mat[i][1]*b.mat[1][j]+this->mat[i][2]*b.mat[2][j];
	return ret;
}

/** Matrix multiplication: Mat33*Vec2, where Vec2 is first 'converted' to Vec3(x, y, 1) */
Vec2 Mat33::operator*(const Vec2& b) const{
	return Vec2( this->mat[0][0]*b[0]+this->mat[0][1]*b[1]+this->mat[0][2], this->mat[1][0]*b[0]+this->mat[1][1]*b[1]+this->mat[1][2] );
}

/** Scalar multiplication: Mat33*k. */
Mat33 Mat33::operator*(const double& k) const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = this->mat[i][j]*k;
	return ret;
}

const double* Mat33::operator[](const int& b) const{
	return this->mat[b];
}

double* Mat33::operator[](const int& b){
	return this->mat[b];
}

Mat33& Mat33::operator+=(const Mat33& b){
	*this = *this+b;
	return *this;
}

Mat33& Mat33::operator-=(const Mat33& b){
	*this = *this-b;
	return *this;
}

Mat33& Mat33::operator*=(const Mat33& b){
	*this = *this*b;
	return *this;
}

Mat33& Mat33::operator*=(const double& k){
	*this = *this*k;
	return *this;
}

Mat33 Mat33::operator+() const{
	return Mat33(this->mat);
}

Mat33 Mat33::operator-() const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = -this->mat[i][j];
	return ret;
}

/** Transpose */
Mat33 Mat33::operator~() const{
	Mat33 ret;
	EACH_ELEMENT(ret.mat) = this->mat[j][i];
	return ret;
}

double Mat33::det() const{
	const double (*m)[3] = this->mat;
	return	 m[0][0]*m[1][1]*m[2][2] +m[0][1]*m[1][2]*m[2][0] +m[0][2]*m[1][0]*m[2][1]
			-m[0][2]*m[1][1]*m[2][0] -m[0][1]*m[1][0]*m[2][2] -m[0][0]*m[1][2]*m[2][1];
}

bool Mat33::operator==(const Mat33 &b) const{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if( this->mat[i][j] != b.mat[i][j] )
				return false;
		}
	}
	return true;
}

bool Mat33::operator!=(const Mat33 &b) const{
	return !(*this == b);
}

/** Scalar operator k*Mat33 */
Mat33 operator*(const double &a, const Mat33 &b){
	return b*a;
}

void Mat33::test()
{
	double aMat[3][3] = {	0,1,2,
							3,4,5,
							6,7,8
						};
	double bMat[3][3] = {	9,8,7,
							6,5,4,
							3,2,1
						};
	Mat33 a(aMat), b(bMat);

	double sum[3][3] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
	assert( a+b == sum );

	double diff[3][3] = {9, 7, 5, 3, 1, -1, -3, -5, -7};
	assert( b-a == diff );

	double mult[3][3] = {	12, 9, 6,
							66, 54, 42,
							120, 99, 78
						};
	assert( a*b == mult );

	Vec2 vec(-20, 37);
	assert( a*vec == Vec2(39, 93) );

	double scaled[3][3] ={	-0.0, -1.5, -3.0,
							-4.5, -6.0, -7.5,
							-9.0, -10.5, -12.0
						};
	const double SCALAR = -1.5;
	assert( a*SCALAR == scaled );
	assert( SCALAR*a == scaled );

	assert( a[0][0] == 0 );
	assert( a[1][0] == 3 );
	assert( a[2][0] == 6 );
	assert( b[0][0] == 9 );
	assert( b[1][1] == 5 );
	assert( b[2][2] == 1 );

	a += b;
	assert( a == sum );

	/*double bMat[3][3] = {	9,8,7,
							6,5,4,
							3,2,1
						};*/
	double minus[3][3] = {	5, 6, 8,
							9, 1, 7,
							5, 2, 6
						};
	double result[3][3] = {	4, 2, -1,
							-3, 4, -3,
							-2, 0, -5
						};
	b -= minus;
	assert( b == result );

	a = aMat;
	b = bMat;
	a *= b;
	assert( a == mult );

	a = aMat;
	a *= SCALAR;
	assert( a == scaled );

	a = aMat;
	assert( +a == a );
	double negA[3][3] = {	-0,-1,-2,
							-3,-4,-5,
							-6,-7,-8
						};
	assert( -a == negA );
	double transA[3][3] = {	0,3,6,
							1,4,7,
							2,5,8
						};
	assert( ~a == transA );

	assert( a.det() == 0.0 );
	assert( b.det() == 0.0 ); //too small, got rounded to zero
	double detSrc[3][3] = {	12,9,6,
							66,54,42,
							120,99,3
						};
	assert( Mat33(detSrc).det() == -4050 );
	
	assert( a == aMat );
	assert( b == bMat );
	assert( a != bMat );
	assert( b != aMat );

}