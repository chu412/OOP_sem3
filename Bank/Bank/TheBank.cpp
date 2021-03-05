#include "pch.h"
#include "TheBank.h"





TheBank::TheBank(string str1, float a, float b, float c, float d)
{
	name = str1;
	prc = a;
	limit = b;
	prcCredit = c;
	limitCredit = d;
}

TheBank::~TheBank()
{

}

void TheBank::addClient()
{
	cout << "Input name and surname\n";
	string str1, str2, str3;
	cin >> str1 >> str2;
	str3 = name + ":" + to_string(idClient++);

	ClientBuilder bd(str1, str2, str3);
	cout << "Add other data(pasport,adress) \n 1 yes 2 no\n";
	int i;
	cin >> i;
	if (i == 1) {
		cout << "Add pasport -1 \n Add adress -2\n Add all -3\n";
		int j;
		cin >> j;
		if (j == 1) {
			cout << "Input pasport\n";
			cin >> str2;
			bd.takePasport(str2);
		}
		if (j == 2) {
			cout << "Input adress\n";
			cin >> str2;
			bd.takeAdress(str2);
		}
		if (j == 3) {
			cout << "Input pasport\n";
			cin >> str2;
			bd.takePasport(str2);
			cout << "Input adress\n";
			cin >> str2;
			bd.takeAdress(str2);

		}

	}
	Client* cl = bd.build();
	clients.push_back(*cl);

}

void TheBank::addMoreInfoClient(string str)
{
	for (unsigned int i = 0; i < clients.size(); i++) {
		string str2;
		if (clients.at(i).getId() == str) {
			cout << "Add pasport -1 \n Add adress -2\n Add all -3\n";
			int j;
			cin >> j;
			if (j == 1) {
				cout << "Input pasport\n";
				cin >> str2;
				clients.at(i).takePasport(str2);
			}
			if (j == 2) {
				cout << "Input adress\n";
				cin >> str2;
				clients.at(i).takeAdress(str2);
			}
			if (j == 3) {
				cout << "Input pasport\n";
				cin >> str2;
				clients.at(i).takePasport(str2);
				cout << "Input adress\n";
				cin >> str2;
				clients.at(i).takeAdress(str2);

			}

		}
	}
}

void TheBank::addAccount(string str)
{
	cout << "Input type\n Debit -1\n Credit -2\n Deposit - 3\n";
	int j;
	float money;
	cin >> j;
	cout << "Input the initial payment or 0 if it is not available\n";
	cin >> money;
	string id = name + ":" + to_string(idAccount++);
	bool st = false;
	for (unsigned int i = 0; i < clients.size(); i++)
		if (clients.at(i).getId() == str)
			if (clients.at(i).getPasport() != "" && clients.at(i).getAdress() != "") st = true;
	if (j == 1) {
		Debit a(prc, id, money);
		a.takeStatus(st);
		debits.push_back(a);
	}
	if (j == 2) {
		Credit b(prcCredit, id, money, limitCredit);
		b.takeStatus(st);
		credits.push_back(b);
	}
	if (j == 3) {
		float p = 3.5;
		if (money < 50000) p = 3;
		if (money >= 100000) p = 4;
		Deposit c(p, id, money, 90);
		c.takeStatus(st);
		deposits.push_back(c);
	}
	base.push_back(dataCl(id, str));

}

void TheBank::nextData()
{
	days++;
	for (unsigned int i = 0; i < credits.size(); i++)
		credits.at(i).getPrc();
	for (unsigned int i = 0; i < debits.size(); i++)
		debits.at(i).takePrc();
	for (unsigned int i = 0; i < deposits.size(); i++)
		deposits.at(i).takePrc();
	if (days % 30 == 0) {
		for (unsigned int i = 0; i < debits.size(); i++)
			debits.at(i).getPrc();
		for (unsigned int i = 0; i < deposits.size(); i++)
			deposits.at(i).getPrc();
	}
}

void TheBank::useMoney(string str)
{
	cout << "Operation type \n Withdrawal -1\n Transfer -2\n Deposit -3\n";
	int j;
	cin >> j;
	float money;
	cout << "Enter the amount\n";
	cin >> money;
	bool status = false;
	if (j == 1) {
		for (unsigned int i = 0; i < credits.size(); i++)
			if (credits.at(i).getId() == str) {
				WithdrawCommand cmd(&credits.at(i), money);
				status = cmd.execute();
			}
		for (unsigned int i = 0; i < debits.size(); i++)
			if (debits.at(i).getId() == str) {
				WithdrawCommand cmd(&debits.at(i), money);
				status = cmd.execute();
			}
		for (unsigned int i = 0; i < deposits.size(); i++)
			if (deposits.at(i).getId() == str) {
				WithdrawCommand cmd(&deposits.at(i), money);
				status = cmd.execute();
			}

	}
	if (j == 2) {
		for (unsigned int i = 0; i < credits.size(); i++)
			if (credits.at(i).getId() == str) {
				TransferCommand cmd(&credits.at(i), money);
				status = cmd.execute();
			}
		
		for (unsigned int i = 0; i < debits.size(); i++)
			if (debits.at(i).getId() == str) {
				TransferCommand cmd(&credits.at(i), money);
				status = cmd.execute();
			}
		
		for (unsigned int i = 0; i < deposits.size(); i++)
			if (deposits.at(i).getId() == str) {
				TransferCommand cmd(&credits.at(i), money);
				status = cmd.execute();
			}
		
	}
	if (j == 3) {
		for (unsigned int i = 0; i < credits.size(); i++)
			if (credits.at(i).getId() == str) {
				TopUpCommand cmd(&credits.at(i), money);
				status = cmd.execute();
			}
	
		for (unsigned int i = 0; i < debits.size(); i++)
			if (debits.at(i).getId() == str) {
				TopUpCommand cmd(&debits.at(i), money);
				status = cmd.execute();
			}
		
		for (unsigned int i = 0; i < deposits.size(); i++)
			if (deposits.at(i).getId() == str) {
				TopUpCommand cmd(&deposits.at(i), money);
				status = cmd.execute();
			}
		
		status = true;
	}
	if (status)operathions.push_back(oper(str, idOperathion++, j, money));
}

void TheBank::returnOperathion(int str1)
{
	for (unsigned int l = 0; l < operathions.size(); l++) {
		if (operathions.at(l).id == str1) {
			string str = operathions.at(l).idAc;
			int j = operathions.at(l).type;
			float money = operathions.at(l).value;
			if (j == 3) {
				for (unsigned int i = 0; i < credits.size(); i++)
					if (credits.at(i).getId() == str)
						WithdrawCommand cmd(&deposits.at(i), money);
				
				for (unsigned int i = 0; i < debits.size(); i++)
					if (debits.at(i).getId() == str)
						WithdrawCommand cmd(&deposits.at(i), money);
				
				for (unsigned int i = 0; i < deposits.size(); i++)
					if (deposits.at(i).getId() == str)
						WithdrawCommand cmd(&deposits.at(i), money);
				
			}
			if (j == 2 || j == 1) {
				for (unsigned int i = 0; i < credits.size(); i++)
					if (credits.at(i).getId() == str)
						UndoCommand cmd(&deposits.at(i), money);
				
				for (unsigned int i = 0; i < debits.size(); i++)
					if (debits.at(i).getId() == str)
						
						UndoCommand cmd(&deposits.at(i), money);
				for (unsigned int i = 0; i < deposits.size(); i++)
					if (deposits.at(i).getId() == str)
						UndoCommand cmd(&deposits.at(i), money);


			}
		}
	}
}

void TheBank::swapLimit(float a)
{
	limit = a;
}

void TheBank::swapPrc(float a)
{
	prc = a;
}

void TheBank::swapPrcCredit(float a)
{
	prcCredit = a;
}

float TheBank::checkMoney(string str)
{
	for (unsigned int i = 0; i < credits.size(); i++)
		if (credits.at(i).getId() == str)
			return  credits.at(i).getValue();
	for (unsigned int i = 0; i < debits.size(); i++)
		if (debits.at(i).getId() == str)
			return  debits.at(i).getValue();
	for (unsigned int i = 0; i < deposits.size(); i++)
		if (deposits.at(i).getId() == str)
			return deposits.at(i).getValue();
	return 0.0f;

}
