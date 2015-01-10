#ifndef MANAGER_H
#define MANAGER_H
#include <queue>
#include "movie.h"
#include "movieClassic.h"
#include "movieComedy.h"
#include "movieDrama.h"
#include "transaction.h"
#include "transactionB.h"
#include "transactionR.h"
#include "transactionH.h"
#include "transactionS.h"
#include "customer.h"
#include "BSTreeMovies.h"
using namespace std;

const int MAXHASH = 26;			// # of characters in alphabet
const int MAXID = 10000;		// max id is 9999

class Manager {

public:
	// constructor takes 3 input files
	Manager(ifstream&, ifstream&, ifstream&);	

	~Manager();								// destructor
	int hash(char);							// has function
	void buildMovieInventory(ifstream&);	// builds movie collections
	void buildCustomerTable(ifstream&);		// builds customer hash table
	void buildTransactionQueue(ifstream&);	// build the queue for transactions
	void processTransactions();				// process transactions
	Movie* createMovie(char);
	Transaction* createTransaction(char);

private:
	Movie* movieFactory[MAXHASH];			// movie factory
	Transaction* transFactory[MAXHASH];		// transaction factory
	BSTreeMovies movieInventory[MAXHASH];	// movie collection, 1genre = 1tree
	Customer* customerTable[MAXID];			// customer hash table
	queue<Transaction*> transactionList;	// transaction queue

	// trees store in the movie hash table
	BSTreeMovies classics;
	BSTreeMovies comedies;
	BSTreeMovies dramas;
};

#endif
