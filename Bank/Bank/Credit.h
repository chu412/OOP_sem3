#pragma once
#include "Account.h"
class Credit :public Account
{
public:
	Credit(float p, string str2, float val, float lt) :Account(p, str2, val) { limit = lt; };
	~Credit();
	bool transfer(float cash) override;
	bool withdraw(float cash) override;
	void getPrc() override;
private:
	float limit;


};