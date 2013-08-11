#include "cbase.h"
#include "c_weapon_custom.h"
#include "hl2/c_basehlcombatweapon.h"
#include "igamemovement.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"
//-----------------------------------------------------------------------------
// Purpose: Get my data in the file weapon info array
//-----------------------------------------------------------------------------
const FileWeaponInfo_t &C_WeaponCustom::GetWpnData( void ) const
{
	return *m_pCustomWeaponInfo;
}
IMPLEMENT_CLIENTCLASS_DT( C_WeaponCustom , DT_WeaponCustom, CWeaponCustom )
END_RECV_TABLE()