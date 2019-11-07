
#ifndef		_LEDEB_OBJPARSER_HPP_
#define		_LEDEB_OBJPARSER_HPP_


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Triangle.hpp"
#include "TypeDef.hpp"

namespace game
{
	class Parser
	{

	public:
		std::vector<Vector3df> vertices;
		std::vector<Vector3df> normals;
		std::vector<Triangle<float> > triangles;

	public:
		Parser(const std::string &filePath);
		~Parser();
		void		parseLine(std::string &line);
		std::vector<game::Triangle<float> >		getTriangleFromLine(std::string &line) const;
		Vector3df		getVertexFromLine(std::string &line) const;
		Vector3df		getNormalFromLine(std::string &line) const;
	};


}

#endif		// !_LEDEB_OBJPARSER_HPP_
