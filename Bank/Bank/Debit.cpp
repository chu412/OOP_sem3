#include "pch.h"
#include "Debit.h"

Debit::~Debit()
{}

bool Debit::transfer(float cash)
{
	if (value < cash)
		return false;
	value -= cash;
	return true;
}

bool Debit::withdraw(float cash)
{
	if (value < cash)
		return false;
	value -= cash;
	return true;
}
