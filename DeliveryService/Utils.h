#pragma once
#include<Windows.h>
#include<string>
#include<strsafe.h>
#include<vector>

std::string Wstr2Str(const std::wstring& wStr);
std::string GetErrorText(DWORD errId);
bool getComputerName(std::string& computerName);