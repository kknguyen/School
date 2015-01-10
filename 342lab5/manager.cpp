#include "manager.h"

//------------------------------------------------------------------------------
// Constructor

Manager::Manager(ifstream& file, ifstream& file2) {
	buildClientTree(file);		// builds tree of client data from file
	buildTransList(file2);		// builds queue of transactions
	processTransaction();		// process the transactions 
	displayReport();			// display initial/final balances
}

//------------------------------------------------------------------------------
// Destructor
// Clears the transaction queue

Manager::~Manager() {
	int size = transactionList.size();
	for (int i = 0; i < size; i++) {
		transactionList.pop();
	}
}

//------------------------------------------------------------------------------
// buildClientTree
// Create the tree from a file

void Manager::buildClientTree(ifstream& infile) {
	Account* ptr;
	bool successfulRead;
	bool success;
	for (;;) {
		ptr = new Account();						// new account
		successfulRead = ptr->setData(infile);		// set data into account
		if (infile.eof()) {
			delete ptr;
			break;
		}
		if (successfulRead) {
			success = accountList.insert(ptr);		// insert if data is valid
		}
		else {
			delete ptr;								// delete account if failed
		}
		if (!success) {								// keep reading til insert fails
			break;
		}
	}
	
}

//------------------------------------------------------------------------------
// buildTransList
// Create queue of trasnsactions

void Manager::buildTransList(ifstream& infile) {
	bool successfulRead;
	for (;;) {
		Transaction temp;
		successfulRead = temp.setData(infile);		// set data in a transaction
		if (infile.eof()) {
			break;
		}

		// Push transaction into queue if the data was set successfully
		if (successfulRead) {						
			transactionList.push(temp);
		}
	}
}

//------------------------------------------------------------------------------
// processTransaction
// Processes the transactions from the queue

void Manager::processTransaction() {
	Account* one;		// pointer to an account deposits/withdraws
	Account* two;		// second pointer for moving funds

	int size = transactionList.size();

	// Loops through the queue of transactions
	// Reinserts the transaction processed into the back of the queue
	for (int i = 0; i < size; i++) {
		Transaction temp;
		temp = transactionList.front();
		transactionList.pop();
		char transactionType = temp.getTransType();

		// Deposit
		if (transactionType == 'D') {
			int id = temp.getAccNum();				// client ID
			int accType = temp.getAccType();		// type of account
			int amount = temp.getAmount();			// $ amount
			Account find(id);						

			// Finds the account and stores in pointer one
			bool found = accountList.retrieve(find, one);

			// If found, deposit money, reinsert the transaction, add to history
			if (found) {
				transactionList.push(temp);
				one->deposit(accType, amount);
				one->addToHistory(temp);
			}
			
			// If not found, do not add back into queue
			else {
				cout << "Unknown client ID " << id << " requested" << endl;	
			}
		}

		// Withdraw
		else if (transactionType == 'W') {
			int id = temp.getAccNum();				// client ID
			int accType = temp.getAccType();		// type of account
			int amount = temp.getAmount();			// $ amount
			Account find(id);

			// Finds the account and stores in pointer one
			bool found = accountList.retrieve(find, one);

			// If found, withdraw money, re-add to queue, add to history
			if (found) {
				bool success = one->withdraw(accType, amount);
				if (success) {
					transactionList.push(temp);
					one->addToHistory(temp);
				}
			}

			// If not found, do not add back into queue
			else {
				cout << "Unknown client ID " << id << " requested" << endl;
			}
		}

		// Move
		else if (transactionType == 'M') {
			int id1 = temp.getAccNum();					// client ID (from)
			int accType = temp.getAccType();			// account type (from)
			int id2 = temp.getTargetAcc();				// client ID (to)
			int accType2 = temp.getTargetAccType();		// account type (to)
			int amount = temp.getAmount();				// $ amount
			Account find1(id1), find2(id2);

			// Finds both accounts and stores in pointers one and two
			bool found1 = accountList.retrieve(find1, one);
			bool found2 = accountList.retrieve(find2, two);

			// If found, perform the move
			if (found1 && found2) {
				bool success = one->withdraw(accType, amount);
				if (success) {
					two->deposit(accType2, amount);
					transactionList.push(temp);
					one->addToHistory(temp);
					two->addToHistory(temp);
				}
			}

			// If not found, do not add back into queue
			else {
				cout << "Unknown client ID " << id1 << " or " << id2
					 << " requested" << endl;
			}
		}

		// Display history
		else if (transactionType == 'H') {
			int id = temp.getAccNum();
			Account find(id);
			bool found = accountList.retrieve(find, one);
			if (found) {
				transactionList.push(temp);
				one->showHistory();
			}
			else {
				cout << "Unknown client ID " << id << " requested" << endl;
			}
		}
		
	}
	one = NULL;
	two = NULL;
}

//------------------------------------------------------------------------------
// displayReport
// Display report for the tree of accounts
// Beginning + Final balances

void Manager::displayReport() const {
	cout << endl << "REPORT" << endl << endl;
	accountList.display();
}
