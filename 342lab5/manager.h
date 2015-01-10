//------------------------------------------------------------------------------
// Kevin Nguyen
// Lab 5
// CSS 342 Spring 2013
// 
// This progam handles transactions for a banking system. 
// The system consists of a Manager, Account, and Transaction classes.
// The Manager class contains a binary search tree (BSTree) of Accounts and
// a queue of Transactions. Each Account also contains a queue of Transactions 
// for history purposes. The Manager class uses the queue of Transactions to 
// update the tree of accounts and prints out information.
//
// Assumptions:
//		-- Data for client's are formatted correctly
//		-- Client IDs are unique
//		-- Accounts cannot be overdrawn (negative balances are illegal)
//		-- Account types 0/1 and 2/3 are linked for withdrawal purposes
//		-- Incorrect transactions are OK as long as they follow the format
//------------------------------------------------------------------------------

#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include "account.h"
#include "transaction.h"
#include "bstree.h"
#include <queue>
using namespace std;

class Manager {

public:
	Manager(ifstream&, ifstream&);			// constructor
	~Manager();								// destructor
	
	void buildClientTree(ifstream&);		// builds the client tree
	void buildTransList(ifstream&);			// builds the transactions queue

	void processTransaction();				// processes the transactions
	void displayHistory();					// display history
	void displayReport() const;				// display beginning/final balances

private:
	BSTree accountList;						// tree of accounts
	queue<Transaction> transactionList;		// queue of transactions
	
};

#endif
