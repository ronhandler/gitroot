#include "main.h"

int main(int argc, char* argv[]) {

	FuncSetter f;
	f.set("my name",
		[=](int i) -> int
		{
			std::cout << "hello world " << i << std::endl; 
			return i*2;
		}
		,
		50
	);

	return 0;
}

