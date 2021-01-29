#include <unistd.h>
#include <fcntl.h>
#include <string>
#define GROUP_PER_LINE 8 

int main( int argc, char* argv[] ) {
	int* offset = 0;
	int addOffset;
       	String contents = NULL; 	
	bool oneByteOctal = false; 
	bool cannonical = false; 
	bool skip = false; 
	for ( int i = 0; i < argc; i++ ) { // iterate through all the arguments

		// checks that arg is not a  flag before treating as file
		if ( argv[argc] != "-b" || argv[argc] != "-C" || argv[argc] != "-s" ) {
			offset = displayContents(argv[argc], offset);
		}
		else if ( argv[argc] == "-b" ) {
			oneByteOctal = true; 
		}
		else if ( argv[argc] == "-C" ) {
			cannonical = true; 
		}
		else if ( argv[argc] == "-s" ) {
			skip = true; 
		}

		if ( skip && addOffset == NULL ) { // TODO fix. Basically should calculate new offset value with -s flag 
			addOffset = argv[argc]; 
		}
		

	}
}

String addContents(char* argv[argc], int* offset) {
	
}	

void toString(char* contents, bool oneByteOctal, bool cannonical, bool skip) {


}
