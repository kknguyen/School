#ifndef TRANSACTION
#define TRANSACTION
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Transaction {

	// Output
	friend ostream& operator<<(ostream&, const Transaction&);

public:
	Transaction();									// constructor?
	bool setData(ifstream&);						// set data from file
	Transaction& operator=(const Transaction&);		// assignment op

	// Comparison Operators
	bool operator==(const Transaction&) const;
	bool operator!=(const Transaction&) const;

	// Getter fuctions
	char getTransType() const;
	int getAccType() const;
	int getAccNum() const;
	int getAmount() const;
	int getTargetAcc() const;
	int getTargetAccType() const;

	void accTypeName(int) const;		// prints out the account type name

private:
	char transType;						// transaction type
	int accType;						// account type
	int accountNum;						// account ID
	int amount;							// $ deposit/withdraw/move
	int targetAcc;						// target account ID
	int targetAccType;					// target account type
};

#endif
