#include "movie.h"


//---------------------------------------------------------------------------
// constructor + destructor shells
Movie::Movie() { }
Movie::~Movie() { }

//---------------------------------------------------------------------------
// borrow a movie
void Movie::borrowMovie() {
	count--;
}

//---------------------------------------------------------------------------
// return a movie
void Movie::returnMovie() {
	count++;
}

//---------------------------------------------------------------------------
// return # of a specific movie in stock
int Movie::getCount() const {
	return count;
}

//---------------------------------------------------------------------------
// set director name
void Movie::setDir(string name) {
	director = name;
}

//---------------------------------------------------------------------------
// set movie title
void Movie::setTitle(string name) {
	title = name;
}

//---------------------------------------------------------------------------
// set movie year
void Movie::setYear(int num) {
	year = num;
}

//---------------------------------------------------------------------------
// return movie title
string Movie::getTitle() const {
	return title;
}

//---------------------------------------------------------------------------
// return movie director
string Movie::getDirector() const {
	return director;
}

//---------------------------------------------------------------------------
// return movie year
int Movie::getYear() const {
	return year;
}

//---------------------------------------------------------------------------
// output
ostream& operator<<(ostream & output, const Movie& a) {
	a.print(output);
	return output;
}
