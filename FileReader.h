#pragma once

class SModelShape;

class CFileReader
{
public:
	static void Save(std::string  const& path, std::vector<std::shared_ptr<SModelShape>> const& shapes);
	static std::vector<std::shared_ptr<SModelShape>> Open(std::string  const& path, std::string const& tempFolderPath);
};

