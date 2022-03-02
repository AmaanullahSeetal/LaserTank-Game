/**********************************************************************
 * Purpose : Controls the map 2D malloc array :
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>

 #include "linkedlist.h"
 #include "structs.h"
 #include "map.h"
 #include "log.h"


/* DESCRIPTION :    Create map 2D malloc array... */
char** createMapArray(Map* map)
{
	int ii		= 0;	
	char** mapArray	= NULL;	

	mapArray = (char**) malloc(map->row * sizeof(char*));	
	for( ii = 0 ; ii < (map->row) ;  ii++ )
	{
		*(mapArray + ii) = (char*) malloc(map->col * sizeof(char));
	}

		
	return mapArray;		
}


/* DESCRIPTION :    Display mirrors... */
void generateMirrors(char** mapArray, Mirrors* mir, int numOfMirrors)
{
	int ii, r, c;
	char dir;

	/* Display each mirror in struct : */	
	for( ii = 0 ; ii < numOfMirrors ;  ii++ )
	{
		r = (mir[ii]).row;
		c = (mir[ii]).col;
		dir = (mir[ii]).dir;
		
		mapArray[r][c] = getMirrorAvatar(dir);
	}
	
}


/* DESCRIPTION :    Returns another ansi color each time it is called... */
char* getNextColor()
{
	static int colorIndex = 0;
	char* color[2] =  { "\033[0;31m", "\033[0;32m"};

	/* Alternate between the 2 colors */
	if(colorIndex == 0)
	{
		colorIndex = 1;
	}
	else
	{
		colorIndex = 0;
	}

	return (color[colorIndex]);
}





/* DESCRIPTION :    Free 2D array malloc memory from heap... */
void deleteMap(char** arr, int r)
{
	int ii;

	/* Free column minor arrays : */
	for(ii = 0; ii < r; ii++)
	{
		free(arr[ii]);
		arr[ii] = NULL;
	}

	/* Free row minor array : */
	free(arr);
	arr = NULL;
}


/* DESCRIPTION :    returns tank avatar to display based on the tank orientation... */
char getTankAvatar(char tankDir)
{
	char tankAvatar;

	/* Set bullet coordinates : */
	switch(tankDir)
	{
		case 'a':
			tankAvatar = '<';
		break;

		case 'd':
			tankAvatar = '>';
		break;

		case 's':
			tankAvatar = 'v';
		break;
			
		case 'w':
			tankAvatar = '^';
		break;
		
		default:
			tankAvatar = '?';
	}
	return tankAvatar;
}




/* DESCRIPTION :    returns mirror avatar to display... */
char getMirrorAvatar(char mirrDir)
{
	char mirrAvatar;

	/* Set laser coordinates : */
	switch(mirrDir)
	{
		case 'b':
			mirrAvatar = '\\';  /* ...have to add escape slash*/
		break;

		case 'f':
			mirrAvatar = '/';
		break;

		default:
			mirrAvatar = '?';
	}
	return mirrAvatar;
}

/* DESCRIPTION :    Update the 2D map malloc... */
void generateMap(char** mapArray, Map* map)
{
	int r, c;

	/* Update 2D map malloc Array : */
	for( r = 0 ; r < map->row ;  r++ )
	{
		for( c = 0 ; c < map->col ;  c++ )
		{
			/* Fill top and bottom rows with "*" : */
			if( r == 0 || r == (map->row - 1) )
			{
				mapArray[r][c] = '*';
			}
			
			else
			{
				/* Fill 1st & 2nd element in middle rows with "*" : */
				if( c == 0 || c == (map->col - 1) )
				{
					mapArray[r][c] = '*';
				}

				else
				{
					mapArray[r][c] = ' ';					
				}
			}			
		}
	}
}



/* DESCRIPTION :    Print gameboard to terminal... */
void displayGameBoard(MapData* mapData, LinkedList* list)
{
	/* Variable Declaration : */
	int r, c;
	char** arr	= mapData->mapArray;
	Map* map	= mapData->map;

	printf("\n");
	for(r = 0; r < (map->row); r++)
	{
		for(c = 0; c < (map->col); c++)
        	{	

			/* Change laser color : */
			if(arr[r][c] == '-' || arr[r][c] == '|')
			{
				printf("%s" , getNextColor());
				printf("%c" , arr[r][c]);
				printf("\033[0m");
			}    
      			else
			{
				/* Default color for others : */
				printf("%c", arr[r][c]);
			}

        	}
        	printf("\n");
	}

	/* Save map state to linkedlist : */
	addLog(mapData, list);

}
