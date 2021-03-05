#pragma once
//#include "Client.h"
extern class Client;
class ClientBuilder
{
public:
	ClientBuilder(string str1, string str2, string str3);
	~ClientBuilder();
public:
	string id;
	string name;
	string surname;
	string adress;
	string pasport;
public:
	void takeAdress(string str);
	void takePasport(string str);
	Client* build();
};
