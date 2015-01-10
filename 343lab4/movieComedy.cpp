#include "movieComedy.h"

MovieComedy::MovieComedy() { }

//---------------------------------------------------------------------------
// create a comedy movie
Movie* MovieComedy::create() {
	return new MovieComedy();	
}

//---------------------------------------------------------------------------
// set data from file
bool MovieComedy::setData(ifstream& infile) {
	infile.get();							// get blank
	getline(infile, director, ',');			// read up to comma
	infile.get();							// get blank
	getline(infile, title, ',');			// read up to comma
	infile.get();
	infile >> year;
	count = 10;
	genre = 'F';
	return true;
}

//---------------------------------------------------------------------------
// set output
void MovieComedy::print(ostream& out) const {
	out << right << setw(3) << count << "  "
		<< setw(2) << (10-count) << "   " 
		<< setw(23) << left
		<< title.substr(0, TITLEMAXLENGTH2)
		<< setw(17) << director.substr(0, DIRMAX)
		<< setw(5) << year;
}

//---------------------------------------------------------------------------
// equality operator uses sorted data members
bool MovieComedy::operator==(const Movie& aMovie) const {
	const MovieComedy& comedy = static_cast<const MovieComedy&>(aMovie);
	return (title == comedy.title && year == comedy.year);
}

//---------------------------------------------------------------------------
// equality operator uses sorted data members
bool MovieComedy::operator!=(const Movie& aMovie) const {
	const MovieComedy& comedy = static_cast<const MovieComedy&>(aMovie);
	return !(title == comedy.title && year == comedy.year);
}

//---------------------------------------------------------------------------
// sorted with title then year
bool MovieComedy::operator<(const Movie& aMovie) const {
	const MovieComedy& comedy = static_cast<const MovieComedy&>(aMovie);
	if (title != comedy.title) {
		return title < comedy.title;
	}
	else {
		return year < comedy.year;
	}
}

//---------------------------------------------------------------------------
// sorted with title then year
bool MovieComedy::operator>(const Movie& aMovie) const {
	const MovieComedy& comedy = static_cast<const MovieComedy&>(aMovie);
	if (title != comedy.title) {
		return title > comedy.title;
	}
	else {
		return year > comedy.year;
	}
}
