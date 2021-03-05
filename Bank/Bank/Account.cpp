#include "pch.h"
#include "Account.h"



Account::Account(float p, string str2, float val)
{
	prc = p;
	id = str2;
	value = val;

}

Account::~Account()
{
}

void Account::topUp(float cash)
{
	value += cash;
}

void Account::takeStatus(bool st)
{
	//if (getPasport() != "" && getAdress() != "") status = true;
	//else status = false;
	status = st;
}

void Account::getPrc()
{
	value += valuePrc;
	valuePrc = 0;
}

void Account::takePrc()
{
	valuePrc = valuePrc + value * prc / 36500.0;
	//cout << to_string(valuePrc) <<" take "<< endl;
}

string Account::getId()
{
	return id;
}

float Account::getValue()
{
	return value;
}
