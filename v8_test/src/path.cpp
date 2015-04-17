#include "path.h"
namespace path {
	std::string getBaseDir(void)
	{
		std::string path = reinterpret_cast<char *>(getauxval(AT_EXECFN));
		unsigned found = path.find_last_of("/\\");
		std::string BaseDir = path.substr(0,found);
		return BaseDir;
	}
}
