#ifndef PATH_HANDLER_H
#define PATH_HANDLER_H

#include <iostream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

/* Reference based Singleton class. */
class PathHandler {
public:
	static PathHandler& getInstance() {
		static PathHandler ins;
		return ins;
	}
	/* Sets executablePath according to argv[0]. This is not fully tested. */
	void Init(int argc, char **argv) {
		executablePath = system_complete(argv[0]).parent_path();
	}
	std::string getCurrentPath() {
		return executablePath.generic_string();
	}
	std::string getResourcePath() {
		path p = executablePath;
		p = p.parent_path() / "/res";
		return p.generic_string();

	}

protected:
	path executablePath;
private:
	PathHandler() {
		/* This is a workaround. If Init() will not be called, use the
		 * current working dir instead of the executable's directory. */
		executablePath = current_path();
	}
	PathHandler(PathHandler const &);
	PathHandler& operator=(PathHandler const &);
};
#endif

