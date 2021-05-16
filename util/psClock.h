#ifndef PS_CLOCK_IMPL
#define PS_CLOCK_IMPL

#include <chrono>

class psClock {

protected:

	double hook;

public:

	psClock() {
		
		setup();
	}

	void setup();

	double getSystemTime() const;

	float getSequence();

	double getHook() const {

		return hook;
	}

};

inline void psClock::setup() {

	hook = getSystemTime();
}

inline double psClock::getSystemTime() const {
	
	using namespace std::chrono;
	system_clock::duration s = system_clock::now().time_since_epoch();

	return s.count() * 1e-7;
}

inline float psClock::getSequence() {

	double t = getSystemTime();
	float e = (float)(t - hook);
	hook = t;

	return e;
}

#endif