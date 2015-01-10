#include "transactionS.h"

//---------------------------------------------------------------------------
// create a show transaction
Transaction* TransactionS::create() {
	return new TransactionS();
}

//---------------------------------------------------------------------------
// set transaction as "show"
void TransactionS::setData(ifstream& infile) { 
	type = 'S';
}

// blank function, here so program compiles
void TransactionS::print() const { }
