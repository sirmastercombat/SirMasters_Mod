
#ifndef C_WEAPON_CUSTOM_H
#define C_WEAPON_CUSTOM_H
#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"
//#include "basehlcombatweapon_shared.h"
#include "c_basehlcombatweapon.h"
class C_WeaponCustom : public C_HLSelectFireMachineGun
{
	DECLARE_CLASS( C_WeaponCustom, C_HLSelectFireMachineGun );
public:	
	DECLARE_PREDICTABLE();
	DECLARE_CLIENTCLASS();
	C_WeaponCustom() {};
private:
	C_WeaponCustom( const C_WeaponCustom & );
};


#endif // C_WEAPON__STUBS_H