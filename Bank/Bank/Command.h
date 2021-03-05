#pragma once
#include "Credit.h"
#include "Debit.h"
#include "Deposit.h"
#include <iostream>
class Command
{
public:
	virtual ~Command() {}
	virtual bool execute() = 0;
protected:
	Command(Credit* ptr, float mn) : p(ptr), money(mn) {
	}
	Command(Debit* ptr, float mn) : p1(ptr), money(mn) {
	}
	Command(Deposit* ptr, float mn) : p2(ptr), money(mn) {
	}
	Credit* p = NULL;
	Debit* p1 = NULL;
	Deposit* p2 = NULL;

	float money;
};

class TopUpCommand :public Command {
public:
	TopUpCommand(Credit* p, float mn) : Command(p, mn) {}
	TopUpCommand(Debit* p, float mn) : Command(p, mn) {}
	TopUpCommand(Deposit* p, float mn) : Command(p, mn) {}

	bool execute();
};
class TransferCommand :public Command {
public:
	TransferCommand(Credit* p, float mn) : Command(p, mn) {}
	TransferCommand(Debit* p, float mn) : Command(p, mn) {}
	TransferCommand(Deposit* p, float mn) : Command(p, mn) {}
	bool execute();
};
class  WithdrawCommand :public Command {
public:
	WithdrawCommand(Credit* p, float mn) : Command(p, mn) {}
	WithdrawCommand(Debit* p, float mn) : Command(p, mn) {}
	WithdrawCommand(Deposit* p, float mn) : Command(p, mn) {}
	bool execute();
};
class UndoCommand :public Command {
public:
	UndoCommand(Credit* p, float mn) : Command(p, mn) {}
	UndoCommand(Debit* p, float mn) : Command(p, mn) {}
	UndoCommand(Deposit* p, float mn) : Command(p, mn) {}
	bool execute();
};


