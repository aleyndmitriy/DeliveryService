#include"SoftingServer.h"

SoftingServer& SoftingServer::Instance()
{
	static SoftingServer shared;
	return shared;
}

SoftingServer::~SoftingServer()
{

}