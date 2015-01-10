#include "customer.h"

//---------------------------------------------------------------------------
// constructor
Customer::Customer() {

}

//---------------------------------------------------------------------------
// destructor
Customer::~Customer() {
	
}

//---------------------------------------------------------------------------
// sets data from file
bool Customer::setData(ifstream& infile) {
	infile >> id >> last >> first;
	return id < MAXCUSTOMERID;
}

//---------------------------------------------------------------------------
// return customer id
int Customer::getID() {
	return id;
}

//---------------------------------------------------------------------------
// print the customer's history
void Customer::print(BSTreeMovies& classics, 
					 BSTreeMovies& comedies, BSTreeMovies& dramas) {
	cout << "  *** Customer ID = " << id << "  " 
		 << first << " " << last << endl;
	Transaction* ptr;
	int size = historyList.size();

	// walk through transaction history queue
	for (int i = 0; i < size; i++) {
		
		// retrieve a transaction from the history
		ptr = historyList.front();
		historyList.pop();
		historyList.push(ptr);
		
		// borrow transaction
		if (ptr->getType() == 'B') {

			// cast to a borrow transaction
			TransactionB* borrow = static_cast<TransactionB*>(ptr);
			Movie* findthis;
			Movie* borrowedMovie;

			// classic movie
			if (borrow->getGenre() == 'C') {

				// create dummy classic and find real movie in the collection
				findthis  = borrow->returnClassic();		
				classics.retrieve(*findthis, borrowedMovie);
			}

			// drama movie
			else if (borrow->getGenre() == 'D') {

				// create dummy drama and find real movie in collection
				findthis = borrow->returnDrama();
				dramas.retrieve(*findthis, borrowedMovie);
			}

			// comedy movie
			else {

				// create dummy comedy and find real movie in collection
				findthis = borrow->returnComedy();
				comedies.retrieve(*findthis, borrowedMovie);
			}

			// print to cout
			cout << "DVD  Borrow  ";
			cout << left << setw(23) 
				 << borrowedMovie->getTitle().substr(0, TITLEMAXLENGTH)
				 << setw(17) << borrowedMovie->getDirector() 
				 << setw(5) << left << borrowedMovie->getYear();

			// extra printing for classic
			if (borrow->getGenre() == 'C') {
				MovieClassic* clas = static_cast<MovieClassic*>(borrowedMovie);
				cout << right << setw(2) << clas->getMonth() << "  "	
					 << left << clas->getActor() << endl;
			}
			else {
				cout << endl;
			}
		}

		// return transaction
		else {

			// cast to a return transaction
			TransactionR* returned = static_cast<TransactionR*>(ptr);
			Movie* findthis;
			Movie* returnedMovie;

			// classic movie
			if (returned->getGenre() == 'C') {

				// create dummy classic and find real movie in collection
				findthis  = returned->returnClassic();
				classics.retrieve(*findthis, returnedMovie);
			}

			// drama movie
			else if (returned->getGenre() == 'D') {

				// create dummy drama and find real movie in collection
				findthis = returned->returnDrama();
				dramas.retrieve(*findthis, returnedMovie);
			}

			// comedy movie
			else {

				// create dummy comedy and find real movie in collection
				findthis = returned->returnComedy();
				comedies.retrieve(*findthis, returnedMovie);
			}

			// print to cout
			cout << "DVD  Return  ";
			cout << left << setw(23) 
				 << returnedMovie->getTitle().substr(0, TITLEMAXLENGTH)
				 << setw(17) << returnedMovie->getDirector() 
				 << setw(5) << left << returnedMovie->getYear();

			// extra printing for classic
			if (returned->getGenre() == 'C') {
				MovieClassic* clas = static_cast<MovieClassic*>(returnedMovie);
				cout << right << setw(2) << clas->getMonth() << "  "	
					 << left << clas->getActor() << endl;
			}
			else {
				cout << endl;
			}
		}
	}
	cout << endl;
}

//---------------------------------------------------------------------------
// add to a customer's history
void Customer::addToHist(Transaction* T) {
	TransactionB* borrow = static_cast<TransactionB*>(T);
	historyList.push(T);
}
