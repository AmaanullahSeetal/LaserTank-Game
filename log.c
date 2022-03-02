/* ********************************************************************
 * File    : log.c
 * Date    : 30th April 2021
 * Author  : Amaanullah Seetal (id:2033 9098)
 * ----------------------------------------------------------------
 * Purpose : Handles all logging tasks :
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "structs.h"
 #include "linkedlist.h"
 #include "log.h"
 #include "map.h"


/* DESCRIPTION : Create new log entry in linkedlist... : */
void addLog(MapData* data, LinkedList* list)
{
	int r, c;
	char** newMapArray 	= NULL;
	MapData* logData	= NULL;
	
	/* Create new map : */
	newMapArray = createMapArray(data->map);
	logData = (MapData*) malloc (sizeof(MapData));	
	
	/* Save content of current map to newMapArray : */
	for(r = 0; r < (data->map)->row; r++)
	{
		for(c = 0; c < (data->map)->col; c++)
        	{
			newMapArray[r][c] = data->mapArray[r][c];
		}
	}
	
	/* Transfer to logData : */
	logData->mapArray = newMapArray;
	logData->map      = data->map;
	
	/* Save array to linkedlist : */
	insertLast(list, logData);
	
}


/* DESCRIPTION : Generic linkedlist function to handle data freeing... : */
void freeData(void* nodeData)
{
	/* Typecast and extract data : */
	MapData* logData 	= (MapData*)nodeData;	
	char** loggedMapArray 	= logData->mapArray;
	Map* map		= logData->map;
	
	/* Free 2D map array malloc : */
	deleteMap( loggedMapArray, map->row );
	
	/* Free node malloc : */
	free(logData);
}
