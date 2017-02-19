#pragma once

class CFileManager
{
public:
	CFileManager();
	~CFileManager();

	std::string AddFile(boost::filesystem::path const& file);

	std::string GetTempFolderPath() const;
	void RecreateTempFolder();

	static void RemoveFile(boost::filesystem::path const& path);
	static std::string CopyFile(boost::filesystem::path const& file, boost::filesystem::path const& toDir);
	static std::string CopyFileWithRandomName(boost::filesystem::path const& file, boost::filesystem::path const& toDir);
	static boost::filesystem::path MakeRelative(boost::filesystem::path a_From, boost::filesystem::path a_To);

private:
	boost::filesystem::path m_tempFolderPath;
};

