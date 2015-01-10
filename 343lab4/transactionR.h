#ifndef TRANSACTIONR_H
#define TRANSACTIONR_H
#include "transaction.h"
#include "movieClassic.h"
#include "movieDrama.h"
#include "movieComedy.h"

class TransactionR : public Transaction {

public:
	virtual Transaction* create();			// creates a return transaction
	virtual void setData(ifstream&);		// sets data from file

	// creates specific types of movies from file (helpers setData(ifstream&);)
	void setClassic(ifstream&);
	void setComedy(ifstream&);
	void setDrama(ifstream&);

	// print functions
	void print() const;
	void printClassic() const;

	// returns values for look ups
	char getGenre() const;
	int getID() const;
	char getFormat() const;
	int getYear() const;
	int getMonth() const;
	string getActor() const;
	string getTitle() const;
	string getDirector() const;

	// returns dummy movie for searching
	virtual Movie* returnClassic();
	virtual Movie* returnDrama();
	virtual Movie* returnComedy();

protected:
	// data members are specific to only borrow and return transactions
	char format;
	int customerID;
	char genre;
	string title;
	string director;
	int month;
	int year;
	string actorFirst;
	string actorLast;
};

#endif
