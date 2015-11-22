#ifndef RANDOM_H
#define RANDOM_H

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

/* This makes generating numbers easier. Call seed() to set a seed number
 * and then call roll() to generate a number between 1 and 6.
 * The class is reference based Singleton, so you'll first have to get its
 * instance by calling the public member function getInstance(). */
class Rand {
public:
	static Rand& getInstance() { static Rand ins; return ins; }

	/* This is a Mersenne-Twister random number generator implementation.
	 * Speed and uniformity are pretty good. */
	typedef boost::mt19937 RNGType;

	/* Rolls the die. Will return output in range 1..6 */
	int roll() { return (*six)(*rng); }

	/* Seeds the random number generator. */
	void seed(int n) {
		if (rng!=NULL) delete rng;
		if (six!=NULL) delete six;
		rng = new RNGType(n);
		six = new boost::random::uniform_int_distribution<> (1,6);
	}

private:
	RNGType *rng;
	boost::random::uniform_int_distribution<> *six;
	Rand() : rng(NULL), six(NULL) { seed(0); }
	Rand(Rand const &);	/* Used to disallow singleton copy constructor. */
	Rand& operator=(Rand const &); /* Disallow singleton = operator. */
};


/* This class is intended to hold 2 dice. */
class Dice {
private:
	int d1, d2;
public:
	Dice() {
		d1 = Rand::getInstance().roll();
		d2 = Rand::getInstance().roll();
		/* If d1 is larger, swap d1 and d2. Makes it pretty. */
		if (d1 > d2) {
			int n = d1;
			d1 = d2;
			d2 = n;
		}
	}
	int get1() { return d1; }
	int get2() { return d2; }
	int getSum() { return d1+d2; }
	bool isDouble() { return (d1 == d2) ? true : false; }
};


#endif

