#ifndef TRANSACTIONH_H
#define TRANSACTIONH_H
#include "transaction.h"

class TransactionH : public Transaction {

public:
	virtual Transaction* create();		// creates a history transaction
	virtual void setData(ifstream&);	// set data from file
	int getID() const;					// get client ID for history
	void print() const;

protected:
	int customerID;		// client ID
};

#endif
