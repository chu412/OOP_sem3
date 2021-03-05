#include "pch.h"
#include "Client.h"





Client::Client(ClientBuilder* bd)
{
	name = bd->name;
	surname = bd->surname;
	id = bd->id;
	adress = bd->adress;
	pasport = bd->pasport;
}

Client::~Client()
{
}

void Client::takeAdress(string str)
{
	adress = str;
}

void Client::takePasport(string str)
{
	pasport = str;
}

string Client::getName()
{
	return name;
}

string Client::getSurname()
{
	return surname;
}

string Client::getPasport()
{
	return pasport;
}

string Client::getAdress()
{
	return adress;
}

string Client::getId()
{
	return id;
}
