#pragma once
//#include "Account.h"
#include "Credit.h"
#include "Debit.h"
#include "Client.h"
#include "Deposit.h"
#include <vector>
#include "Command.h"

struct oper {
	oper(string str, int j, int i, float b) { idAc = str; id = j; type = i; value = b; };
	string idAc;
	int id;
	int type;
	float value;
};
struct dataCl {
	dataCl(string str, string str2) { idAc = str; idCl = str2; }
	string idAc;
	string idCl;
};
class TheBank
{
public:
	TheBank(string str1, float a, float b, float c, float d);
	~TheBank();
private:
	string name;
	vector <Client> clients;
	vector <Credit> credits;
	vector <Debit> debits;
	vector <Deposit> deposits;
	vector <oper> operathions;
	vector <dataCl> base;
	float prc = 1;
	float limit = 50000;
	float limitCredit = 50000;
	float prcCredit = 100;
	int idClient = 1;
	int idAccount = 1;
	int idOperathion = 1;
	int days = 1;
public:
	void addClient();
	void addMoreInfoClient(string str);
	void addAccount(string str);
	void nextData();
	void useMoney(string str);
	void returnOperathion(int str1);
	void swapLimit(float a);
	void swapPrc(float a);
	void swapPrcCredit(float a);
	float checkMoney(string str);

};

