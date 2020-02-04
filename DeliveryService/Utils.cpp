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