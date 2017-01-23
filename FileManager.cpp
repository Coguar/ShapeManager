#include "stdafx.h"
#include "FileManager.h"
#define _AFXDLL
#include <afxdlgs.h>

std::string CFileManager::GetFileToSave()
{
	return GetFilePath(false);
}

std::string CFileManager::GetFileToOpen()
{
	return GetFilePath(true);
}

std::string CFileManager::GetFilePath(bool isOpened)
{
	CFileDialog dlgFile(isOpened, NULL, NULL, OFN_EXPLORER, _T("Shape files (*.sm)|*.sm|"));
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	dlgFile.GetOFN().nMaxFile = c_cMaxFiles;

	dlgFile.DoModal();
	fileName.ReleaseBuffer();

	return std::string(CT2CA(fileName));
}
