#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <functional>

class FuncSetter {
public:
	template < typename Functor, typename ... Args >
	void set (std::string name, Functor functor, Args ... a) {
		auto func =
			[&, a...]()
			{
				return functor(a...);
			};

		std::cout << func();
	}
};

#endif

