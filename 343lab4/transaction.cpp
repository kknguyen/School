#include "transaction.h"

//---------------------------------------------------------------------------
// constructor + destructor shells
Transaction::Transaction() { }
Transaction::~Transaction() { }

//---------------------------------------------------------------------------
// return transaction type (S, H, R, B)
char Transaction::getType() {
	return type;
}
