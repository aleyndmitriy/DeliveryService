#pragma once

class ISoftingServerSettingsViewInput
{
public:
	virtual void setupInitialState() = 0;
	virtual ~ISoftingServerSettingsViewInput() {};
};