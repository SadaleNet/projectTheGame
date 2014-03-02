class TImer;

#ifndef TIMER_H
#define TIMER_H
#include "../GameObject.h"
#include <functional>

/**
	@brief	A class of delayed execution of function
	@note	To cancel the execution, call Timer::destroy()
*/
class Timer: public GameObject{
protected:
	std::function<void()> action; ///the function to be executed
	double timeout; ///the timeout to execute the function
	bool absolute; ///if true, timeout is absolute. Else, timeout is relative to the time that this object is added to the scene.

protected:
	/**	@brief	Calculates this->timeout if this->absolute is false<br>
				If this->timeout > this->getScene()->getSec(), the timer is destroyed **without** action() being executed.
	*/
	virtual void onSceneAdded() override;
	/// @brief	Check whether it is the time to execute the function. If so, execute it and destroy this object. Does nothing else.
	virtual void updateHook() override;

public:
	/**
		@brief	Create a timer that execute a function after/at timeout.<br>
				Timer is not activated until it is added to a scene.
		@param	action	The callback function to be executed.
		@param	timeout	timeout in seconds.
		@param	absolute	If true, the callback is executed at timeout, relative to the creation time of the scene.
				Otherwise(default), it is executed after timout, relative to the current time.
	*/
	Timer(std::function<void()> action, double timeout, bool absolute=false);

	/// @brief execute the action now and destroy the timer.
	void execute();

};

#endif