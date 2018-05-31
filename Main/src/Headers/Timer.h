#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

class Timer {
  private:
	using hrClock = std::chrono::high_resolution_clock;
	std::chrono::time_point<hrClock> start; 
  public:
  	/**
  	 * @brief default constructor for class
  	 * @details sets a timepoint as soon as the class is constructed
  	 */
  	Timer() : start{hrClock::now()} {}
  	/**
  	 * @brief resets the time point that was set by the constructor
  	 */
  	void reset() {start=hrClock::now();}
  	/**
  	 * @brief measures the time passed from the previously set time point
  	 */
  	double elapsed() const {return std::chrono::duration<double> (hrClock::now()-start).count();}
};

#endif