#include"Utils.h"
#include<memory>

std::string Wstr2Str(const std::wstring& wStr)
{
	size_t wStrSz = wStr.size() + 1;
	std::unique_ptr<char[]> chBuffer = std::make_unique<char[]>(wStrSz);
	WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), wStrSz, chBuffer.get(), (int)wStrSz, NULL, NULL);
	std::string str(chBuffer.get());
	return str;
}

std::string GetErrorText(DWORD errId)
{
	HLOCAL hlocal = NULL;
	DWORD systemLocale = LANG_SYSTEM_DEFAULT;

	// Get the error code's textual description
	BOOL fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, errId, systemLocale,
		(PTSTR)&hlocal, 0, NULL);

	if (!fOk) {
		// Is it a network-related error?
		HMODULE hDll = LoadLibraryEx(TEXT("netmsg.dll"), NULL,
			DONT_RESOLVE_DLL_REFERENCES);

		if (hDll != NULL) {
			fOk = FormatMessage(
				FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS |
				FORMAT_MESSAGE_ALLOCATE_BUFFER,
				hDll, errId, systemLocale,
				(PTSTR)&hlocal, 0, NULL);
			FreeLibrary(hDll);
		}
	}
	std::string errText("No text found for this error number.");
	if (fOk && (hlocal != NULL)) {
		PCTSTR pStr = (PCTSTR)LocalLock(hlocal);
		if (pStr != NULL) {
			errText = std::string(pStr);
		}
		LocalFree(hlocal);
	}
	return errText;
}

bool getComputerName(std::string& computerName)
{
	TCHAR buffer[256];
	DWORD bufferSize = sizeof(buffer);
	bool result = false;
	computerName = std::string();
	result = (GetComputerName(buffer, &bufferSize) != 0);
	if (result)
	{
		computerName = buffer;
	}
	return result;
}

int CompareSystemDateTime(const SYSTEMTIME* time1, const SYSTEMTIME* time2)
{
	FILETIME fTime1;
	FILETIME fTime2;
	BOOL res = SystemTimeToFileTime(time1, &fTime1);
	if (!res) {
		DWORD err = GetLastError();
		return -1;
	}
	res = SystemTimeToFileTime(time2, &fTime2);
	if (!res) {
		DWORD err = GetLastError();
		return -1;
	}
	return CompareFileTime(&fTime1, &fTime2);
}

bool loadFileIntoByteString(const std::string& fileName, SoftingOPCToolbox5::ByteString& byteString)
{
	HANDLE hFileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	BOOL isRead = false;
	DWORD readSize = 0;
	if (hFileHandle == INVALID_HANDLE_VALUE) {
		return false;
	}
	DWORD dwfileSize = GetFileSize(hFileHandle, NULL);
	if (dwfileSize == INVALID_FILE_SIZE) {
		DWORD error = GetLastError();
		CloseHandle(hFileHandle);
		return false;
	}
	std::unique_ptr<unsigned char[]> chBuffer = std::make_unique<unsigned char[]>(dwfileSize);
	isRead = ReadFile(hFileHandle, chBuffer.get(), dwfileSize, &readSize, NULL);
	if (isRead == FALSE || readSize != dwfileSize) {
		DWORD error = GetLastError();
		CloseHandle(hFileHandle);
		return false;
	}
	CloseHandle(hFileHandle);
	if (StatusCode::isSUCCEEDED(byteString.init(dwfileSize, chBuffer.get())))
	{
		return true;
	}
	else {
		return false;
	}
}