#include "pch.h"
#include "Command.h"





bool TopUpCommand::execute()
{

	if (p) p->topUp(money);
	if (p1) p1->topUp(money);
	if (p2) p2->topUp(money);
	return true;
}

bool TransferCommand::execute()
{

	if (p) return p->transfer(money);
	if (p1) return p1->transfer(money);
	if (p2)return  p2->transfer(money);
}

bool WithdrawCommand::execute()
{

	if (p) return p->withdraw(money);
	if (p1) return p1->withdraw(money);
	if (p2) return p2->withdraw(money);
}

bool UndoCommand::execute()
{

	if (p) p->topUp(money);
	if (p1) p1->topUp(money);
	if (p2) p2->topUp(money);
	return true;
}
