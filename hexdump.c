#include <unistd.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
// system calls to be used: open, read, and close 

void toString(char* fileName, int oneByteOctal, int cannonical, int skip, int offset) {
	int fd, sz = 16;
	short* rawFileData = NULL;
	char* textFileData = NULL; 

	if ( oneByteOctal == 1 && cannonical == 0 ) {
		fd = open(fileName, O_RDONLY);
		while ( sz == 16 ) {
			rawFileData = (short*)calloc(8, sizeof(short)); 
			sz = read(fd, rawFileData, 16); 
			printf("%07x  ", offset); 
			for ( size_t i = 0; i < sz; i++ ) {
				printf("%03d ", rawFileData[i]);  
			}
			offset += 16; 
		}
		close(fd); 
		free(rawFileData); 	
	} else if ( oneByteOctal == 0 && cannonical == 0 ) {
		fd = open(fileName, O_RDONLY); 
		while ( sz == 16 ) {
			rawFileData = (short*)calloc(8, sizeof(short)); 
			sz = read(fd, rawFileData, 16); 
			printf("%07x  ", offset); 
			for ( size_t i = 0; i < sz / 2; i++ ) {
				printf("%04x ", rawFileData[i]); 
			}
			offset += 16; 	
		}
		close(fd);
		free(rawFileData); 
	} else if ( oneByteOctal == 0 && cannonical == 1 ) {
		fd = open(fileName, O_RDONLY); 
		while ( sz == 16 ) {
			textFileData = (char*)calloc(8, sizeof(short)); 
			sz = read(fd, textFileData, 16); 
			printf("%07x  ", offset); 
			for ( size_t i = 0; i < sz ; i++ ) {
				printf("%02x ", textFileData[i]);
				if( i == 7) 
					printf(" "); 
			}
			int counter = sz; 
			while ( counter < 16 ) {
				printf("    ");
				counter++;
			}
			offset += 16; 
			printf("|"); 
			for ( size_t i = 0; i < sz; i++ ) {
				if (isprint(textFileData[i])) {
					printf("%c", textFileData[i]); 
				} else {
					printf("."); 
				}	
			}
			printf("|\n"); 
		}
	} else {
		printf("Unknown error. Exiting"); 
	}	
}

int main( int argc, char* argv[] ) {
	int offset = 0;
	int* offsetP = NULL; 
	int offsetSet = 0;
	int addOffset;
	char* textFileContents = NULL; 
	short* rawFileContents = NULL; 
	int oneByteOctal = 0; 
	int cannonical = 0; 
	int skip = 0; 
	int status;
	size_t fileNameLength; 
//	int fd, sz = 16; 
	
	for ( int i = 1; i < argc; i++ ) { // iterate through all the arguments

        // checks that arg is not a  flag before treating as file
        if (strcmp(argv[i], "-b") == 0) {
            oneByteOctal = 1;
        } else if (strcmp(argv[i], "-C") == 0) {
            cannonical = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            skip = 1;

        } else { // if the above are not true, then it must be a file 
            if (access(argv[i], F_OK) == 0) // continue through loop if file exists
                continue;
            else {
                fprintf( stderr, "%s: file does not exist.", argv[argc]);
		
                return -1;
            }
        }

        	if (skip && offsetSet == 0) { // TODO fix. Basically should calculate new offset value with -s flag
            		addOffset = atoi(argv[argc]);
            		offsetSet = 1;
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
		} else if(rawFileContents != NULL) {

		} else { // if the above are not true, it must be a file 			
			toString(argv[i], oneByteOctal, cannonical, skip, offset);

		}
		
    	}	
	return 0; 
}

/*string addContents( char* argument, int* offset) {
	return "success";	
}	
*/

