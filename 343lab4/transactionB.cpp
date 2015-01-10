#include "transactionB.h"

TransactionB::TransactionB() { }

//---------------------------------------------------------------------------
// create a new borrow transaction
Transaction* TransactionB::create() {
	return new TransactionB();
}

//---------------------------------------------------------------------------
// set datafrom file
void TransactionB::setData(ifstream& infile) {
	type = 'B';
	infile >> customerID >> format;
	infile >> genre;

	// seperate functions used to set data for specific movie genre
	if (genre == 'F') {
		setComedy(infile);
	}
	else if (genre == 'D') {
		setDrama(infile);
	}
	else {
		setClassic(infile);
	}
}

//---------------------------------------------------------------------------
// classic movie setter
void TransactionB::setClassic(ifstream& infile) {
	infile >> month >> year >> actorFirst >> actorLast;
}

//---------------------------------------------------------------------------
// comedy setter
void TransactionB::setComedy(ifstream& infile) {
	infile.get();
	getline(infile, title, ',');
	infile.get();
	infile >> year;
}

//---------------------------------------------------------------------------
// drama setter
void TransactionB::setDrama(ifstream& infile) {
	infile.get();
	getline(infile, director, ',');
	infile.get();
	getline(infile, title, ',');
}

//---------------------------------------------------------------------------
// here so program compiles
void TransactionB::print() const { }

//---------------------------------------------------------------------------
// print classic transaction
void TransactionB::printClassic() const {
	cout << title << " " << director << " " << year 
		 <<  " " << month << " " << actorFirst << " " << actorLast << endl;
}

//---------------------------------------------------------------------------
// getting functions to return data members
char TransactionB::getGenre() const { return genre; }
int TransactionB::getID() const { return customerID; }
char TransactionB::getFormat() const { return format; }
string TransactionB::getTitle() const { return title; }
string TransactionB::getDirector() const { return director; }
int TransactionB::getYear() const { return year; }
int TransactionB::getMonth() const { return month; }
string TransactionB::getActor() const { return actorFirst + " " + actorLast; }

//---------------------------------------------------------------------------
// creates dummy classic for searching; only sorted criteria used
Movie* TransactionB::returnClassic() {
	MovieClassic* classic = new MovieClassic();
	classic->setYear(year);
	classic->setMonth(month);
	classic->setFirst(actorFirst);
	classic->setLast(actorLast);
	return classic;
}

//---------------------------------------------------------------------------
// creates dummy drama for searching
Movie* TransactionB::returnDrama() {
	MovieDrama* drama = new MovieDrama();
	drama->setDir(director);
	drama->setTitle(title);
	return drama;
}

//---------------------------------------------------------------------------
// creates dummy comedy movie for searching
Movie* TransactionB::returnComedy() {
	MovieComedy* comedy = new MovieComedy();
	comedy->setTitle(title);
	comedy->setYear(year);
	return comedy;
}
