#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int TITLEMAXLENGTH2 = 21;
const int DIRMAX = 15;

class Movie {
	
	// output
	friend ostream& operator<<(ostream&, const Movie&);

public:
	Movie();				// constructor
	virtual ~Movie();		// destructor

	virtual Movie* create() = 0;					// returns a new Movie
	virtual bool setData(ifstream&) = 0;			// sets data from file
	virtual void print(ostream& out) const = 0;		// output helper
	virtual void borrowMovie();						// -- movie count
	virtual void returnMovie();						// ++ movie count

	virtual int getCount() const;					// return count
	virtual string getTitle() const;				// return title
	virtual string getDirector() const;				// return director
	virtual int getYear() const;					// return year

	virtual void setDir(string);					// sets director
	virtual void setTitle(string);					// sets title
	virtual void setYear(int);						// sets year

	// comparison operators
	virtual bool operator<(const Movie&) const = 0;
	virtual bool operator>(const Movie&) const = 0;
	virtual bool operator==(const Movie&) const = 0;
	virtual bool operator!=(const Movie&) const = 0;

protected:

	// these are data members that ALL movies have
	char genre;
	string director;
	string title;
	int year;
	int count;
};

#endif
