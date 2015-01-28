#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include <SDL2/SDL.h>

/* Reference based Singleton class. */
class TimeHandler {
public:
	static TimeHandler& getInstance() {
		static TimeHandler ins;
		return ins;
	}

	void initTimer() {
		delta = 0;
		now = SDL_GetTicks();
		previous = now;
	}
	void calcDelta() {
		now = SDL_GetTicks();
		delta = now - previous;
		previous = now;
	}
	Uint32 getDelta() {
		return delta;
	}

protected:
private:
	Uint32 delta;
	Uint32 now;
	Uint32 previous;
	TimeHandler() : delta(0),now(0),previous(0) { /* TODO: Add some code... */ }
	TimeHandler(TimeHandler const &);
	TimeHandler& operator=(TimeHandler const &);
};
#endif

