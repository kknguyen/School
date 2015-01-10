#include "account.h"

//------------------------------------------------------------------------------
// Construtor
// Basic constructor used to create a shell account to find a client via ID

Account::Account(int num) {
	accountNum = num;
}

//------------------------------------------------------------------------------
// Destructor
// Removes all elements from the queue

Account::~Account() { 
	int size = historyList.size();
	for (int i = 0; i < size; i++) {
		historyList.pop();
	}
}

//------------------------------------------------------------------------------
// Copy Constructor

Account& Account::operator=(const Account& toCopy) {

	// Check so that the two items are different to avoid extra work
	if (&toCopy != this) {
		lastName = toCopy.lastName;
		firstName = toCopy.firstName;
		accountNum = toCopy.accountNum;
		for (int i = 0; i < 10; i++) {
			startingBalances[i] = toCopy.startingBalances[i];
			finalBalances[i] = toCopy.finalBalances[i];
		}
	}
	return *this;
}

//------------------------------------------------------------------------------
// setData
// Sets data using input from the file

bool Account::setData(ifstream& inFile) {
	inFile >> lastName >> firstName >> accountNum;
	for (int i = 0; i < 10; i++) {
		inFile >> startingBalances[i];
	}
	for (int i = 0; i < 10; i++) {
		finalBalances[i] = startingBalances[i];
	}
	return accountNum < MAXID;
}

//------------------------------------------------------------------------------
// operator<
// Only compares client ID for inserting into tree

bool Account::operator<(const Account& A) const {
	return accountNum < A.accountNum;
}

//------------------------------------------------------------------------------
// operator>
// Only compares client ID for inserting into tree

bool Account::operator>(const Account& A) const {
	return accountNum > A.accountNum;
}

//------------------------------------------------------------------------------
// operator==
// Checks for equality

bool Account::operator==(const Account& A) const {
	return accountNum == A.accountNum;
}

//------------------------------------------------------------------------------
// operator!=
// Checks for inequality

bool Account::operator!=(const Account& A) const {
	return accountNum != A.accountNum;
}

//------------------------------------------------------------------------------
// addToHistory
// Adds transactions to a queue as a record for history

void Account::addToHistory(const Transaction& T) {
	historyList.push(T);
}

//------------------------------------------------------------------------------
// showHistory
// Displays the history 

void Account::showHistory() {

	// Formatting title of history display
	cout << endl << "History of transactons for client " << firstName << " " 
		 << lastName << ", client ID = " << accountNum  << endl << setw(10)
		 << left << "Type" 
		 << setw(7) << "Amount" << " Detail" << endl << setw(10) << "---------" 
		 << setw(7) << "-------" << " --------------------------------------" << 
		 endl;

	int size = historyList.size();			// size of the transaction queue for loop
	Transaction trans;						// temp variable to hold transactions

	// Loops through the queue and displays each transaction
	// Removes a transaction from queue to display and then puts back in the end 
	for (int i = 0; i < size; i++) {
		trans = historyList.front();
		char type = trans.getTransType();

		// Deposit
		if (type == 'D') {
			cout << setw(9) << left << "Deposit " << "$" << setw(7) << right 
				 << trans.getAmount() << " into ";
			trans.accTypeName(trans.getAccType());
			historyList.pop();
			historyList.push(trans);
		}

		// Withdraw
		else if (type == 'W') {
			cout << setw(9) << left << "Withdraw" << "$" << setw(7) << right 
				 << trans.getAmount() << " from ";
			trans.accTypeName(trans.getAccType());
			historyList.pop();
			historyList.push(trans);
		}

		// Move
		else if (type == 'M') {
			int accountID = trans.getAccNum();

			// Displays as move if withdrawing from account
			if (accountID == accountNum) {
				cout << setw(9) << left << "Move" << "$" << setw(7) << right 
					 << trans.getAmount() << " from ";
				trans.accTypeName(trans.getAccType());
				cout << endl << setw(18) << "" << "to ";
				trans.accTypeName(trans.getTargetAccType());
				cout << " for client " << trans.getTargetAcc();
			}

			// Displays as deposit for move into the target account
			else {
				cout << setw(9) << left << "Deposit" << "$" << setw(7) << right 
					 << trans.getAmount() << " into ";
				trans.accTypeName(trans.getTargetAccType());
			}
			historyList.pop();
			historyList.push(trans);
		}
		cout << endl;
	}
	cout << "history" << endl;
}

//------------------------------------------------------------------------------
// deposit
// Updates the balance of an account depending on how much deposited 

void Account::deposit(int accType, int amount) {
	finalBalances[accType] += amount;
}

//------------------------------------------------------------------------------
// withdraw
// Updates the balance of an account depending on how much withdrawn

bool Account::withdraw(int accType, int amount) {
	bool success = true;

	// Account types 0 through 4 are handled differently from the rest
	if (accType > -1 && accType < 4) {

		// Money Market
		if (accType == 0) {

			// If there is enough money in the Money Market account,
			// perform the withdrawl
			if (amount <= finalBalances[accType]) {
				finalBalances[accType] -= amount;
			}

			// If there is not enough money in the Money Market account, 
			// use funds from Prime Money Market. If there is enough,
			// perform the withdrawal with the accounts
			else if (amount <= (finalBalances[accType] + finalBalances[1])) {
				int temp = amount - finalBalances[accType];
				finalBalances[accType] = 0;
				finalBalances[1] -= temp;
			}

			// If there is not enough money in both accounts combined, 
			// do not perform withdrawal
			else {
				success = false;		// withdraw faild
				cout << left << "Withdrawal not performed on Money Market for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			}
		}

		// Money Market + Prime Money Market accounts linked
		// Handled the same
		else if (accType == 1) {
			if (amount <= finalBalances[accType]) {
				finalBalances[accType] -= amount;
			}
			else if (amount <= (finalBalances[accType] + finalBalances[0])) {
				int temp = amount - finalBalances[accType];
				finalBalances[accType] = 0;
				finalBalances[0] -= temp;
			}
			else {
				success = false;		// withdraw faild
				cout << left << "Withdrawal not performed on Prime Money Market for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			}
		}

		// Long-Term and Short-Term bond accounts linked
		// Handled the same
		else if (accType == 2) {
			if (amount <= finalBalances[accType]) {
				finalBalances[accType] -= amount;
			}
			else if (amount <= (finalBalances[accType] + finalBalances[3])) {
				int temp = amount - finalBalances[accType];
				finalBalances[accType] = 0;
				finalBalances[3] -= temp;
			}
			else {
				success = false;		// withdraw faild
				cout << left << "Withdrawal not performed on Prime Money Market for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			}
		}

		// Long-Term and Short-Term bond accounts linked
		// Handled the same
		else {
			if (amount <= finalBalances[accType]) {
				finalBalances[accType] -= amount;
			}
			else if (amount <= (finalBalances[accType] + finalBalances[2])) {
				int temp = amount - finalBalances[accType];
				finalBalances[accType] = 0;
				finalBalances[2] -= temp;
			}
			else {
				success = false;		// withdraw faild
				cout << left << "Withdrawal not performed on Prime Money Market for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			}
		}
	}

	// Withdrawing money from accounts 4 through 9
	else {

		// Do not perform if not enough money in the account
		if (amount > finalBalances[accType]) {
			success = false;		// withdraw failed
			switch (accType) {
			case 4:
				cout << left << "Withdrawal not performed on 500 Index Fund for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			
			case 5:
				cout << left << "Withdrawal not performed on Capital Value Fund for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			
			case 6:
				cout << left << "Withdrawal not performed on Growth Equity Fund for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			
			case 7:
				cout << left << "Withdrawal not performed on Growth Index Fund for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			
			case 8:
				cout << left << "Withdrawal not performed on Value Fund for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			
			case 9:
				cout << left << "Withdrawal not performed on Value Stock Index for client " 
					 << accountNum << ";" << endl << right << setw(23) 
					 << "insufficient funds" << endl << endl;
			}
		}

		// If there is enough, make the withdrawal
		else {
			finalBalances[accType] -= amount;
		}
	}
	return success;
}

//------------------------------------------------------------------------------
// Output
// Formats the account to display an account

ostream& operator<<(ostream& output, const Account& A) { 
   output << left << setw(6) << A.accountNum << A.firstName << " " 
		  << A.lastName << endl << setw(18) << "Initial Balances:";
   for (int i = 0; i < 10; i++) {
	   output << right << setw(6) << A.startingBalances[i];
   }
   output << endl << left << setw(18) << "Final Balances";
   for (int i = 0; i < 10; i++) {
	   output << right << setw(6) << A.finalBalances[i];
   }
   output << endl;
   return output;
}
