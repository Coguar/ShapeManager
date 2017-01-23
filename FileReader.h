#pragma once

class CShape;
class CCanvas;

class CFileReader
{
public:
	static bool Save(std::vector<std::shared_ptr<CShape>> const& shapes);
	static bool Open(std::shared_ptr<CCanvas> & canvas);
};

