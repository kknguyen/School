#include "BSTreeMovies.h"

//---------------------------------------------------------------------------
// constructor
BSTreeMovies::BSTreeMovies() {
	root = NULL;
}

//---------------------------------------------------------------------------
// destructor
BSTreeMovies::~BSTreeMovies() {
	if (root != NULL) {
		makeEmpty();
	}
}

//---------------------------------------------------------------------------
// Is the tree empty?
bool BSTreeMovies::isEmpty() const {
	return root == NULL;
}

//---------------------------------------------------------------------------
// makeEmpty
void BSTreeMovies::makeEmpty() {
	makeEmptyHelper(root);
	root = NULL;
}

// recursive helper
void BSTreeMovies::makeEmptyHelper(Node*& node) {

	// Base case
	if (node == NULL) {
		return;
	}
	// Recursive case
	else {
		makeEmptyHelper(node->left);
		makeEmptyHelper(node->right);
		delete node->data;
		node->data = NULL;
		delete node;
		node = NULL;
	}
}

//---------------------------------------------------------------------------
// insert a Movie into the tree
bool BSTreeMovies::insert(Movie* dataptr) {
   Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
		  if (*ptr->data < *current->data) {
			  if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) {             // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }
   }
   return true;
}

//---------------------------------------------------------------------------
// helper function for insert. prevents repeated string values from being
// added to the tree
bool BSTreeMovies::isInTree(Movie* test) const {
	bool found = false;
	isInTreeHelper(test, found, root);
	return found;
}

// recursive helper
void BSTreeMovies::isInTreeHelper(Movie* test, bool & found, Node* aNode) const {
	if (aNode == NULL) {
		return;
	}
	else if (*test == *aNode->data) {
		found = true;
	}
	else {
		isInTreeHelper(test, found, aNode->left);
		isInTreeHelper(test, found, aNode->right);
	}
}


//---------------------------------------------------------------------------
// retrieve a Movie object from the tree and stores into another object
bool BSTreeMovies::retrieve(const Movie& object, Movie*& saved) const {
	bool success = false;
	retrieveHelper(root, success, object, saved);
	return success;
}

// recursive helper
void BSTreeMovies::retrieveHelper(Node* node, bool& success, const 
							 Movie& lookFor, Movie*& found) const {
	// base case
	if (node == NULL) {
		return;
	}
	// recusive case
	else {
		retrieveHelper(node->left, success, lookFor, found);
		retrieveHelper(node->right, success, lookFor, found);

		// if the data is found, set the data to the Movie reference
		if (*node->data == lookFor) {
			found = node->data;
			success = true;
		}
	}
}

//---------------------------------------------------------------------------
// output
ostream& operator<<(ostream & output, const BSTreeMovies & a) {
	a.outputHelper(a.root, output);
	output;
	return output;
}

// recursive helper
void BSTreeMovies::outputHelper(Node* aNode, ostream & output) const {
	if (aNode == NULL) {
		return;
	}
	else {
		outputHelper(aNode->left, output);
		output << *aNode->data << endl;		//save data to output
		outputHelper(aNode->right, output);
	}
}
