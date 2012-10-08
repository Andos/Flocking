// Object identifier "Floc"
#define IDENTIFIER	MAKEID(F,l,o,c)

#include <vector>
#include <hash_map>
#include <map>

class ObjectSelection;

// ------------------------------
// LAST CODES
// ------------------------------
#define	CND_LAST					1
#define	ACT_LAST					31
#define	EXP_LAST                    25

#define ANGLE_SETTING				0
#define DIR_SETTING					1
#define NODIR_SETTING				2

struct BoidType
{
	float idleSpeed, minSpeed, maxSpeed, acceleration, deceleration, turnSpeed;
	float viewRadius, avoidanceRadius;
	float movementRandomization;
	float separationWeight, alignmentWeight, cohesionWeight;
	char angleDirSetting;
	bool avoidObstacles;
	bool speedDependantTurn;
};

struct Boid
{
	long fixedValue;
	int boidType;
	int cellX, cellY;
	float x, y;
	float oldX, oldY;
	float speed, oldSpeed;
	float dirAngle, dirX, dirY;
	float sepX, sepY, cohX, cohY, aliX, aliY;
	float forceX, forceY;
	float targetX, targetY, targetDistance;
	
	int sepNeighbourCount;
	int aliCohNeighbourCount;
};

struct BoidLoop
{
	char name[32];
};

struct Vec2f
{
	float x,y;
};

struct Vec2i
{
	int x,y;
};

typedef std::pair<int,int>					Cell;

struct CellHash : public stdext::hash_compare<Cell>{
	size_t operator()(const Cell& p) const {
		return p.first*239 + p.second*137;
	}
	bool operator()(const Cell& a, const Cell& b) const {
		return a.first < b.first && a.second < b.second;
	}
};

//typedef std::multimap<Cell,Boid> CellMap;		//Slow beyond imagination in debug mode
typedef stdext::hash_multimap<Cell,Boid, CellHash> CellMap;
typedef std::pair<Cell,Boid>	CellBoidPair;



// ---------------------
// OBJECT DATA STRUCTURE 
// ---------------------
// Used at edit time and saved in the MFA/CCN/EXE files

typedef struct tagEDATA_V1
{
	// Header - required
	extHeader		eHeader;
	int				cellsize;
	BoidType		defaultParameters;

	// Object's data
//	short			swidth;
//	short			sheight;

} EDITDATA;
typedef EDITDATA *			LPEDATA;

// Object versions
#define	KCX_CURRENT_VERSION			1

// --------------------------------
// RUNNING OBJECT DATA STRUCTURE
// --------------------------------
typedef struct tagRDATA
{
	// Main header - required
	headerObject	rHo;					// Header

	//Mapping from a cell into a number of Boids in that cell.
	CellMap* cells;
	int	cellsize;
	BoidType boidtypes[100];
	
	bool hwa;
	bool unicode;

	int numLoops;
	BoidLoop boidLoops[10];

	Boid loopedBoid;
	Boid centerBoid;
} RUNDATA;
typedef	RUNDATA	*			LPRDATA;

// Size when editing the object under level editor
// -----------------------------------------------
#define	MAX_EDITSIZE			sizeof(EDITDATA)

// Default flags - see documentation for more info
// -------------
#define	OEFLAGS      			0
#define	OEPREFS      			0


// If to handle message, specify the priority of the handling procedure
// 0= low, 255= very high. You should use 100 as normal.                                                
// --------------------------------------------------------------------
#define	WINDOWPROC_PRIORITY		100




long FixedValue( LPRO object );
LPRO LPROFromFixed( LPRDATA rdPtr, long fixedvalue );
long returnFloat(LPRDATA rdPtr, float value);

/*
void Debug( char * string, int value );
void Debug( char * string, float value );
void Debug( char * string, float valueA, float valueB );
void DebugObject(Boid boid);
*/
float RotateTowards(float angle, float targetAngle, float speed);
float ToRadians(float degrees);
float ToDegrees(float radians);

int packFloat(float value);
void LoopNeighbourBoids(LPRDATA rdPtr, char* loopname, Boid boid, int radius);

Vec2i TracePosition(headerObject* rHo, int layer, Vec2i a, Vec2i b);
float clamp(float val, float min, float max);

float Q_rsqrt( float number );