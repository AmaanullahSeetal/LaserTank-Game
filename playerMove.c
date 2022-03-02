/* ********************************************************************
 * File    : playerMove.c
 * Date    : 03 May 2021
 * Author  : Amaanullah Seetal (id:2033 9098)
 * ----------------------------------------------------------------
 * Purpose : Move the player's tank by altering its coordinates :
 **********************************************************************/

 #include "structs.h"
 #include "macros.h"
 #include "playerMove.h"

/* DESCRIPTION :    Move or face player UP... */
void moveUp(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors)
{
	int ii = 0;
	int collided = FALSE;

	/* Move or face player UP : */
	if(pla->dir != 'w')
	{
		pla->dir = 'w';
	}
	else
	{	
		/* CHECK - Is player going above the map top limit? : */
		if( pla->row > 1 )
		{
			/* CHECK - Is player colliding with enemy : */
			if(ene->col == (pla->col)  &&  ene->row == (pla->row)-1 )
			{
				collided = TRUE;
			}

			/* CHECK - Is player colliding with mirrors : */	
			for( ii = 0 ; ii < numMirrors ;  ii++ )
			{
				if(mir[ii].col == (pla->col)  &&  mir[ii].row == (pla->row)-1 )
				{
					collided = TRUE;
				}
			}

			/* CHECK - Any collision detected? : */
			if(collided == FALSE)
			{
				(pla->row)--;
			}

		}

	}
}


/* DESCRIPTION :    Move or face player DOWN... */
void moveDown(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors)
{
	int ii = 0;
	int collided = FALSE;

	/* Move or face player DOWN */
	if(pla->dir != 's')
	{
		pla->dir = 's';
	}
	else
	{
		/* Is player going below the map bottom limit? */
		if( pla->row < (map->row)-2 )
		{	
			/* CHECK - Is player colliding with enemy : */
			if(ene->col == (pla->col)  &&  ene->row == (pla->row)+1 )
			{
				collided = TRUE;
			}

			/* CHECK - Is player colliding with mirrors : */	
			for( ii = 0 ; ii < numMirrors ;  ii++ )
			{
				if(mir[ii].col == (pla->col)  &&  mir[ii].row == (pla->row)+1 )
				{
					collided = TRUE;
				}
			}

			/* CHECK - Any collision detected? : */
			if(collided == FALSE)
			{
				(pla->row)++;
			}

		}
	
	}
}


/* DESCRIPTION :    Move or face player LEFT... */
void moveLeft(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors)
{
	int ii = 0;
	int collided = FALSE;

	/* Move or face player LEFT */
	if( (pla->dir) != 'a')
	{
		pla->dir = 'a';
	}
	else
	{
		/* Is player going beyond the map left limit? */
		if( (pla->col) > 1 )
		{
			/* CHECK - Is player colliding with enemy : */
			if( ene->row == (pla->row)  &&  ene->col == (pla->col)-1 )
			{
				collided = TRUE;
			}

			/* CHECK - Is player colliding with mirrors : */	
			for( ii = 0 ; ii < numMirrors ;  ii++ )
			{
				if(mir[ii].row == (pla->row)  &&  mir[ii].col == (pla->col)-1)
				{
					collided = TRUE;
				}
			}

			/* CHECK - Any collision detected? : */
			if(collided == FALSE)
			{
				(pla->col)--;
			}

		}
	}
}







/* DESCRIPTION :    Move or face player RIGHT... */
void moveRight(Map* map, Tank* pla, Tank* ene, Mirrors* mir, int numMirrors)
{
	int ii = 0;
	int collided = FALSE;

	/* Move or face player RIGHT */
	if(pla->dir != 'd')
	{
		pla->dir = 'd';
	}
	else
	{
		/* Is player going beyond the map right limit? */
		if( pla->col < (map->col)-2 )
		{
			/* CHECK - Is player colliding with enemy : */
			if(ene->row == (pla->row)  &&  ene->col == (pla->col)+1 )
			{
				collided = TRUE;
			}

			/* CHECK - Is player colliding with mirrors : */	
			for( ii = 0 ; ii < numMirrors ;  ii++ )
			{
				if(mir[ii].row == (pla->row)  &&  mir[ii].col == (pla->col)+1)
				{
					collided = TRUE;
				}
			}

			/* CHECK - Any collision detected? : */
			if(collided == FALSE)
			{
				(pla->col)++;
			}

		}
	}
}
