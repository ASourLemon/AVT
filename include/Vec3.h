#ifndef INCLUDE_VEC3_H_
#define INCLUDE_VEC3_H_

class Vec3 {
private:
	float _x;
	float _y;
	float _z;

public:
	Vec3() :
			_x(0), _y(0), _z(0) {
	}
	Vec3(float x, float y, float z) :
			_x(x), _y(y), _z(z) {
	}
	inline float getX() {
		return _x;
	}
	inline float getY() {
		return _y;
	}
	inline float getZ() {
		return _z;
	}
	inline void set(float x, float y, float z) {
		_x = x;
		_y = x;
		_z = x;
	}
	inline void operator=(const Vec3& vec) {
		_x = vec._x;
		_y = vec._y;
		_z = vec._z;
	}
	inline Vec3 operator+(const Vec3& vec) {
		return Vec3(_x + vec._x, _y + vec._y, _z + vec._z);
	}
	inline Vec3 operator-(const Vec3& vec) {
		return Vec3(_x - vec._x, _y - vec._y, _z - vec._z);
	}
	inline Vec3 operator*(float scalar) {
		return Vec3(_x * scalar, _y * scalar, _z * scalar);
	}
};

#endif /* INCLUDE_VEC3_H_ */
