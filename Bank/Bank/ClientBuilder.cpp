#include "pch.h"
#include "ClientBuilder.h"


ClientBuilder::ClientBuilder(string str1, string str2, string str3)
{
	name = str1;
	surname = str2;
	id = str3;
}


ClientBuilder::~ClientBuilder()
{
}
void ClientBuilder::takeAdress(string str)
{
	adress = str;
}

void ClientBuilder::takePasport(string str)
{
	pasport = str;
}
Client* ClientBuilder::build()
{
	return new Client(this);
}