#pragma once
#include<Windows.h>
#include<string>
#include<strsafe.h>
#include<vector>
#include<ByteString.h>

std::string Wstr2Str(const std::wstring& wStr);
std::string GetErrorText(DWORD errId);
bool getComputerName(std::string& computerName);
int CompareSystemDateTime(const SYSTEMTIME* time1, const SYSTEMTIME* time2);
bool loadFileIntoByteString(const std::string& fileName, SoftingOPCToolbox5::ByteString& byteString);