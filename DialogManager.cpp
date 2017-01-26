#include "stdafx.h"
#define _AFXDLL
#include <afxwin.h>
#include <afxdlgs.h>
#include "DialogManager.h"

std::string CDialogManager::GetFileToSave()
{
	return GetFilePath(false);
}

std::string CDialogManager::GetFileToOpen()
{
	return GetFilePath(true);
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

std::string CDialogManager::GetFilePath(bool isOpened)
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
