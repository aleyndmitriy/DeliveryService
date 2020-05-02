#pragma once

class ISoftingApplicationSettingsViewInput
{
public:
	virtual void setupInitialState() = 0;
	virtual ~ISoftingApplicationSettingsViewInput() {};
};