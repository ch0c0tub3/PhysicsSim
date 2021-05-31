#ifndef PS_MATHLIB
#define PS_MATHLIB
#define _USE_MATH_DEFINES

#include <cstring>
#include <math.h>
#include <glm/glm.hpp>

inline float _frad(float x) {

	return x * (float)M_PI / 180.f;
}

inline float _fsqrt(float x) {

	int i;
	memcpy(&i, &x, sizeof(x));
	int u = 0x2035AD0C + (i >> 1);
	float f;
	memcpy(&f, &u, sizeof(f));

	return x / f + f * 0.25f;
}

inline float _finvsqrt(float x) {

	float y = x;
	long i = 0x5F3759DF - (*(long *)&y >> 1);
	y = *(float *)&i;

	return y * (1.5f - (x * 0.5f * y * y));
}

#endif