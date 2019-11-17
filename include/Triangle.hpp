#ifndef		_LEDEB_TRIANGLE_HPP_
#define		_LEDEB_TRIANGLE_HPP_


#include <vector>
#include "TypeDef.hpp"

namespace game
{
	template<class T> class Triangle
	{

	public:
		std::vector<Vector3d<T> > vertices;
		Vector3d<T>	normal;

	public:
	
		template <typename _L> operator Triangle<_L>() const { return Triangle<_L>(vertices, normal); };

		Triangle() {};
		Triangle(const std::vector<Vector3d<T> > &Vertices) {
			vertices.insert(vertices.begin(), Vertices.begin(), Vertices.end());
		}
		Triangle(const std::vector<Vector3d<T> > &Vertices, const Vector3d<T> &norm) {
			vertices.insert(vertices.begin(), Vertices.begin(), Vertices.end());
			normal = norm;
		}
		Triangle(const Vector3d<T> &a, const Vector3d<T> &b, const Vector3d<T> &c) {
			vertices.push_back(a);
			vertices.push_back(b);
			vertices.push_back(c);
			setNormal();
		}
		Triangle(const Vector3d<T> &a, const Vector3d<T> &b, const Vector3d<T> &c, const Vector3d<T> &Normal) {
			vertices.push_back(a);
			vertices.push_back(b);
			vertices.push_back(c);
			normal = Normal;
		}
		~Triangle() {
			vertices.clear();
		}

		void	setNormal()
		{
			Vector3d<T>	U = vertices[1] - vertices[0];
			Vector3d<T>	V = vertices[2] - vertices[0];

			normal.x = (U.y * V.z) - (U.z * V.y);
			normal.y = (U.z * V.x) - (U.x * V.z);
			normal.z = (U.x * V.y) - (U.y * V.x);
			normal = normal.normalize();
		}
	};


}

//
//std::ostream  &operator<<(std::ostream& out, const game::Triangle<int> &triangle)
//{
//	return out << "Triangle points :" << std::endl
//		<< "\tFirst Point  : " << triangle.vertices[0]
//		<< "\tSecond Point : " << triangle.vertices[1]
//		<< "\tThird Point  : " << triangle.vertices[2] << std::endl;
//}
/*std::ostream  &operator<<(std::ostream& out, const game::Triangle<float> &triangle)
{
	return out << "Triangle points :" << std::endl
		<< "\tFirst Point  : " << triangle.vertices[0].x
		<< "\tSecond Point : " << triangle.vertices[1].x
		<< "\tThird Point  : " << triangle.vertices[2].x << std::endl;
}*/
//std::ostream  &operator<<(std::ostream& out, const game::Triangle<double> &triangle)
//{
//	return out << "Triangle points :" << std::endl
//		<< "\tFirst Point  : " << triangle.vertices[0]
//		<< "\tSecond Point : " << triangle.vertices[1]
//		<< "\tThird Point  : " << triangle.vertices[2] << std::endl;
//}

#endif		// !_LEDEB_TRIANGLE_HPP_
