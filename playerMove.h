#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

	/* Function declarations: */
	void moveUp(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors);
	void moveDown(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors);
	void moveRight(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors);
	void moveLeft(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors);
	
#endif
