#pragma once

enum class DialogAnswer
{
	Yes = 0,
	No,
	Cancel,
};

class CFileManager
{
public:

	static std::string GetFileToSave();
	static std::string GetFileToOpen();
	static DialogAnswer StartDialog(std::string const& message);
private:
	static std::string GetFilePath(bool isOpened);
};

