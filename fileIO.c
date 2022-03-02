/* ********************************************************************
 * Purpose : Handles all file reading and writing tasks :
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "linkedlist.h"
 #include "structs.h"
 #include "fileIO.h"


/* DESCRIPTION :    Read input file content to structs... */
void readFile(char* inFilename, Map* map, Tank* pla, Tank* ene, Mirrors* mir)
{
	FILE* inFile 	= fopen(inFilename, "r");
	int count	= 0;
	char *linePtr	= NULL;
	int lineSize	= 100;
	char line[101];
	
	
	/* CHECK - Can file be opened? : */
	if(inFile == NULL) 
	{
		perror("Could not open file");
	}	
	else 
	{
		/* Read & save map data : */
		fscanf(inFile, "%d %d \n", &(map->row), &(map->col));		
		
		/* Read & save player data : */
		fscanf( inFile, "%d %d %c \n", &(pla->row), &(pla->col), &(pla->dir) );
		(pla->dir) = convertDir(pla->dir);
		
		/* Read & save enemy data : */
		fscanf( inFile, "%d %d %c \n", &(ene->row), &(ene->col), &(ene->dir) );		
		(ene->dir) = convertDir(ene->dir);
	

		/* Read mirrors data : */		
		do
		{
			linePtr = fgets(line, lineSize, inFile);			

			if(linePtr != NULL)
			{
				sscanf( line, "%d %d %c \n", &((mir[count]).row), &((mir[count]).col), &((mir[count]).dir)  );
				count++;
			}
				
		}
		while(linePtr != NULL);
				
		/* CHECK - Any reading errors? : */
		if(ferror(inFile)) 
		{
			perror("Error reading file\n");
		}		
		
		fclose(inFile);
	}
	
}


/* DESCRIPTION :   Count how many mirrors data are provided... */
int countNumMirrors(char* inFilename)
{
	char *linePtr		= '\0';
	int numMirrors		= 0;
	int offset 		= 3;
	FILE* inFile 		= fopen(inFilename, "r");
	int lineSize 		= 100;
	char line[101];

	/* CHECK - Can file be opened? : */
	if(inFile == NULL) 
	{
		perror("Could not open file");
	}

	else
	{

		/* Count number of mirror entries (dummy read) : */
		do
		{
			linePtr = fgets(line, lineSize, inFile);
		
			if(linePtr != NULL)
			{
				numMirrors++;
			}

		}			
		while(linePtr != NULL);
		

		/* CHECK - Any reading errors? : */
		if(ferror(inFile)) 
		{
			perror("Error reading file\n");
		}

		fclose(inFile);
	}

	return (numMirrors - offset);
}


/* DESCRIPTION :    Find equivalent directions characters... */
char convertDir(char UserInput_Dirn)
{
	char equiv_Dirn;

	/* Convert "lrdu" directions to "adsw" directions : */
	switch(UserInput_Dirn)
	{
		case 'l':
			equiv_Dirn = 'a';
		break;

		case 'r':
			equiv_Dirn = 'd';
		break;

		case 'd':
			equiv_Dirn = 's';
		break;
			
		case 'u':
			equiv_Dirn = 'w';
		break;
	}
	return equiv_Dirn;
}


/* DESCRIPTION :    Write linkedlist content to file... */
void writeFile(char* outFilename, LinkedList* list)
{	
	FILE* outFile = fopen(outFilename, "w");	

	if(outFile == NULL) 
	{
		perror("Could not open file");
	}
	else 
	{
		/* Generic linkedlist function to handle data writing : */
		writeLinkedList(list, outFile, &writeData);		
		
		
		/* Check for any errors : */
		if(ferror(outFile)) 
		{
			perror("Error writing file\n");
		}

		/* Close files : */
		fclose(outFile);		
	}
}


/* Generic linkedlist function to handle data writing : */
void writeData(void* data, FILE* outFile)
{
	int r, c;
	MapData* logData 	= NULL;
	char** loggedMapArray 	= NULL;
	char writeChar 		= '\0';
	

	/* Extract linkedlist nodedata : */
	logData = (MapData*) data;
	loggedMapArray 	= logData->mapArray;

	
	/* Write array to file : */
	for(r = 0; r < (logData->map)->row; r++)
	{
		for(c = 0; c < (logData->map)->col; c++)
		{
		
			writeChar = loggedMapArray[r][c];
			fprintf(outFile, "%c", writeChar);

		}
		fprintf(outFile, "\n");
	}
	
	/* Write line separator : */
	for(c = 0; c < (logData->map)->col; c++)
	{
		fprintf(outFile, "%c", '-');
	}

	fprintf(outFile, "\n");
}























