#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Transaction {

public:
	Transaction();							// constructor
	virtual ~Transaction();					// destructor
	virtual Transaction* create() = 0;		// creates new transaction
	virtual void setData(ifstream&) = 0;	// sets data from file
	virtual void print() const = 0;			// print transaction for testing
	virtual char getType();					// return char

protected:
	char type;		// type of transaction
};

#endif
