#ifndef PATH_H
#define PATH_H

#include <string>
#include <iostream>
#include <sys/auxv.h>

namespace path {
	std::string getBaseDir(void);
}

#endif
