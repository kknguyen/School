#include "movieClassic.h"

MovieClassic::MovieClassic() { }

//---------------------------------------------------------------------------
// create a classic movie
Movie* MovieClassic::create() {
	return new MovieClassic();	
}

//---------------------------------------------------------------------------
// set data
bool MovieClassic::setData(ifstream& infile) {

	infile.get();						// get blank
	getline(infile, director, ',');		// read up to comma
	infile.get();						// get blank
	getline(infile, title, ',');		// read up to comma
	infile.get();
	infile >> actorFirst >> actorLast;
	infile >> month >> year;
	count = 10;
	genre = 'C';
	return true;
}

//---------------------------------------------------------------------------
// set output
void MovieClassic::print(ostream& out) const {
	out << right << setw(3) << count << "  "
		<< setw(2) << (10-count) << "   " 
		<< setw(23) << left
		<< title.substr(0, TITLEMAXLENGTH2)
		<< setw(17) << director.substr(0, DIRMAX)
		<< setw(5) << year
		<< setw(2) << right << month
		<< "  " << actorFirst << " " << actorLast;
}

//---------------------------------------------------------------------------
// equality operator compares the members used for sorting
bool MovieClassic::operator==(const Movie& aMovie) const {
	const MovieClassic& classic = static_cast<const MovieClassic&>(aMovie);
	return (year == classic.year && month == classic.month &&
		   actorFirst == classic.actorFirst && actorLast == classic.actorLast);
}

//---------------------------------------------------------------------------
// inequality
bool MovieClassic::operator!=(const Movie& aMovie) const {
	const MovieClassic& classic = static_cast<const MovieClassic&>(aMovie);
	return !(year == classic.year && month == classic.month &&
		   actorFirst == classic.actorFirst && actorLast == classic.actorLast);
}

//---------------------------------------------------------------------------
// operator< compares data members based on sorting
bool MovieClassic::operator<(const Movie& aMovie) const {
	const MovieClassic& classic = static_cast<const MovieClassic&>(aMovie);
	if (year != classic.year) {
		return year < classic.year;
	}
	else if (month != classic.month) {
		return month < classic.month;
	}
	else if (actorFirst != classic.actorFirst) {
		return actorFirst < classic.actorFirst;
	}
	else {
		return actorLast < classic.actorLast;
	}
}

//---------------------------------------------------------------------------
// operator > compares data members used for sorting
bool MovieClassic::operator>(const Movie& aMovie) const {
	const MovieClassic& classic = static_cast<const MovieClassic&>(aMovie);
	if (year != classic.year) {
		return year > classic.year;
	}
	else if (month != classic.month) {
		return month > classic.month;
	}
	else if (actorFirst != classic.actorFirst) {
		return actorFirst > classic.actorFirst;
	}
	else {
		return actorLast > classic.actorLast;
	}
}

//---------------------------------------------------------------------------
// set actor first name
void MovieClassic::setFirst(string name) {
	actorFirst = name;
}

//---------------------------------------------------------------------------
// set actor last name
void MovieClassic::setLast(string name) {
	actorLast = name;
}

//---------------------------------------------------------------------------
// set month of movie
void MovieClassic::setMonth(int num) {
	month = num;
}

//---------------------------------------------------------------------------
// return actor, specific to classics
string MovieClassic::getActor() const {
	return actorFirst + " " + actorLast;
}

//---------------------------------------------------------------------------
// return month, specific to classics
int MovieClassic::getMonth() const {
	return month;
}
