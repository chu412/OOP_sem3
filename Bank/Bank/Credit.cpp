#include "pch.h"
#include "Credit.h"

Credit::~Credit()
{
}

bool Credit::transfer(float cash)
{
	if (abs(value - limit) < cash)
		return false;
	value -= cash;
	return true;
}

bool Credit::withdraw(float cash)
{
	if (abs(value - limit) < cash)
		return false;
	value -= cash;
	return true;
}

void Credit::getPrc()
{
	if (value < 0) {
		value -= prc;
		//takePrc;
	}

}
