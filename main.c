/* ********************************************************************
 * Purpose : main file where game starts :
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "structs.h"
 #include "linkedlist.h"
 #include "log.h"
 #include "main.h"
 #include "fileIO.h"
 #include "map.h"
 #include "macros.h"
 #include "playerMove.h"
 #include "laser.h"


int main(int argc, char* argv[]) 
{
	/* Variables declaration : */
	char* inFilename	= NULL;
	char* outFilename	= NULL;
	char usrInput		= '\0';
	int numMirrors		= 0;
	int isGameOver 		= FALSE;
	char** mapArray		= NULL;
	
	
	Tank* pla 		= NULL;
	Tank* ene 		= NULL;
	Map* map 		= NULL;
	Laser* las 		= NULL;
	Mirrors* mir 		= NULL;
	MapData* mapData	= NULL;
	LinkedList* list	= NULL;
	
	
	/* Create tanks, laser, map structs : */	
	map = (Map*) malloc (sizeof(Map));
	pla = (Tank*) malloc (sizeof(Tank));
	ene = (Tank*) malloc (sizeof(Tank));
	las = (Laser*) malloc (sizeof(Laser));
	mapData = (MapData*) malloc (sizeof(MapData));
	
	
	/* Assign structs default values : */
	map->row	= 0;
	map->col	= 0;
	pla->row 	= 0;
	pla->col 	= 0;
	pla->dir 	= '\0';	
	ene->row 	= 0;
	ene->col 	= 0;
	ene->dir 	= '\0';
	las->row	= 0;
	las->col	= 0;
	ene->dir 	= '\0';

	
	/* CHECK: is the number of arguments correct? */
	if(argc == 3)
	{
		/* Read filenames : */
		inFilename  = argv[1];
		outFilename = argv[2];
		
		
		/* Count number of mirrors : */
		numMirrors = countNumMirrors(inFilename);
		
		
		/* Create mirror struct array : */
		mir = (Mirrors*) malloc ( sizeof(Mirrors) * numMirrors );
		
		
		/* Read and transfer file contents to stucts : */
		readFile(inFilename, map, pla, ene, mir);

			
		/* CHECK - Are inputs valid? */
		if( checkInputs(map, pla, ene, mir) == TRUE)
		{
			
			/* Create 2D map malloc Array : */
			mapArray = createMapArray(map);
			
			
			/* Create linkedlist for logging : */
			list = createLinkedList();
			
			
			/* Setup logData for logging purposes : */
			mapData->mapArray = mapArray;
			mapData->map      = map;
			
			
			while(isGameOver == FALSE)
			{

				switch(usrInput)
				{
					case 'a':
						/* Move or face player LEFT */
						moveLeft(map, pla, ene, mir, numMirrors);
					break;
						
					case 'd':
						/* Move or face player RIGHT */
						moveRight(map, pla, ene, mir, numMirrors);;				
					break;

					case 'w':
						/* Move or face player UP */
						moveUp(map, pla, ene, mir, numMirrors);					
					break;

					case 's':
						/* Move or face player DOWN */
						moveDown(map, pla, ene, mir, numMirrors);				
					break;

					case 'f':				
						/* Fire player's laser : */
						relocateLaser(las, pla);

						/* Animate player's laser pulse : */
						animateLaser(&isGameOver, las, mir, numMirrors, pla, ene, mapData, list);
					break;

					case 'l':				
						/* Save log of game progress : */
						writeFile(outFilename, list);					
					break;
				}


				/* CHECK - is player is in front of enemy : */
				if(isDetected(ene, map, pla) == TRUE)
				{
					/* Reset laser position : */
					relocateLaser(las, ene);

					/* Animate enemy's laser pulse : */
					animateLaser(&isGameOver, las, mir, numMirrors, ene, pla, mapData, list);
				}
				
				
				/* CHECK - is game still running? : */
				if(isGameOver == FALSE)
				{		
					/* Update 2D map malloc Array : */
					generateMap(mapArray, map);
					generateMirrors(mapArray, mir, numMirrors);
					mapArray[pla->row][pla->col] = getTankAvatar(pla->dir);
					mapArray[ene->row][ene->col] = getTankAvatar(ene->dir);

					/* Display 2D map malloc Array : */
					system("clear"); 
					displayGameBoard(mapData, list);

					/* Display Instructions : */
					dispInstructions();
					
					/* Request user input : */
					scanf (" %c", &usrInput);
				}

			}
			
			/* Free map malloc : */
			deleteMap(mapArray, map->row );
		}		


		/* Write linked list content to file : */
		writeFile(outFilename, list);		
		

		/* Free all linkedlist mallocs used :*/
		freeLinkedList(list, &freeData);


		/* Free logData : */
		free(mapData);
		
		
		/* CHECK - which tank was destroyed? : */
		if(pla->dir == 'X')
		{
			printf("You lose! \n");
		}
		else if(ene->dir == 'X')
		{
			printf("You win! \n");
		}
		else
		{
			printf("??? \n");
		}
		
	}
	
	else
	{
		printf("Error: Not enough or too many arguments!\n");
	}
	
	/* Free struct mallocs : */
	free(pla);
	free(ene);
	free(map);
	free(las);	
	free(mir);
	
	return 0;
}


/* DESCRIPTION :    check whether inputs are valid... */
int checkInputs(Map* map, Tank* pla, Tank* ene, Mirrors* mir)
{
	int isValid = FALSE;

	/* CHECK - is the map size within the limits? : */
	if(BETWEEN(5, 25, map->row) == TRUE && BETWEEN(5, 25, map->col) == TRUE )
	{
		/* CHECK - are the tanks location within the map limits? : */
		if(BETWEEN(1, (map->row)-2 , pla->row) == TRUE && BETWEEN(1, (map->col)-2 , pla->col) == TRUE 
		&& BETWEEN(1, (map->row)-2 , ene->row) == TRUE && BETWEEN(1, (map->col)-2 , ene->col) == TRUE )
		{
			isValid = TRUE;
		}
		else
		{
			printf("Error: Tank location out of map boundries! \n");
		}
	}
	else
	{
		printf("Error: Map size should be between 5 and 25! (inclusive)\n");
	}	

	return isValid;
}


/* DESCRIPTION :    Print instructions to player... */
void dispInstructions()
{
	printf("w to go/face up\n");
	printf("s to go/face down\n");
	printf("a to go/face left\n");
	printf("d to go/face right\n");
	printf("f to shoot laser\n");
	printf("l to save the log\n");
	printf("action:");
}

