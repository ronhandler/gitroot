#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "board.h"

// Singleton class that represents the board.
// Use Game::getInstance() to get a reference to the single instance.
class Game
{
public:
	// The game loop.
	void gameloop(void) {
		init_ncurses();
		while (running) {
			drawboard();
			keyhandler();
		}
		end_ncurses();
	}
private:
	bool running;
	Board board;
	void drawboard(void) const {
		clear();
		for (int y=0; y<board.HEIGHT; ++y) {
			for (int x=0; x<board.WIDTH; ++x) {
				printw("%d ", board.get(x,y));
			}
			printw("\n");
		}
		refresh();
	}
	void keyhandler(void) {
		int c = getch();
		if (c == ERR)
			return;
		switch(c) {
			case 'q':
			case 'Q':
			case  27: // Escape key code.
				running=false;
				break;
		}
	}
	void init_ncurses() {
		// Init the ncurses screen.
		initscr();
		noecho();
		nodelay(stdscr, true);
		timeout(1000);
		clear();
		// Init some stuff.
		running=true;
	}
	void end_ncurses() {
		// End the ncurses screen.
		endwin();
	}
	Game() {}
	~Game() {}
public:
	static Game& getInstance() {
		// Instantiated on first use and guaranteed to be destroyed.
		static Game instance;
		return instance;
	}
private:
	// Don't implement the copy constructor or the assignment operator.
	Game(Game const &);
	void operator=(Game const &);
};

#endif
