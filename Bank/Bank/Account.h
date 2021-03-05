#pragma once
#include <string>
#include <iostream>
using namespace std;
class Account
{
public:
	Account(float p, string str2, float val);
	~Account();
protected:
	float value = 0;
	string id;
	bool status = false;
	float prc = 0;
	float valuePrc = 0;

public:
	void topUp(float cash);
	virtual bool transfer(float cash) = 0;
	virtual bool withdraw(float cash) = 0;
	void takeStatus(bool st);
	virtual void getPrc();
	void takePrc();
	string getId();
	float getValue();
};

