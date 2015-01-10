#ifndef MOVIECOMEDY_H
#define MOVIECOMEDY_H
#include "movie.h"

class MovieComedy : public Movie {

public:
	MovieComedy();								// constructor
	virtual Movie* create();					// creates new Drama
	virtual bool setData(ifstream&);			// sets data from file
	virtual void print(ostream& out) const;		// creates output

	// comparison operators
	virtual bool operator<(const Movie&) const;
	virtual bool operator>(const Movie&) const;
	virtual bool operator==(const Movie&) const;
	virtual bool operator!=(const Movie&) const;
};

#endif
