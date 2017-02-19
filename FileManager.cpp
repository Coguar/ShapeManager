#include "stdafx.h"
#include "FileManager.h"

using namespace boost::filesystem;

CFileManager::CFileManager()
	: m_tempFolderPath(unique_path("TEMP%%%%"))
{
	if(!exists(m_tempFolderPath))
		create_directory(m_tempFolderPath);
}


CFileManager::~CFileManager()
{
	remove_all(m_tempFolderPath);
}

std::string CFileManager::AddFile(boost::filesystem::path const & file)
{
	auto ext = file.extension();
	path newPath = m_tempFolderPath.wstring() + unique_path("/F%%%%%%%%").wstring() + ext.wstring();
	boost::filesystem::copy_file(file, newPath, copy_option::overwrite_if_exists);
	return newPath.string();
}

void CFileManager::RemoveFile(boost::filesystem::path const & path)
{
	if (exists(path))
	{
		remove(path);
	}
}

std::string CFileManager::CopyFile(boost::filesystem::path const & file, boost::filesystem::path const & toDir)
{
	auto pathToCopy = toDir;
	if (!is_directory(boost::filesystem::symlink_status(pathToCopy)))
	{
		pathToCopy.remove_filename();	
	}
	auto folderName = toDir.filename().replace_extension();
	pathToCopy.append(boost::filesystem::path("/").wstring());
	pathToCopy.append(folderName.wstring());
	if (!exists(pathToCopy))
	{
		boost::filesystem::create_directory(pathToCopy);
	}
	if (exists(file))
	{
		boost::filesystem::copy_file(file, pathToCopy.wstring() + boost::filesystem::path("/").wstring() + file.filename().wstring(), copy_option::overwrite_if_exists);
		return pathToCopy.string() + boost::filesystem::path("/").string() + file.filename().string();
	}
	return std::string();
}
