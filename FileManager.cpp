#include "stdafx.h"
#include "FileManager.h"

template < >
boost::filesystem::path& boost::filesystem::path::append< typename boost::filesystem::path::iterator >(typename boost::filesystem::path::iterator begin, typename boost::filesystem::path::iterator end, const codecvt_type& /*cvt*/)
{
	for (; begin != end; ++begin)
		*this /= *begin;
	return *this;
}

using namespace boost::filesystem;

namespace fs = boost::filesystem;
using fs::path;

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
	auto mainFolder = pathToCopy;
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
		return MakeRelative(mainFolder ,pathToCopy.string() + boost::filesystem::path("/").string() + file.filename().string()).string();
	}
	return std::string();
}

boost::filesystem::path CFileManager::MakeRelative(boost::filesystem::path a_From, boost::filesystem::path a_To)
{
	a_From = absolute(a_From);
	a_To = absolute(a_To);
	path ret;
	auto itrFrom(a_From.begin());
	auto itrTo(a_To.begin());
	// Find common base
	for (path::const_iterator toEnd(a_To.end()), fromEnd(a_From.end()); itrFrom != fromEnd && itrTo != toEnd && *itrFrom == *itrTo; ++itrFrom, ++itrTo);
	// Navigate backwards in directory to reach previously found base
	for (path::const_iterator fromEnd(a_From.end()); itrFrom != fromEnd; ++itrFrom) //-V683
	{
		if ((*itrFrom) != ".")
			ret /= "..";
	}
	// Now navigate down the directory branch
	for (auto itrAppend = itrTo; itrAppend != a_To.end(); ++itrAppend)
	{
		ret /= *itrAppend;
	}
	return ret;
}
