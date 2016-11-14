#include "ExecCommand.hxx"

std::string exec(const char* cmd) {
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(
#ifdef WIN32
		_popen(cmd, "r"),
		_pclose
#else
		popen(cmd, "r"),
		pclose
#endif
	);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}
	return result;
}
