#pragma once
#include <string>
#include <iostream>
#include "ClientBuilder.h"
using namespace std;
class Client
{
public:
	Client(ClientBuilder* bd);
	~Client();
private:
	string id;
	string name;
	string surname;
	string adress;
	string pasport;
public:
	void takeAdress(string str);
	void takePasport(string str);
	string getName();
	string getSurname();
	string getPasport();
	string getAdress();
	string getId();
};

