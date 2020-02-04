#pragma once
#include<tchar.h>

static const TCHAR* NETWORK_LIBRARY = "NetworkConnectLibrary.dll";
static const TCHAR* CSV_PARSER_LIBRARY = "CSVParser.dll";
static const TCHAR* APPLICATION_NAME = "DeliveryService.exe";
static const TCHAR* NETWORK_MENU_CHOOSE_CONNECTION_INTERFACE = "Choose connection interface";
static const TCHAR* NETWORK_MENU_CLOSE_CONNECTION = "Close connection";
static const TCHAR* NETWORK_MENU_ERROR_CONNECTION = "Connection error";
static const TCHAR* NETWORK_STATUSBAR_DEFAULT_STATE = "Application is not connected. Click right mouse to create connection.";
static const TCHAR* SERVICE_STATUSBAR_DEFAULT_STATE = "Service is not connected. Click right mouse to create connection.";
static const TCHAR* SERVICE_MENU_START = "Start Softing Service";
static const TCHAR* SERVICE_MENU_STOP = "Stop Softing Service";
static const TCHAR* SERVICE_MENU_ERROR = "Stop Softing Error";
static const int IDD_STATUS_BAR = 105;
static const int IDD_MENU_CONNECTIONS_IP_LIST = 11;
static const int IDD_MENU_CONNECTION_CLOSE = 12;
static const int IDD_MENU_CONNECTION_ERROR = 13;
static const int IDD_MENU_SERVICE_START = 14;
static const int IDD_MENU_SERVICE_STOP = 15;
static const int IDD_MENU_SERVICE_ERROR = 16;
static const int MAX_MENU_TITLE_LENGTH = 32;
const size_t MAX_UUID_LENGTH = 127;
const size_t MAX_END_POINT_SECURITY_CONFIGURATIONS = 23;
