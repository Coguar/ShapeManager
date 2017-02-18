#pragma once

enum class DialogAnswer
{
	Yes = 0,
	No,
	Cancel,
};

class CDialogManager
{
public:

	static std::string GetFileToSave();
	static std::string GetFileToOpen();
	static std::string GetPathToPicture();
	static DialogAnswer StartDialog(std::string const& message);
	static void ErrorDialog(std::string const& message);
private:
	static std::string GetFilePath(bool isOpened, std::string const& exp, std::string const& autoAddedExp);
};

