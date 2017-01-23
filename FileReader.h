#pragma once

class CShape;

class CFileReader
{
public:
	static void Save(std::vector<std::shared_ptr<CShape>> const& shapes);
	static void Open(std::vector<std::shared_ptr<CShape>> & shapesVec);
};

