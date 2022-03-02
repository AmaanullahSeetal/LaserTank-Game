#ifndef MAP_H
#define MAP_H

	/* Function declarations : */
	char** createMapArray(Map* map);
	void displayGameBoard(MapData* mapData, LinkedList* list);
	void deleteMap(char** arr, int r);
	char getTankAvatar(char tank_Dirn);
	char getMirrorAvatar(char mirrDir);
	void generateMap(char** mapArray, Map* map);
	char* getNextColor();
	void generateMirrors(char** mapArray, Mirrors* mir, int numOfMirrors);

#endif

