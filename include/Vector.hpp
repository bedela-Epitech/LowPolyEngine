#ifndef		_LEDEB_VECTOR_HPP_
#define		_LEDEB_VECTOR_HPP_

#include <string>
#include <cmath>

namespace game
{
	template<class T> class Vector3d
	{
	public:
		T x, y, z;
		T norm;
	public:
		Vector3d(T X = 0, T Y = 0, T Z = 0) : x(X), y(Y), z(Z), norm(sqrt(X * X + Y * Y + Z * Z)) {}

		template <typename _L> operator Vector3d<_L>() const { return Vector3d<_L>(x, y, z); };

		Vector3d operator-() const {
			return Vector3d<T>(-x, -y, -z);
		};

		bool operator==(const Vector3d& other) const {
			return (x == other.x && y == other.y && z == other.z);
		};
		Vector3d &operator=(const Vector3d& other)  {
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		};
		bool operator!=(const Vector3d& other) const {
			return !operator==(other);
		};

		bool operator<(const Vector3d& other) const {
			if (x < other.x)
				return true;
			if (x > other.x)
				return false;
			//x == other.x
			if (y < other.y)
				return true;
			if (y > other.y)
				return false;
			//y == other.y
			if (z < other.z)
				return true;
			if (z > other.z)
				return false;
			//z == other.z
			return false;
		};
		bool operator>(const Vector3d& other) const {
			return other < *this;
		};
		bool operator<=(const Vector3d& other) const {
			return !operator>(other);
		};
		bool operator>=(const Vector3d& other) const {
			return !operator<(other);
		};

		Vector3d& operator*= (const Vector3d& other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		};
		Vector3d operator* (const Vector3d& other) const {
			return Vector3d<T>(x * other.x, y * other.y, z * other.z);
		};

		Vector3d& operator/= (const Vector3d& other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		};
		Vector3d operator/ (const Vector3d& other) const {
			return Vector3d<T>(x / other.x, y / other.y, z / other.z);
		};

		Vector3d& operator+= (const Vector3d& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		};
		Vector3d operator+ (const Vector3d& other) const {
			return Vector3d<T>(x + other.x, y + other.y, z + other.z);
		};

		Vector3d& operator-= (const Vector3d& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		};
		Vector3d operator- (const Vector3d& other) const {
			return Vector3d<T>(x - other.x, y - other.y, z - other.z);
		};

		Vector3d& operator*= (const T f) {
			x *= f;
			y *= f;
			z *= f;
			return *this;
		};
		Vector3d operator* (const T f) const {
			return Vector3d<T>(x*f, y*f, z*f);
		};

		Vector3d& operator/= (const T f) {
			x /= f;
			y /= f;
			z /= f;
			return *this;
		};
		Vector3d operator/ (const T f) const {
			return Vector3d<T>(x / f, y / f, z / f);
		};

		Vector3d& operator+= (const T f) {
			x += f;
			y += f;
			z += f;
			return *this;
		};
		Vector3d operator+ (const T f) const {
			return Vector3d<T>(x + f, y + f, z + f);
		};

		Vector3d& operator-= (const T f) {
			x -= f;
			y -= f;
			z -= f;
			return *this;
		};
		Vector3d operator- (const T f) const {
			return Vector3d<T>(x - f, y - f, z - f);
		};

		/* Returns the magnitude of this vector. */
		T magnitude() const {
			return sqrt(sqrMagnitude());
		};
		/* Returns the squared magnitude of this vector. */
		T sqrMagnitude() const {
			return x*x + y*y + z*z;
		};

		/* Returns the inverse of this vector (1 / vector). */
		Vector3d& invert() {
			return ((*this) = 1 / (*this));
		}
		/* Returns a copy of this vector inverted (1 / vector). */
		Vector3d inverse() const {
			return (1 / (*this));
		}

		/* Normalizes this vector. */
		Vector3d& normalize() {
			return ((*this) *= 1 / magnitude());
		};
		/* Returns a copy of this vector normalized. */
		Vector3d normalized() const {
			return ((*this) * 1 / magnitude());
		};

		/* Return the dot product of this vector and 'other'. */
		T dot(const Vector3d& other) const {
			return x*other.x + y*other.y + z*other.z;
		};
		/* Return the dot product of vector a and b. */
		static T dot(const Vector3d& a, const Vector3d& b) {
			return a.x*b.x + a.y*b.y + a.z*b.z;
		};

		/* Return the cross product of this vector and 'other'. */
		Vector3d cross(const Vector3d& other) const {
			return Vector3d<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
		};
		/* Return the cross product of vector a and b. */
		static Vector3d cross(const Vector3d& a, const Vector3d& b) {
			return Vector3d<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		};

		/* Returns the distance from this vector to 'to'. */
		T distance(const Vector3d& to) const {
			return (*this - to).magnitude();
		};
		/* Returns the distance between vector a and b. */
		static T distance(const Vector3d& a, const Vector3d& b) {
			return (a - b).magnitude();
		};

		/* Returns a linearly interpolated vector between this vector and 'other' based on t. */
		Vector3d lerp(const Vector3d& other, const float t) const {
			return ((1.0f - t)*(*this) + t*other);
		};
		/* Returns a linearly interpolated vector between vector a and b based on t. */
		static Vector3d lerp(const Vector3d& a, const Vector3d& b, const float t) {
			return ((1.0f - t)*a + t*b);
		};

		/* Returns a spherically interpolated vector between this vector and 'other' based on t. */
		Vector3d slerp(const Vector3d& other, float t) const {
			float dotproduct = dot(other);
			float theta = acos(dotproduct);

			t /= 2;

			if (theta < 0.0f)
				theta = -theta;

			float st = sin(theta);
			float coeff1 = sin((1 - t)*theta) / st;
			float coeff2 = sin(t*theta) / st;

			return (coeff1*(*this) + coeff2*other).normalize();
		};
		/* Returns a spherically interpolated vector between vector a and b based on t. */
		static Vector3d slerp(const Vector3d& a, const Vector3d& b, float t) {
			float dotproduct = dot(a, b);

			t /= 2;

			float theta = acos(dotproduct);
			if (theta < 0.0f)
				theta = -theta;

			float st = sin(theta);
			float coeff1 = sin((1 - t)*theta) / st;
			float coeff2 = sin(t*theta) / st;

			return (coeff1*a + coeff2*b).normalize();
		};

		/* Calculate the angle between two vectors in radians. */
		T angle(const Vector3d& to) {
			float dot = (*this).dot(to);
			dot /= ((*this).magnitude() * to.magnitude());
			return acos(dot);
		};
		/* Calculate the angle between two vectors in radians. */
		static T angle(const Vector3d& from, const Vector3d& to) {
			float dot = from.dot(to);
			dot /= (from.magnitude() * to.magnitude());
			return acos(dot);
		};

		/* Returns a structured string representation of this vector. */

		friend Vector3d<T> operator* (const T d, const Vector3d& vec) {
			return Vector3d<T>(d * vec.x, d * vec.y, d * vec.z);
		};

		friend Vector3d<T> operator/ (const T d, const Vector3d& vec) {
			return Vector3d<T>(d / vec.x, d / vec.y, d / vec.z);
		};

		Vector3d<T> operator/ (const int &div) {
			return Vector3d<T>(x / div, y / div, z / div);
		};

		friend Vector3d<T> operator+ (const T d, const Vector3d& vec) {
			return Vector3d<T>(d + vec.x, d + vec.y, d + vec.z);
		};

		friend Vector3d<T> operator- (const T d, const Vector3d& vec) {
			return Vector3d<T>(d - vec.x, d - vec.y, d - vec.z);
		};

		static const Vector3d left;
		static const Vector3d right;
		static const Vector3d up;
		static const Vector3d down;
		static const Vector3d forward;
		static const Vector3d back;
		static const Vector3d zero;
		static const Vector3d one;
	};

	template<class T> class Vector2d
	{
	public:
		T x, y;
		T norm;
	public:
		Vector2d(T X = 0, T Y = 0) : x(X), y(Y), norm(sqrt(X * X + Y * Y)) {}

		template <typename _L> operator Vector2d<_L>() const { return Vector2d<_L>(x, y); };

		Vector2d operator-() const {
			return Vector2d<T>(-x, -y);
		};

		bool operator==(const Vector2d& other) const {
			return (x == other.x && y == other.y);
		};
	};
}

#endif		// !_LEDEB_VECTOR_HPP_
