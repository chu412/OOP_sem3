#pragma once
#include "Account.h"
class Deposit :public Account
{
public:
	Deposit(float p, string str2, float val, int ct) :Account(p, str2, val) { count = ct; };
	~Deposit();
	bool transfer(float cash) override;
	bool withdraw(float cash) override;
private:
	int count;
public:
	void nextDay();
};


