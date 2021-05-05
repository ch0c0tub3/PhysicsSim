#ifndef PS_MATRIX4_IMPL
#define PS_MATRIX4_IMPL

#include "psVector3.h"
#include "psMath.h"

// Good luck searching in this garbage of functions.
class psMatrix4 {

protected:

	float components[16];

public:

	psMatrix4();

	psMatrix4(float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33);

	psMatrix4(const psMatrix4 &ref);

	static psMatrix4 _perspective(float fov, float aspect, float near, float far) {

		float t = tanf(fov * 0.5f);
		return psMatrix4(1.f / (t * aspect), 0.f, 0.f, 0.f,
			0.f, 1.f / t, 0.f, 0.f,
			0.f, 0.f, (far + near) / (near - far), -1.f,
			0.f, 0.f, far * 2.f * near / (near - far), 0.f);
	}

	float m00() {

		return components[0];
	}

	void m00(float _m00);

	float m01() {

		return components[1];
	}

	void m01(float _m01);

	float m02() {

		return components[2];
	}

	void m02(float _m02);

	float m03() {

		return components[3];
	}

	void m03(float _m03);

	float m10() {

		return components[4];
	}

	void m10(float _m10);

	float m11() {

		return components[5];
	}

	void m11(float _m11);

	float m12() {

		return components[6];
	}

	void m12(float _m12);

	float m13() {

		return components[7];
	}

	void m13(float _m13);

	float m20() {

		return components[8];
	}

	void m20(float _m20);

	float m21() {

		return components[9];
	}

	void m21(float _m21);

	float m22() {

		return components[10];
	}

	void m22(float _m22);

	float m23() {

		return components[11];
	}

	void m23(float _m23);

	float m30() {

		return components[12];
	}

	void m30(float _m30);

	float m31() {

		return components[13];
	}

	void m31(float _m31);

	float m32() {

		return components[14];
	}

	void m32(float _m32);

	float m33() {

		return components[15];
	}

	void m33(float _m33);

	const float m00() const {

		return components[0];
	}

	const float m01() const {

		return components[1];
	}

	const float m02() const {

		return components[2];
	}

	const float m03() const {

		return components[3];
	}

	const float m10() const {

		return components[4];
	}

	const float m11() const {

		return components[5];
	}

	const float m12() const {

		return components[6];
	}

	const float m13() const {

		return components[7];
	}

	const float m20() const {

		return components[8];
	}

	const float m21() const {

		return components[9];
	}

	const float m22() const {

		return components[10];
	}

	const float m23() const {

		return components[11];
	}

	const float m30() const {

		return components[12];
	}

	const float m31() const {

		return components[13];
	}

	const float m32() const {

		return components[14];
	}

	const float m33() const {

		return components[15];
	}

	const float *data() const {

		return components;
	}

	void set(float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33);

	void set(const psMatrix4 &ref);

	float operator[](unsigned index);

	const float operator[](unsigned index) const;

	psMatrix4 &operator=(const psMatrix4 &ref);

	psMatrix4 operator+(const psMatrix4 &ref) const;

	psMatrix4 &operator+=(const psMatrix4 &ref);

	psMatrix4 operator-() const;

	psMatrix4 operator-(const psMatrix4 &ref) const;

	psMatrix4 &operator-=(const psMatrix4 &ref);

	psMatrix4 operator*(float scalar) const;

	psMatrix4 &operator*=(float scalar);

	psMatrix4 operator*(const psMatrix4 &ref) const;

	psMatrix4 &operator*=(const psMatrix4 &ref);

	bool operator==(const psMatrix4 &ref) const;

	bool operator!=(const psMatrix4 &ref) const;

	void identity();

	void translate(float _x, float _y, float _z);

	void translate(const psVector3 &ref);

	// Angle is in radians.
	void rotate(float angle, float _x, float _y, float _z);

	void rotateX(float angle);

	void rotateY(float angle);

	void rotateZ(float angle);

	void rotate(float _x, float _y, float _z);

};

inline psMatrix4::psMatrix4() {}

inline psMatrix4::psMatrix4(float _m00, float _m01, float _m02, float _m03,
	float _m10, float _m11, float _m12, float _m13,
	float _m20, float _m21, float _m22, float _m23,
	float _m30, float _m31, float _m32, float _m33) {

	set(_m00, _m01, _m02, _m03,
		_m10, _m11, _m12, _m13,
		_m20, _m21, _m22, _m23,
		_m30, _m31, _m32, _m33);
}

inline psMatrix4::psMatrix4(const psMatrix4 &ref) {

	set(ref);
}

inline void psMatrix4::m00(float _m00) {

	components[0] = _m00;
}

inline void psMatrix4::m01(float _m01) {

	components[1] = _m01;
}

inline void psMatrix4::m02(float _m02) {

	components[2] = _m02;
}

inline void psMatrix4::m03(float _m03) {

	components[3] = _m03;
}

inline void psMatrix4::m10(float _m10) {

	components[4] = _m10;
}

inline void psMatrix4::m11(float _m11) {

	components[5] = _m11;
}

inline void psMatrix4::m12(float _m12) {

	components[6] = _m12;
}

inline void psMatrix4::m13(float _m13) {

	components[7] = _m13;
}

inline void psMatrix4::m20(float _m20) {

	components[8] = _m20;
}

inline void psMatrix4::m21(float _m21) {

	components[9] = _m21;
}

inline void psMatrix4::m22(float _m22) {

	components[10] = _m22;
}

inline void psMatrix4::m23(float _m23) {

	components[11] = _m23;
}

inline void psMatrix4::m30(float _m30) {

	components[12] = _m30;
}

inline void psMatrix4::m31(float _m31) {

	components[13] = _m31;
}

inline void psMatrix4::m32(float _m32) {

	components[14] = _m32;
}

inline void psMatrix4::m33(float _m33) {

	components[15] = _m33;
}

inline void psMatrix4::set(float _m00, float _m01, float _m02, float _m03,
	float _m10, float _m11, float _m12, float _m13,
	float _m20, float _m21, float _m22, float _m23,
	float _m30, float _m31, float _m32, float _m33) {

	m00(_m00);
	m01(_m01);
	m02(_m02);
	m03(_m03);
	m00(_m00);
	m01(_m01);
	m02(_m02);
	m03(_m03);
	m00(_m00);
	m01(_m01);
	m02(_m02);
	m03(_m03);
	m00(_m00);
	m01(_m01);
	m02(_m02);
	m03(_m03);
}

// I don't feel right about iterating over and over.
// TODO: don't be lazy.
inline void psMatrix4::set(const psMatrix4 &ref) {

	float *ptr0 = components;
	const float *ptr1 = ref.data();
	while ((*ptr0++ = *ptr1++));
}

inline float psMatrix4::operator[](unsigned index) {

	return components[index > 15 ? 0 : index];
}

inline const float psMatrix4::operator[](unsigned index) const {

	return components[index > 15 ? 0 : index];
}

inline psMatrix4 &psMatrix4::operator=(const psMatrix4 &ref) {

	if (&ref != this)
		set(ref);

	return *this;
}

inline psMatrix4 psMatrix4::operator+(const psMatrix4 &ref) const {

	return psMatrix4(m00() + ref.m00(), m01() + ref.m01(), m02() + ref.m02(), m03() + ref.m03(),
		m10() + ref.m10(), m11() + ref.m11(), m12() + ref.m12(), m13() + ref.m13(),
		m20() + ref.m20(), m21() + ref.m21(), m22() + ref.m22(), m23() + ref.m23(),
		m30() + ref.m30(), m31() + ref.m31(), m32() + ref.m32(), m33() + ref.m33());
}

inline psMatrix4 &psMatrix4::operator+=(const psMatrix4 &ref) {

	components[0] += ref.m00();
	components[1] += ref.m01();
	components[2] += ref.m02();
	components[3] += ref.m03();
	components[4] += ref.m10();
	components[5] += ref.m11();
	components[6] += ref.m12();
	components[7] += ref.m13();
	components[8] += ref.m20();
	components[9] += ref.m21();
	components[10] += ref.m22();
	components[11] += ref.m23();
	components[12] += ref.m30();
	components[13] += ref.m31();
	components[14] += ref.m32();
	components[15] += ref.m33();

	return *this;
}

inline psMatrix4 psMatrix4::operator-() const {

	float a = m00() * m11() - m01() * m10();
	float b = m00() * m12() - m02() * m10();
	float c = m00() * m13() - m03() * m10();
	float d = m01() * m12() - m02() * m11();
	float e = m01() * m13() - m03() * m11();
	float f = m02() * m13() - m03() * m12();
	float g = m20() * m31() - m21() * m30();
	float h = m20() * m32() - m22() * m30();
	float i = m20() * m33() - m23() * m30();
	float j = m21() * m32() - m22() * m31();
	float k = m21() * m33() - m23() * m31();
	float l = m22() * m33() - m23() * m32();
	float n = 1.f / (a * l - b * k + c * j + d * i - e * h + f * g);
	psMatrix4 mat;
	mat.m00(fmaf(m11(), l, fmaf(-m12(), k, m13() * j)) * n);
	mat.m01(fmaf(-m01(), l, fmaf(m02(), k, -m03() * j)) * n);
	mat.m02(fmaf(m31(), f, fmaf(-m32(), e, m33() * d)) * n);
	mat.m03(fmaf(-m21(), f, fmaf(m22(), e, -m23() * d)) * n);
	mat.m10(fmaf(-m10(), l, fmaf(m12(), i, -m13() * h)) * n);
	mat.m11(fmaf(m00(), l, fmaf(-m02(), i, m03() * h)) * n);
	mat.m12(fmaf(-m30(), f, fmaf(m32(), c, -m33() * b)) * n);
	mat.m13(fmaf(m20(), f, fmaf(-m22(), c, m23() * b)) * n);
	mat.m20(fmaf(m10(), k, fmaf(-m12(), i, m13() * g)) * n);
	mat.m21(fmaf(-m00(), k, fmaf(m02(), i, -m03() * g)) * n);
	mat.m22(fmaf(m30(), e, fmaf(-m31(), c, m33() * a)) * n);
	mat.m23(fmaf(-m20(), e, fmaf(m21(), c, -m23() * a)) * n);
	mat.m30(fmaf(-m10(), j, fmaf(m11(), h, -m12() * g)) * n);
	mat.m31(fmaf(m00(), j, fmaf(-m01(), h, m02() * g)) * n);
	mat.m32(fmaf(-m30(), d, fmaf(m31(), b, -m32() * a)) * n);
	mat.m33(fmaf(m20(), d, fmaf(-m21(), b, m22() * a)) * n);

	return mat;
}

inline psMatrix4 psMatrix4::operator-(const psMatrix4 &ref) const {

	return psMatrix4(m00() - ref.m00(), m01() - ref.m01(), m02() - ref.m02(), m03() - ref.m03(),
		m10() - ref.m10(), m11() - ref.m11(), m12() - ref.m12(), m13() - ref.m13(),
		m20() - ref.m20(), m21() - ref.m21(), m22() - ref.m22(), m23() - ref.m23(),
		m30() - ref.m30(), m31() - ref.m31(), m32() - ref.m32(), m33() - ref.m33());
}

inline psMatrix4 &psMatrix4::operator-=(const psMatrix4 &ref) {

	components[0] -= ref.m00();
	components[1] -= ref.m01();
	components[2] -= ref.m02();
	components[3] -= ref.m03();
	components[4] -= ref.m10();
	components[5] -= ref.m11();
	components[6] -= ref.m12();
	components[7] -= ref.m13();
	components[8] -= ref.m20();
	components[9] -= ref.m21();
	components[10] -= ref.m22();
	components[11] -= ref.m23();
	components[12] -= ref.m30();
	components[13] -= ref.m31();
	components[14] -= ref.m32();
	components[15] -= ref.m33();

	return *this;
}

inline psMatrix4 psMatrix4::operator*(float scalar) const {

	return scalar != 1.f ? psMatrix4(m00() * scalar, m01() * scalar, m02() * scalar, m03() * scalar,
		m10() * scalar, m11() * scalar, m12() * scalar, m13() * scalar,
		m20() * scalar, m21() * scalar, m22() * scalar, m23() * scalar,
		m30(), m31(), m32(), m33()) : psMatrix4(*this);
}

inline psMatrix4 &psMatrix4::operator*=(float scalar) {

	if (scalar != 1.f) {
		components[0] *= scalar;
		components[1] *= scalar;
		components[2] *= scalar;
		components[3] *= scalar;
		components[4] *= scalar;
		components[5] *= scalar;
		components[6] *= scalar;
		components[7] *= scalar;
		components[8] *= scalar;
		components[9] *= scalar;
		components[10] *= scalar;
		components[11] *= scalar;
		// Ignore translation components.
	}

	return *this;
}

inline psMatrix4 psMatrix4::operator*(const psMatrix4 &ref) const {

	psMatrix4 mat;
	mat.m00(fmaf(m00(), ref.m00(), fmaf(m10(), ref.m01(), fmaf(m20(), ref.m02(), m30() * ref.m03()))));
	mat.m01(fmaf(m01(), ref.m00(), fmaf(m11(), ref.m01(), fmaf(m21(), ref.m02(), m31() * ref.m03()))));
	mat.m02(fmaf(m02(), ref.m00(), fmaf(m12(), ref.m01(), fmaf(m22(), ref.m02(), m32() * ref.m03()))));
	mat.m03(fmaf(m03(), ref.m00(), fmaf(m13(), ref.m01(), fmaf(m23(), ref.m02(), m33() * ref.m03()))));
	mat.m10(fmaf(m00(), ref.m10(), fmaf(m10(), ref.m11(), fmaf(m20(), ref.m12(), m30() * ref.m13()))));
	mat.m11(fmaf(m01(), ref.m10(), fmaf(m11(), ref.m11(), fmaf(m21(), ref.m12(), m31() * ref.m13()))));
	mat.m12(fmaf(m02(), ref.m10(), fmaf(m12(), ref.m11(), fmaf(m22(), ref.m12(), m32() * ref.m13()))));
	mat.m13(fmaf(m03(), ref.m10(), fmaf(m13(), ref.m11(), fmaf(m23(), ref.m12(), m33() * ref.m13()))));
	mat.m20(fmaf(m00(), ref.m20(), fmaf(m10(), ref.m21(), fmaf(m20(), ref.m22(), m30() * ref.m23()))));
	mat.m21(fmaf(m01(), ref.m20(), fmaf(m11(), ref.m21(), fmaf(m21(), ref.m22(), m31() * ref.m23()))));
	mat.m22(fmaf(m02(), ref.m20(), fmaf(m12(), ref.m21(), fmaf(m22(), ref.m22(), m32() * ref.m23()))));
	mat.m23(fmaf(m03(), ref.m20(), fmaf(m13(), ref.m21(), fmaf(m23(), ref.m22(), m33() * ref.m23()))));
	mat.m30(fmaf(m00(), ref.m30(), fmaf(m10(), ref.m31(), fmaf(m20(), ref.m32(), m30() * ref.m33()))));
	mat.m31(fmaf(m01(), ref.m30(), fmaf(m11(), ref.m31(), fmaf(m21(), ref.m32(), m31() * ref.m33()))));
	mat.m32(fmaf(m02(), ref.m30(), fmaf(m12(), ref.m31(), fmaf(m22(), ref.m32(), m32() * ref.m33()))));
	mat.m33(fmaf(m03(), ref.m30(), fmaf(m13(), ref.m31(), fmaf(m23(), ref.m32(), m33() * ref.m33()))));

	return mat;
}

inline psMatrix4 &psMatrix4::operator*=(const psMatrix4 &ref) {

	float n00 = fmaf(m00(), ref.m00(), fmaf(m10(), ref.m01(), fmaf(m20(), ref.m02(), m30() * ref.m03())));
	float n01 = fmaf(m01(), ref.m00(), fmaf(m11(), ref.m01(), fmaf(m21(), ref.m02(), m31() * ref.m03())));
	float n02 = fmaf(m02(), ref.m00(), fmaf(m12(), ref.m01(), fmaf(m22(), ref.m02(), m32() * ref.m03())));
	float n03 = fmaf(m03(), ref.m00(), fmaf(m13(), ref.m01(), fmaf(m23(), ref.m02(), m33() * ref.m03())));
	float n10 = fmaf(m00(), ref.m10(), fmaf(m10(), ref.m11(), fmaf(m20(), ref.m12(), m30() * ref.m13())));
	float n11 = fmaf(m01(), ref.m10(), fmaf(m11(), ref.m11(), fmaf(m21(), ref.m12(), m31() * ref.m13())));
	float n12 = fmaf(m02(), ref.m10(), fmaf(m12(), ref.m11(), fmaf(m22(), ref.m12(), m32() * ref.m13())));
	float n13 = fmaf(m03(), ref.m10(), fmaf(m13(), ref.m11(), fmaf(m23(), ref.m12(), m33() * ref.m13())));
	float n20 = fmaf(m00(), ref.m20(), fmaf(m10(), ref.m21(), fmaf(m20(), ref.m22(), m30() * ref.m23())));
	float n21 = fmaf(m01(), ref.m20(), fmaf(m11(), ref.m21(), fmaf(m21(), ref.m22(), m31() * ref.m23())));
	float n22 = fmaf(m02(), ref.m20(), fmaf(m12(), ref.m21(), fmaf(m22(), ref.m22(), m32() * ref.m23())));
	float n23 = fmaf(m03(), ref.m20(), fmaf(m13(), ref.m21(), fmaf(m23(), ref.m22(), m33() * ref.m23())));
	float n30 = fmaf(m00(), ref.m30(), fmaf(m10(), ref.m31(), fmaf(m20(), ref.m32(), m30() * ref.m33())));
	float n31 = fmaf(m01(), ref.m30(), fmaf(m11(), ref.m31(), fmaf(m21(), ref.m32(), m31() * ref.m33())));
	float n32 = fmaf(m02(), ref.m30(), fmaf(m12(), ref.m31(), fmaf(m22(), ref.m32(), m32() * ref.m33())));
	float n33 = fmaf(m03(), ref.m30(), fmaf(m13(), ref.m31(), fmaf(m23(), ref.m32(), m33() * ref.m33())));
	set(n00, n01, n02, n03,
		n10, n11, n12, n13,
		n20, n21, n22, n23,
		n30, n31, n32, n33);

	return *this;
}

inline bool psMatrix4::operator==(const psMatrix4 &ref) const {

	return m00() == ref.m00() && m01() == ref.m01() && m02() == ref.m02() && m03() == ref.m03() &&
		m10() == ref.m10() && m11() == ref.m11() && m12() == ref.m12() && m13() == ref.m13() &&
		m20() == ref.m20() && m21() == ref.m21() && m22() == ref.m22() && m23() == ref.m23() &&
		m30() == ref.m30() && m31() == ref.m31() && m32() == ref.m32() && m33() == ref.m33();
}

inline bool psMatrix4::operator!=(const psMatrix4 &ref) const {

	return !(*this == ref);
}

inline void psMatrix4::identity() {

	set(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}

inline void psMatrix4::translate(float _x, float _y, float _z) {

	m30(fmaf(m00(), _x, fmaf(m10(), _y, fmaf(m20(), _z, m30()))));
	m31(fmaf(m01(), _x, fmaf(m11(), _y, fmaf(m21(), _z, m31()))));
	m32(fmaf(m02(), _x, fmaf(m12(), _y, fmaf(m22(), _z, m32()))));
	m33(fmaf(m03(), _x, fmaf(m13(), _y, fmaf(m23(), _z, m33()))));
}

inline void psMatrix4::translate(const psVector3 &ref) {

	translate(ref.x(), ref.y(), ref.z());
}

inline void psMatrix4::rotate(float angle, float _x, float _y, float _z) {

	float sin = sinf(angle);
	float cos = cosf(angle);
	float op = 1.f - cos;
	float r00 = _x * _x * op + cos;
	float r01 = _x * _y * op + _z * sin;
	float r02 = _x * _z * op - _y * sin;
	float r10 = _x * _y * op - _z * sin;
	float r11 = _y * _y * op + cos;
	float r12 = _y * _z * op + _x * sin;
	float r20 = _x * _z * op + _y * sin;
	float r21 = _y * _z * op - _x * sin;
	float r22 = _z * _z * op + cos;
	float n00 = m00() * r00 + m10() * r01 + m20() * r02;
	float n01 = m01() * r00 + m11() * r01 + m21() * r02;
	float n02 = m02() * r00 + m12() * r01 + m22() * r02;
	float n03 = m03() * r00 + m13() * r01 + m23() * r02;
	float n10 = m00() * r10 + m10() * r11 + m20() * r12;
	float n11 = m01() * r10 + m11() * r11 + m21() * r12;
	float n12 = m02() * r10 + m12() * r11 + m22() * r12;
	float n13 = m03() * r10 + m13() * r11 + m23() * r12;
	m20(m00() * r20 + m10() * r21 + m20() * r22);
	m21(m01() * r20 + m11() * r21 + m21() * r22);
	m22(m02() * r20 + m12() * r21 + m22() * r22);
	m23(m03() * r20 + m13() * r21 + m23() * r22);
	m00(n00);
	m01(n01);
	m02(n02);
	m03(n03);
	m10(n10);
	m11(n11);
	m12(n12);
	m13(n13);
}

inline void psMatrix4::rotateX(float angle) {
	
	float sin = sinf(angle);
	float cos = cosf(angle);
	float n10 = m10();
	float n11 = m11();
	float n12 = m12();
	float n13 = m13();
	float n20 = m20();
	float n21 = m21();
	float n22 = m22();
	float n23 = m23();
	m10(fmaf(n10, cos, n20 * sin));
	m11(fmaf(n11, cos, n21 * sin));
	m12(fmaf(n12, cos, n22 * sin));
	m13(fmaf(n13, cos, n22 * sin));
	m20(fmaf(n10, -sin, n20 * cos));
	m21(fmaf(n11, -sin, n21 * cos));
	m22(fmaf(n12, -sin, n22 * cos));
	m23(fmaf(n13, -sin, n22 * cos));
}

inline void psMatrix4::rotateY(float angle) {

	float sin = sinf(angle);
	float cos = cosf(angle);
	float n00 = fmaf(m00(), cos, m20() * -sin);
	float n01 = fmaf(m01(), cos, m21() * -sin);
	float n02 = fmaf(m02(), cos, m22() * -sin);
	float n03 = fmaf(m03(), cos, m23() * -sin);
	m20(fmaf(m00(), sin, m20() * cos));
	m21(fmaf(m01(), sin, m21() * cos));
	m22(fmaf(m02(), sin, m22() * cos));
	m23(fmaf(m03(), sin, m23() * cos));
	m00(n00);
	m01(n01);
	m02(n02);
	m03(n03);
}

inline void psMatrix4::rotateZ(float angle) {

	float sin = sinf(angle);
	float cos = cosf(angle);
	float n00 = fmaf(m00(), cos, m10() * sin);
	float n01 = fmaf(m01(), cos, m11() * sin);
	float n02 = fmaf(m02(), cos, m12() * sin);
	float n03 = fmaf(m03(), cos, m13() * sin);
	m10(fmaf(m00(), -sin, m10() * cos));
	m11(fmaf(m01(), -sin, m11() * cos));
	m12(fmaf(m02(), -sin, m12() * cos));
	m13(fmaf(m03(), -sin, m13() * cos));
	m00(n00);
	m01(n01);
	m02(n02);
	m03(n03);
}

inline void psMatrix4::rotate(float _x, float _y, float _z) {

	if (_x)
		rotateX(_x);

	if (_y)
		rotateY(_y);

	if (_z)
		rotateZ(_z);

}

#endif