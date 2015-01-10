#ifndef MOVIECLASSIC_H
#define MOVIECLASSIC_H
#include "movie.h"

class MovieClassic : public Movie {

public:
	MovieClassic();								// constructor
	virtual Movie* create();					// create new Classic
	virtual bool setData(ifstream&);			// sets data from file
	virtual void print(ostream& out) const;		// creates output

	// setters for classic-specific data members
	void setFirst(string);
	void setLast(string);
	void setMonth(int);

	string getActor() const;					// returns actor name
	int getMonth() const;						// returns month

	// comparison operators
	virtual bool operator<(const Movie&) const;
	virtual bool operator>(const Movie&) const;
	virtual bool operator==(const Movie&) const;
	virtual bool operator!=(const Movie&) const;

private:
	// classic-specific data members
	string actorFirst;
	string actorLast;
	int month;
};

#endif
