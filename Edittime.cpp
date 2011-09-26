
// ============================================================================
//
// This file contains routines that are handled only during the Edittime,
// under the Frame and Event editors.
//
// Including creating, display, and setting up your object.
// 
// ============================================================================

// Common
#include	"common.h"

#if !defined(RUN_ONLY)

// PROPERTIES /////////////////////////////////////////////////////////////////

// Property identifiers
enum {
	PROPID_SETTINGS = PROPID_EXTITEM_CUSTOM_FIRST,
	
	PROPID_FLOCKINGHEADER_TITLE,
	PROPID_CELLSIZE,

	PROPID_DEFAULTPARAMETER_TITLE,
	PROPID_IDLESPEED,
	PROPID_MINSPEED,
	PROPID_MAXSPEED,
	PROPID_ACCELERATION,
	PROPID_DECELERATION,
	PROPID_TURNSPEED,
	PROPID_VIEWRADIUS,
	PROPID_AVOIDANCERADIUS,
	PROPID_RANDOMIZATION,
	PROPID_ANGLEDIRSETTING,
	PROPID_SPEEDDEPENDANTTURN,
	PROPID_AVOIDOBSTACLES,

	PROPID_DEFAULTWEIGHT_TITLE,
	PROPID_SEPARATIONWEIGHT,
	PROPID_ALIGNMENTWEIGHT,
	PROPID_COHESIONWEIGHT,
};

// Example of content of the PROPID_COMBO combo box
LPCSTR AngleDirList[] = {
	0,	
	MAKEINTRESOURCE(IDS_USEANGLES),	
	MAKEINTRESOURCE(IDS_USEDIRECTIONS),
	MAKEINTRESOURCE(IDS_USENONE),
	NULL
};

// Property definitions
//
// Type, ID, Text, Text of Info box [, Options, Init Param]
//
PropData Properties[] = {

	PropData_Group		(PROPID_FLOCKINGHEADER_TITLE,	IDS_FLOCKINGHEADER_TITLE,		IDS_FLOCKINGHEADER_TITLE),
	PropData_EditNumber	(PROPID_CELLSIZE,				IDS_PROP_CELLSIZE,				IDS_PROPINFO_CELLSIZE),

	PropData_Group		(PROPID_DEFAULTPARAMETER_TITLE,	IDS_DEFAULTPARAMETERS,			IDS_DEFAULTPARAMETERS),
	PropData_EditFloat	(PROPID_IDLESPEED,				IDS_PROP_IDLESPEED,				IDS_PROPINFO_IDLESPEED),
	PropData_EditFloat	(PROPID_MINSPEED,				IDS_PROP_MINSPEED,				IDS_PROPINFO_MINSPEED),
	PropData_EditFloat	(PROPID_MAXSPEED,				IDS_PROP_MAXSPEED,				IDS_PROPINFO_MAXSPEED),
	PropData_EditFloat	(PROPID_ACCELERATION,			IDS_PROP_ACCELERATION,			IDS_PROPINFO_ACCELERATION),
	PropData_EditFloat	(PROPID_DECELERATION,			IDS_PROP_DECELERATION,			IDS_PROPINFO_DECELERATION),
	PropData_EditFloat	(PROPID_TURNSPEED,				IDS_PROP_TURNSPEED,				IDS_PROPINFO_TURNSPEED),
	PropData_EditFloat	(PROPID_VIEWRADIUS,				IDS_PROP_VIEWRADIUS,			IDS_PROPINFO_VIEWRADIUS),
	PropData_EditFloat	(PROPID_AVOIDANCERADIUS,		IDS_PROP_AVOIDANCERADIUS,		IDS_PROPINFO_AVOIDANCERADIUS),
	PropData_EditFloat	(PROPID_RANDOMIZATION,			IDS_PROP_RANDOMIZATION,			IDS_PROP_RANDOMIZATION),
	PropData_ComboBox	(PROPID_ANGLEDIRSETTING,		IDS_PROP_ANGLEDIRSETTING,		IDS_PROPINFO_ANGLEDIRSETTING,	AngleDirList),
	
	PropData_CheckBox	(PROPID_SPEEDDEPENDANTTURN,		IDS_PROP_SPEEDDEPENDANTTURN,	IDS_PROPINFO_SPEEDDEPENDANTTURN),
	PropData_CheckBox	(PROPID_AVOIDOBSTACLES,			IDS_PROP_AVOIDOBSTACLES,		IDS_PROPINFO_AVOIDOBSTACLES),

	PropData_Group		(PROPID_DEFAULTWEIGHT_TITLE,	IDS_DEFAULTWEIGHTS,				IDS_DEFAULTWEIGHTS),
	PropData_EditFloat	(PROPID_SEPARATIONWEIGHT,		IDS_PROP_SEPARATIONWEIGHT,		IDS_PROPINFO_SEPARATIONWEIGHT),
	PropData_EditFloat	(PROPID_ALIGNMENTWEIGHT,		IDS_PROP_ALIGNMENTWEIGHT,		IDS_PROPINFO_ALIGNMENTWEIGHT),
	PropData_EditFloat	(PROPID_COHESIONWEIGHT,			IDS_PROP_COHESIONWEIGHT,		IDS_PROPINFO_COHESIONWEIGHT),

	PropData_End()
};

// SETUP PROC /////////////////////////////////////////////////////////////////

// Prototype of setup procedure
BOOL CALLBACK DLLExport setupProc(HWND hDlg,uint msgType,WPARAM wParam,LPARAM lParam);

// Structure defined to pass edptr and mv into setup box
typedef struct tagSetP
{
	EDITDATA _far *	edpt;
	mv _far	*		kv;
} setupParams;

#endif // !defined(RUN_ONLY)


// -----------------
// GetObjInfos
// -----------------
// Return object info
//
// Info displayed in the object's About properties
// Note: ObjComment is also displayed in the Quick Description box in the Insert Object dialog box
//
void WINAPI	DLLExport GetObjInfos (mv _far *mV, LPEDATA edPtr, LPSTR ObjName, LPSTR ObjAuthor, LPSTR ObjCopyright, LPSTR ObjComment, LPSTR ObjHttp)
{
#ifndef RUN_ONLY
	// Name
	LoadString(hInstLib, IDST_OBJNAME,ObjName, 255);

	// Author
	LoadString(hInstLib, IDST_AUTHOR,ObjAuthor,255);

	// Copyright
	LoadString(hInstLib, IDST_COPYRIGHT,ObjCopyright,255);

	// Comment
	LoadString(hInstLib, IDST_COMMENT,ObjComment,1024);

	// Internet address
	LoadString(hInstLib, IDST_HTTP,ObjHttp,255);
#endif // !defined(RUN_ONLY)
}

// -----------------
// GetHelpFileName
// -----------------
// Returns the help filename of the object.
//
LPCSTR WINAPI GetHelpFileName()
{
#ifndef RUN_ONLY
	// Return a file without path if your help file can be loaded by the MMF help file.
//	return "MyExt.chm";

	// Or return the path of your file, relatively to the MMF directory
	// if your file is not loaded by the MMF help file.
	return "Help\\MyExt.chm";
#else
	return NULL;
#endif // !defined(RUN_ONLY)
}


// ============================================================================
//
// ROUTINES USED UNDER FRAME EDITOR
// 
// ============================================================================

// --------------------
// CreateObject
// --------------------
// Called when you choose "Create new object". It should display the setup box 
// and initialize everything in the datazone.

int WINAPI DLLExport CreateObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr)
{
	BoidType & f = edPtr->defaultParameters;

	f.idleSpeed = 1.0f;
	f.minSpeed = 0.0f;
	f.maxSpeed = 1.0f;
	f.acceleration = 5.0f;
	f.deceleration = 5.0f;
	f.turnSpeed = 10.0f;
	f.viewRadius = 99.0f;
	f.avoidanceRadius = 32.0f;
	f.movementRandomization = 0.0;
	f.angleDirSetting = 0;
	f.separationWeight = 1.0f;
	f.alignmentWeight =  0.1f;
	f.cohesionWeight = 0.01f;
	f.avoidObstacles = 0;
	f.speedDependantTurn = 1;

	edPtr->cellsize = 100;
	return 0;
}

// --------------------
// EditObject
// --------------------
// Called when the user selects the Edit command in the object's popup menu
//
BOOL WINAPI EditObject (mv _far *mV, fpObjInfo oiPtr, fpLevObj loPtr, LPEDATA edPtr)
{
	return FALSE;
}

// --------------------
// PutObject
// --------------------
// Called when each individual object is dropped in the frame.
//
void WINAPI	DLLExport PutObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
#ifndef RUN_ONLY
#endif // !defined(RUN_ONLY)
}

// --------------------
// RemoveObject
// --------------------
// Called when each individual object is removed from the frame.
//
void WINAPI	DLLExport RemoveObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
#ifndef RUN_ONLY
	// Is the last object removed?
    if (0 == cpt)
	{
		// Do whatever necessary to remove our data
	}
#endif // !defined(RUN_ONLY)
}

// --------------------
// DuplicateObject
// --------------------
void WINAPI DLLExport DuplicateObject(mv __far *mV, fpObjInfo oiPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetObjectRect
// --------------------
void WINAPI DLLExport GetObjectRect(mv _far *mV, RECT FAR *rc, fpLevObj loPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	rc->right = rc->left + 32;	// edPtr->swidth;
	rc->bottom = rc->top + 32;	// edPtr->sheight;
#endif // !defined(RUN_ONLY)
	return;
}



// --------------------
// IsTransparent
// --------------------
extern "C" BOOL WINAPI DLLExport IsTransparent(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, int dx, int dy)
{
	return FALSE;
}

// --------------------
// PrepareToWriteObject
// --------------------
void WINAPI	DLLExport PrepareToWriteObject(mv _far *mV, LPEDATA edPtr, fpObjInfo adoi)
{
#ifndef RUN_ONLY
	// Write your code here
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetFilters
// --------------------
BOOL WINAPI GetFilters(LPMV mV, LPEDATA edPtr, DWORD dwFlags, LPVOID pReserved)
{
	return FALSE;
}

// --------------------
// UsesFile
// --------------------
BOOL WINAPI	DLLExport UsesFile (LPMV mV, LPSTR fileName)
{
	return FALSE;
}


// --------------------
// CreateFromFile
// --------------------
void WINAPI	DLLExport CreateFromFile (LPMV mV, LPSTR fileName, LPEDATA edPtr){}

// ============================================================================
//
// PROPERTIES
// 
// ============================================================================

// --------------------
// GetProperties
// --------------------
BOOL WINAPI DLLExport GetProperties(LPMV mV, LPEDATA edPtr, BOOL bMasterItem)
{
#ifndef RUN_ONLY
	mvInsertProps(mV, edPtr, Properties, PROPID_TAB_GENERAL, TRUE);
#endif // !defined(RUN_ONLY)

	// OK
	return TRUE;
}

// --------------------
// ReleaseProperties
// --------------------
void WINAPI DLLExport ReleaseProperties(LPMV mV, LPEDATA edPtr, BOOL bMasterItem)
{
#ifndef RUN_ONLY
	// Write your code here
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetPropCreateParam
// --------------------
LPARAM WINAPI DLLExport GetPropCreateParam(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
//	if ( nPropID == PROPID_COMBO )
//	{
//		switch (edPtr->sType)
//		{
//		case TYPE1:
//			return (LPARAM)ComboList1;
//		case TYPE2:
//			return (LPARAM)ComboList2;
//		}
//	}
#endif // !defined(RUN_ONLY)
	return NULL;
}

// ----------------------
// ReleasePropCreateParam
// ----------------------
void WINAPI DLLExport ReleasePropCreateParam(LPMV mV, LPEDATA edPtr, UINT nPropID, LPARAM lParam)
{
#ifndef RUN_ONLY
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetPropValue
// --------------------
LPVOID WINAPI DLLExport GetPropValue(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	switch (nPropID)
	{
		case PROPID_CELLSIZE:
			return new CPropDWordValue(edPtr->cellsize);
		case PROPID_IDLESPEED:
			return new CPropFloatValue(edPtr->defaultParameters.idleSpeed);
		case PROPID_MINSPEED:
			return new CPropFloatValue(edPtr->defaultParameters.minSpeed);
		case PROPID_MAXSPEED:
			return new CPropFloatValue(edPtr->defaultParameters.maxSpeed);
		case PROPID_ACCELERATION:
			return new CPropFloatValue(edPtr->defaultParameters.acceleration);
		case PROPID_DECELERATION:
			return new CPropFloatValue(edPtr->defaultParameters.deceleration);
		case PROPID_TURNSPEED:
			return new CPropFloatValue(edPtr->defaultParameters.turnSpeed);
		case PROPID_VIEWRADIUS:
			return new CPropFloatValue(edPtr->defaultParameters.viewRadius);
		case PROPID_AVOIDANCERADIUS:
			return new CPropFloatValue(edPtr->defaultParameters.avoidanceRadius);
		case PROPID_RANDOMIZATION:
			return new CPropFloatValue(edPtr->defaultParameters.movementRandomization);
		case PROPID_ANGLEDIRSETTING:
			return new CPropDWordValue(edPtr->defaultParameters.angleDirSetting);
		case PROPID_SEPARATIONWEIGHT:
			return new CPropFloatValue(edPtr->defaultParameters.separationWeight);
		case PROPID_ALIGNMENTWEIGHT:
			return new CPropFloatValue(edPtr->defaultParameters.alignmentWeight);
		case PROPID_COHESIONWEIGHT:
			return new CPropFloatValue(edPtr->defaultParameters.cohesionWeight);
	}
#endif // !defined(RUN_ONLY)
	return NULL;
}

// --------------------
// GetPropCheck
// --------------------
// Returns the checked state of properties that have a check box.
//
BOOL WINAPI DLLExport GetPropCheck(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY

	switch (nPropID)
	{
		case PROPID_AVOIDOBSTACLES:
			return (bool)edPtr->defaultParameters.avoidObstacles;
			break;
		case PROPID_SPEEDDEPENDANTTURN:
			return (bool)edPtr->defaultParameters.speedDependantTurn;
			break;
	}
#endif // !defined(RUN_ONLY)
	return 0;
}

// --------------------
// SetPropValue
// --------------------
// This routine is called by MMF after a property has been modified.
//
void WINAPI DLLExport SetPropValue(LPMV mV, LPEDATA edPtr, UINT nPropID, LPVOID lParam)
{
#ifndef RUN_ONLY
	// Gets the pointer to the CPropValue structure
	CPropValue* pValue = (CPropValue*)lParam;
	CPropDWordValue* dValue = (CPropDWordValue*)pValue;
	CPropFloatValue* fValue = (CPropFloatValue*)pValue;

	switch (nPropID)
	{
		case PROPID_CELLSIZE:
			edPtr->cellsize = dValue->m_dwValue;
			break;
		case PROPID_IDLESPEED:
			edPtr->defaultParameters.idleSpeed = fValue->m_fValue;
			break;
		case PROPID_MINSPEED:
			edPtr->defaultParameters.minSpeed = fValue->m_fValue;
			break;
		case PROPID_MAXSPEED:
			edPtr->defaultParameters.maxSpeed = fValue->m_fValue;
			break;
		case PROPID_ACCELERATION:
			edPtr->defaultParameters.acceleration = fValue->m_fValue;
			break;
		case PROPID_DECELERATION:
			edPtr->defaultParameters.deceleration = fValue->m_fValue;
			break;
		case PROPID_TURNSPEED:
			edPtr->defaultParameters.turnSpeed = fValue->m_fValue;
			break;
		case PROPID_VIEWRADIUS:
			edPtr->defaultParameters.viewRadius = fValue->m_fValue;
			break;
		case PROPID_AVOIDANCERADIUS:
			edPtr->defaultParameters.avoidanceRadius = fValue->m_fValue;
			break;
		case PROPID_RANDOMIZATION:
			edPtr->defaultParameters.movementRandomization = fValue->m_fValue;
			break;
		case PROPID_ANGLEDIRSETTING:
			edPtr->defaultParameters.angleDirSetting = (char)dValue->m_dwValue;
			break;
		case PROPID_SEPARATIONWEIGHT:
			edPtr->defaultParameters.separationWeight = fValue->m_fValue;
			break;
		case PROPID_ALIGNMENTWEIGHT:
			edPtr->defaultParameters.alignmentWeight = fValue->m_fValue;
			break;
		case PROPID_COHESIONWEIGHT:
			edPtr->defaultParameters.cohesionWeight = fValue->m_fValue;
			break;
		break;
	}
#endif // !defined(RUN_ONLY)
}

// --------------------
// SetPropCheck
// --------------------
// This routine is called by MMF when the user modifies a checkbox in the properties.
//
void WINAPI DLLExport SetPropCheck(LPMV mV, LPEDATA edPtr, UINT nPropID, BOOL nCheck)
{
#ifndef RUN_ONLY

	switch (nPropID)
	{
		case PROPID_AVOIDOBSTACLES:
			edPtr->defaultParameters.avoidObstacles = (nCheck==0) ? false : true;
			mvInvalidateObject(mV, edPtr);
			mvRefreshProp(mV, edPtr, PROPID_AVOIDOBSTACLES, TRUE);
			break;
		case PROPID_SPEEDDEPENDANTTURN:
			edPtr->defaultParameters.speedDependantTurn = (nCheck==0) ? false : true;
			mvInvalidateObject(mV, edPtr);
			mvRefreshProp(mV, edPtr, PROPID_SPEEDDEPENDANTTURN, TRUE);
			break;
	}
#endif // !defined(RUN_ONLY)
}

// --------------------
// EditProp
// --------------------
// This routine is called when the user clicks the button of a Button or EditButton property.
//
BOOL WINAPI DLLExport EditProp(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY

	// Example
	// -------
/*
	if (nPropID==PROPID_EDITCONTENT)
	{
		if ( EditObject(mV, NULL, NULL, edPtr) )
			return TRUE;
	}
*/

#endif // !defined(RUN_ONLY)
	return FALSE;
}

// --------------------
// IsPropEnabled
// --------------------
// This routine returns the enabled state of a property.
//
BOOL WINAPI IsPropEnabled(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
/*
	switch (nPropID) {

	case PROPID_CHECK:
		return (edPtr->nComboIndex != 0);
	}
*/
#endif // !defined(RUN_ONLY)
	return TRUE;
}


// ============================================================================
//
// TEXT PROPERTIES
// 
// ============================================================================

// --------------------
// GetTextCaps
// --------------------
// Return the text capabilities of the object under the frame editor.
//
DWORD WINAPI DLLExport GetTextCaps(mv _far *mV, LPEDATA edPtr)
{
	return 0;	// (TEXT_ALIGN_LEFT|TEXT_ALIGN_HCENTER|TEXT_ALIGN_RIGHT|TEXT_ALIGN_TOP|TEXT_ALIGN_VCENTER|TEXT_ALIGN_BOTTOM|TEXT_FONT|TEXT_COLOR);
}

// --------------------
// GetTextFont
// --------------------
// Return the font used the object.
// Note: the pStyle and cbSize parameters are obsolete and passed for compatibility reasons only.
//
BOOL WINAPI DLLExport GetTextFont(mv _far *mV, LPEDATA edPtr, LPLOGFONT plf, LPSTR pStyle, UINT cbSize)
{
#if !defined(RUN_ONLY)
	// Example: copy LOGFONT structure from EDITDATA
	// memcpy(plf, &edPtr->m_lf, sizeof(LOGFONT));
#endif // !defined(RUN_ONLY)

	return TRUE;
}

// --------------------
// SetTextFont
// --------------------
// Change the font used the object.
// Note: the pStyle parameter is obsolete and passed for compatibility reasons only.
//
BOOL WINAPI DLLExport SetTextFont(mv _far *mV, LPEDATA edPtr, LPLOGFONT plf, LPCSTR pStyle)
{
#if !defined(RUN_ONLY)
	// Example: copy LOGFONT structure to EDITDATA
	// memcpy(&edPtr->m_lf, plf, sizeof(LOGFONT));
#endif // !defined(RUN_ONLY)

	return TRUE;
}

// --------------------
// GetTextClr
// --------------------
// Get the text color of the object.
//
COLORREF WINAPI DLLExport GetTextClr(mv _far *mV, LPEDATA edPtr)
{
	// Example
	return 0;	// edPtr->fontColor;
}

// --------------------
// SetTextClr
// --------------------
// Set the text color of the object.
//
void WINAPI DLLExport SetTextClr(mv _far *mV, LPEDATA edPtr, COLORREF color)
{
	// Example
	//edPtr->fontColor = color;
}

// --------------------
// GetTextAlignment
// --------------------
// Get the text alignment of the object.
//
DWORD WINAPI DLLExport GetTextAlignment(mv _far *mV, LPEDATA edPtr)
{
	DWORD dw = 0;
#if !defined(RUN_ONLY)
	// Example
	// -------
/*	if ( (edPtr->eData.dwFlags & ALIGN_LEFT) != 0 )
		dw |= TEXT_ALIGN_LEFT;
	if ( (edPtr->eData.dwFlags & ALIGN_HCENTER) != 0 )
		dw |= TEXT_ALIGN_HCENTER;
	if ( (edPtr->eData.dwFlags & ALIGN_RIGHT) != 0 )
		dw |= TEXT_ALIGN_RIGHT;
	if ( (edPtr->eData.dwFlags & ALIGN_TOP) != 0 )
		dw |= TEXT_ALIGN_TOP;
	if ( (edPtr->eData.dwFlags & ALIGN_VCENTER) != 0 )
		dw |= TEXT_ALIGN_VCENTER;
	if ( (edPtr->eData.dwFlags & ALIGN_BOTTOM) != 0 )
		dw |= TEXT_ALIGN_BOTTOM;
*/
#endif // !defined(RUN_ONLY)
	return dw;
}

// --------------------
// SetTextAlignment
// --------------------
// Set the text alignment of the object.
//
void WINAPI DLLExport SetTextAlignment(mv _far *mV, LPEDATA edPtr, DWORD dwAlignFlags)
{
#if !defined(RUN_ONLY)
	// Example
	// -------
/*	DWORD dw = edPtr->eData.dwFlags;

	if ( (dwAlignFlags & TEXT_ALIGN_LEFT) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_LEFT;
	if ( (dwAlignFlags & TEXT_ALIGN_HCENTER) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_HCENTER;
	if ( (dwAlignFlags & TEXT_ALIGN_RIGHT) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_RIGHT;

	if ( (dwAlignFlags & TEXT_ALIGN_TOP) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_TOP;
	if ( (dwAlignFlags & TEXT_ALIGN_VCENTER) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_VCENTER;
	if ( (dwAlignFlags & TEXT_ALIGN_BOTTOM) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_BOTTOM;

	edPtr->eData.dwFlags = dw;
*/
#endif // !defined(RUN_ONLY)
}


// ============================================================================
//
// ROUTINES USED UNDER EVENT / TIME / STEP-THROUGH EDITOR
// You should not need to change these routines
// 
// ============================================================================

// -----------------
// menucpy
// -----------------
// Internal routine used later, copy one menu onto another
// 
#ifndef RUN_ONLY
void menucpy(HMENU hTargetMenu, HMENU hSourceMenu)
{
	int			n, id, nMn;
	NPSTR		strBuf;
	HMENU		hSubMenu;

	nMn = GetMenuItemCount(hSourceMenu);
	strBuf = (NPSTR)LocalAlloc(LPTR, 80);
	for (n=0; n<nMn; n++)
	{
		if (0 == (id = GetMenuItemID(hSourceMenu, n)))
			AppendMenu(hTargetMenu, MF_SEPARATOR, 0, 0L);
		else
		{
			GetMenuString(hSourceMenu, n, strBuf, 80, MF_BYPOSITION);
			if (id != -1)
				AppendMenu(hTargetMenu, GetMenuState(hSourceMenu, n, MF_BYPOSITION), id, strBuf);
			else
			{
				hSubMenu = CreatePopupMenu();
				AppendMenu(hTargetMenu, MF_POPUP | MF_STRING, (uint)hSubMenu, strBuf);
				menucpy(hSubMenu, GetSubMenu(hSourceMenu, n));
			}
		}
	}
	LocalFree((HLOCAL)strBuf);
}

// -----------------
// GetPopupMenu
// -----------------
// Internal routine used later. Returns the first popup from a menu
// 
HMENU GetPopupMenu(short mn)
{
	HMENU	hMn, hSubMenu, hPopup = NULL;

	if ((hMn = LoadMenu(hInstLib, MAKEINTRESOURCE(mn))) != NULL)
	{
		if ((hSubMenu = GetSubMenu(hMn, 0)) != NULL)
		{
			if ((hPopup = CreatePopupMenu()) != NULL)
				menucpy(hPopup, hSubMenu);
		}
		DestroyMenu(hMn);
	}
	return hPopup;
}

// --------------------
// GetEventInformations
// --------------------
// Internal routine used later. Look for one event in one of the eventInfos array...
// No protection to go faster: you must properly enter the conditions/actions!
// 
static LPEVENTINFOS2 GetEventInformations(LPEVENTINFOS2 eiPtr, short code)

{
	while(eiPtr->infos.code != code)
		eiPtr = EVINFO2_NEXT(eiPtr);
	
	return eiPtr;
}
#endif // !defined(RUN_ONLY)


// ----------------------------------------------------
// GetConditionMenu / GetActionMenu / GetExpressionMenu
// ----------------------------------------------------
// Load the condition/action/expression menu from the resource, eventually
// enable or disable some options, and returns it to CC&C.
//
HMENU WINAPI DLLExport GetConditionMenu(mv _far *mV, fpObjInfo oiPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		return GetPopupMenu(MN_CONDITIONS);
#endif // !defined(RUN_ONLY)
	return NULL;
}

HMENU WINAPI DLLExport GetActionMenu(mv _far *mV, fpObjInfo oiPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		return GetPopupMenu(MN_ACTIONS);
#endif // !defined(RUN_ONLY)
	return NULL;
}

HMENU WINAPI DLLExport GetExpressionMenu(mv _far *mV, fpObjInfo oiPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		return GetPopupMenu(MN_EXPRESSIONS);
#endif // !defined(RUN_ONLY)
	return NULL;
}


// -------------------------------------------------------
// GetConditionTitle / GetActionTitle / GetExpressionTitle
// -------------------------------------------------------
// Returns the title of the dialog box displayed when entering
// parameters for the condition, action or expressions, if any.
// Here, we simply return the title of the menu option
//

#ifndef RUN_ONLY
void GetCodeTitle(LPEVENTINFOS2 eiPtr, short code, short param, short mn, LPSTR strBuf, WORD maxLen)
{
	HMENU		hMn;

	// Finds event in array
	eiPtr=GetEventInformations(eiPtr, code);

	// If a special string is to be returned
	short strID = EVINFO2_PARAMTITLE(eiPtr, param);

	if ( strID != 0 )
		LoadString(hInstLib, strID, strBuf, maxLen);
	else
	{
		// Otherwise, returns the menu option 
		if ((hMn = LoadMenu(hInstLib, MAKEINTRESOURCE(mn))) != NULL )
		{
			GetMenuString(hMn, eiPtr->menu, strBuf, maxLen, MF_BYCOMMAND);
			DestroyMenu(hMn);
		}
	}
}
#else
#define GetCodeTitle(a,b,c,d,e,f)
#endif // !defined(RUN_ONLY)

void WINAPI DLLExport GetConditionTitle(mv _far *mV, short code, short param, LPSTR strBuf, short maxLen)
{
	GetCodeTitle((LPEVENTINFOS2)conditionsInfos, code, param, MN_CONDITIONS, strBuf, maxLen);
}
void WINAPI DLLExport GetActionTitle(mv _far *mV, short code, short param, LPSTR strBuf, short maxLen)
{
	GetCodeTitle((LPEVENTINFOS2)actionsInfos, code, param, MN_ACTIONS, strBuf, maxLen);
}
void WINAPI DLLExport GetExpressionTitle(mv _far *mV, short code, LPSTR strBuf, short maxLen)
{
	GetCodeTitle((LPEVENTINFOS2)expressionsInfos, code, 0, MN_EXPRESSIONS, strBuf, maxLen);
}

// -------------------------------------------------------
// GetConditionTitle / GetActionTitle / GetExpressionTitle
// -------------------------------------------------------
// From a menu ID, these routines returns the code of the condition,
// action or expression, as defined in the .H file
//

short WINAPI DLLExport GetConditionCodeFromMenu(mv _far *mV, short menuId)
{
#ifndef RUN_ONLY
	LPEVENTINFOS2	eiPtr;
	int				n;

	for (n=CND_LAST, eiPtr=(LPEVENTINFOS2)conditionsInfos; n>0 && eiPtr->menu!=menuId; n--)
		eiPtr = EVINFO2_NEXT(eiPtr);
	if (n>0) 
		return eiPtr->infos.code;
#endif // !defined(RUN_ONLY)
	return -1;
}

short WINAPI DLLExport GetActionCodeFromMenu(mv _far *mV, short menuId)
{
#ifndef RUN_ONLY
	LPEVENTINFOS2	eiPtr;
	int				n;

	for (n=ACT_LAST, eiPtr=(LPEVENTINFOS2)actionsInfos; n>0 && eiPtr->menu!=menuId; n--)
		eiPtr = EVINFO2_NEXT(eiPtr);
	if (n>0) 
		return eiPtr->infos.code;
#endif // !defined(RUN_ONLY)
	return -1;
}

short WINAPI DLLExport GetExpressionCodeFromMenu(mv _far *mV, short menuId)
{
#ifndef RUN_ONLY
	LPEVENTINFOS2	eiPtr;
	int				n;

	for (n=EXP_LAST, eiPtr=(LPEVENTINFOS2)expressionsInfos; n>0 && eiPtr->menu!=menuId; n--)
		eiPtr = EVINFO2_NEXT(eiPtr);
	if (n>0) 
		return eiPtr->infos.code;
#endif // !defined(RUN_ONLY)
	return -1;
}


// -------------------------------------------------------
// GetConditionInfos / GetActionInfos / GetExpressionInfos
// -------------------------------------------------------
// From a action / condition / expression code, returns 
// an infosEvents structure. 
//

LPINFOEVENTSV2 WINAPI DLLExport GetConditionInfos(mv _far *mV, short code)
{
#ifndef RUN_ONLY
	return &GetEventInformations((LPEVENTINFOS2)conditionsInfos, code)->infos;
#else
	return NULL;
#endif // !defined(RUN_ONLY)
}

LPINFOEVENTSV2 WINAPI DLLExport GetActionInfos(mv _far *mV, short code)
{
#ifndef RUN_ONLY
	return &GetEventInformations((LPEVENTINFOS2)actionsInfos, code)->infos;
#else
	return NULL;
#endif // !defined(RUN_ONLY)
}

LPINFOEVENTSV2 WINAPI DLLExport GetExpressionInfos(mv _far *mV, short code)
{
#ifndef RUN_ONLY
	return &GetEventInformations((LPEVENTINFOS2)expressionsInfos, code)->infos;
#else
	return NULL;
#endif // !defined(RUN_ONLY)
}


// ----------------------------------------------------------
// GetConditionString / GetActionString / GetExpressionString
// ----------------------------------------------------------
// From a action / condition / expression code, returns 
// the string to use for displaying it under the event editor
//

void WINAPI DLLExport GetConditionString(mv _far *mV, short code, LPSTR strPtr, short maxLen)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		LoadString(hInstLib, GetEventInformations((LPEVENTINFOS2)conditionsInfos, code)->string, strPtr, maxLen);
#endif // !defined(RUN_ONLY)
}

void WINAPI DLLExport GetActionString(mv _far *mV, short code, LPSTR strPtr, short maxLen)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		LoadString(hInstLib, GetEventInformations((LPEVENTINFOS2)actionsInfos, code)->string, strPtr, maxLen);
#endif // !defined(RUN_ONLY)
}

void WINAPI DLLExport GetExpressionString(mv _far *mV, short code, LPSTR strPtr, short maxLen)
{
#ifndef RUN_ONLY
	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
		LoadString(hInstLib, GetEventInformations((LPEVENTINFOS2)expressionsInfos, code)->string, strPtr, maxLen);
#endif // !defined(RUN_ONLY)
}

// ----------------------------------------------------------
// GetExpressionParam
// ----------------------------------------------------------
// Returns the parameter name to display in the expression editor
//
void WINAPI DLLExport GetExpressionParam(mv _far *mV, short code, short param, LPSTR strBuf, short maxLen)
{
#if !defined(RUN_ONLY)
	short		strID;

	// Finds event in array
	LPEVENTINFOS2 eiPtr=GetEventInformations((LPEVENTINFOS2)expressionsInfos, code);

	// If a special string is to be returned
	strID = EVINFO2_PARAMTITLE(eiPtr, param);
	if ( strID != 0 )
		LoadString(hInstLib, strID, strBuf, maxLen);
	else
		*strBuf=0;
#endif // !defined(RUN_ONLY)
}

// ----------------------------------------------------------
// Custom Parameters
// ----------------------------------------------------------

// --------------------
// InitParameter
// --------------------
// Initialize the parameter.
//
void WINAPI InitParameter(mv _far *mV, short code, paramExt* pExt)
{
#if !defined(RUN_ONLY)
	// Example
	// -------
	// strcpy(&pExt->pextData[0], "Parameter Test");
	// pExt->pextSize = sizeof(paramExt) + strlen(pExt->pextData)+1;
#endif // !defined(RUN_ONLY)
}

// Example of custom parameter setup proc
// --------------------------------------
/*
#if !defined(RUN_ONLY)
BOOL CALLBACK DLLExport SetupProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam)
{
	paramExt*			pExt;

	switch (msgType)
	{
		case WM_INITDIALOG: // Init dialog

			// Save edptr
			SetWindowLong(hDlg, DWL_USER, lParam);
			pExt=(paramExt*)lParam;

			SetDlgItemText(hDlg, IDC_EDIT, pExt->pextData);
			return TRUE;

		case WM_COMMAND: // Command

			// Retrieve edptr
			pExt = (paramExt *)GetWindowLong(hDlg, DWL_USER);

			switch (wmCommandID)
			{
			case IDOK:	// Exit
				GetDlgItemText(hDlg, IDC_EDIT, pExt->pextData, 500);
				pExt->pextSize=sizeof(paramExt)+strlen(pExt->pextData)+1;
				EndDialog(hDlg, TRUE);
				return TRUE;

				default:
					break;
			}
			break;

		default:
			break;
	}
	return FALSE;
}
#endif // !defined(RUN_ONLY)
*/

// --------------------
// EditParameter
// --------------------
// Edit the parameter.
//
void WINAPI EditParameter(mv _far *mV, short code, paramExt* pExt)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
	// DialogBoxParam(hInstLib, MAKEINTRESOURCE(DB_TRYPARAM), mV->mvHEditWin, SetupProc, (LPARAM)(LPBYTE)pExt);

#endif // !defined(RUN_ONLY)
}

// --------------------
// GetParameterString
// --------------------
// Initialize the parameter.
//
void WINAPI GetParameterString(mv _far *mV, short code, paramExt* pExt, LPSTR pDest, short size)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
	// wsprintf(pDest, "Super parameter %s", pExt->pextData);

#endif // !defined(RUN_ONLY)
}

