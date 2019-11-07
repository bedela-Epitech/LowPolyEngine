
#include "engine/ObjParser.hpp"

game::Parser::Parser(const std::string &filePath)
{

	std::string line;
	std::ifstream infile(filePath);
	int i = 0;
	while (std::getline(infile, line))
	{
		parseLine(line);
		i++;
		std::cout << "1/4 step is at line : " << i << std::endl;
	}
}

game::Parser::~Parser()
{

}

Vector3df		game::Parser::getVertexFromLine(std::string &line) const
{
	Vector3df		vertex;
	std::string firstWord = line.substr(0, line.find(" "));

	vertex.x = atof(firstWord.c_str());

	line.erase(0, line.find(" ") + 1);
	firstWord = line.substr(0, line.find(" "));
	vertex.y = atof(firstWord.c_str());

	line.erase(0, line.find(" ") + 1);
	vertex.z = atof(line.c_str());

	vertex = vertex / 2;
	vertex.z += 2.5f;
	//vertex.y -= 1.0f;
	return (vertex);
}

Vector3df		game::Parser::getNormalFromLine(std::string &line) const
{
	Vector3df		normal;
	std::string firstWord = line.substr(0, line.find(" "));

	normal.x = atof(firstWord.c_str());

	line.erase(0, line.find(" ") + 1);
	firstWord = line.substr(0, line.find(" "));
	normal.y = atof(firstWord.c_str());

	line.erase(0, line.find(" ") + 1);
	normal.z = atof(line.c_str());

	//vertex = vertex / 50;
	//normal.z += 2.5f;
	//vertex.y -= 1.0f;
	return (normal);
}

std::vector<game::Triangle<float> >		game::Parser::getTriangleFromLine(std::string &line) const
{
	std::vector<Triangle<float> >		trianglesParsed;
	std::vector<int>		verticesIndex;
	std::string firstWord = line.substr(0, line.find(" "));

	verticesIndex.push_back(atoi(firstWord.substr(0, firstWord.find("/")).c_str()));

	line.erase(0, line.find(" ") + 1);
	firstWord = line.substr(0, line.find(" "));
	verticesIndex.push_back(atoi(firstWord.substr(0, firstWord.find("/")).c_str()));



	std::string getNorm = line;
	getNorm.erase(0, getNorm.find("/") + 1);
	getNorm.erase(0, getNorm.find("/") + 1);
	int norm = atoi(getNorm.c_str());



	line.erase(0, line.find(" ") + 1);
	if (line.find(" ") == std::string::npos)
	{
		verticesIndex.push_back(atoi(line.substr(0, line.find("/")).c_str()));
		trianglesParsed.push_back(Triangle<float>(vertices[verticesIndex[0] - 1], vertices[verticesIndex[2] - 1], vertices[verticesIndex[1] - 1], normals[norm - 1]));

	}
	else
	{
		firstWord = line.substr(0, line.find(" "));
		verticesIndex.push_back(atoi(firstWord.substr(0, firstWord.find("/")).c_str()));

		line.erase(0, line.find(" ") + 1);
		verticesIndex.push_back(atoi(line.substr(0, line.find("/")).c_str()));


		trianglesParsed.push_back(Triangle<float>(vertices[verticesIndex[0] - 1], vertices[verticesIndex[2] - 1], vertices[verticesIndex[1] - 1], normals[norm - 1]));
		trianglesParsed.push_back(Triangle<float>(vertices[verticesIndex[0] - 1], vertices[verticesIndex[3] - 1], vertices[verticesIndex[2] - 1], normals[norm - 1]));
	}

	return (trianglesParsed);
}

void		game::Parser::parseLine(std::string &line)
{
	std::string firstWord = line.substr(0, line.find(" "));
	std::vector<Triangle<float> > triGet;
	if (firstWord == "v" || firstWord == "f" || firstWord == "vn")
	{
		line.erase(0, line.find(" ") + 1);
		if (firstWord == "v")
			vertices.push_back(getVertexFromLine(line));
		if (firstWord == "vn")
			normals.push_back(getNormalFromLine(line));
		if (firstWord == "f")
		{
			triGet = getTriangleFromLine(line);
			triangles.insert(triangles.end(), triGet.begin(), triGet.end());
		}
	}
}