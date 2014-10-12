/*
   CITS1002 Project 2
   2013 Name: David Blake McGrath
   Student number: 21301821
   Date: 01/11/2013
*/

#include "version.h"

void getTimeStamp()
{
	time_t rawTime;
	struct tm* localTime;

	rawTime = time( NULL );
	localTime = localtime( &rawTime );

	strftime( timeStamp , TIME_STAMP_LENGTH , "-%y%m%d.%H%M%S" , localTime );
}
