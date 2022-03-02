/* ********************************************************************
 * File    : laser.c
 * Date    : 03 May 2021
 * Author  : Amaanullah Seetal (id:2033 9098)
 * ----------------------------------------------------------------
 * Purpose : Handles all laser events, inclu. animations
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "linkedlist.h"
 #include "structs.h"
 #include "newSleep.h"
 #include "laser.h"
 #include "macros.h"
 #include "map.h"

/* DESCRIPTION :   animate laser pulse until it hits the map border or a tank... */
void animateLaser(int *isGameOver, Laser* las, Mirrors* mir, int numMirrors, Tank* src, Tank* des,  MapData* mapData, LinkedList* list)
{	
	int ii = 0;
	int hit = FALSE;
	char** mapArray	= (mapData->mapArray);
	Map* map	= mapData->map;
	
	/* Set laser dirn same as the src tank :  */
	(las->dir) = (src->dir);
	
	/* CHECK - is laser within map boundary : */
	while( BETWEEN( 1, (map->col)-2, las->col ) && BETWEEN( 1, (map->row)-2, las->row ) && *isGameOver == FALSE )
	{
		/* Update 2D map malloc Array  + tanks avatar : */
		generateMap(mapArray, map);
		generateMirrors(mapArray, mir, numMirrors);
		mapArray[src->row][src->col] = getTankAvatar(src->dir);
		mapArray[des->row][des->col] = getTankAvatar(des->dir);

		printf("las [%d %d]\n", las->col, las->row);
		

		/* CHECK - did laser hit destn tank? : */
		if(las->row == des->row && las->col == des->col)
		{
			/* Set player dir for win/lose! */
			des->dir = 'X';

			mapArray[las->row][las->col] = 'X';
			*isGameOver = TRUE;
		}

		/*CHECK - did laser hit src tank? : */
		else if(las->row == src->row && las->col == src->col)
		{
			/* Set player dir for win/lose! */
			src->dir = 'X';

			mapArray[las->row][las->col] = 'X';
			*isGameOver = TRUE;
		}

		else
		{
			/* CHECK - did laser hit any mirror? : */
			for( ii = 0 ; ii < numMirrors ;  ii++ )
			{
				if(mir[ii].col == (las->col)  &&  mir[ii].row == (las->row) )
				{
					hit = TRUE;
					reOrientLaser(mir[ii].dir, las);
				}
			}
			
			/* CHECK - Any mirror collision? */
			if(hit == TRUE)
			{
				/* Reset : */
				hit = FALSE;
			}
			else
			{
				mapArray[las->row][las->col] = getLaserAvatar(las->dir);
			}			
		}
		
		/* Display 2D map malloc Array : */
		system("clear"); 
		displayGameBoard(mapData, list);

		/* Pause animation : */
		newSleep(0.5);

		/* increment laser position : */
		moveLaser(las, las->dir);

	}
}


/* DESCRIPTION :    Update laser pluse position... */
void reOrientLaser(char mirDir, Laser* las)
{
	
	/* Reorient - Backslash mirror : */
	if(mirDir == 'b')
	{
		/* Set position of laser : */
		switch(las->dir)
		{
			case 'd':
				las->dir = 's';
			break;

			case 'a':
				las->dir = 'w';
			break;

			case 's':
				las->dir = 'd';
			break;
				
			case 'w':
				las->dir = 'a';
			break;			
		}
	}

	/* Reorient - forwardslash mirror : */
	if(mirDir == 'f')
	{
		/* Set position of laser : */
		switch(las->dir)
		{
			case 'd':
				las->dir = 'w';
			break;

			case 'a':
				las->dir = 's';
			break;

			case 's':
				las->dir = 'a';
			break;
				
			case 'w':
				las->dir = 'd';
			break;			
		}
	}

	
	
}


/* DESCRIPTION :    Update laser pluse position */
void moveLaser(Laser* las, char srcDir)
{
	/* Set position of laser : */
	switch(srcDir)
	{
		case 'a':
			(las->col)--;
		break;

		case 'd':
			(las->col)++;
		break;

		case 's':
			(las->row)++;
		break;
			
		case 'w':
			(las->row)--;
		break;
		
	}
}


/* DESCRIPTION :    returns laser avatar to display based on the src orientation... */
char getLaserAvatar(char srcDir)
{
	char laserAvatar;

	/* Set laser coordinates : */
	switch(srcDir)
	{
		case 'a':
			laserAvatar = '-';
		break;

		case 'd':
			laserAvatar = '-';
		break;

		case 's':
			laserAvatar = '|';
		break;
			
		case 'w':
			laserAvatar = '|';
		break;

		default:
			laserAvatar = '?';
	}
	return laserAvatar;
}



/* DESCRIPTION :    Relocate laser position to tank... */
void relocateLaser(Laser* las, Tank* tank)
{
	/* Set position of laser : */
	switch(tank->dir)
	{
		case 'a':
			las->row = tank->row;
			las->col = (tank->col) - 1;
		break;

		case 'd':
			las->row = tank->row;
			las->col = (tank->col) + 1;
		break;

		case 's':
			las->row = (tank->row) + 1;
			las->col = tank->col;
		break;
			
		case 'w':
			las->row = (tank->row) - 1;
			las->col = tank->col;
		break;
	}
}


/* DESCRIPTION :    Check if player passes in front of enemy... */
int isDetected(Tank* ene, Map* map, Tank* pla)
{
	int detected = FALSE;

	/* Is player in the same row as the enemy? */
	if(pla->row == ene->row)
	{
		/* Is player in front of enemy? */
		if( 	 ene->dir == 'a' && BETWEEN(0, ene->col, pla->col) == TRUE )
		{
			detected = TRUE;
		}

		else if( ene->dir == 'd' && BETWEEN(ene->col, map->col, pla->col) == TRUE )
		{
			detected = TRUE;
		}

		else
		{
			detected = FALSE;
		}
	}

	/* Is player in the same column as the enemy? */
	else if(pla->col == ene->col)
	{
		/* Is player in front of enemy? */
		if( 	 ene->dir == 'w' && BETWEEN(0, ene->row, pla->row) == TRUE )
		{
			detected = TRUE;
		}

		else if( ene->dir == 's' && BETWEEN(ene->row, map->row, pla->row) == TRUE )
		{
			detected = TRUE;
		}
		
		else
		{
			detected =  FALSE;
		}
	}
	else
	{
		detected = FALSE;
	}

	return detected;
		
}

