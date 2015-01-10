#include "movieDrama.h"

MovieDrama::MovieDrama() { }

//---------------------------------------------------------------------------
// create a new drama movie
Movie* MovieDrama::create() {
	return new MovieDrama();	
}

//---------------------------------------------------------------------------
// set data
bool MovieDrama::setData(ifstream& infile) {
	infile.get();
	getline(infile, director, ',');
	infile.get();
	getline(infile, title, ',');
	infile.get();
	infile >> year;
	count = 10;
	genre = 'D';
	return true;
}

//---------------------------------------------------------------------------
// print
void MovieDrama::print(ostream& out) const {
	out << right << setw(3) << count << "  "
		<< setw(2) << (10-count) << "   " 
		<< setw(23) << left
		<< title.substr(0, TITLEMAXLENGTH2)
		<< setw(17) << director.substr(0, DIRMAX)
		<< setw(5) << year;
}

//---------------------------------------------------------------------------
// equality operator
bool MovieDrama::operator==(const Movie& aMovie) const {
	const MovieDrama& drama = static_cast<const MovieDrama&>(aMovie);
	return (director == drama.director && title == drama.title);
}

//---------------------------------------------------------------------------
// inequality operator
bool MovieDrama::operator!=(const Movie& aMovie) const {
	const MovieDrama& drama = static_cast<const MovieDrama&>(aMovie);
	return !(director == drama.director && title == drama.title);
}

//---------------------------------------------------------------------------
// comparison
bool MovieDrama::operator<(const Movie& aMovie) const {
	const MovieDrama& drama = static_cast<const MovieDrama&>(aMovie);
	if (director != drama.director) {
		return director < drama.director;
	}
	else {
		return title < drama.title;
	}
}

//---------------------------------------------------------------------------
// comparison
bool MovieDrama::operator>(const Movie& aMovie) const {
	const MovieDrama& drama = static_cast<const MovieDrama&>(aMovie);
	if (director != drama.director) {
		return director > drama.director;
	}
	else {
		return title > drama.title;
	}
}

