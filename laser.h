#ifndef LASER_H
#define LASER_H

	/* Function Declarations: */
	void moveLaser(Laser* las, char srcDir);
	void relocateLaser(Laser* las, Tank* tank);
	void reOrientLaser(char mirDir, Laser* las);
	void animateLaser(int *isGameOver, Laser* las, Mirrors* mir, int numMirrors, Tank* src, Tank* des,  MapData* mapData, LinkedList* list);
	int isDetected(Tank* ene, Map* map, Tank* pla);		
	char getLaserAvatar(char dirn);
	void moveLaser(Laser* las, char srcDir);
#endif
