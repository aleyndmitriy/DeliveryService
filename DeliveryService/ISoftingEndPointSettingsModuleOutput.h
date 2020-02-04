#pragma once
#include"SoftingServerEndPointSettings.h"

class ISoftingEndPointSettingsModuleOutput
{
public:
	virtual void GetEndPoints(const std::map<std::string, SoftingServerEndPointSettings>& settings) = 0;
	virtual ~ISoftingEndPointSettingsModuleOutput() {};
};