#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "transaction.h"

class TransactionS : public Transaction {

public:
	virtual Transaction* create();			// creates a show action
	virtual void setData(ifstream&);		// sets data
	void print() const;

};

#endif
