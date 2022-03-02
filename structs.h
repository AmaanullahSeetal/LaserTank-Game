#ifndef STRUCTS_H
#define STRUCTS_H

	/* Create Structs to store data: */
	typedef struct 
	{
		int row;
		int col;
		char dir;
	} Tank;

	typedef struct 
	{
		int row;
		int col;
	} Map;

	typedef struct 
	{
		int row;
		int col;
		char dir;
	} Laser;

	typedef struct 
	{
		int row;
		int col;
		char dir;
	} Mirrors;


	typedef struct 
	{
		char** mapArray;
		Map* map;
	} MapData;

#endif
