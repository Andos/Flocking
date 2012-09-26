// ============================================================================
//
// This file contains routines that are handled during the Runtime.
//
// Including creating, display, and handling your object.
// 
// ============================================================================

// Common Include
#include	"common.h"
#include	"ObjectSelection.h"

// DEBUGGER /////////////////////////////////////////////////////////////////

#if !defined(RUN_ONLY)
// Identifiers of items displayed in the debugger
enum
{
// Example
// -------
//	DB_CURRENTSTRING,
//	DB_CURRENTVALUE,
//	DB_CURRENTCHECK,
//	DB_CURRENTCOMBO
};

// Items displayed in the debugger
WORD DebugTree[]=
{
// Example
// -------
//	DB_CURRENTSTRING|DB_EDITABLE,
//	DB_CURRENTVALUE|DB_EDITABLE,
//	DB_CURRENTCHECK,
//	DB_CURRENTCOMBO,

	// End of table (required)
	DB_END
};

#endif // !defined(RUN_ONLY)


// --------------------
// GetRunObjectDataSize
// --------------------
// Returns the size of the runtime datazone of the object
// 
ushort WINAPI DLLExport GetRunObjectDataSize(fprh rhPtr, LPEDATA edPtr)
{
	return(sizeof(RUNDATA));
}



// ---------------
// CreateRunObject
// ---------------
// The routine where the object is actually created
//
short WINAPI DLLExport CreateRunObject(LPRDATA rdPtr, LPEDATA edPtr, fpcob cobPtr)
{
	rdPtr->cells = new CellMap();
	rdPtr->cellsize = edPtr->cellsize;

	for(int i=0; i<100; ++i)
		rdPtr->boidtypes[i] = edPtr->defaultParameters;

	rdPtr->numLoops = 0;
	memset(&rdPtr->loopedBoid, 0, sizeof(Boid));

	mv* mvI = rdPtr->rHo.hoAdRunHeader->rh4.rh4Mv;
	rdPtr->hwa = mvI->mvCallFunction(NULL, EF_ISHWA, 0, 0, 0) == 1;
	rdPtr->unicode = mvI->mvCallFunction(NULL, EF_ISUNICODE, 0, 0, 0) == 1;	
	return 0;
}


// ----------------
// DestroyRunObject
// ----------------
// Destroys the run-time object
// 
short WINAPI DLLExport DestroyRunObject(LPRDATA rdPtr, long fast)
{
	rdPtr->cells->clear();
	delete rdPtr->cells;
	return 0;
}

// ----------------
// HandleRunObject
// ----------------
// Called (if you want) each loop, this routine makes the object live
// 
short WINAPI DLLExport HandleRunObject(LPRDATA rdPtr)
{
	float cellsize = (float)rdPtr->cellsize;
	
	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator cellit;
	CellMap::iterator lastElement;
	CellMap::iterator cellsEnd = rdPtr->cells->end();

	//Amount of boids that needs to change cells
	int moveCount = 0;

	while(it != cellsEnd)
	{
		Boid & boid = it->second;
		BoidType & boidtype = rdPtr->boidtypes[boid.boidType];
		LPRO object = LPROFromFixed(rdPtr, boid.fixedValue);
		float viewRadiusSquared = boidtype.viewRadius*boidtype.viewRadius;
		float avoidanceRadiusSquared = boidtype.avoidanceRadius*boidtype.avoidanceRadius;

		if(object == NULL)
		{
			it = rdPtr->cells->erase(it);
			continue;
		}

		// Separation: steer to avoid crowding local flockmates
		// Alignment:  steer towards the average heading of local flockmates
		// Cohesion:   steer to move toward the average position of local flockmates
		
		boid.aliCohNeighbourCount = boid.sepNeighbourCount = 0;
		boid.cohX = 0.0f; boid.cohY = 0.0f;
		boid.aliX = 0.0f; boid.aliY = 0.0f;
		boid.sepX = 0.0f; boid.sepY = 0.0f;
		
		//Target position relative to the boid itself (cartesian coordinates)
		boid.targetX = 0.0f;
		boid.targetY = 0.0f;

		//Find all cells inside the radius:
		int startCellX = (int)floorf((boid.x - boidtype.viewRadius)/cellsize);
		int endCellX = (int)ceilf((boid.x + boidtype.viewRadius)/cellsize);
		int startCellY = (int)floorf((boid.y - boidtype.viewRadius)/cellsize);
		int endCellY = (int)ceilf((boid.y + boidtype.viewRadius)/cellsize);

		for(int y = startCellY; y<endCellY; ++y)
		{
			for(int x=startCellX; x<endCellX; ++x)
			{
				//Iterate through all objects in the cell:
				//=========================================
				Cell key = Cell(x,y);
				cellit = rdPtr->cells->find(key);
				
				//If the cell is empty
				if(cellit == cellsEnd)
					continue;
				
				lastElement = rdPtr->cells->upper_bound(key);

				for(; cellit != lastElement; ++cellit )
				{
					Boid & neighbour = cellit->second;

					//avoid the checked boid testing itself
					if( neighbour.fixedValue != boid.fixedValue )
					{
						float dX = neighbour.x - boid.x;
						float dY = neighbour.y - boid.y;
						float distanceSquared = dX*dX + dY*dY;
						if(distanceSquared < viewRadiusSquared)
						{
							float distance = sqrtf(distanceSquared);
							if(neighbour.boidType == boid.boidType)
							{
								++boid.aliCohNeighbourCount;
								float influence = 1.0f - distance/boidtype.viewRadius;
								boid.cohX += (neighbour.x - boid.x) * influence;
								boid.cohY += (neighbour.y - boid.y) * influence;
								boid.aliX += neighbour.dirX * influence;
								boid.aliY += neighbour.dirY * influence;
							}
							if(distance < boidtype.avoidanceRadius)
							{
								//The closer to the boid, the faster it will escape in the opposite direction.
								++boid.sepNeighbourCount;
								float escapeFactor = 1.0f - distance/boidtype.avoidanceRadius;
								boid.sepX += (boid.x - neighbour.x) * escapeFactor;
								boid.sepY += (boid.y - neighbour.y) * escapeFactor;
							}
						}
					}
				}
			}
		}

		// Avoid obstacles
		if(boidtype.avoidObstacles)
		{
			float wallX = 0, wallY = 0;
			Vec2i startpoint = {(int)boid.x, (int)boid.y};
			int countWalls = 0;

			for(int iangle=-132; iangle<132; iangle+=22)
			{
				float angle = ToRadians(boid.dirAngle+iangle);
				Vec2i endpoint = {(int)(boid.x + cosf(angle)*boidtype.avoidanceRadius), (int)(boid.y + sinf(angle)*boidtype.avoidanceRadius)};
				Vec2i respoint = TracePosition(&rdPtr->rHo, object->roHo.hoLayer, startpoint, endpoint);
				
				if(respoint.x != endpoint.x || respoint.y != endpoint.y)
				{
					endpoint.x -= startpoint.x;
					endpoint.y -= startpoint.y;		
					wallX += endpoint.x;
					wallY += endpoint.y;
					++countWalls;
				}
			}
			if(countWalls>0)
			{
				float distance = sqrtf(wallX*wallX + wallY*wallY);
				float escapeFactor = 1.0f - distance/boidtype.avoidanceRadius;		

				++boid.sepNeighbourCount;
				boid.sepX += ((startpoint.x+wallX) - boid.x) * escapeFactor;
				boid.sepY += ((startpoint.y+wallY) - boid.y) * escapeFactor;
			}
		}

		//Divide all values with the number of neighbours to get the average
		float invNeighAliCoh = (boid.aliCohNeighbourCount > 0) ? 1.0f/boid.aliCohNeighbourCount : 1.0f;
		float invNeighSep = (boid.sepNeighbourCount > 0) ? 1.0f/boid.sepNeighbourCount : 1.0f;

		boid.aliX *= invNeighAliCoh; boid.aliY *= invNeighAliCoh;
		boid.cohX *= invNeighAliCoh; boid.cohY *= invNeighAliCoh;
		boid.sepX *= invNeighSep; boid.sepY *= invNeighSep;

		boid.targetX += boid.sepX * boidtype.separationWeight + boid.cohX * boidtype.cohesionWeight;
		boid.targetY += boid.sepY * boidtype.separationWeight + boid.cohY * boidtype.cohesionWeight;
		
		//Normalize average angle
		float aliDirLength = sqrtf(boid.aliX*boid.aliX + boid.aliY*boid.aliY);
		if(aliDirLength > 0.001f)
		{
			boid.targetX += boid.aliX/aliDirLength * boidtype.alignmentWeight;
			boid.targetY += boid.aliY/aliDirLength * boidtype.alignmentWeight;
		}

		//Increment
		++it;
	}

	//Loop over all boids to update their cell and position them on the screen.
	it = rdPtr->cells->begin();
	while(it != cellsEnd)
	{
		Boid & boid = it->second;
		BoidType & boidtype = rdPtr->boidtypes[boid.boidType];
		LPRO object = LPROFromFixed(rdPtr, boid.fixedValue);

		//Apply the external force and reset it
		boid.targetX += boid.forceX;
		boid.targetY += boid.forceY;
		boid.forceX = boid.forceY = 0.0f;

		boid.oldSpeed = boid.speed;

		//Apply movement randomization
		if(boidtype.movementRandomization > 0)
		{
			boid.targetX += ((rand()/(float)RAND_MAX)*2.0f-1.0f) *boidtype.movementRandomization;
			boid.targetY += ((rand()/(float)RAND_MAX)*2.0f-1.0f) *boidtype.movementRandomization;
		}

		//Calculate the vector length to the target position
		boid.targetDistance = max(sqrtf(boid.targetX*boid.targetX + boid.targetY*boid.targetY), 0.00001f);

		//Update the direction information for the boid
		float invNeg = 1.0f/boid.targetDistance;
		float newDirX = boid.targetX * invNeg;
		float newDirY = boid.targetY * invNeg;
		float newDirAngle = boid.dirAngle;
		if(boid.targetDistance > 0.001f)
			newDirAngle = ToDegrees(atan2f(newDirY, newDirX));

		//Calculate dot product between the old direction and the target direction
		float cosO = boid.dirX*newDirX + boid.dirY*newDirY;
		bool targetIsBehind = cosO < 0;

		//Adjust speed based on target distance and which direction it is located in.
		if(cosO < -0.01f || cosO > 0.01f)
			boid.speed = boid.targetDistance * cosO;
		else
			boid.speed = boid.targetDistance;

		//Nothing to do? Set to idle speed
		bool hasNoTarget = boid.targetDistance < 0.001f;
		bool targetInFront = boid.targetDistance > 0.001f && !targetIsBehind;
		if( hasNoTarget || boidtype.idleSpeed > 0 && boid.speed > 0)
			boid.speed = max(boidtype.idleSpeed, boid.speed);

		//Fix for objects getting stuck if they cannot reverse while their target is behind them
		if(targetIsBehind && boidtype.speedDependantTurn && boidtype.minSpeed >= 0)
			boid.speed = boid.targetDistance;

		//Compensate for acceleration and deceleration
		float deltaSpeed = boid.speed - boid.oldSpeed;
		if(deltaSpeed > 0 && deltaSpeed > boidtype.acceleration)
			boid.speed = min(boid.speed, boid.oldSpeed+boidtype.acceleration);
		else if(deltaSpeed < 0 && deltaSpeed < -boidtype.deceleration )
			boid.speed = max(boid.speed, boid.oldSpeed-boidtype.deceleration);

		//Min and Max speed
		boid.speed = clamp(boid.speed, boidtype.minSpeed, boidtype.maxSpeed);

		//Turn towards target
		if(boid.targetDistance > 0.001f)
		{
			//Turn speed depends on the haste the boid has
			if(boidtype.speedDependantTurn)
			{
				float speedFactor = abs((boid.speed+0.01f)/boidtype.maxSpeed);
				boid.dirAngle = RotateTowards(boid.dirAngle, newDirAngle, boidtype.turnSpeed*speedFactor);
			}
			else	// Turn speed independant of boid speed
				boid.dirAngle = RotateTowards(boid.dirAngle, newDirAngle, boidtype.turnSpeed);

			boid.dirX = cos(ToRadians(boid.dirAngle));
			boid.dirY = sin(ToRadians(boid.dirAngle));
		}

		//Check if the boid was manually moved since last frame and then update the internal position
		if(object->roHo.hoX != (int)boid.x || object->roHo.hoY != (int)boid.y)
		{
			boid.x = (float)object->roHo.hoX;
			boid.y = (float)object->roHo.hoY;
		}

		//Update old positions
		boid.oldX = boid.x;
		boid.oldY = boid.y;

		//Update positions
		boid.x += boid.dirX * boid.speed;
		boid.y += boid.dirY * boid.speed;

		//Push out of obstacle if it ended up inside:
		if(boidtype.avoidObstacles)
		{
			if(!callColMaskTestPoint(((headerObject*)&rdPtr->rHo), (int)boid.x, (int)boid.y, object->roHo.hoLayer, SCF_OBSTACLE))
			{
				int x = (int)boid.x;
				int y = (int)boid.y;
				int oX = (int)boid.oldX;
				int oY = (int)boid.oldY;
				int dX = x-oX;
				int dY = y-oY;
				//No previous position recorded, cannot reliably push out
				if( !(dX == 0 && dY == 0))
				{
					int distance = (int)ceil(sqrtf((float)(dX*dX+dY*dY)));
					for(int i=0; i<distance; ++i)
					{
						float step = i/(float)distance;
						int testX = (int)(oX+dX*step);
						int testY = (int)(oY+dY*step);

						if(callColMaskTestPoint(((headerObject*)&rdPtr->rHo), testX, testY, object->roHo.hoLayer, SCF_OBSTACLE))
						{
							boid.x = (float)testX;
							boid.y = (float)testY;
						}
						else
							break;
					}
				}

			}
		}

		//Count how many boids needs to be moved
		if((int)(boid.x/rdPtr->cellsize) != boid.cellX || (int)(boid.y/rdPtr->cellsize) != boid.cellY )
			++moveCount;

		//Reposition the object on screen and mark as changed to force a redraw.
		object->roc.rcChanged = true;
		object->roHo.hoX = (int)boid.x;
		object->roHo.hoY = (int)boid.y;
		object->roc.rcCheckCollides = 1;

		//Store angle value
		switch(boidtype.angleDirSetting)
		{
			case ANGLE_SETTING:
				if(rdPtr->hwa)
				{
					int angle = 0;
					float resultAngle = 360.0f-boid.dirAngle;
					memcpy(&angle,&resultAngle,sizeof(int));
					object->roc.rcAngle = angle;
				}
				else
					object->roc.rcAngle = 360-(int)boid.dirAngle;	
				break;
			
			case DIR_SETTING:
				object->roc.rcDir = (int)((360.0f-boid.dirAngle)/11.25f);
				break;
			default:
				break;
		}
		//Increment
		++it;
	}

	if(moveCount == 0)
		return 0;

	CellBoidPair * newArray = new CellBoidPair[moveCount];
	
	//Final pass to move all boids to their new cells if needed
	it = rdPtr->cells->begin();
	cellsEnd = rdPtr->cells->end();
	int arrIt = 0;
	while(it != cellsEnd)
	{
		Boid & boid = it->second;
		BoidType & boidtype = rdPtr->boidtypes[boid.boidType];

		//Boid moved cell, relocate!
		if((int)(boid.x/rdPtr->cellsize) != boid.cellX || (int)(boid.y/rdPtr->cellsize) != boid.cellY )
		{
			Boid newboid = boid;
			it = rdPtr->cells->erase(it);
			newboid.cellX = (int)newboid.x/rdPtr->cellsize;
			newboid.cellY = (int)newboid.y/rdPtr->cellsize;
			Cell newkey = Cell(newboid.cellX, newboid.cellY);
			CellBoidPair replaceElement = CellBoidPair(newkey,newboid);
			newArray[arrIt] = replaceElement;
			++arrIt;
			continue;
		}
		++it;
	}

	//Insert all the new objects
	for(int i=0; i<moveCount; ++i)
		rdPtr->cells->insert( newArray[i] );

	delete [] newArray;

	return 0;
}

// ----------------
// DisplayRunObject
// ----------------
// Draw the object in the application screen.
// 
short WINAPI DLLExport DisplayRunObject(LPRDATA rdPtr)
{
/*
   If you return REFLAG_DISPLAY in HandleRunObject this routine will run.
*/
	// Ok
	return 0;
}

// ----------------
// PauseRunObject
// ----------------
// Enters the pause mode
// 
short WINAPI DLLExport PauseRunObject(LPRDATA rdPtr)
{
	// Ok
	return 0;
}


// -----------------
// ContinueRunObject
// -----------------
// Quits the pause mode
//
short WINAPI DLLExport ContinueRunObject(LPRDATA rdPtr)
{
	// Ok
	return 0;
}

// -----------------
// SaveRunObject
// -----------------
// Saves the object to disk
// 

BOOL WINAPI SaveRunObject(LPRDATA rdPtr, HANDLE hf)
{            
	BOOL bOK = FALSE;

#ifndef VITALIZE

	// Save the object's data here

	// OK
	bOK = TRUE;

#endif // VITALIZE

	return bOK;
}

// -----------------
// LoadRunObject
// -----------------
// Loads the object from disk
// 
BOOL WINAPI LoadRunObject(LPRDATA rdPtr, HANDLE hf)
{            
	BOOL bOK=FALSE;

	// Load the object's data here

	// OK
	bOK = TRUE;

	return bOK; 
}




// ============================================================================
//
// START APP / END APP / START FRAME / END FRAME routines
// 
// ============================================================================

// -------------------
// StartApp
// -------------------
// Called when the application starts or restarts.
// Useful for storing global data
// 
void WINAPI DLLExport StartApp(mv _far *mV, CRunApp* pApp)
{
	// Example
	// -------
	// Delete global data (if restarts application)
//	CMyData* pData = (CMyData*)mV->mvGetExtUserData(pApp, hInstLib);
//	if ( pData != NULL )
//	{
//		delete pData;
//		mV->mvSetExtUserData(pApp, hInstLib, NULL);
//	}
}

// -------------------
// EndApp
// -------------------
// Called when the application ends.
// 
void WINAPI DLLExport EndApp(mv _far *mV, CRunApp* pApp)
{
	// Example
	// -------
	// Delete global data
//	CMyData* pData = (CMyData*)mV->mvGetExtUserData(pApp, hInstLib);
//	if ( pData != NULL )
//	{
//		delete pData;
//		mV->mvSetExtUserData(pApp, hInstLib, NULL);
//	}
}

// -------------------
// StartFrame
// -------------------
// Called when the frame starts or restarts.
// 
void WINAPI DLLExport StartFrame(mv _far *mV, DWORD dwReserved, int nFrameIndex)
{
}

// -------------------
// EndFrame
// -------------------
// Called when the frame ends.
// 
void WINAPI DLLExport EndFrame(mv _far *mV, DWORD dwReserved, int nFrameIndex)
{
}

// ============================================================================
//
// TEXT ROUTINES (if OEFLAG_TEXT)
// 
// ============================================================================

// -------------------
// GetRunObjectFont
// -------------------
// Return the font used by the object.
// 
/*

  // Note: do not forget to enable the functions in the .def file 
  // if you remove the comments below.

void WINAPI GetRunObjectFont(LPRDATA rdPtr, LOGFONT* pLf)
{
	// Example
	// -------
	// GetObject(rdPtr->m_hFont, sizeof(LOGFONT), pLf);
}

// -------------------
// SetRunObjectFont
// -------------------
// Change the font used by the object.
// 
void WINAPI SetRunObjectFont(LPRDATA rdPtr, LOGFONT* pLf, RECT* pRc)
{
	// Example
	// -------
//	HFONT hFont = CreateFontIndirect(pLf);
//	if ( hFont != NULL )
//	{
//		if (rdPtr->m_hFont!=0)
//			DeleteObject(rdPtr->m_hFont);
//		rdPtr->m_hFont = hFont;
//		SendMessage(rdPtr->m_hWnd, WM_SETFONT, (WPARAM)rdPtr->m_hFont, FALSE);
//	}

}

// ---------------------
// GetRunObjectTextColor
// ---------------------
// Return the text color of the object.
// 
COLORREF WINAPI GetRunObjectTextColor(LPRDATA rdPtr)
{
	// Example
	// -------
	return 0;	// rdPtr->m_dwColor;
}

// ---------------------
// SetRunObjectTextColor
// ---------------------
// Change the text color of the object.
// 
void WINAPI SetRunObjectTextColor(LPRDATA rdPtr, COLORREF rgb)
{
	// Example
	// -------
	rdPtr->m_dwColor = rgb;
	InvalidateRect(rdPtr->m_hWnd, NULL, TRUE);
}
*/


// ============================================================================
//
// WINDOWPROC (interception of messages sent to hMainWin and hEditWin)
//
// Do not forget to enable the WindowProc function in the .def file if you implement it
// 
// ============================================================================
/*
// Get the pointer to the object's data from its window handle
// Note: the object's window must have been subclassed with a
// callRunTimeFunction(rdPtr, RFUNCTION_SUBCLASSWINDOW, 0, 0);
// See the documentation and the Simple Control example for more info.
//
LPRDATA GetRdPtr(HWND hwnd, LPRH rhPtr)
{
	return (LPRDATA)GetProp(hwnd, (LPCSTR)rhPtr->rh4.rh4AtomRd);
}

// Called from the window proc of hMainWin and hEditWin.
// You can intercept the messages and/or tell the main proc to ignore them.
//
LRESULT CALLBACK DLLExport WindowProc(LPRH rhPtr, HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	LPRDATA rdPtr = NULL;

	switch (nMsg) {

	// Example
	case WM_CTLCOLORSTATIC:
		{
			// Get the handle of the control
			HWND hWndControl = (HWND)lParam;

			// Get a pointer to the RUNDATA structure (see GetRdptr function above for more info)
			rdPtr = GetRdPtr(hWndControl, rhPtr);

			// Check if the rdPtr pointer is valid and points to an object created with this extension
			if ( rdPtr == NULL || rdPtr->rHo.hoIdentifier != IDENTIFIER )
				break;

			// OK, intercept the message
			HDC hDC = (HDC)wParam;
			SetBkColor(hDC, rdPtr->backColor);
			SetTextColor(hDC, rdPtr->fontColor);
			rhPtr->rh4.rh4KpxReturn = (long)rdPtr->hBackBrush;
			return REFLAG_MSGRETURNVALUE;
		}
		break;
	}

	return 0;
}
*/

// ============================================================================
//
// DEBUGGER ROUTINES
// 
// ============================================================================

// -----------------
// GetDebugTree
// -----------------
// This routine returns the address of the debugger tree
//
LPWORD WINAPI DLLExport GetDebugTree(LPRDATA rdPtr)
{
#if !defined(RUN_ONLY)
	return DebugTree;
#else
	return NULL;
#endif // !defined(RUN_ONLY)
}

// -----------------
// GetDebugItem
// -----------------
// This routine returns the text of a given item.
//
void WINAPI DLLExport GetDebugItem(LPSTR pBuffer, LPRDATA rdPtr, int id)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
/*
	char temp[DB_BUFFERSIZE];

	switch (id)
	{
	case DB_CURRENTSTRING:
		LoadString(hInstLib, IDS_CURRENTSTRING, temp, DB_BUFFERSIZE);
		wsprintf(pBuffer, temp, rdPtr->text);
		break;
	case DB_CURRENTVALUE:
		LoadString(hInstLib, IDS_CURRENTVALUE, temp, DB_BUFFERSIZE);
		wsprintf(pBuffer, temp, rdPtr->value);
		break;
	case DB_CURRENTCHECK:
		LoadString(hInstLib, IDS_CURRENTCHECK, temp, DB_BUFFERSIZE);
		if (rdPtr->check)
			wsprintf(pBuffer, temp, "TRUE");
		else
			wsprintf(pBuffer, temp, "FALSE");
		break;
	case DB_CURRENTCOMBO:
		LoadString(hInstLib, IDS_CURRENTCOMBO, temp, DB_BUFFERSIZE);
		wsprintf(pBuffer, temp, rdPtr->combo);
		break;
	}
*/

#endif // !defined(RUN_ONLY)
}

// -----------------
// EditDebugItem
// -----------------
// This routine allows to edit editable items.
//
void WINAPI DLLExport EditDebugItem(LPRDATA rdPtr, int id)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
/*
	switch (id)
	{
	case DB_CURRENTSTRING:
		{
			EditDebugInfo dbi;
			char buffer[256];

			dbi.pText=buffer;
			dbi.lText=TEXT_MAX;
			dbi.pTitle=NULL;

			strcpy(buffer, rdPtr->text);
			long ret=callRunTimeFunction(rdPtr, RFUNCTION_EDITTEXT, 0, (LPARAM)&dbi);
			if (ret)
				strcpy(rdPtr->text, dbi.pText);
		}
		break;
	case DB_CURRENTVALUE:
		{
			EditDebugInfo dbi;

			dbi.value=rdPtr->value;
			dbi.pTitle=NULL;

			long ret=callRunTimeFunction(rdPtr, RFUNCTION_EDITINT, 0, (LPARAM)&dbi);
			if (ret)
				rdPtr->value=dbi.value;
		}
		break;
	}
*/
#endif // !defined(RUN_ONLY)
}


