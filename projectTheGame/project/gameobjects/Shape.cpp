#include "Shape.h"

Polygon& Polygon::addPoint(const Vec2& p){
	points.push_back(p);
	return *this;
}

bool Polygon::isCollide(const GameObject& b) const{
	//TODO: stub
	//Use owner->getGTrans(); and b->getGTrans();
	return false;
}

bool Polygon::isCollide(const Vec2& b) const{
	//TODO: stub
	//Use owner->getGTrans(); and b->getGTrans();
	return false;
}

//forwards to points
std::vector<Vec2>::iterator Polygon::begin(){
	return this->points.begin();
}
std::vector<Vec2>::iterator Polygon::end(){
	return this->points.end();
}