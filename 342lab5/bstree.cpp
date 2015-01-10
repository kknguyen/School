#include "bstree.h"

//------------------------------------------------------------------------------
// Constructor

BSTree::BSTree() {
	root = NULL;
}

//------------------------------------------------------------------------------
// Destructor

BSTree::~BSTree() {
	if (root != NULL) {
		makeEmpty();
	}
}

//------------------------------------------------------------------------------
// insert
// Insert an account into the tree

bool BSTree::insert(Account* dataptr) {
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

      // If item is less than current item, insert in left subtree,
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

//------------------------------------------------------------------------------
// retrieve
// Retrieves an account and saves the location in a pointer

bool BSTree::retrieve(const Account& object, Account*& saved) const {
	bool success = false;
	retrieveHelper(root, success, object, saved);
	return success;
}

// Recursive helper
void BSTree::retrieveHelper(Node* node, bool& success, const Account& lookFor, Account*& found) const {
	
	// Base case
	if (node == NULL) {
		return;
	}

	// Recusive case
	else {
		retrieveHelper(node->left, success, lookFor, found);
		retrieveHelper(node->right, success, lookFor, found);
		if (*node->data == lookFor) {
			found = node->data;
			success = true;
		}
	}
}

//------------------------------------------------------------------------------
// display
// Display the contents of the tree

void BSTree::display() const {

	// If tree is empty, do nothing and return
	if (root == NULL) {
		return;
	}
	displayHelper(root);
}

// Recursive helper
void BSTree::displayHelper(Node* node) const {

	// Base case
	if (node == NULL) {
		return;
	}

	// Recursive case
	else {
		displayHelper(node->left);
		cout << *node->data << endl;
		displayHelper(node->right);
	}
}

//------------------------------------------------------------------------------
// makeEmpty
// Clears the tree contents

void BSTree::makeEmpty() {
	if (root != NULL) {
		makeEmptyHelper(root);
	}
}

// Recursive helper
void BSTree::makeEmptyHelper(Node* node) {

	// Base case
	if (node == NULL) {
		return;
	}

	// Recursive case
	else {
		makeEmptyHelper(node->left);
		makeEmptyHelper(node->right);
		delete node->data;				// delete account
		node->data = NULL;
		delete node;					// delete the node
		node = NULL;
	}

}

//------------------------------------------------------------------------------
// Is the tree empty?

bool BSTree::isEmpty() const {
	return root == NULL;
}
