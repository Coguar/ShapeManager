#pragma once

class CFileManager
{
public:
	CFileManager();
	~CFileManager();

	std::string AddFile(boost::filesystem::path const& file);

	void RemoveFile(boost::filesystem::path const& path);
	static std::string CopyFile(boost::filesystem::path const& file, boost::filesystem::path const& toDir);

private:
	boost::filesystem::path m_tempFolderPath;
	std::map<std::string, std::string> m_loadedFiles;
};

