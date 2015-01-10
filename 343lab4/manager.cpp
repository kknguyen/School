#include "manager.h"

//---------------------------------------------------------------------------
// constructor
// reads in 3 files for the creation of collections and processes
Manager::Manager(ifstream& file, ifstream& file2, ifstream& file3) {

	// initialize movie factory
	for (int i = 0; i < MAXHASH; i++) {
		movieFactory[i] = NULL;
	}

	// initialize transaction factory
	for (int i = 0; i < MAXHASH; i++) {
		transFactory[i] = NULL;
	}

	// empty tree memories
	classics.makeEmpty();
	comedies.makeEmpty();
	dramas.makeEmpty();

	// set the initial genres
	movieFactory[hash('C')] = new MovieClassic();
	movieInventory[hash('C')] = classics;
	movieFactory[hash('D')] = new MovieDrama();
	movieInventory[hash('D')] = dramas;
	movieFactory[hash('F')] = new MovieComedy();
	movieInventory[hash('F')] = comedies;

	// set transaction/action types
	transFactory[hash('B')] = new TransactionB();
	transFactory[hash('R')] = new TransactionR();
	transFactory[hash('H')] = new TransactionH();
	transFactory[hash('S')] = new TransactionS();

	buildMovieInventory(file);		// create inventory from data file
	buildCustomerTable(file2);		// create client collection from data file
	buildTransactionQueue(file3);	// create collection of commands
	processTransactions();			// process the transaction
	
}

//---------------------------------------------------------------------------
// destructor
Manager::~Manager() {

	// deallocate movie factory
	Movie* ptr;
	ptr = movieFactory[hash('C')];
	delete ptr;
	movieFactory[hash('C')] = NULL;
	ptr = movieFactory[hash('D')];
	delete ptr;
	movieFactory[hash('D')] = NULL;
	ptr = movieFactory[hash('F')];
	delete ptr;
	movieFactory[hash('F')] = NULL;
	ptr = NULL;

	// deallocate transaction factory
	Transaction* ptr2;
	ptr2 = transFactory[hash('B')];
	delete ptr2;
	transFactory[hash('B')] = NULL;
	ptr2 = transFactory[hash('R')];
	delete ptr2;
	transFactory[hash('R')] = NULL;
	ptr2 = transFactory[hash('H')];
	delete ptr2;
	transFactory[hash('H')] = NULL;
	ptr2 = transFactory[hash('S')];
	delete ptr2;
	transFactory[hash('S')] = NULL;
	ptr2 = NULL;

	// delete client information
	for (int i = 0; i < MAXID; i++) {
		delete customerTable[i];
		customerTable[i] = NULL;
	}

	// clear command queue
	Transaction* ptr3;
	int size = transactionList.size();
	for (int i = 0; i < size ; i++) {
		ptr3 = transactionList.front();
		delete ptr3;
		transactionList.pop();
	}
}


//---------------------------------------------------------------------------
// creates a movie object with hash function
Movie* Manager::createMovie(char c) {
	int hashval = hash(c);
	return movieFactory[hashval]->create();
}

//---------------------------------------------------------------------------
// creates a transaction object with hash function
Transaction* Manager::createTransaction(char c) {
	int hashval = hash(c);
	return transFactory[hashval]->create();
}

//---------------------------------------------------------------------------
// build movie collection
void Manager::buildMovieInventory(ifstream& infile) {
	Movie* ptr;
	char movieCode;
	bool successfulRead;
	bool success;
	for (;;) {

		// read the first character of the line which represents the genre
		infile >> movieCode;
		if (movieFactory[hash(movieCode)] == NULL) {

			// if not a valid type, assume classic format
			ptr = createMovie('C');
		}
		else {

			// if valid, create the movie type
			ptr = createMovie(movieCode);
		}
		ptr->setData(infile);

		// successful read means comedy, drama, or classic is read
		if ((movieCode == 'F') | (movieCode == 'D') | (movieCode == 'C')) {
			successfulRead = true;
		}

		// unsuccessful read + error output
		else {
			cout << "[AddtoInventoryError]: Genre " 
				 << movieCode << " invalid" << endl << endl;
			successfulRead = false;
		}

		// end of file -> delete memory and break
		if (infile.eof()) {
			delete ptr;
			break;
		}

		// if sucessful, insert to the corresponding movie tree
		if (successfulRead) {
			if (movieCode == 'F') {

				// already in tree, don't add
				if (comedies.isInTree(ptr)) {
					cout << "[AddtoInventoryError]: Found duplicate movie" 
						 << endl << endl;
				}
				else {
					success = comedies.insert(ptr);
				}
			}
			else if (movieCode == 'C') {

				// already in tree, don't add
				if (classics.isInTree(ptr)) {
					cout << "[AddtoInventoryError]: Found duplicate movie" 
						 << endl << endl;
				}
				else {
					success = classics.insert(ptr);
				}
			}
			else {

				// already in tree, don't add
				if (dramas.isInTree(ptr)) {
					cout << "[AddtoInventoryError]: Found duplicate movie" 
						 << endl << endl;
				}
				else {
					success = dramas.insert(ptr);
				}
			}
		}
		
		// if unsuccessful, delete memory
		else {
			delete ptr;
		}

		// if insert fails, no memory is left; break out of loop
		if (!success) {
			break;
		}
	}
}

//---------------------------------------------------------------------------
// build customer hash table
void Manager::buildCustomerTable(ifstream& infile) {
	Customer* ptr;
	bool successfulRead;

	// initialize data
	for (int i = 0; i < MAXID; i++) {
		customerTable[i] = NULL;
	}
	for (;;) {
		ptr = new Customer();
		successfulRead = ptr->setData(infile);		// sets data
		if (infile.eof()) {
			delete ptr;
			break;
		}

		// if successfull, add to the hash table; ID is used for hash
		if (successfulRead) {
			customerTable[ptr->getID()] = ptr;
		}
		
		// if unsuccessfull, delete memory
		else {
			delete ptr;
		}
	}
}

//---------------------------------------------------------------------------
// build queue of transactions
void Manager::buildTransactionQueue(ifstream& infile) {
	Transaction* ptr = NULL;
	char type;
	string badData;
	for (;;) {

		// read in type of transaction
		infile >> type;

		// show action, set data
		if (type == 'S') {
			ptr = createTransaction('S');
			ptr->setData(infile);
		}

		// history action, set data
		else if (type == 'H') {
			ptr = createTransaction('H');
			ptr->setData(infile);
		}

		// borrow transaction, set data
		else if (type == 'B') {
			ptr = createTransaction('B');
			ptr->setData(infile);
		}

		// return transaction, set data
		else if (type == 'R') {
			ptr = createTransaction('R');
			ptr->setData(infile);
		}

		// bad transaction type, print error
		else {
			getline(infile, badData);
			cout << "[TransactionError]: Transaction type " << type 
				 << " indvalid" << endl << endl;
		}
		
		// break out if end of file
		if (infile.eof()) {
			delete ptr;
			break;
		}

		// add the valid transaction to the queue for processing later
		if ((type == 'S') | (type == 'H') | (type == 'B') | (type == 'R')) {
			transactionList.push(ptr);
		}
	}
}

//---------------------------------------------------------------------------
// process transactions
// note: structure of the code is very messy with a lot of "if/else-if/else"
//       should have seperated functionality into different functions for
//       easy readability 
void Manager::processTransactions() {
	Movie* item;
	bool test = true;
	int size = transactionList.size();

	// loop though transaction queue
	for (int i = 0; i < size; i++) {
		Transaction* transPtr;
		transPtr = transactionList.front();		// handle front of the queue
		transactionList.pop();					// remove the transaction
		char transType = transPtr->getType();	// get the transaction type 
		
//--------------------------------- BORROW ------------------------------------
		if (transType == 'B') {

			// cast to a borrow transaction
			TransactionB* borrow = static_cast<TransactionB*>(transPtr);
			char genre = borrow->getGenre();

			// only DVD format is supported 
			if (borrow->getFormat() != 'D') {
				cout << "[TransactionError]: Media type " 
					 << borrow->getFormat() << " invalid" << endl << endl;
			}

			// transaction involves classic movie
			else if (genre == 'C') {

				// create dummy classic for searching
				Movie* findthis = borrow->returnClassic();

				// find movie
				bool found = classics.retrieve(*findthis, item);
				if (!found) {
					cout << "[TransactionError]: " << findthis->getTitle() 
						 << " does not exist in system" << endl << endl;
				}

				// find customer
				else {
					if (customerTable[borrow->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << borrow->getID() 
							 << " invalid" << endl << endl;
					}
					if (found) {
						if (item->getCount() > 0) {
							item->borrowMovie();	// borrow movie

							// add to customer history
							customerTable[borrow->getID()]->addToHist(borrow);
						}
						else {

							// movie not available
							cout << "[TransactionError]: " 
								 << item->getTitle() << " not available" 
								 << endl << endl;
						}
					}
				}	
				delete findthis;	
			}

			// transaction involves drama movie
			else if (genre == 'D') {

				// create dummy drama for searching
				Movie* findthis = borrow->returnDrama();

				// find movie
				bool found = dramas.retrieve(*findthis, item);
				if (!found) {
					cout << "[TransactionError]: " << findthis->getTitle() 
						 << " does not exist in system" << endl << endl;
				}

				// find customer
				else {
					if (customerTable[borrow->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << borrow->getID() 
							 << " invalid" << endl << endl;
					}
					if (found) {
						if (item->getCount() > 0) {
							item->borrowMovie();	// borrow movie
							
							// add to customer history
							customerTable[borrow->getID()]->addToHist(borrow);
						}
						else {

							// movie not available
							cout << "[TransactionError]: " 
								 << item->getTitle() << " not available" 
								 << endl << endl;
						}		
					}
				}
				delete findthis;
			}

			// transaction involves comedy movie
			else if (genre == 'F') {
				
				// return dummy comedy for searching
				Movie* findthis = borrow->returnComedy();

				// find movie
				bool found = comedies.retrieve(*findthis, item);
				if (!found) {
					cout << "[TransactionError]: " << findthis->getTitle() 
						 << " does not exist in system" << endl << endl;
				}

				// find customer
				else {
					if (customerTable[borrow->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << borrow->getID() 
							 << " invalid" << endl << endl;
					}
					if (found) {
						if (item->getCount() > 0) {
							item->borrowMovie();	// borrow movie

							// add to customer history
							customerTable[borrow->getID()]->addToHist(borrow);
						}
						else {
							
							// movie not available
							cout << "[TransactionError]: " 
								 << item->getTitle() << " not available" 
							 	 << endl << endl;
						}
					}
				}
				delete findthis;
			}

			// bad genre type
		    else {
				cout << "[TransactionError]: Genre " 
					<< genre << " invalid" << endl << endl;
			}
		}
		
//--------------------------------- RETURN ------------------------------------
		else if (transType == 'R') {
			
			// cast to a return transaction
			TransactionR* returning = static_cast<TransactionR*>(transPtr);
			char genre = returning->getGenre();

			// only DVDs supported
			if (returning->getFormat() != 'D') {
				cout << cout << "[TransactionError]: Media type " 
				     << returning->getFormat() << " invalid" << endl << endl;
			}

			// transaction involves a classic
			else if (genre == 'C') {
				Movie* findthis = returning->returnClassic();

				// find movie
				bool found = classics.retrieve(*findthis, item);
				if (found) {

					// find customer
					if (customerTable[returning->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << returning->getID() 
							 << " invalid" << endl << endl;
					}
					if (found) {
						item->returnMovie();
						int returnID = returning->getID();
						customerTable[returnID]->addToHist(returning);
					}
				}
				delete findthis;
			}

			// transaction involves a drama
			else if (genre == 'D') {
				Movie* findthis = returning->returnDrama();

				// find movie
				bool found = dramas.retrieve(*findthis, item);

				// find customer
				if (found) {
					if (customerTable[returning->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << returning->getID() 
							 << " invalid" << endl << endl;
						delete transPtr;
						transPtr = NULL;
					}

					// if found, return movie and add to customer history
					if (found) {
						item->returnMovie();
						int returnID = returning->getID();
						customerTable[returnID]->addToHist(returning);
					}
				}	
				delete findthis;
			}

			// transaction involves a comedy
			else if (genre == 'F') {
				Movie* findthis = returning->returnComedy();

				// find movie
				bool found = comedies.retrieve(*findthis, item);

				// find customer
				if (found) {
					if (customerTable[returning->getID()] == NULL) {
						found = false;
						cout << "[TransactionError]: Customer ID " 
							 << returning->getID() 
							 << " invalid" << endl << endl;
						transPtr = NULL;
					}

					// if found, return movie and add to customer history
					if (found) {
						item->returnMovie();
						int returnID = returning->getID();
						customerTable[returnID]->addToHist(returning);
					}
				}	
				delete findthis;
			}

			// if genre is not found, print error
			else {
				cout << "[TransactionError]: Genre " 
					<< genre << " invalid" << endl << endl;
				transPtr = NULL;
			}
		}

//--------------------------------- HISTORY -----------------------------------
		else if (transType == 'H') {

			// cast to a history transaction
			TransactionH* history = static_cast<TransactionH*>(transPtr);
			Customer* person = customerTable[history->getID()];

			// print
			person->print(classics, comedies, dramas);
			delete transPtr;
		}

//--------------------------------- SHOW --------------------------------------
		else if (transType == 'S') { 
			cout << "Inventory----------------------------------" 
				 << "----------------------------------" << endl
			     << " IN  OUT  TITLE                  "
				 << "DIRECTOR         YEAR MO  ACTOR" << endl
				 << "----------------------------------------------"
				 << "-------------------------------" << endl;
			cout << classics << dramas << comedies << endl;
		}
	}
}

//---------------------------------------------------------------------------
// hash function
int Manager::hash(char ch) {
	return ch-'A';
}
