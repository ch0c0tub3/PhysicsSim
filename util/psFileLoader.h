#ifndef PS_FILELOADER_IMPL
#define PS_FILELOADER_IMPL

#include <sstream>
#include <fstream>


#define VECTOR_CAPACITY 4


#pragma warning(push)
#pragma warning(disable : 4996)

struct s_vector {

	size_t capacity;
	size_t size;
	const char **data;
};

inline struct s_vector *new_vector(void) {

	struct s_vector *vector = (struct s_vector *)malloc(sizeof(struct s_vector));
	if (!vector)
		return NULL;
	
	vector->capacity = VECTOR_CAPACITY;
	vector->size = 0;
	vector->data = (const char **)calloc(VECTOR_CAPACITY, sizeof(const char *));
	if (!vector->data) {
		free(vector);

		return NULL;
	}

	return vector;
}

inline int vector_push(struct s_vector *vector, const char *elm) {

	if (!vector)
		return 1;

	if (vector->size >= vector->capacity) {
		void *data = realloc(vector->data, vector->capacity << 1);
		if (!data)
			return 1;
		vector->capacity <<= 1;
		vector->data = (const char **)data;
	}


	vector->data[vector->size++] = elm;

	return 0;
}

inline const char *vector_pop(struct s_vector *vector) {

	if (!vector->size)
		return NULL;

	return vector->data[--vector->size];
}

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

inline struct s_vector *readfile_to_lines(const char *filepath) {

	std::ifstream input(filepath, std::ios::in);
	if (!input.is_open())
		return NULL;

	struct s_vector *lines = new_vector();
	std::string line;
	while (!input.eof()) {
		std::getline(input, line);
		const char *data = line.c_str();
		// Transit between functions.
		char *pass = (char *)malloc(strlen(data) + 1);
		if (!pass)
			return NULL;

		strcpy(pass, data);
		vector_push(lines, pass);
	}

	input.close();

	return lines;
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