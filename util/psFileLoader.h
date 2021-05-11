#ifndef PS_FILELOADER_IMPL
#define PS_FILELOADER_IMPL

#include <sstream>
#include <fstream>

#pragma warning(push)
#pragma warning(disable : 4996)

inline const char *readfile_s(const char *filepath) {

	std::ifstream input(filepath, std::ios::in);
	if (!input.is_open())
		return NULL;

	std::string line, result;
	while (!input.eof()) {
		std::getline(input, line);
		result.append(line + "\n");
	}

	input.close();
	const char *data = result.c_str();
	// Transit between functions.
	char *pass = (char *)malloc(strlen(data) + 1);
	if (!pass)
		return NULL;

	strcpy(pass, data);

	return pass;
}

#pragma warning(pop)

#endif