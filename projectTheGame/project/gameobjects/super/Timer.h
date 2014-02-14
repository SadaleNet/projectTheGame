class TImer;

#ifndef TIMER_H
#define TIMER_H
#include "../GameObject.h"
#include <functional>

/*
	To cancel the execution, you can call Timer::destroy()
*/
class Timer: public GameObject{
protected:
	std::function<void()> action;
	double timeout;
	bool absolute;

protected:
	/**	@brief	Calculates this->timeout if this->absolute is false
				If this->timeout > this->getScene()->getSec(), the timer is destroyed **without** action() being executed.
	*/
	virtual void onSceneAdded() override;
	virtual void updateHook() override;
	virtual void render() const override;

public:
	/**
		@brief	Create a timer that execute a function after/at timeout.
				Timer is not activated until it is added to a scene.
		@param	The callback function to be executed.
		@param	timeout in seconds.
		@param	If true, the callback is executed at timeout, relative to the creation time of the scene.
				Otherwise(default), it is executed after timout, relative to the current time.
	*/
	Timer(std::function<void()> action, double timeout, bool absolute=false);

	/// @brief execute the action now and destroy the timer.
	void execute();

};

#endif