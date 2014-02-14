#include "../GameObject.h"
#include <functional>

double linear(double input){
	return input;
}

/**
	If an object is destroyed, remember to delete ALL associated Animator object
		because Animator is holding a reference to the target variable.
*/
template <class TargetType>
class Animator: public GameObject{
protected:
	TargetType& target;
	TargetType begin, end;
	double beginTime, endTime;
	std::function<double(double)> interpolate;
	bool absoluteTiming;

protected:
	/**	@brief	Calculates this->begin and this->end if this->absolute is false */
	virtual void onSceneAdded() override{
		if( !this->absoluteTiming ){
			this->beginTime += this->getScene()->getSec();
			this->endTime += this->getScene()->getSec();
		}
	}

	virtual void updateHook() override{
		double time = this->getScene()->getSec();
		if( time >= this->endTime ){
			this->target = this->end;
			this->destroy();
		}else if( time >= this->beginTime ){
			this->target = this->interpolate( (time-this->beginTime)/(this->endTime-this->beginTime) ) //interpolates from 0.0 to 1.0
						*(this->end-this->begin)+this->begin; //calculate the final value
		}
	}

	virtual void render() const override{
	}

public:
	Animator(TargetType& target, double beginTime, TargetType begin, double endTime, TargetType end, std::function<double(double)> interpolate=linear,  bool absoluteTiming=false):
		GameObject(Vec2(0,0), Vec2(0,0)),
		target(target),
		beginTime(beginTime),
		begin(begin),
		endTime(endTime),
		end(end),
		interpolate(interpolate),
		absoluteTiming(absoluteTiming){
	}
	Animator(TargetType& target, double beginTime, TargetType begin, double endTime, TargetType end, bool absoluteTiming):
		GameObject(Vec2(0,0), Vec2(0,0)),
		target(target),
		beginTime(beginTime),
		begin(begin),
		endTime(endTime),
		end(end),
		interpolate(linear),
		absoluteTiming(absoluteTiming){
	}
	Animator(TargetType& target, double endTime, TargetType end):
		GameObject(Vec2(0,0), Vec2(0,0)),
		target(target),
		beginTime(0.0),
		begin(target),
		endTime(endTime),
		end(end),
		interpolate(linear),
		absoluteTiming(false){
	}

};
