#include "manager.h"

int main() {

	// set data files to variables
	ifstream infile("data4movies.txt"), infile2("data4customers.txt"),
			 infile3("data4commands.txt");

	// create instance of a Manager
	Manager movieStore(infile, infile2, infile3);

	return 0;
}
