#pragma once
#include "Account.h"
class Debit :public Account
{
public:
	Debit(float p, string str2, float val) : Account(p, str2, val) {};
	~Debit();
	bool transfer(float cash) override;
	bool withdraw(float cash) override;
};

