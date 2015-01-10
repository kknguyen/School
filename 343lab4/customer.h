#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "transaction.h"
#include "transactionB.h"
#include "transactionR.h"
#include <iomanip>
#include "BSTreeMovies.h"
using namespace std;

const int MAXCUSTOMERID = 10000;   // max customer id is 9999
const int TITLEMAXLENGTH = 21;     // max character length of title is 21

class Customer {

public:
	Customer();						  // constructor
	~Customer();					  // destructor
	bool setData(ifstream&);		  // sets data via data file
	int getID();					  // returns id of the customer

	// prints three different movie trees (classic, comedy, drama)
	void print(BSTreeMovies&, BSTreeMovies&, BSTreeMovies&);

	void addToHist(Transaction*);    // adds a transaction to history

private:
	string first;							// first name
	string last;							// last name
	int id;									// client ID
	queue<Transaction*> historyList;		// history
};

#endif
