#ifndef FILEIO_H
#define FILEIO_H

	/* Function declarations : */
	void readFile(char* inFilename, Map* map, Tank* pla, Tank* ene, Mirrors* mir);
	int countNumMirrors(char* inFilename);
	char convertDir(char UserInput_Dirn);	
	void writeFile(char* outFilename, LinkedList* list);	
	void writeData(void* data, FILE* outFile);

#endif
