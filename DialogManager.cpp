#include "stdafx.h"
#define _AFXDLL
#include <afxwin.h>
#include <afxdlgs.h>
#include "DialogManager.h"

namespace
{
	static const std::string SHAPE_MANAGER_FILE_TYPE = ".sm";
	static const std::string SHAPE_MANAGER_FILE_EXPR = "Shape files (*.sm) | *.sm|";

	static const std::string PICTURE_TYPE = ".png";
	static const std::string PICTURE_EXPR = "Picture (*.png; *.jpg) | *.png; *.jpg|";
}

std::string CDialogManager::GetFileToSave()
{
	return GetFilePath(false, SHAPE_MANAGER_FILE_EXPR, SHAPE_MANAGER_FILE_TYPE);
}

std::string CDialogManager::GetFileToOpen()
{
	return GetFilePath(true, SHAPE_MANAGER_FILE_EXPR, SHAPE_MANAGER_FILE_TYPE);
}

std::string CDialogManager::GetPathToPicture()
{
	return GetFilePath(true, PICTURE_EXPR, PICTURE_TYPE);
}

DialogAnswer CDialogManager::StartDialog(std::string const & message)
{
	std::wstring wmsg(message.begin(), message.end());
	auto answer = AfxMessageBox(wmsg.data(), MB_YESNOCANCEL);

	switch (answer)
	{
	case IDYES:
		return DialogAnswer::Yes;
	case IDNO:
		return DialogAnswer::No;
	case IDCANCEL:
		return DialogAnswer::Cancel;
	default:
		return DialogAnswer::Cancel;
	}
}

void CDialogManager::ErrorDialog(std::string const & message)
{
	std::wstring wmsg(message.begin(), message.end());
	AfxMessageBox(wmsg.data(), MB_ICONERROR);
}

std::string CDialogManager::GetFilePath(bool isOpened, std::string const& exp, std::string const& autoAddedExp)
{
	std::wstring wautoExp(autoAddedExp.begin(), autoAddedExp.end());
	std::wstring wexp(exp.begin(), exp.end());

	CFileDialog dlgFile(isOpened, wautoExp.data(), NULL, OFN_EXPLORER | OFN_OVERWRITEPROMPT, wexp.data());
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;

	dlgFile.DoModal();
	fileName.ReleaseBuffer();

	return std::string(CT2CA(fileName));
}
