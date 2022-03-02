/* ********************************************************************
 * File    : newSleep.c
 * Date    : n/a
 * Author  : Dr. Antoni Liang
 * ----------------------------------------------------------------
 * Purpose : Pause terminal for animation purposes :
 **********************************************************************/

 #define _DEFAULT_SOURCE
 #include <time.h>
 #include "newSleep.h"

/* DESCRIPTION :    Pauses the program for a certain amount of time... */
void newSleep(float sec)
{
	struct timespec ts;
	ts.tv_sec = (int) sec;
	ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
	nanosleep(&ts,NULL);
}
