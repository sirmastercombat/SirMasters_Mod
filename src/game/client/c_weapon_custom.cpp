#include "cbase.h"
#include "c_weapon_custom.h"
//#include "c_weapon__stubs.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"
 
//Link a global entity name to this class (name used in Hammer etc.)
//LINK_ENTITY_TO_CLASS( myentity, C_WeaponCustom );
 
// Link data table DT_MyEntity to client class and map variables (RecvProps)
// DO NOT create this in the header! Put it in the main CPP file.
/*
IMPLEMENT_CLIENTCLASS_DT( C_CWeaponCustom, DT_WeaponCustom, CWeaponCustom )
//	RecvPropInt( RECVINFO( m_nMyInteger ) ),
//	RecvPropFloat( RECVINFO( m_fMyFloat )),
END_RECV_TABLE()*/

IMPLEMENT_CLIENTCLASS_DT( C_WeaponCustom, DT_WeaponCustom, CWeaponCustom )
END_RECV_TABLE()

BEGIN_PREDICTION_DATA( C_WeaponCustom  )
END_PREDICTION_DATA()				