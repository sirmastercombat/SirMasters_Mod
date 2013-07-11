//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ========
//
// Purpose: Simple logical entity that counts up to a threshold value, then
//			fires an output when reached.
//
//=============================================================================
 
#ifndef MAPADD_H
#define MAPADD_H


#include "cbase.h"
 
class CMapAddLabel : public CBaseEntity
{
	public:
	DECLARE_CLASS( CMapAddLabel, CBaseEntity );
	DECLARE_DATADESC();
 
	// Constructor
	CMapAddLabel()
	{
		m_nCounter = 0;
		m_bDeleteOnFire = true;
		m_szLabel = "";
	}
 
	// Input function
	void InputRunLabel( inputdata_t &inputData ); //Runmapadd
 
	private:
 
	int	m_nThreshold;	// Count at which to fire our output
	int	m_nCounter;	// Internal counter
	bool	m_bDeleteOnFire;
	const char * m_szLabel;
	COutputEvent	m_OnThreshold;	// Output event when the counter reaches the threshold
};

 
class CMapAdd : public CBaseEntity
{
	public:
		DECLARE_CLASS( CMapAdd, CBaseEntity );
		DECLARE_DATADESC();
 
		// Constructor
		CMapAdd()
		{
			bFirstRun = true;
		}
		virtual void Precache( void );
		bool RunLabel( const char *mapaddMap, const char *szLabel);
		bool RunPlayerInit( const char *mapaddMap, const char *szLabel);
		bool HandlePlayerEntity( KeyValues *playerEntity, bool initLevel = false );
		bool HandleSMODEntity( KeyValues *smodEntity );
		bool HandleSpecialEnitity( KeyValues *specialEntity);
		bool HandleRemoveEnitity( KeyValues *mapaddValue);
		void InputRunLabel( inputdata_t &inputData);
	private:
		bool bFirstRun;
		//COutputEvent	m_OnThreshold;	// Output event when the counter reaches the threshold
};
CMapAdd* GetMapAddEntity();
CMapAdd* CreateMapAddEntity();

#endif	//HL2_PLAYER_H