#include"Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

//https://docs.microsoft.com/en-us/windows/win32/api/iphlpapi/nf-iphlpapi-getadaptersaddresses
//http://man7.org/linux/man-pages/man3/getifaddrs.3.html
//https://stackoverflow.com/questions/13042561/fatal-error-lnk1104-cannot-open-file-libboost-system-vc110-mt-gd-1-51-lib
//https://curl.haxx.se/libcurl/c/externalsocket.html
int CreateServer()
{
	const unsigned int WORKING_BUFFER_SIZE = 15000;
	const int MAX_TRIES = 3;
	int   ret;
	DWORD langId;
	LPVOID lpMsgBuf = NULL;
	ULONG family = AF_UNSPEC;
	ULONG flags = GAA_FLAG_INCLUDE_PREFIX;
	WSADATA wsaData = { 0 };
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
	PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
	PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
	PSOCKET_ADDRESS pIPAddress = NULL;
	char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];
	ULONG outBufLen = WORKING_BUFFER_SIZE;
	ULONG iterations = 0;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		return 0;
	}
	do {
		pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(),0,outBufLen);
		if (pAddresses == NULL) {
			return 0;
		}
		dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
		if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
			HeapFree(GetProcessHeap(),0,pAddresses);
			pAddresses = NULL;
		}
		else {
			break;
		}
		iterations++;
	} while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (iterations < MAX_TRIES));
	if (dwRetVal == NO_ERROR) {
		PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
		ULONG count = 0;
		while (pCurrAddresses != NULL) {
			pUnicast = pCurrAddresses->FirstUnicastAddress;
			count = 0;
			while (pUnicast != NULL) {
				pIPAddress = &(pUnicast->Address);
				dwRetVal = getnameinfo(pIPAddress->lpSockaddr, pIPAddress->iSockaddrLength, hostname, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICHOST);
				pUnicast = pUnicast->Next;
				count++;
			}
			pAnycast = pCurrAddresses->FirstAnycastAddress;
			while (pAnycast != NULL) {
				pIPAddress = &(pAnycast->Address);
				dwRetVal = getnameinfo(pIPAddress->lpSockaddr, pIPAddress->iSockaddrLength, hostname, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);
				pAnycast = pAnycast->Next;
			}
			/*pMulticast = pCurrAddresses->FirstMulticastAddress;
			count = 0;
			while (pMulticast != NULL) {
				pIPAddress = &(pMulticast->Address);
				dwRetVal = getnameinfo(pIPAddress->lpSockaddr, pIPAddress->iSockaddrLength, hostname, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);
				pMulticast = pMulticast->Next;
				count++;
			}*/
			pCurrAddresses = pCurrAddresses->Next;
		}
		WSACleanup();
		return 1;
	}
	else {
		if (dwRetVal == ERROR_NO_DATA)
		{

		}
		else {
			ret = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_ILANGUAGE,(LPWSTR)& langId, sizeof(langId) / sizeof(WCHAR));
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, dwRetVal, langId, (LPTSTR)& lpMsgBuf, 0, NULL)) {
				LocalFree(lpMsgBuf);		
			}
		}
		if (pAddresses) {
			HeapFree(GetProcessHeap(), 0, pAddresses);
		}
		WSACleanup();
		return 0;
	}

}