/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include "version.h"

// Finds the most recent version of the specified file and returns the time stamp suffix
char* getRecentBackup( char* name , char* path )
{
	DIR* dp;
	struct dirent* dirp;
	
	// Holds the directory containing the backups
	char dirPath[ MAXPATHLEN ];
	sprintf( dirPath , "%s/%s" , backupPath , path );
	
	if( ( dp = opendir( dirPath ) ) != NULL ) {
		
		char latest[ TIME_STAMP_LENGTH ];
		strcpy( latest , ZERO_TIME_STAMP );
		int nameLength = strlen( name );
		
		while( ( dirp = readdir( dp ) ) != NULL ) {
			if( strncmp( name , dirp->d_name , nameLength ) == 0 && strlen( dirp->d_name + nameLength ) == TIME_STAMP_LENGTH - 1 ) {
				if( strcmp( latest , dirp->d_name + nameLength ) < 0 ) {
					strcpy( latest , dirp->d_name + nameLength );
				}
			}
		}

		closedir( dp );
		
		if( strcmp( latest , ZERO_TIME_STAMP ) == 0 ) {
			return NULL;
		} else {
			char* suffix = strdup( latest );
			return suffix;
		}
	} else {
		perror( "Could not open directory" );
		exit( EXIT_FAILURE );
	}
}

// Checks if the file has changed since the most recent backup
bool checkBackup( char* name , char* path )
{
	bool result;
	
	char* suffix = getRecentBackup( name , path );
	if( suffix == NULL ) {
		return true;
	}
	
	char fullBackupPath[ MAXPATHLEN ];
	sprintf( fullBackupPath , "%s/%s/%s%s" , backupPath , path , name , suffix );
	char* backupSummary = filesummary( fullBackupPath );
	
	char fullPath[ MAXPATHLEN ];
	sprintf( fullPath , "%s/%s" , path , name );
	char* originalSummary = filesummary( fullPath );
	
	if( backupSummary == NULL || originalSummary == NULL ) {
		return true;
	}
	
	result = strcmp( backupSummary , originalSummary );
	
	free( backupSummary );
	free( originalSummary );
	free( suffix );
	
	return result;
}
