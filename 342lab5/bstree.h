#ifndef BSTREE_H
#define BSTREE_H
#include "account.h"
using namespace std;


class BSTree { 

public:
	BSTree();					// constructor
	~BSTree();					// destructor

	// Insert object into the tree, parameter holds pointer to object to insert 
	bool insert(Account*);	

	// Retrieve object, first parameter is object to retrieve 
	// Second parameter holds pointer to found object, NULL if not found 
	bool retrieve(const Account& , Account*&)const; 

	void display() const;		// displays the contents of a tree to cout 
	void makeEmpty();			// empties the current tree 
	bool isEmpty() const;		// returns true if tree is empty 

private: 
	struct Node{				// glue that holds data properly 
		Account* data; 
		Node* right;
		Node* left;
	}; 
	Node* root;					// root of the tree 
	
	// recursive helpers
	void displayHelper(Node*) const;
	void makeEmptyHelper(Node*);
	void retrieveHelper(Node*, bool&, const Account&, Account*&) const;
};

#endif
