
#include "pch.h"
#include <iostream>

int main()
{

	TheBank a("aaa", 3, 50000, 100, 50000);
	a.addClient();
	a.addAccount("aaa:1");
	a.useMoney("aaa:1");

	cout << to_string(a.checkMoney("aaa:1")) << "\n";

	for (int i = 0; i < 31; i++)
		a.nextData();
	cout << to_string(a.checkMoney("aaa:1")) << "\n";



}

