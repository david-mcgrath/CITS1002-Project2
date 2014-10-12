/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include "version.h"



int fFlag = 0;
int iFlag = 0;
int rFlag = 0;
bool RFlag = false;
char* backupPath = NULL;
char timeStamp[ TIME_STAMP_LENGTH ];



int main( int argc , char** argv )
{
	int opt;
	
	getTimeStamp();

	bool argumentError = false;

	while( ( opt = getopt( argc , argv , OPTLIST ) ) != -1 ) {
		switch( opt ) {
			case 'd':
				backupPath = strdup( optarg );
				break;
			case 'f':
				fFlag++;
				break;
			case 'i':
				iFlag++;
				break;
			case 'r':
				rFlag++;
				break;
			case 'R':
				if( RFlag )
					argumentError = true;
				RFlag = true;
				break;
			default:
				argumentError = true;
				break;
		};
	}
	
	argv += optind;
	argc -= optind;



	if( backupPath == NULL ) {
		if( ( backupPath = getenv( "VERSIONDIR" ) ) == NULL ) {
			argumentError = true;
		}
	}

	if( fFlag + iFlag + rFlag != 1 ) {
		argumentError = true;
	}

	if( argumentError ) {
		fprintf( stderr , "Invalid arguments\n" );	// ADD MORE TO ERROR
		exit( EXIT_FAILURE );
	}
	
	
	
	makeBackupDirectory();
	
	
	
	// Defaults to ./ directory if namelist is empty (and -r was not used)
	if( argc == 0 && !rFlag ) {
		backup( "./" , "" , true );
	}
	
	// Iterates through name / file list
	for( int i = 0 ; i < argc ; i++ ) {
		
		if( fFlag || iFlag ) {
			backup( argv[ i ] , "" , true );
		} else if( rFlag ) {
			// Splits path from filename and calls recovery function
			char* path = argv[ i ];
			char* name = strrchr( argv[ i ] , '/' );
			if( name != NULL ) {
				*name = 0;
				name++;
				recover( name , path );
			} else {
				name = path;
				recover( name , "" );
			}
		}
	}

	exit( EXIT_SUCCESS );
}
