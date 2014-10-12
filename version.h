/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/param.h>

// GLOBAL CONSTANTS
#define OPTLIST "d:firR"
#define TIME_STAMP_LENGTH 15
#define ZERO_TIME_STAMP "-000000.000000"

#ifdef __linux__
extern char* strdup( const char* );
#endif

// GLOBAL FUNCTIONS
extern void makeBackupDirectory();
extern void backup( char* , char* , bool );
extern void recover( char* , char* );
extern char* getRecentBackup( char* , char* );
extern bool checkBackup( char* , char* );
extern void getTimeStamp();

extern char* filesummary( char* );

// GLOBAL VARIABLES
extern int fFlag;
extern int iFlag;
extern int rFlag;
extern bool RFlag;
extern char* backupPath;
extern char timeStamp[ TIME_STAMP_LENGTH ];
