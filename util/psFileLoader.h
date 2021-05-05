#ifndef PS_FILELOADER_IMPL
#define PS_FILELOADER_IMPL

#include <vector>
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

inline const char **readfile_to_lines(const char *filepath, size_t *sizeptr) {

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

inline const char *trim_str(const char *str) {

	while (isspace((unsigned char)*str)) str++;
	if (!*str)
		return str;

	const char *end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	end++;
	size_t s = end - str;
	char *newptr = (char *)malloc(sizeof(char) * s);
	if (!newptr)
		return str;

	memcpy(newptr, str, s);
	newptr[end - str] = 0;

	return newptr;
}

#pragma warning(pop)

#endif