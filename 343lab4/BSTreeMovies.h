#ifndef BSTREEMOVIES_H
#define BSTREEMOVIES_H
#include "movie.h"
#include <iostream>
using namespace std;

class BSTreeMovies {

	// output
	friend ostream& operator<<(ostream &, const BSTreeMovies &);

public:
	
	BSTreeMovies();  // constructor
	~BSTreeMovies();  // destructor
  
	bool isEmpty() const;  // true if tree is empty, otherwise false 
	void makeEmpty();  // make the tree empty so isEmpty returns true 
	bool isInTree(Movie*) const;  // is the data in tree?

	bool insert(Movie*);  // inserts nodedata into the tree

	// retrieves a node and stores it
	bool retrieve(const Movie&, Movie*&) const;


private: 

	struct Node { 
		Movie* data;  // pointer to data object 
		Node* left;  // left subtree pointer 
		Node* right;  // right subtree pointer 
	};

	Node* root;  // root of the tree 
 
	// utility functions 
	void makeEmptyHelper(Node*&);
	void retrieveHelper(Node*, bool&, const Movie&, Movie*&) const;
	void outputHelper(Node*, ostream&) const;
	void isInTreeHelper(Movie*, bool&, Node*) const;
};

#endif
