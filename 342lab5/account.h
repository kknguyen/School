#ifndef account
#define account
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue>
#include "transaction.h"

using namespace std;

const int MAXACC = 10;			// max # of account types
const int MAXID = 10000;		// IDs need to be 4 digits
const int MAXHISTNUM = 100;		// history cannot exceed 100 items

class Account{
   
	// Output
	friend ostream& operator<<(ostream &, const Account &);

public: 
	Account(int = 0);							// constructor
	~Account();									// destructor

	bool setData(ifstream&);					// set data from file
	Account& operator=(const Account&);			// assignment operator

	//Comparison Operators
	bool operator<(const Account&) const;
	bool operator>(const Account&) const;
	bool operator==(const Account&) const;
	bool operator!=(const Account&) const;

	void addToHistory(const Transaction&);		// add items to history
	void showHistory();							// display history

	void deposit(int, int);						// deposit money
	bool withdraw(int, int);					// withdraw money

private:
	queue<Transaction> historyList;				// history of transactions
	int historySize;							// size of history
	string lastName;
	string firstName;
	int accountNum;
	int startingBalances[MAXACC];
	int finalBalances[MAXACC];
};

#endif
