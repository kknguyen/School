#include "transactionH.h"

//---------------------------------------------------------------------------
// create a new history transaction
Transaction* TransactionH::create() {
	return new TransactionH();
}

//---------------------------------------------------------------------------
// set data from file
void TransactionH::setData(ifstream& infile) {
	type = 'H';
	infile >> customerID;
}

//---------------------------------------------------------------------------
// return customer ID
int TransactionH::getID() const {
	return customerID;
}

// blank function for compiler
void TransactionH::print() const { }
