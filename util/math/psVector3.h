#ifndef PS_VECTOR3_IMPL
#define PS_VECTOR3_IMPL

#include <stdlib.h>
#include "psMath.h"

class psVector3 {

protected:

	float components[3];

public:

	psVector3();

	psVector3(float _x, float _y, float _z);

	psVector3(const psVector3 &ref);

	float x() {

		return components[0];
	}

	void x(float _x);

	float y() {

		return components[1];
	}

	void y(float _y);

	float z() {

		return components[2];
	}

	void z(float _z);

	const float x() const {

		return components[0];
	}

	const float y() const {

		return components[1];
	}

	const float z() const {

		return components[2];
	}

	const float *data() const {

		return components;
	}

	void set(float _x, float _y, float _z);

	void set(const psVector3 &ref);

	int compare(const psVector3 &ref) const;

	float length() const;

	float lengthSquared() const;

	float operator[](unsigned index);

	const float operator[](unsigned index) const;

	psVector3 &operator=(const psVector3 &ref);

	psVector3 operator+(const psVector3 &ref) const;

	psVector3 &operator+=(const psVector3 &ref);

	psVector3 operator-() const;

	psVector3 operator-(const psVector3 &ref) const;

	psVector3 &operator-=(const psVector3 &ref);

	psVector3 operator*(const psVector3 &ref) const;

	psVector3 &operator*=(const psVector3 &ref);

	psVector3 operator/(const psVector3 &ref) const;

	psVector3 &operator/=(const psVector3 &ref);

	// Not xor operator, scalar dot.
	float operator^(const psVector3 &ref) const;

	bool operator<=(const psVector3 &ref) const;

	bool operator>=(const psVector3 &ref) const;

	bool operator<(const psVector3 &ref) const;

	bool operator>(const psVector3 &ref) const;

	bool operator==(const psVector3 &ref) const;

	bool operator!=(const psVector3 &ref) const;

	void addX(float _x);

	void addY(float _y);

	void addZ(float _z);

	void add(float _x, float _y, float _z);

	void subX(float _x);

	void subY(float _y);

	void subZ(float _z);

	void sub(float _x, float _y, float _z);

	void normalize();

	psVector3 normalized() const;

};

inline psVector3::psVector3() {}

inline psVector3::psVector3(float _x, float _y, float _z) {

	set(_x, _y, _z);
}

inline psVector3::psVector3(const psVector3 &ref) {

	set(ref);
}

inline void psVector3::x(float _x) {

	components[0] = _x;
}

inline void psVector3::y(float _y) {

	components[1] = _y;
}

inline void psVector3::z(float _z) {

	components[2] = _z;
}

inline void psVector3::set(float _x, float _y, float _z) {

	x(_x);
	y(_y);
	z(_z);
}

inline void psVector3::set(const psVector3 &ref) {

	set(ref.x(), ref.y(), ref.z());
}

inline int psVector3::compare(const psVector3 &ref) const {

	int comp = 0;
	if (x() != ref.x())
		comp++;

	if (y() != ref.y())
		comp++;

	if (z() != ref.z())
		comp++;

	return comp;
}

inline float psVector3::length() const {
	return _fsqrt(lengthSquared());
}

inline float psVector3::lengthSquared() const {

	return fmaf(x(), x(), fma(y(), y(), z() * z()));
}

inline float psVector3::operator[](unsigned index) {

	return components[index > 2 ? 0 : index];
}

inline const float psVector3::operator[](unsigned index) const {

	return components[index > 2 ? 0 : index];
}

inline psVector3 &psVector3::operator=(const psVector3 &ref) {

	if (&ref != this)
		set(ref);

	return *this;
}

inline psVector3 psVector3::operator+(const psVector3 &ref) const {

	return psVector3(x() + ref.x(), y() + ref.y(), z() + ref.z());
}

inline psVector3 &psVector3::operator+=(const psVector3 &ref) {

	components[0] += ref.x();
	components[1] += ref.y();
	components[2] += ref.z();

	return *this;
}

inline psVector3 psVector3::operator-() const {

	return psVector3(-x(), -y(), -z());
}

inline psVector3 psVector3::operator-(const psVector3 &ref) const {

	return psVector3(x() - ref.x(), y() - ref.y(), z() - ref.z());
}

inline psVector3 &psVector3::operator-=(const psVector3 &ref) {

	components[0] -= ref.x();
	components[1] -= ref.y();
	components[2] -= ref.z();

	return *this;
}

inline psVector3 psVector3::operator*(const psVector3 &ref) const {

	return psVector3(x() * ref.x(), y() * ref.y(), z() * ref.z());
}

inline psVector3 &psVector3::operator*=(const psVector3 &ref) {

	components[0] *= ref.x();
	components[1] *= ref.y();
	components[2] *= ref.z();

	return *this;
}

inline psVector3 psVector3::operator/(const psVector3 &ref) const {

	return psVector3(x() / ref.x(), y() / ref.y(), z() / ref.z());
}

inline psVector3 &psVector3::operator/=(const psVector3 &ref) {

	components[0] /= ref.x();
	components[1] /= ref.y();
	components[2] /= ref.z();

	return *this;
}

inline float psVector3::operator^(const psVector3 &ref) const {

	return fmaf(x(), ref.x(), fmaf(y(), ref.y(), z() * ref.z()));
}

inline bool psVector3::operator<=(const psVector3 &ref) const {

	return x() <= ref.x() && y() <= ref.y() && z() <= ref.z();
}

inline bool psVector3::operator>=(const psVector3 &ref) const {

	return x() >= ref.x() && y() >= ref.y() && z() >= ref.z();
}

inline bool psVector3::operator<(const psVector3 &ref) const {

	return x() < ref.x() && y() < ref.y() && z() < ref.z();
}

inline bool psVector3::operator>(const psVector3 &ref) const {

	return x() > ref.x() && y() > ref.y() && z() > ref.z();
}

inline bool psVector3::operator==(const psVector3 &ref) const {

	return x() == ref.x() && y() == ref.y() && z() == ref.z();
}

inline bool psVector3::operator!=(const psVector3 &ref) const {

	return !(*this == ref);
}

inline void psVector3::addX(float _x) {

	components[0] += _x;
}

inline void psVector3::addY(float _y) {

	components[1] += _y;
}

inline void psVector3::addZ(float _z) {

	components[2] += _z;
}

inline void psVector3::add(float _x, float _y, float _z) {

	addX(_x);
	addY(_y);
	addZ(_z);
}

inline void psVector3::subX(float _x) {

	components[0] -= _x;
}

inline void psVector3::subY(float _y) {

	components[1] -= _y;
}

inline void psVector3::subZ(float _z) {

	components[2] -= _z;
}

inline void psVector3::sub(float _x, float _y, float _z) {

	subX(_x);
	subY(_y);
	subZ(_z);
}

inline void psVector3::normalize() {

	float f = _finvsqrt(lengthSquared());
	components[0] *= f;
	components[1] *= f;
	components[2] *= f;
}

inline psVector3 psVector3::normalized() const {

	psVector3 vec = psVector3(*this);
	vec.normalize();

	return vec;
}

#endif