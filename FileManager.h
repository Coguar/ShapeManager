#pragma once

class CFileManager
{
public:

	static std::string GetFileToSave();
	static std::string GetFileToOpen();

private:
	static std::string GetFilePath(bool isOpened);
};

