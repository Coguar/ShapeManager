#pragma once

class CShape;

class CFileManager
{
public:

	static void SaveToFile(std::vector<std::shared_ptr<CShape>> const& shapes);

private:
	static std::string const& GetFilePath(bool isOpened);
};

