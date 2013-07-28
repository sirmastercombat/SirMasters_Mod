#include "cbase.h"
#include "mapadd.h"
#include "filesystem.h"
#include "weapon_custom.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

static CMapAdd *g_MapAddEntity = NULL;
LINK_ENTITY_TO_CLASS( mapadd, CMapAdd  );
CMapAdd* GetMapAddEntity()
{
	return g_MapAddEntity;
}
CMapAdd* CreateMapAddEntity()
{
	return dynamic_cast<CMapAdd*>((CBaseEntity*)CBaseEntity::Create("mapadd", Vector(0,0,0), QAngle(0,0,0)));
}
void CMapAdd::Precache( void )
{
	g_MapAddEntity = this;
}
bool CMapAdd::RunPlayerInit( const char *mapaddMap, const char *szLabel)
{
	if(AllocPooledString(mapaddMap) == AllocPooledString("") || !mapaddMap)
		return false; //Failed to load!
	if(!szLabel)
		szLabel = "Init";
	//FileHandle_t fh = filesystem->Open(szMapadd,"r","MOD");
	// Open the mapadd data file, and abort if we can't
	KeyValues *pMapAdd = new KeyValues( "MapAdd" );
	if(pMapAdd->LoadFromFile( filesystem, mapaddMap, "MOD" ))
	{
		KeyValues *pMapAdd2 = pMapAdd->FindKey(szLabel);
		if(pMapAdd2)
		{
			KeyValues *pMapAddEnt = pMapAdd2->GetFirstTrueSubKey();
			while (pMapAddEnt)
			{
				HandlePlayerEntity(pMapAddEnt, false);
				pMapAddEnt = pMapAddEnt->GetNextTrueSubKey(); //Got to keep this!
			}
		}
	}
	pMapAdd->deleteThis();
	return true;
}
bool CMapAdd::RunLabel( const char *mapaddMap, const char *szLabel)
{

	if(AllocPooledString(mapaddMap) == AllocPooledString("") || !mapaddMap || !szLabel || AllocPooledString(szLabel) == AllocPooledString(""))
		return false; //Failed to load!
	//FileHandle_t fh = filesystem->Open(szMapadd,"r","MOD");
	// Open the mapadd data file, and abort if we can't
	KeyValues *pMapAdd = new KeyValues( "MapAdd" );
	if(pMapAdd->LoadFromFile( filesystem, mapaddMap, "MOD" ))
	{
		KeyValues *pMapAdd2 = pMapAdd->FindKey(szLabel);
		if(pMapAdd2)
		{
			KeyValues *pMapAddEnt = pMapAdd2->GetFirstTrueSubKey();
			while (pMapAddEnt)
			{
				if(!HandlePlayerEntity(pMapAddEnt, false) && !HandleSMODEntity(pMapAddEnt) && !HandleSpecialEnitity(pMapAddEnt))
				{
					Vector SpawnVector = Vector(0,0,0);
					QAngle SpawnAngle = QAngle(0,0,0);
			
					SpawnVector.x = pMapAddEnt->GetFloat("x", SpawnVector.x);
					SpawnVector.y = pMapAddEnt->GetFloat("y", SpawnVector.y);
					SpawnVector.z = pMapAddEnt->GetFloat("z", SpawnVector.z);

					SpawnAngle[PITCH] = pMapAddEnt->GetFloat("pitch", SpawnAngle[PITCH]);
					SpawnAngle[YAW] = pMapAddEnt->GetFloat("yaw", SpawnAngle[YAW]);
					SpawnAngle[ROLL] = pMapAddEnt->GetFloat("roll", SpawnAngle[ROLL]);

					CBaseEntity *createEnt = CBaseEntity::CreateNoSpawn(pMapAddEnt->GetName(),SpawnVector,SpawnAngle);
					KeyValues *pEntKeyValues = pMapAddEnt->FindKey("KeyValues");
					if(pEntKeyValues && createEnt)
					{
						Msg("keyvalue for %s Found!\n",pMapAddEnt->GetName());
						KeyValues *pEntKeyValuesAdd = pEntKeyValues->GetFirstValue();
						while(pEntKeyValuesAdd && createEnt)
						{
							if(AllocPooledString(pEntKeyValuesAdd->GetName()) == AllocPooledString("model"))
							{
								PrecacheModel(pEntKeyValuesAdd->GetString(""));
								createEnt->SetModel(pEntKeyValuesAdd->GetString(""));
							}
							else if(AllocPooledString(pEntKeyValuesAdd->GetName()) == AllocPooledString("name"))
							{
								createEnt->SetName(AllocPooledString(pEntKeyValuesAdd->GetString("")));
							}
							else if(AllocPooledString(pEntKeyValuesAdd->GetName()) == AllocPooledString("spawnflags"))
							{
								createEnt->AddSpawnFlags(pEntKeyValuesAdd->GetInt());
							}
							else
							{
								createEnt->KeyValue(pEntKeyValuesAdd->GetName(),pEntKeyValuesAdd->GetString(""));
							}
							pEntKeyValuesAdd = pEntKeyValuesAdd->GetNextValue();
						}
					}
					//createEnt->Activate();//Is this a good idea? Not sure!
					//createEnt->Spawn();
					DispatchSpawn( createEnt ); //I derped
				}
				pMapAddEnt = pMapAddEnt->GetNextTrueSubKey(); //Got to keep this!
			}
		}
	}
	
	pMapAdd->deleteThis();
	return true;
}

bool CMapAdd::HandlePlayerEntity( KeyValues *playerEntityKV, bool initLevel)
{
	if(AllocPooledString(playerEntityKV->GetName()) == AllocPooledString("player"))
	{
	//	if(initLevel)
	//	{
	//		return true; //Just pretend we did
	//	}
		CBasePlayer *playerEnt =UTIL_GetLocalPlayer();
		Vector SpawnVector = playerEnt->GetAbsOrigin();
		QAngle SpawnAngle = playerEnt->GetAbsAngles();
			
		SpawnVector.x = playerEntityKV->GetFloat("x", SpawnVector.x);
		SpawnVector.y = playerEntityKV->GetFloat("y", SpawnVector.y);
		SpawnVector.z = playerEntityKV->GetFloat("z", SpawnVector.z);

		SpawnAngle[PITCH] = playerEntityKV->GetFloat("pitch", SpawnAngle[PITCH]);
		SpawnAngle[YAW] = playerEntityKV->GetFloat("yaw", SpawnAngle[YAW]);
		SpawnAngle[ROLL] = playerEntityKV->GetFloat("roll", SpawnAngle[ROLL]);
//		KeyValues *pEntKeyValues = playerEntityKV->FindKey("KeyValues");
		/*if(pEntKeyValues && playerEnt)
		{
			KeyValues *pEntKeyValuesAdd = pEntKeyValues->GetFirstValue();
			while(pEntKeyValuesAdd && playerEnt)
			{
				if(AllocPooledString(pEntKeyValuesAdd->GetName()) == AllocPooledString("model"))
				{
					char szModel[128];
					Q_snprintf( szModel, sizeof( szModel ), "%s", playerEnt->GetModelName() );
					PrecacheModel(pEntKeyValuesAdd->GetString(szModel));
					playerEnt->SetModel(pEntKeyValuesAdd->GetString(szModel) );
				}
				pEntKeyValuesAdd = pEntKeyValuesAdd->GetNextValue();
			}
		}*/
		playerEnt->SetAbsOrigin(SpawnVector);
		playerEnt->SetAbsAngles(SpawnAngle);
		return true;
	}
	return false;
}
bool CMapAdd::HandleSMODEntity( KeyValues *smodEntity)
{
	return false;
}
bool CMapAdd::HandleSpecialEnitity( KeyValues *specialEntity)
{
	return false;
}
bool CMapAdd::HandleRemoveEnitity( KeyValues *mapaddValue)
{
	if(AllocPooledString(mapaddValue->GetName()) == AllocPooledString("remove:sphere"))
	{
		Vector RemoveVector = Vector(0,0,0);
		CBaseEntity *ppEnts[256];
//		CBaseEntity *ppCandidates[256];
		RemoveVector.x = mapaddValue->GetFloat("x", RemoveVector.x);
		RemoveVector.y = mapaddValue->GetFloat("y", RemoveVector.y);
		RemoveVector.z = mapaddValue->GetFloat("z", RemoveVector.z);
		int nEntCount = UTIL_EntitiesInSphere( ppEnts, 256, RemoveVector, mapaddValue->GetFloat("radius", 0), 0 );

				//Look through the entities it found
			KeyValues *pEntKeyValues = mapaddValue->FindKey("entities");
			if(pEntKeyValues)
			{
				KeyValues *pEntKeyValuesRemove = pEntKeyValues->GetFirstValue();
				while(pEntKeyValuesRemove)
				{
					int i;
					for ( i = 0; i < nEntCount; i++ )
					{
			
						if ( ppEnts[i] == NULL )
							continue;
						if(AllocPooledString(pEntKeyValuesRemove->GetName()) == AllocPooledString("classname")) // || ( AllocPooledString(pEntKeyValuesRemove->GetName()) == ppEnts[i]->GetEntityName())
						{
							if(AllocPooledString(pEntKeyValuesRemove->GetString()) == AllocPooledString(ppEnts[i]->GetClassname()))
							{
								UTIL_Remove(ppEnts[i]);
								continue;
							}
						}
						if(AllocPooledString(pEntKeyValuesRemove->GetName()) == AllocPooledString("targetname")) // || ( AllocPooledString(pEntKeyValuesRemove->GetName()) == ppEnts[i]->GetEntityName())
						{
							if(AllocPooledString(pEntKeyValuesRemove->GetString()) == ppEnts[i]->GetEntityName())
							{
								UTIL_Remove(ppEnts[i]);
								continue;
							}
						}
					}
					pEntKeyValuesRemove = pEntKeyValuesRemove->GetNextValue();
				}
			}
			return true;
	}
	return false;
}
void CMapAdd::InputRunLabel( inputdata_t &inputData ) //Input this directly!
{
	char szMapadd[128];
	Q_snprintf( szMapadd, sizeof( szMapadd ), "mapadd/%s.txt", gpGlobals->mapname );
	this->RunLabel( szMapadd, inputData.value.String());
}
BEGIN_DATADESC( CMapAdd )
	// Links our input name from Hammer to our input member function
	DEFINE_INPUTFUNC( FIELD_STRING, "RunLabel", InputRunLabel ),
END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Handle a tick input from another entity
//-----------------------------------------------------------------------------
void CMapAddLabel::InputRunLabel( inputdata_t &inputData )
{
	
	if(m_bDeleteOnFire)
	{
		Warning("Unable to run label! Deleting mapadd_label!");
		UTIL_Remove(this);
	}

	if(m_nCounter <= m_nThreshold)
	{
		char szMapadd[128];
		Q_snprintf( szMapadd, sizeof( szMapadd ), "mapadd/%s.txt", gpGlobals->mapname );
		CMapAdd *entMapAdd = GetMapAddEntity();
		if(!entMapAdd)
			entMapAdd = CreateMapAddEntity();
		entMapAdd->RunLabel(szMapadd, m_szLabel);
		if(m_bDeleteOnFire)
			UTIL_Remove(this);
	}
	else
	{
		m_nCounter++;
	}
}

LINK_ENTITY_TO_CLASS( mapadd_label, CMapAddLabel  );
 
// Start of our data description for the class
BEGIN_DATADESC( CMapAddLabel  )
 
// For save/load
DEFINE_FIELD( m_nCounter, FIELD_INTEGER ),
// Links our member variable to our keyvalue from Hammer
DEFINE_KEYFIELD( m_nThreshold, FIELD_INTEGER, "countlimit" ),
// Links our member variable to our keyvalue from Hammer
DEFINE_KEYFIELD( m_szLabel, FIELD_STRING, "label" ),
// Links our member variable to our keyvalue from Hammer
DEFINE_KEYFIELD( m_bDeleteOnFire, FIELD_BOOLEAN, "deleteonfire" ),
// Links our input name from Hammer to our input member function
DEFINE_INPUTFUNC( FIELD_VOID, "RunLabel", InputRunLabel ),
 
// Links our output member to the output name used by Hammer
//DEFINE_OUTPUT( m_OnThreshold, "OnThreshold" ),
 
END_DATADESC()
 