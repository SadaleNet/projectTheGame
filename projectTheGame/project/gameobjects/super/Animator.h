#include "../GameObject.h"
#include <functional>

double linear(double input){
	return input;
}

/**
	@brief	A class for animating object with interpolation.
	@note	Before an object is destroyed, remember to delete ALL associated Animator object because
			Animator is holding a reference to the target variable.
*/
template <class TargetType>
class Animator: public GameObject{
protected:
	TargetType& target; ///The target variable to be animated
	TargetType begin, end; ///Two values for interpolation
	double beginTime, endTime; ///Absolute begin and end time
	std::function<double(double)> interpolate; //The interpolate function
	bool absoluteTiming;

protected:
	/**	@brief	Calculates this->begin and this->end if this->absolute is false */
	virtual void onSceneAdded() override{
		if( !this->absoluteTiming ){
			this->beginTime += this->getScene()->getSec();
			this->endTime += this->getScene()->getSec();
		}
	}
	/** @brief	Update the target value to a new interpolated value. Then destroy itself if animation time is ended. */
	virtual void updateHook() override{
		double time = this->getScene()->getSec();

		if( time >= this->endTime ){
			this->target = this->interpolate(1.0)*(this->end-this->begin)+this->begin;
			this->destroy();
		}else if( time >= this->beginTime ){
			double interpolated = this->interpolate( (time-this->beginTime)/(this->endTime-this->beginTime) ); //interpolates from 0.0 to 1.0;
			this->target = interpolated*(this->end-this->begin)+this->begin; //calculate the final value
		}
	}

public:
	/**	@param	target	target variable to be animated
		@param	beginTime	time to begin animation
		@param	begin		initial valueof the animation 
		@param	endTime		time to stop animation
		@param	end			final value for the animation
		@param	interpolate	interpolation function. The function accepts a double(value: 0.0 to 1.0)
							showing the process of animation and return another double
		@param	absoluteTiming	If true, beginTime and endTime are absolute.
								Else, beginTime and endTime are relative to the time that the animation object is added to the scene.
	*/
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
	///@brief	Shortcut ctor equivalent to Animator(target, beginTime, begin, endTime, end, linear, absoluteTiming)
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
	///@brief	Shortcut ctor equivalent to Animator(target, 0.0, target, endTime, end, linear, false)
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
