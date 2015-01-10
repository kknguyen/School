#include "transaction.h"

//------------------------------------------------------------------------------
// Constructor?

Transaction::Transaction() {

}

//------------------------------------------------------------------------------
// setData
// Set data from a file

bool Transaction::setData(ifstream& inFile) {
	char type;			// transaction type (D/W/M/H)
	int temp;			// temporary integer for setting values
	bool success = false;
	inFile >> type;
	switch (type) {

	// Deposit
	case 'D':
		transType = type;
		inFile >> temp;
		accType = temp % 10;
		accountNum = temp / 10;
		targetAcc = -1;
		targetAccType = -1;
		inFile >> amount;
		success = true;
		break;

	// Withdraw
	case 'W':
		transType = type;
		inFile >> temp;
		accType = temp % 10;
		accountNum = temp / 10;
		targetAcc = -1;
		targetAccType = -1;
		inFile >> amount;
		success = true;
		break;

	// Move
	case 'M':
		transType = type;
		inFile >> temp;
		accType = temp % 10;
		accountNum = temp / 10;
		inFile >> amount;
		inFile >> temp;
		targetAccType = temp % 10;
		targetAcc = temp / 10;
		success = true;
		break;

	// History
	case 'H':
		transType = type;
		inFile >> accountNum;
		accType = -1;
		amount = -1;
		targetAcc = -1;
		targetAccType = -1;
		success = true;
		break;

	// Not a valid transaction
	default:
		if (type >= 'a' && type <= 'z' || type >= 'A' && type <= 'Z') {
			cout << "Unknown transaction type '" << type
			 << "' requested" << endl << endl;
		}
		transType = type;

		// Reads until the next line when given a bad transaction type
		while ((type = inFile.get()) != '\n') {
			accType = -1;
			accountNum = -1;
			amount = -1;
			targetAcc = -1;
			targetAccType = -1;
			success = false;
			break;
		}	
	}
	return success;
}

//------------------------------------------------------------------------------
// operator =
// Assignment operator

Transaction& Transaction::operator=(const Transaction& T) {
	if (&T != this) {
		transType = T.transType; 
		accType = T.accType;
		accountNum = T.accountNum;
		amount = T.amount;
		targetAcc = T.targetAcc;
		targetAccType = T.targetAccType;
	}
	return *this;
}

//------------------------------------------------------------------------------
// operator==
// Equality

bool Transaction::operator==(const Transaction& T) const {
	return transType == T.transType && accType == T.accType &&
		   accountNum == T.accountNum && amount == T.amount &&
		   targetAcc == T.targetAcc && targetAccType == T.targetAccType;
}

//------------------------------------------------------------------------------
// operator!=
// Inequality

bool Transaction::operator!=(const Transaction& T) const {
	return !(*this == T);
}

//------------------------------------------------------------------------------
// Return transaction type

char Transaction::getTransType() const { 
	return transType;
}

//------------------------------------------------------------------------------
// Return account type
int Transaction::getAccType() const { 
	return accType;
}

//------------------------------------------------------------------------------
// Return account ID

int Transaction::getAccNum() const { 
	return accountNum;
}

//------------------------------------------------------------------------------
// Return amount deposited/withdrawn/moved

int Transaction::getAmount() const { 
	return amount;
}

//------------------------------------------------------------------------------
// Return target acount ID

int Transaction::getTargetAcc() const { 
	return targetAcc;
}

//------------------------------------------------------------------------------
// Return target account type

int Transaction::getTargetAccType() const { 
	return targetAccType;
}

//------------------------------------------------------------------------------
// Prints out the name of the account type

void Transaction::accTypeName(int value) const {
	switch (value) {
	case 0:
		cout << "Money Market";
		break;
	case 1:
		cout << "Prime Money Market";
		break;
	case 2:
		cout << "Long-Term Bond";
		break;
	case 3:
		cout << "Short-Term Bond";
		break;
	case 4:
		cout << "500 Index Fund";
		break;
	case 5:
		cout << "Capital Vaue Fund";
		break;
	case 6:
		cout << "Growth Equity Fund";
		break;
	case 7:
		cout << "Growth Index Fund";
		break;
	case 8:
		cout << "Value Fund";
		break;
	case 9:
		cout << "Value Stock Index";
		break;
	default:
		cout << "Invalid type";
		break;
	}
}

//------------------------------------------------------------------------------
// operator<<
// Displays the values to output; Used for testing purposes

ostream& operator<<(ostream& output, const Transaction& T) {
	output << T.transType << endl << T.accType << endl
	       << T.accountNum << endl << T.amount << endl
		   << T.targetAcc << endl << T.targetAccType << endl; 
	return output;
}
