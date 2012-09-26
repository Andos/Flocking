// ============================================================================
//
// This file are where the Conditions/Actions/Expressions are defined.
// You can manually enter these, or use CICK (recommended)
// See the Extension FAQ in this SDK for more info and where to download it
//
// ============================================================================

// Common Include
#include	"common.h"
#include	"ObjectSelection.h"

// Quick memo: content of the eventInformations arrays
// ---------------------------------------------------
// Menu ID
// String ID
// Code
// Flags
// Number_of_parameters
// Parameter_type [Number_of_parameters]
// Parameter_TitleString [Number_of_parameters]

// Definitions of parameters for each condition
short conditionsInfos[]=
		{
		ID_ONLOOPEDBOID, ID_ONLOOPEDBOID, 0, 0, 2,  PARAM_EXPSTRING, PARAM_OBJECT, IDS_LOOPNAME, IDS_SELECTOBJECT,
		};

//New conditions:
/*
	Pick boids: <Object> is having it's neighbours looped
	Pick boids: <Object> is within <radius> units of <Object>
	Pick boids: <Object> is closest to <Object>
*/


// Definitions of parameters for each action
short actionsInfos[]=
		{
		ID_ADDOBJECTASBOID,						ID_ADDOBJECTASBOID,						0,	0, 2,	PARAM_OBJECT,	  PARAM_EXPRESSION,	IDS_SELECTOBJECT, IDS_BOIDTYPE,
		ID_REMOVEOBJECT,						ID_REMOVEOBJECT,						1,	0, 1,	PARAM_OBJECT,	  IDS_SELECTOBJECT,
		
		ID_SETIDLESPEED,						ID_SETIDLESPEED,						2,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_SPEED,
		ID_SETMINSPEED,							ID_SETMINSPEED,							3,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_MINSPEED,
		ID_SETMAXSPEED,							ID_SETMAXSPEED,							4,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_MAXSPEED,
		ID_SETACCELERATION,						ID_SETACCELERATION,						5,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_ACCELERATION,
		ID_SETDECELERATION,						ID_SETDECELERATION,						6,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_DECELERATION,
		ID_SETTURNSPEED,						ID_SETTURNSPEED,						7,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_TURNSPEED,
		ID_SETVIEWRADIUS,						ID_SETVIEWRADIUS,						8,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_RADIUS,
		ID_SETAVOIDANCERADIUS,					ID_SETAVOIDANCERADIUS,					9,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_RADIUS,
		ID_SETMOVEMENTRANDOMIZATION,			ID_SETMOVEMENTRANDOMIZATION,			10,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_RANDOMIZATION,
		ID_SETSEPARATIONWEIGHT,					ID_SETSEPARATIONWEIGHT,					11,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_WEIGHT,
		ID_SETALIGNMENTWEIGHT,					ID_SETALIGNMENTWEIGHT,					12,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_WEIGHT,
		ID_SETCOHESIONWEIGHT,					ID_SETCOHESIONWEIGHT,					13,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_WEIGHT,
		ID_SETANGLEDIRSETTING,					ID_SETANGLEDIRSETTING,					14,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION,	IDS_BOIDTYPE, IDS_ANGLEDIRSETTING,
		ID_SETSPEEDDEPENDANTTURN,				ID_SETSPEEDDEPENDANTTURN,				15,	0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION,	IDS_BOIDTYPE, IDS_SPEEDDEPENDANTTURN,
		ID_SETAVOIDOBSTACLES,					ID_SETAVOIDOBSTACLES,					16, 0, 2,	PARAM_EXPRESSION, PARAM_EXPRESSION,	IDS_BOIDTYPE, IDS_AVOIDOBSTACLESETTING,

		ID_ALLOFTYPE_ATTRACTTOWARDSPOSITION,	ID_ALLOFTYPE_ATTRACTTOWARDSPOSITION,	17,	0, 4,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XPOSITION, IDS_YPOSITION, IDS_WEIGHT,
		ID_ALLOFTYPE_CHASEAWAYFROMPOSITION,		ID_ALLOFTYPE_CHASEAWAYFROMPOSITION,		18,	0, 4,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XPOSITION, IDS_YPOSITION, IDS_WEIGHT,
		ID_ALLOFTYPE_APPLYFORCE,				ID_ALLOFTYPE_APPLYFORCE,				19,	0, 3,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XSPEED, IDS_YSPEED,
		ID_WITHINRADIUS_ATTRACTTOWARDPOSITION,	ID_WITHINRADIUS_ATTRACTTOWARDPOSITION,	20,	0, 5,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XPOSITION, IDS_YPOSITION, IDS_RADIUS, IDS_WEIGHT,
		ID_WITHINRADIUS_CHASEAWAYFROMPOSITION,	ID_WITHINRADIUS_CHASEAWAYFROMPOSITION,	21,	0, 5,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XPOSITION, IDS_YPOSITION, IDS_RADIUS, IDS_WEIGHT,
		ID_WITHINRADIUS_APPLYFORCE,				ID_WITHINRADIUS_APPLYFORCE,				22,	0, 6,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_BOIDTYPE, IDS_XPOSITION, IDS_YPOSITION, IDS_RADIUS, IDS_XSPEED, IDS_YSPEED,
		ID_SINGLEBOID_ATTRACTTOWARDSPOSITION,	ID_SINGLEBOID_ATTRACTTOWARDSPOSITION,	23,	0, 4,	PARAM_OBJECT,	  PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_SELECTOBJECT, IDS_XPOSITION, IDS_YPOSITION, IDS_WEIGHT,
		ID_SINGLEBOID_CHASEAWAYFROMPOSITION,	ID_SINGLEBOID_CHASEAWAYFROMPOSITION,	24,	0, 4,	PARAM_OBJECT,	  PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_SELECTOBJECT, IDS_XPOSITION, IDS_YPOSITION, IDS_WEIGHT,
		ID_SINGLEBOID_APPLYFORCE,				ID_SINGLEBOID_APPLYFORCE,				25,	0, 3,	PARAM_OBJECT,	  PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_SELECTOBJECT, IDS_XSPEED, IDS_YSPEED,

		ID_LOOPNEIGHBOURBOIDS,					ID_LOOPNEIGHBOURBOIDS,					26,	0, 3,	PARAM_EXPSTRING,  PARAM_OBJECT,		PARAM_EXPRESSION, IDS_LOOPNAME, IDS_SELECTOBJECT, IDS_RADIUS,
		ID_LOOPBOIDSINRADIUS,					ID_LOOPBOIDSINRADIUS,					27,	0, 4,	PARAM_EXPSTRING,  PARAM_EXPRESSION,	PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_LOOPNAME, IDS_XPOSITION, IDS_YPOSITION, IDS_RADIUS,
		ID_LOOPBOIDSINRECTANGLE,				ID_LOOPBOIDSINRECTANGLE,				28,	0, 5,	PARAM_EXPSTRING,  PARAM_EXPRESSION,	PARAM_EXPRESSION, PARAM_EXPRESSION, PARAM_EXPRESSION, IDS_LOOPNAME, IDS_XPOSITION, IDS_YPOSITION, IDS_WIDTH, IDS_HEIGHT,
		ID_LOOPALLBOIDS,						ID_LOOPALLBOIDS,						29,	0, 1,	PARAM_EXPSTRING,  IDS_LOOPNAME,
		ID_LOOPALLOFTYPE,						ID_LOOPALLOFTYPE,						30,	0, 2,	PARAM_EXPSTRING,  PARAM_EXPRESSION, IDS_LOOPNAME, IDS_BOIDTYPE,
		0 };

// Definitions of parameters for each expression
short expressionsInfos[]=
		{
		ID_FROMBOIDTYPE_GETIDLESPEED,			ID_FROMBOIDTYPE_GETIDLESPEED,			0,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETMINSPEED,			ID_FROMBOIDTYPE_GETMINSPEED,			1,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETMAXSPEED,			ID_FROMBOIDTYPE_GETMAXSPEED,			2,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETACCELERATION,		ID_FROMBOIDTYPE_GETACCELERATION,		3,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETDECELERATION,		ID_FROMBOIDTYPE_GETDECELERATION,		4,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETTURNSPEED,			ID_FROMBOIDTYPE_GETTURNSPEED,			5,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETBOIDVIEWRADIUS,		ID_FROMBOIDTYPE_GETBOIDVIEWRADIUS,		6,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETAVOIDANCERADIUS,		ID_FROMBOIDTYPE_GETAVOIDANCERADIUS,		7,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETRANDOMIZATION,		ID_FROMBOIDTYPE_GETRANDOMIZATION,		8,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETVIEWRADIUS,			ID_FROMBOIDTYPE_GETVIEWRADIUS,			9,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETSEPARATIONWEIGHT,	ID_FROMBOIDTYPE_GETSEPARATIONWEIGHT,	10,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETALIGNMENTWEIGHT,		ID_FROMBOIDTYPE_GETALIGNMENTWEIGHT,		11,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMBOIDTYPE_GETCOHESIONWEIGHT,		ID_FROMBOIDTYPE_GETCOHESIONWEIGHT,		12,	0,	1,	EXPPARAM_LONG,	IDS_EXPBOIDTYPE,
		ID_FROMOBJECT_GETANGLE,					ID_FROMOBJECT_GETANGLE,					13,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,
		ID_FROMOBJECT_GETSPEED,					ID_FROMOBJECT_GETSPEED,					14,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,
		ID_FROMOBJECT_GETXSPEED,				ID_FROMOBJECT_GETXSPEED,				15,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,	
		ID_FROMOBJECT_GETYSPEED,				ID_FROMOBJECT_GETYSPEED,				16,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,
		ID_FROMOBJECT_GETTARGETX,				ID_FROMOBJECT_GETTARGETX,				17,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,
		ID_FROMOBJECT_GETTARGETY,				ID_FROMOBJECT_GETTARGETY,				18,	0,	1,	EXPPARAM_LONG,	IDS_FIXEDVALUE,	
		ID_LOOPCURRENT_GETANGLE,				ID_LOOPCURRENT_GETANGLE,				19,	0,	0,
		ID_LOOPCURRENT_GETSPEED,				ID_LOOPCURRENT_GETSPEED,				20,	0,	0,
		ID_LOOPCURRENT_GETXSPEED,				ID_LOOPCURRENT_GETXSPEED,				21,	0,	0,
		ID_LOOPCURRENT_GETYSPEED,				ID_LOOPCURRENT_GETYSPEED,				22,	0,	0,
		ID_LOOPCURRENT_GETTARGETX,				ID_LOOPCURRENT_GETTARGETX,				23,	0,	0,
		ID_LOOPCURRENT_GETTARGETY,				ID_LOOPCURRENT_GETTARGETY,				24,	0,	0,
		};


_inline float GetFloatParamEx(LPRDATA rdPtr)
{
	long val = CNC_GetFloatParameter(rdPtr);
	return *(float*)&val;
}

_inline float RecastFloat(long value)
{
	return *(float*)&value;
}

// ============================================================================
//
// CONDITION ROUTINES
// 
// ============================================================================

// -----------------
// Sample Condition
// -----------------
// Returns TRUE when the two values are equal!
// 

long WINAPI DLLExport con_onLoopedBoid(LPRDATA rdPtr, long param1, long param2)
{
	if(rdPtr->numLoops == 0 || rdPtr->numLoops > 9)
		return false;

	char* loopName = (char*)param1;
	eventParam* evtParam = ((eventParam*)param2);
	short oi = evtParam->evp.evpW.evpW1;

	BoidLoop currentLoop = rdPtr->boidLoops[rdPtr->numLoops-1];
	bool nameEquals = (strcmp(loopName, currentLoop.name) == 0);
	if(!nameEquals)
		return false;

	LPRO object = LproFromFixed(rdPtr, rdPtr->loopedBoid.fixedValue);
	ObjectSelection select = ObjectSelection(rdPtr->rHo.hoAdRunHeader, rdPtr->hwa, rdPtr->unicode);

	if(object != NULL && select.ObjectIsOfType(object, oi))
	{
		rdPtr->rHo.hoAdRunHeader->rh2.rh2ActionOn = true;
		select.SelectOneObject(object);
		return true;
	}
	select.SelectNone(oi);
	return false;
}


// ============================================================================
//
// ACTIONS ROUTINES
// 
// ============================================================================

short WINAPI DLLExport act_addObjectAsBoid(LPRDATA rdPtr, long param1, long boidType)
{
	LPRO object = (LPRO)param1;

	if(object == NULL)
		return 0;

	long fixedValue = FixedValue((LPRO)param1);

	//Loop through all elements to ensure it isn't added twice.
	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();
	for(; it != end; ++it)
		if(it->second.fixedValue == fixedValue)
			return 0;
	
	//Object wasn't already in the flock, so add it.
	Boid b = {0};
	b.fixedValue = fixedValue;

	if(rdPtr->hwa)
		b.dirAngle	= 360.0f - *(float*)&object->roc.rcAngle;
	else
		b.dirAngle	= 360.0f - (float)object->roc.rcAngle;
	
	
	b.dirX		= cos(ToRadians(b.dirAngle));
	b.dirY		= sin(ToRadians(b.dirAngle));
	b.x			= (float)object->roHo.hoX;
	b.y			= (float)object->roHo.hoY;
	b.boidType	= boidType;
	b.cellX		= object->roHo.hoX / rdPtr->cellsize;
	b.cellY		= object->roHo.hoY / rdPtr->cellsize;

	b.targetX = b.targetY = b.targetDistance = b.forceX = b.forceY = 0.0f;

	Cell cellpos = Cell((int)(b.x/rdPtr->cellsize),(int)(b.y/rdPtr->cellsize));
	CellBoidPair newElement = CellBoidPair(cellpos,b);
	rdPtr->cells->insert(newElement);
	
	return 0;
}

short WINAPI DLLExport act_removeObject(LPRDATA rdPtr, long param1, long param2)
{
	LPRO object = (LPRO)param1;

	if(object == NULL)
		return 0;

	long fixedValue = FixedValue((LPRO)param1);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();
	for(; it != end; ++it)
		if(it->second.fixedValue == fixedValue)
		{
			rdPtr->cells->erase(it);
			return 0;
		}
	return 0;
}

short WINAPI DLLExport act_setIdleSpeed(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].idleSpeed = value;
	return 0;
}

short WINAPI DLLExport act_setMinSpeed(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].minSpeed = value;
	return 0;
}

short WINAPI DLLExport act_setMaxSpeed(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].maxSpeed = value;
	return 0;
}

short WINAPI DLLExport act_setAcceleration(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].acceleration = value;
	return 0;
}

short WINAPI DLLExport act_setDeceleration(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].deceleration = value;
	return 0;
}

short WINAPI DLLExport act_setTurnSpeed(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].turnSpeed = value;
	return 0;
}

short WINAPI DLLExport act_setViewRadius(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].viewRadius = value;
	return 0;
}

short WINAPI DLLExport act_setAvoidanceRadius(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].avoidanceRadius = value;
	return 0;
}

short WINAPI DLLExport act_setMovementRandomization(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].movementRandomization = value;
	return 0;
}

short WINAPI DLLExport act_setSeparationWeight(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].separationWeight = value;
	return 0;
}

short WINAPI DLLExport act_setAlignmentWeight(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].alignmentWeight = value;
	return 0;
}

short WINAPI DLLExport act_setCohesionWeight(LPRDATA rdPtr, long param1, long param2)
{
	int index = CNC_GetIntParameter(rdPtr);
	float value = RecastFloat(CNC_GetFloatParameter(rdPtr));
	rdPtr->boidtypes[index].cohesionWeight = value;
	return 0;
}


short WINAPI DLLExport act_SetAngleDirSetting(LPRDATA rdPtr, long param1, long param2)
{
	int index = param1;
	char value = (char)param2;
	rdPtr->boidtypes[index].angleDirSetting = value;
	return 0;
}

short WINAPI DLLExport act_SetTurnSpeedSetting(LPRDATA rdPtr, long param1, long param2)
{
	int index = param1;
	char value = (char)param2;
	rdPtr->boidtypes[index].speedDependantTurn = (value != 0);
	return 0;
}

short WINAPI DLLExport act_SetAvoidObstacleSetting(LPRDATA rdPtr, long param1, long param2)
{
	int index = param1;
	char value = (char)param2;
	rdPtr->boidtypes[index].avoidObstacles = (value != 0);
	return 0;
}


///////////////////////
//////ALL OF TYPE//////
///////////////////////
short WINAPI DLLExport act_allOfType_attractTowardsPosition(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.boidType == type)
		{
			float dX = boid.x-posX;
			float dY = boid.y-posY;
			float invDistance = 1.0f/sqrtf(dX*dX+dY*dY);
			boid.forceX += (posX - boid.x) * invDistance * weight;
			boid.forceY += (posY - boid.y) * invDistance * weight;
		}
	}

	return 0;
}

short WINAPI DLLExport act_allOfType_chaseAwayFromPosition(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.boidType == type)
		{
			float dX = boid.x-posX;
			float dY = boid.y-posY;
			float invDistance = 1.0f/sqrtf(dX*dX+dY*dY);
			boid.forceX += (boid.x - posX) * invDistance * weight;
			boid.forceY += (boid.y - posY) * invDistance * weight;
		}
	}

	return 0;
}

short WINAPI DLLExport act_allOfType_applyForce(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	float forceX = GetFloatParamEx(rdPtr);
	float forceY = GetFloatParamEx(rdPtr);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.boidType == type)
		{
			boid.forceX += forceX;
			boid.forceY += forceY;
		}
	}

	return 0;
}


///////////////////////
/////WITHIN RAIDUS/////
///////////////////////
short WINAPI DLLExport act_withinRadius_attractTowardsPosition(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	int radius = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	float cellsize = (float)rdPtr->cellsize;
	int startCellX = (int)floorf((posX - radius)/cellsize);
	int endCellX = (int)ceilf((posX + radius)/cellsize);
	int startCellY = (int)floorf((posY - radius)/cellsize);
	int endCellY = (int)ceilf((posY + radius)/cellsize);

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
				Boid & boid = cellit->second;
				if(boid.boidType != type)
					continue;

				float diffX = boid.x-posX;
				float diffY = boid.y-posY;
				float distance = sqrtf(diffX*diffX+diffY*diffY);
				if(distance < radius)
				{
					float factor = 1.0f - (distance / radius);
					boid.forceX += (posX - boid.x) * factor * weight;
					boid.forceY += (posY - boid.y) * factor * weight;
				}
			}
		}
	}

	return 0;
}

short WINAPI DLLExport act_withinRadius_chaseAwayFromPosition(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	int radius = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	float cellsize = (float)rdPtr->cellsize;
	int startCellX = (int)floorf((posX - radius)/cellsize);
	int endCellX = (int)ceilf((posX + radius)/cellsize);
	int startCellY = (int)floorf((posY - radius)/cellsize);
	int endCellY = (int)ceilf((posY + radius)/cellsize);

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
				Boid & boid = cellit->second;
				if(boid.boidType != type)
					continue;

				float diffX = boid.x-posX;
				float diffY = boid.y-posY;
				float distance = sqrtf(diffX*diffX+diffY*diffY);
				if(distance < radius)
				{
					float factor = 1.0f - (distance / radius);
					boid.forceX += (boid.x - posX) * factor * weight;
					boid.forceY += (boid.y - posY) * factor * weight;
				}
			}
		}
	}

	return 0;
}

short WINAPI DLLExport act_withinRadius_applyForce(LPRDATA rdPtr, long param1, long param2)
{
	int type = CNC_GetIntParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	int radius = CNC_GetIntParameter(rdPtr);
	float forceX = GetFloatParamEx(rdPtr);
	float forceY = GetFloatParamEx(rdPtr);

	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	float cellsize = (float)rdPtr->cellsize;
	int startCellX = (int)floorf((posX - radius)/cellsize);
	int endCellX = (int)ceilf((posX + radius)/cellsize);
	int startCellY = (int)floorf((posY - radius)/cellsize);
	int endCellY = (int)ceilf((posY + radius)/cellsize);

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
				Boid & boid = cellit->second;
				if(boid.boidType != type)
					continue;

				float diffX = boid.x-posX;
				float diffY = boid.y-posY;
				float distance = sqrtf(diffX*diffX+diffY*diffY);
				if(distance < radius)
				{
					float factor = 1.0f - (distance / radius);
					boid.forceX += forceX * factor;
					boid.forceY += forceY * factor;
				}
			}
		}
	}

	return 0;
}



///////////////////////
//////SINGLE BOID//////
///////////////////////
short WINAPI DLLExport act_singleBoid_attractTowardsPosition(LPRDATA rdPtr, long param1, long param2)
{
	LPRO object = (LPRO)CNC_GetParameter(rdPtr);;
	
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	if(object == NULL)
		return 0;

	long fixed = FixedValue(object);
	Cell cell = Cell(object->roHo.hoX/rdPtr->cellsize, object->roHo.hoY/rdPtr->cellsize);

	CellMap::iterator it = rdPtr->cells->find(cell);
	CellMap::iterator end = rdPtr->cells->upper_bound(cell);

	if(it == rdPtr->cells->end())
		return 0;

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;

		if(boid.fixedValue == fixed)
		{
			boid.forceX += (posX - boid.x) * weight;
			boid.forceY += (posY - boid.y) * weight;
			return 0;
		}
	}

	return 0;
}

short WINAPI DLLExport act_singleBoid_chaseAwayFromPosition(LPRDATA rdPtr, long param1, long param2)
{
	LPRO object = (LPRO)CNC_GetParameter(rdPtr);
	int posX = CNC_GetIntParameter(rdPtr);
	int posY = CNC_GetIntParameter(rdPtr);
	float weight = GetFloatParamEx(rdPtr);

	if(object == NULL)
		return 0;

	long fixed = FixedValue(object);
	Cell cell = Cell(object->roHo.hoX/rdPtr->cellsize, object->roHo.hoY/rdPtr->cellsize);
	CellMap::iterator it = rdPtr->cells->find(cell);
	
	if(it == rdPtr->cells->end())
		return 0;

	CellMap::iterator end = rdPtr->cells->upper_bound(cell);

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.fixedValue == fixed)
		{
			float dX = boid.x-posX;
			float dY = boid.y-posY;
			float invDistance = 1.0f/sqrtf(dX*dX+dY*dY);
			boid.forceX += (boid.x - posX) * invDistance * weight;
			boid.forceY += (boid.y - posY) * invDistance * weight;
			return 0;
		}
	}

	return 0;
}

short WINAPI DLLExport act_singleBoid_applyForce(LPRDATA rdPtr, long param1, long param2)
{
	LPRO object = (LPRO)CNC_GetParameter(rdPtr);
	float forceX = GetFloatParamEx(rdPtr);
	float forceY = GetFloatParamEx(rdPtr);

	if(object == NULL)
		return 0;

	long fixed = FixedValue(object);
	Cell cell = Cell(object->roHo.hoX/rdPtr->cellsize, object->roHo.hoY/rdPtr->cellsize);
	CellMap::iterator it = rdPtr->cells->find(cell);

	if(it == rdPtr->cells->end())
		return 0;
	
	CellMap::iterator end = rdPtr->cells->upper_bound(cell);

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.fixedValue == fixed)
		{
			boid.forceX += forceX;
			boid.forceY += forceY;
			return 0;
		}
	}
	return 0;
}


///////////////////////
///////LOOPING/////////
///////////////////////
short WINAPI DLLExport act_loopNeighbourBoids(LPRDATA rdPtr, long param1, long param2)
{
	char* loopname = (char*)CNC_GetStringParameter(rdPtr);
	LPRO object = (LPRO)CNC_GetParameter(rdPtr);
	int radius = CNC_GetIntParameter(rdPtr);

	if(object == NULL)
		return 0;

	long fixed = FixedValue(object);

	int cellX = object->roHo.hoX/rdPtr->cellsize;
	int cellY = object->roHo.hoY/rdPtr->cellsize;
	Cell cell = Cell(cellX,cellY);

	CellMap::iterator it = rdPtr->cells->find(cell);
	if(it == rdPtr->cells->end())
		return 0;
	CellMap::iterator end = rdPtr->cells->upper_bound(cell);

	for(; it!=end; ++it)
	{
		Boid & boid = it->second;
		if(boid.fixedValue == fixed)
		{
			LoopNeighbourBoids(rdPtr, loopname, boid, radius);
			return 0;
		}
	}
	return 0;
}



short WINAPI DLLExport act_loopBoidsInRadius(LPRDATA rdPtr, long param1, long param2)
{
	char* loopname = (char*)CNC_GetStringParameter(rdPtr);
	int xPos = CNC_GetIntParameter(rdPtr);
	int yPos = CNC_GetIntParameter(rdPtr);
	int radius = CNC_GetIntParameter(rdPtr);
	if(rdPtr->numLoops >= 9)
		return 0;
	BoidLoop &currentLoop = rdPtr->boidLoops[rdPtr->numLoops];
	rdPtr->numLoops++;
	strcpy_s(currentLoop.name, 31, loopname);
	float cellsize = (float)rdPtr->cellsize;
	
	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	std::vector<Boid> foundBoids = std::vector<Boid>();

	int left = xPos-radius;
	int right = xPos+radius;
	int top = yPos-radius;
	int bottom = yPos+radius;

	int startCellX = (int)floorf(left/cellsize);
	int endCellX = (int)ceilf(right/cellsize);
	int startCellY = (int)floorf(top/cellsize);
	int endCellY = (int)ceilf(bottom/cellsize);

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
				Boid & boid = cellit->second;
				float xDist = xPos - boid.x;
				float yDist = yPos - boid.y;
				float distance = sqrtf(xDist*xDist + yDist*yDist);

				if(distance >= radius)
					continue;

				foundBoids.push_back(boid);
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
	return 0;
}

short WINAPI DLLExport act_loopBoidsInRectangle(LPRDATA rdPtr, long param1, long param2)
{
	char* loopname = (char*)CNC_GetStringParameter(rdPtr);
	int xPos = CNC_GetIntParameter(rdPtr);
	int yPos = CNC_GetIntParameter(rdPtr);
	int width = CNC_GetIntParameter(rdPtr);
	int height = CNC_GetIntParameter(rdPtr);

	int right = xPos + width;
	int bottom = yPos + height;

	if(rdPtr->numLoops >= 9)
		return 0;

	BoidLoop &currentLoop = rdPtr->boidLoops[rdPtr->numLoops];
	rdPtr->numLoops++;
	strcpy_s(currentLoop.name, 31, loopname);
	float cellsize = (float)rdPtr->cellsize;
	
	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator cellit;
	CellMap::iterator lastElement;

	std::vector<Boid> foundBoids = std::vector<Boid>();

	int startCellX = (int)floorf(xPos/cellsize);
	int endCellX = (int)ceilf(right/cellsize);
	int startCellY = (int)floorf(yPos/cellsize);
	int endCellY = (int)ceilf(bottom/cellsize);

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
				Boid & boid = cellit->second;
				if( boid.x < xPos || boid.y < yPos || boid.x > right || boid.y > bottom )
					continue;
				foundBoids.push_back(boid);
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
	return 0;
}

short WINAPI DLLExport act_loopAllBoids(LPRDATA rdPtr, long param1, long param2)
{
	char* loopname = (char*)CNC_GetStringParameter(rdPtr);
	if(rdPtr->numLoops >= 9)
		return 0;

	BoidLoop &currentLoop = rdPtr->boidLoops[rdPtr->numLoops];
	rdPtr->numLoops++;
	strcpy_s(currentLoop.name, 31, loopname);

	CellMap::iterator lastElement = rdPtr->cells->end();
	std::vector<Boid> foundBoids = std::vector<Boid>();

	for(CellMap::iterator cellit = rdPtr->cells->begin(); cellit != lastElement; ++cellit )
	{
		Boid & boid = cellit->second;
		foundBoids.push_back(boid);
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
	return 0;
}

short WINAPI DLLExport act_loopAllBoidsOfType(LPRDATA rdPtr, long param1, long param2)
{
	char* loopname = (char*)CNC_GetStringParameter(rdPtr);
	if(rdPtr->numLoops >= 9)
		return 0;
	int boidType = CNC_GetIntParameter(rdPtr);

	BoidLoop &currentLoop = rdPtr->boidLoops[rdPtr->numLoops];
	rdPtr->numLoops++;
	strcpy_s(currentLoop.name, 31, loopname);

	CellMap::iterator lastElement = rdPtr->cells->end();
	std::vector<Boid> foundBoids = std::vector<Boid>();

	for(CellMap::iterator cellit = rdPtr->cells->begin(); cellit != lastElement; ++cellit )
	{
		Boid & boid = cellit->second;
		LPRO object = LproFromFixed(rdPtr, boid.fixedValue);
		if(boid.boidType == boidType)
			foundBoids.push_back(boid);
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
	return 0;
}


// ============================================================================
//
// EXPRESSIONS ROUTINES
// 
// ============================================================================

long WINAPI DLLExport exp_fromBoidType_getIdleSpeed(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].idleSpeed;
    return *((long*)&fResult);
}
long WINAPI DLLExport exp_fromBoidType_getMinSpeed(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].minSpeed;
    return *((long*)&fResult);
}
long WINAPI DLLExport exp_fromBoidType_getMaxSpeed(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].maxSpeed;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getAcceleration(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].acceleration;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getDeceleration(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].deceleration;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getTurnSpeed(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].turnSpeed;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getBoidViewRadius(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].viewRadius;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getAvoidanceRadius(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].avoidanceRadius;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getMovementRandomization(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].movementRandomization;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getViewRadius(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].viewRadius;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getSeparationWeight(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].separationWeight;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getAlignmentWeight(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
	rdPtr->rHo.hoFlags |= HOF_FLOAT;
	float fResult = rdPtr->boidtypes[boidType].alignmentWeight;
    return *((long*)&fResult);
}

long WINAPI DLLExport exp_fromBoidType_getCohesionWeight(LPRDATA rdPtr,long param1)
{
	long boidType = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_INT);
    return returnFloat(rdPtr, rdPtr->boidtypes[boidType].cohesionWeight);
}

long WINAPI DLLExport exp_fromObject_getAngle(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.dirAngle);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_fromObject_getSpeed(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.speed);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_fromObject_getXspeed(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.forceX);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_fromObject_getYspeed(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.forceY);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_fromObject_getTargetX(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.targetX);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_fromObject_getTargetY(LPRDATA rdPtr,long param1)
{
	long fixed = CNC_GetFirstExpressionParameter(rdPtr, param1, TYPE_LONG);

	CellMap::iterator it = rdPtr->cells->begin();
	CellMap::iterator end = rdPtr->cells->end();

	for(; it != end; ++it)
		if(it->second.fixedValue == fixed)
			return returnFloat(rdPtr, it->second.targetY);
	return returnFloat(rdPtr, 0.0f);
}

long WINAPI DLLExport exp_current_getAngle(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.dirAngle);
}

long WINAPI DLLExport exp_current_getSpeed(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.speed);
}

long WINAPI DLLExport exp_current_getXspeed(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.forceX);
}

long WINAPI DLLExport exp_current_getYspeed(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.forceY);
}

long WINAPI DLLExport exp_current_getTargetX(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.targetX);
}

long WINAPI DLLExport exp_current_getTargetY(LPRDATA rdPtr,long param1)
{
	return returnFloat(rdPtr, rdPtr->loopedBoid.targetY);
}



// ----------------------------------------------------------
// Condition / Action / Expression jump table
// ----------------------------------------------------------
// Contains the address inside the extension of the different
// routines that handle the action, conditions and expressions.
// Located at the end of the source for convinience
// Must finish with a 0
//
long (WINAPI * ConditionJumps[])(LPRDATA rdPtr, long param1, long param2) = 
			{ 
			con_onLoopedBoid,
			0
			};
	
short (WINAPI * ActionJumps[])(LPRDATA rdPtr, long param1, long param2) =
			{
			act_addObjectAsBoid,
			act_removeObject,
			act_setIdleSpeed,
			act_setMinSpeed,
			act_setMaxSpeed,
			act_setAcceleration,
			act_setDeceleration,
			act_setTurnSpeed,
			act_setViewRadius,
			act_setAvoidanceRadius,
			act_setMovementRandomization,
			act_setSeparationWeight,
			act_setAlignmentWeight,
			act_setCohesionWeight,
			act_SetAngleDirSetting,
			act_SetTurnSpeedSetting,
			act_SetAvoidObstacleSetting,
			act_allOfType_attractTowardsPosition,
			act_allOfType_chaseAwayFromPosition,
			act_allOfType_applyForce,
			act_withinRadius_attractTowardsPosition,
			act_withinRadius_chaseAwayFromPosition,
			act_withinRadius_applyForce,
			act_singleBoid_attractTowardsPosition,
			act_singleBoid_chaseAwayFromPosition,
			act_singleBoid_applyForce,
			act_loopNeighbourBoids,
			act_loopBoidsInRadius,
			act_loopBoidsInRectangle,
			act_loopAllBoids,
			act_loopAllBoidsOfType,
			0
			};

long (WINAPI * ExpressionJumps[])(LPRDATA rdPtr, long param) = 
			{
			exp_fromBoidType_getIdleSpeed,
			exp_fromBoidType_getMinSpeed,
			exp_fromBoidType_getMaxSpeed,
			exp_fromBoidType_getAcceleration,
			exp_fromBoidType_getDeceleration,
			exp_fromBoidType_getTurnSpeed,
			exp_fromBoidType_getBoidViewRadius,
			exp_fromBoidType_getAvoidanceRadius,
			exp_fromBoidType_getMovementRandomization,
			exp_fromBoidType_getViewRadius,
			exp_fromBoidType_getSeparationWeight,
			exp_fromBoidType_getAlignmentWeight,
			exp_fromBoidType_getCohesionWeight,
			exp_fromObject_getAngle,
			exp_fromObject_getSpeed,
			exp_fromObject_getXspeed,
			exp_fromObject_getYspeed,
			exp_fromObject_getTargetX,
			exp_fromObject_getTargetY,
			exp_current_getAngle,
			exp_current_getSpeed,
			exp_current_getXspeed,
			exp_current_getYspeed,
			exp_current_getTargetX,
			exp_current_getTargetY,
			0
			};