#pragma once
__declspec(dllexport) int __stdcall GetIPInterfaces(char** ipv4List, int* ipv4Number, char** ipv6List, int* ipv6Number);
__declspec(dllexport) void __stdcall FreeAllocatedIpLists(char* ipv4List, char* ipv6List);