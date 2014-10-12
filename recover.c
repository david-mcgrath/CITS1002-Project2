/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include "version.h"

// Recovers a file given the filename and path to it within the backup directory
void recover( char* name , char* path )
{
	char backupWithSuffix[ MAXPATHLEN ];
	char* suffix = getRecentBackup( name , path );
	sprintf( backupWithSuffix , "%s%s/%s%s" , backupPath , path , name , suffix );
	
	FILE* backup = fopen( backupWithSuffix , "r" );
	if( backup == NULL ) {
		perror( "Could not open backup file" );
		exit( EXIT_FAILURE );
	}
	
	FILE* recovered = fopen( name , "w" );
	if( recovered == NULL ) {
		perror( "Could not open file for recovery" );
		exit( EXIT_FAILURE );
	}
	
	char c;
	while( ( c = fgetc( backup ) ) != EOF ) {
		fputc( c , recovered );
	}
	
	fclose( backup );
	fclose( recovered );
}
