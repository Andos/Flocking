#include "common.h"
#include <math.h>

// -----------------------------------------
// Returns a fixed value from an LPRO value
// -----------------------------------------
long FixedValue( LPRO object )
{
	return (object->roHo.hoCreationId << 16) + object->roHo.hoNumber;
}


float RotateTowards(float angle, float targetAngle, float speed)
{
	float diff = targetAngle - angle;
	float dist = abs(diff);
	float direction = (diff > 0) ? 1.0f : -1.0f;
	if(dist > 180.0f)
		direction *= -1.0f;

	float ret = angle + direction*min(speed, dist);
	if(ret >= 360.0f)
		return ret-360.0f;
	else if(ret < 0.0f)
		return ret+360.0f;
	else
		return ret;
}


//Carmacks 1/squareRoot
float Q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	//      y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

/*float RotateTowards(float CurAngle, float TargetAngle, float RotateAmt)
{
	LONG rightdist = (360.0f + (CurAngle - TargetAngle)) % 360.0f;
	LONG leftdist  = (360.0f + (TargetAngle - CurAngle)) % 360.0f;

	// Distance right is shorter, AND distance right is greater than rotate amount
	if ((rightdist <= leftdist) && (rightdist >= RotateAmt))
		return (360.0f + (CurAngle - RotateAmt)) % 360.0f;		// Rotate by amount

	// Distance right is shorter AND distance right is less than rotate amount
	if ((rightdist <= leftdist) && (rightdist < RotateAmt))
		return (360.0f + TargetAngle) % 360.0f;		// Target direction can be reached immediately

	// Left distance is shorter AND distance left is greater than rotate amount
	if ((rightdist > leftdist) && (leftdist >= RotateAmt))
		return (360.0f + (CurAngle + RotateAmt)) % 360.0f;		// Rotate by amount

	if ((rightdist > leftdist) && (leftdist < RotateAmt))
		return (360.0f + TargetAngle) % 360.0f;		// Target direction can be reached immediately

	// (Unreachable)
	return 0;

}*/


float ToRadians(float degrees)
{
	return degrees * (float)PI/180.0f;
}

float ToDegrees(float radians)
{
	float ret = radians * 180.0f/(float)PI;
	if (ret < 0)
		return 360+ret;
	else
		return ret;
}

long returnFloat(LPRDATA rdPtr, float value)
{
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
    return *((long*)&value);
}

// ------------------------------------------------
// Return a valid LPRO pointer from a fixed value,
// NULL if object doesn't exist.
// ------------------------------------------------
LPRO LPROFromFixed( LPRDATA rdPtr, long fixedvalue )
{
	LPOBL objList = rdPtr->rHo.hoAdRunHeader->rhObjectList;
	int index = 0x0000FFFF & fixedvalue;

	if (index < 0 || index >= 10000)
		return NULL;

	LPRO theObject = (LPRO)objList[0x0000FFFF & fixedvalue].oblOffset;

	if (theObject == NULL)
		return NULL;
	else if (FixedValue(theObject) != fixedvalue)
		return NULL;

	return theObject;
}


/*void Debug( char * string, int value )
{
	char output [1024];
	sprintf_s( output, 1024, "%s: %i", string, value );
	MessageBox(NULL,output,"",NULL);
}

void Debug( char * string, float value )
{
	char output [1024];
	sprintf_s( output, 1024, "%s: %f", string, value );
	MessageBox(NULL,output,"",NULL);
}

void Debug( char * string, float valueA, float valueB )
{
	char output [1024];
	sprintf_s( output, 1024, "%s: %f    %f", string, valueA, valueB );
	MessageBox(NULL,output,"",NULL);
}


void DebugObject(Boid boid)
{
	char output [2048];
	sprintf_s(output, 1024, "Object: %i\nPosition: %f, %f\nSeparation: %f, %f\nAlignment: %f, %f\nCohesion: %f, %f\n-----------\nTarget: %f, %f\n", boid.fixedValue, boid.x, boid.y, boid.sepX, boid.sepY, boid.aliX, boid.aliY, boid.cohX, boid.cohY, boid.targetX, boid.targetY);
	MessageBox(NULL,output,"",NULL);	
}*/


void LoopNeighbourBoids(LPRDATA rdPtr, char* loopname, Boid boid, int radius)
{
	if(rdPtr->numLoops >= 9)
		return;

	BoidLoop &currentLoop = rdPtr->boidLoops[rdPtr->numLoops];
	rdPtr->numLoops++;

	strcpy_s(currentLoop.name, 31, loopname);
	rdPtr->centerBoid = boid;

	BoidType & boidtype = rdPtr->boidtypes[boid.boidType];
	float cellsize = (float)rdPtr->cellsize;
	
	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	std::vector<Boid> foundBoids = std::vector<Boid>();

	int startCellX = (int)floor((boid.x - radius)/cellsize);
	int endCellX = (int)ceil((boid.x + radius)/cellsize);
	int startCellY = (int)floor((boid.y - radius)/cellsize);
	int endCellY = (int)ceil((boid.y + radius)/cellsize);

	for(int y = startCellY; y<endCellY; ++y)
	{
		for(int x=startCellX; x<endCellX; ++x)
		{
			Cell key = Cell(x,y);
			cellit = rdPtr->cells->find(key);
			if(cellit == rdPtr->cells->end())
				continue;
			lastElement = rdPtr->cells->upper_bound(key);

			for(; cellit != lastElement; ++cellit )
			{
				Boid & neighbour = cellit->second;
				if(neighbour.fixedValue == boid.fixedValue)
					continue;

				float xDist = neighbour.x - boid.x;
				float yDist = neighbour.y - boid.y;
				float distance = sqrt(xDist*xDist + yDist*yDist);

				if(distance >= radius)
					continue;
	
				foundBoids.push_back(neighbour);
			}
		}
	}
	
	rdPtr->rHo.hoAdRunHeader->rh2.rh2ActionOn = false;
	int numBoids = foundBoids.size();
	for(int i=0; i<numBoids; ++i)
	{
		rdPtr->loopedBoid = foundBoids[i];
		callRunTimeFunction(rdPtr,RFUNCTION_GENERATEEVENT,0,0);
	}
	rdPtr->rHo.hoAdRunHeader->rh2.rh2ActionOn = true;
	foundBoids.clear();

	rdPtr->numLoops--;
}



Vec2i TracePosition(headerObject* rHo, int layer, Vec2i a, Vec2i b)
{
	//Optimization: Return if the endpoint isn't obstacle
	if(callColMaskTestPoint(rHo, b.x, b.y, layer, SCF_OBSTACLE))
		return b;

	int oX = a.x;
	int oY = a.y;
	int dX = b.x-oX;
	int dY = b.y-oY;
	int onX = a.x, onY = a.y;

	int distance = (int)ceil(sqrt((float)(dX*dX+dY*dY)));
	int lowerbound = 0;
	int upperbound = distance;
	int current = distance/2;
	float progress = 0.5f;

	//Push out, maximum 10 iterations
	for(int i=0; i<10; ++i)
	{
		int nX = (int)(oX+dX*progress);
		int nY = (int)(oY+dY*progress);

		//If it's done pusing out
		if(onX == nX && onY == nY)
			break;
		
		onX = nX;
		onY = nY;
	
		if(callColMaskTestPoint(rHo, nX, nY, layer, SCF_OBSTACLE))
			lowerbound = current;
		else
			upperbound = current;

		current = (upperbound+lowerbound)/2;
		progress = current/(float)distance;
	}
	Vec2i ret = {onX, onY};
	return ret;
}


float clamp(float val, float min, float max)
{
	return min(max(val, min), max);
}