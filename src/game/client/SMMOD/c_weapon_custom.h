#include "hl2/c_basehlcombatweapon.h"

#ifndef	C_WEAPONCUSTOM_H
#define	C_WEAPONCUSTOM_H
#ifdef _WIN32
#pragma once
#endif

class C_WeaponCustom : public C_HLSelectFireMachineGun			
{														
	DECLARE_CLASS( C_WeaponCustom, C_HLSelectFireMachineGun );					
public:													
	//DECLARE_PREDICTABLE();									
	DECLARE_CLIENTCLASS();									
	C_WeaponCustom() {
			
		char sz[128];
		Q_snprintf( sz, sizeof( sz ), "scripts/weapon_custom/%s", this->m_iClassname );
		KeyValues *pKV  = ReadEncryptedKVFile( filesystem, sz, NULL, false ); //CUSTOM WEAPONS DO NOT HAVE CTX FILES!
		char szName[128];
		Q_snprintf( szName, sizeof( szName ), "%s", this->m_iClassname );
		m_pCustomWeaponInfo->Parse( pKV, szName );

		pKV->deleteThis();
	};	
	const FileWeaponInfo_t	&GetWpnData( void ) const;
	FileWeaponInfo_t *m_pCustomWeaponInfo;
private:												
//	C_WeaponCustom( const C_WeaponCustom & );	
};				

#endif	//WEAPONCUSTOM_H