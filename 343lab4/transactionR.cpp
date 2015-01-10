#include "transactionR.h"

//---------------------------------------------------------------------------
// create new return transaction
Transaction* TransactionR::create() {
	return new TransactionR();
}

//---------------------------------------------------------------------------
// set data from file
void TransactionR::setData(ifstream& infile) {
	type = 'R';
	infile >> customerID >> format;
	infile >> genre;

	// seperate functions used to set each movie
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
// set classic movie
void TransactionR::setClassic(ifstream& infile) {
	infile >> month >> year >> actorFirst >> actorLast;
}

//---------------------------------------------------------------------------
// set comedy movie
void TransactionR::setComedy(ifstream& infile) {
	infile.get();
	getline(infile, title, ',');
	infile.get();
	infile >> year;
}

//---------------------------------------------------------------------------
// set drama movie
void TransactionR::setDrama(ifstream& infile) {
	infile.get();
	getline(infile, director, ',');
	infile.get();
	getline(infile, title, ',');
}

// for compiler
void TransactionR::print() const { }

//---------------------------------------------------------------------------
// getter functions to return data members
char TransactionR::getGenre() const {return genre;}
int TransactionR::getID() const {return customerID;}
char TransactionR::getFormat() const {return format;}
string TransactionR::getTitle() const {return title;}
string TransactionR::getDirector() const {return director;}
int TransactionR::getYear() const {return year;}
int TransactionR::getMonth() const {return month;}
string TransactionR::getActor() const {return actorFirst + " " + actorLast;}

//---------------------------------------------------------------------------
// creates dummy classic movie for searching; only uses sorting criteria
Movie* TransactionR::returnClassic() {
	MovieClassic* classic = new MovieClassic;
	classic->setYear(year);
	classic->setMonth(month);
	classic->setFirst(actorFirst);
	classic->setLast(actorLast);
	return classic;
}

//---------------------------------------------------------------------------
// creates dummy drama movie
Movie* TransactionR::returnDrama() {
	MovieDrama* drama = new MovieDrama;
	drama->setDir(director);
	drama->setTitle(title);
	return drama;
}

//---------------------------------------------------------------------------
// creates dummy comedy movie
Movie* TransactionR::returnComedy() {
	MovieComedy* comedy = new MovieComedy;
	comedy->setTitle(title);
	comedy->setYear(year);
	return comedy;
}
