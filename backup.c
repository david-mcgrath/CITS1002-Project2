/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include "version.h"

// Creates the initial backup directory if it does not already exist
void makeBackupDirectory()
{
	struct stat st;
	
	char path[ MAXPATHLEN ];
	sprintf( path , "%s/" , backupPath );
	int l = strlen( path );
	
	for( int i = 0 ; i < l ; i++ ) {
		if( path[ i ] == '/' ) {
			path[ i ] = 0;
			
			if( stat( path , &st ) != 0 ) {
				mkdir( path , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
			}
			
			path[ i ] = '/';
		}
	}
}

// Backs up the contents of a directory
void backupDirectory( char* name , char* path )
{
	DIR* dp;
	struct dirent* dirp;
	
	char tempPath[ MAXPATHLEN ];
	sprintf( tempPath , "%s%s/" , path , name );
	
	if( ( dp = opendir( tempPath ) ) != NULL ) {
		// Makes directory in the backup directory if it doesn't already exist
		struct stat st;
		
		char fullBackupPath[ MAXPATHLEN ];
		sprintf( fullBackupPath , "%s/%s%s" , backupPath , path , name );

		if( stat( fullBackupPath , &st ) != 0 ) {
			mkdir( fullBackupPath , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
		}
		
		// Iterates through contents of directory, backing them up
		while( ( dirp = readdir( dp ) ) != NULL ) {
			if( strcmp( dirp->d_name , "." ) && strcmp( dirp->d_name , ".." ) ) {
				backup( dirp->d_name , tempPath , false );
			}
		}
	}
}

// Backs up individual files
void backupFile( char* name , char* path )
{
	if( fFlag || ( iFlag && checkBackup( name , path ) ) ) {
		char fullBackupPath[ MAXPATHLEN ];
		sprintf( fullBackupPath , "%s/%s%s%s" , backupPath , path , name , timeStamp );
		
		char originalPath[ MAXPATHLEN ];
		sprintf( originalPath , "%s%s" , path , name );
		
		FILE* original = fopen( originalPath , "r" );
		if( original == NULL ) {
			perror( "Could not open file to be backed up" );
			exit( EXIT_FAILURE );
		}
		
		FILE* backup = fopen( fullBackupPath , "w" );
		if( backup == NULL ) {
			perror( "Could not open file to back up to" );
			exit( EXIT_FAILURE );
		}
		
		int c;
		while( ( c = fgetc( original ) ) != EOF ) {
			fputc( c , backup );
		}
		
		fclose( original );
		fclose( backup );
	}
}

void backup( char* name , char* path , bool firstRun )
{
	struct stat st;
	
	char filePath[ BUFSIZ ];
	sprintf( filePath , "%s%s" , path , name );
	
	if( stat( filePath , &st ) != 0 ) {
		perror( "File stats could not be read" );
		exit( EXIT_FAILURE );
	} else if( S_ISDIR( st.st_mode ) ) {
		if( RFlag || firstRun ) {
			backupDirectory( name , path );
		}
	} else if( S_ISREG ( st.st_mode ) ) {
		backupFile( name , path );
	}
}
