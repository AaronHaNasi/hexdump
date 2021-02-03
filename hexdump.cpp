#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
//#include <string>
#include <string.h>
#include <stdio.h>
#define GROUP_PER_LINE 8 
// system calls to be used: open, read, and close 

void toString(char* contents, bool oneByteOctal, bool cannonical, bool skip, int fileLength) {
	int offset = 0x0000000;
		
	int counter = 0; 
	for ( size_t i = 0; i < fileLength; i++ ) {
		if ( counter == 0 ) {
			printf("%07x %02x", offset, contents[i]);
		       	counter++; 	
		} else if ( counter % 2 == 0 && counter != 15) {
			printf("%02x", contents[i]); 
			counter++;
		} else if ( counter % 2 == 1 && counter != 15) { 
			printf("%02x ", contents[i]); 
			counter++; 
		} else if ( counter == 15 ) {
			printf("%02x\n", contents[i]);
			counter = 0;
		       	offset += 16;	
		}	
	}
}

int main( int argc, char* argv[] ) {
	int offset = 0;
	int* offsetP = NULL; 
	bool offsetSet = false;
	int addOffset;
//	string contents; 	
	char* fileContents; 
	bool oneByteOctal = false; 
	bool cannonical = false; 
	bool skip = false; 
	int status;
	size_t fileNameLength; 
	int fd, sz; 
	
	for ( int i = 1; i < argc; i++ ) { // iterate through all the arguments

        // checks that arg is not a  flag before treating as file
        if (strcmp(argv[i], "-b") == 0) {
            oneByteOctal = true;
        } else if (strcmp(argv[i], "-C") == 0) {
            cannonical = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            skip = true;
        } else { // if the above are not true, then it must be a file 
            if (access(argv[i], F_OK) == 0) // continue through loop if file exists
                continue;
            else {
                fprintf( stderr, "%s: file does not exist.", argv[argc]);
		
                return -1;
            }
        }

        	if (skip && !offsetSet) { // TODO fix. Basically should calculate new offset value with -s flag
            		addOffset = atoi(argv[argc]);
            		offsetSet = true;
        	}
    	}	

	// second loop to actually access files after args are all processed and files exist
	for ( int i = 1; i < argc; i++ ) {
        	if (strcmp(argv[i],"-b") == 0 ) {
			continue; 
        	} else if (strcmp(argv[i], "-C") == 0) {
			continue; 
		} else if (strcmp(argv[i], "-s") == 0) {
			continue; //TODO when this hits, it should skip a second time 
		} else if(fileContents != NULL) {

		} else { // if the above are not true, it must be a file 
			fd = open(argv[i], O_RDONLY); // open file as read only 
			off_t fileLength = lseek(fd, offset, SEEK_END); // get file size 
			lseek(fd, offset, SEEK_SET); // reset file position
			// fileContents = (char*)calloc(fileLength,sizeof(char)); 
			fileContents = (char*)calloc(fileLength, sizeof(char)); 
			// TODO figure out how to allocate fileContents properly 
			sz = read(fd, fileContents, fileLength); // read from file into fileContents	
			close(fd);
		//       	printf("%s", fileContents); 	
			toString(fileContents, oneByteOctal, cannonical, skip, fileLength); 
			
		/*	
			for( size_t j = 0; j < fileLength; j++ ) { 
				printf("%x", fileContents[j]); 
			}*/
		}
		
    	}	
	free(fileContents); 
	return 0; 
}

/*string addContents( char* argument, int* offset) {
	return "success";	
}	
*/

