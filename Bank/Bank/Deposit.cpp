#include "pch.h"
#include "Deposit.h"


Deposit::~Deposit()
{}

bool Deposit::transfer(float cash)
{
	if (value < cash || count != 0)
		return false;
	value -= cash;
	return true;
}

bool Deposit::withdraw(float cash)
{
	if (value < cash || count != 0)
		return false;
	value -= cash;
	return true;
}

void Deposit::nextDay()
{
	if (count > 0) count--;
}
