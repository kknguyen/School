#ifndef MOVIEDRAMA_H
#define MOVIEDRAMA_H
#include "movie.h"

class MovieDrama : public Movie {

public:
	MovieDrama();								// constructor
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
