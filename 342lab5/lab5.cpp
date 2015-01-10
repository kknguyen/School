using namespace std;

#include "manager.h"

int main() {

	ifstream infile("lab5data.txt"), infile2("lab5command.txt");
	Manager manager(infile, infile2);
	
	return 0;
}
