#include "cbase.h"
#include "weapon_parse.h"
#include "KeyValues.h"
 /*
 Refrence Format

 "WeaponSpec"
{
	"PrimaryFire"
	{
		"Bullet" {
			"AmmoType"	"Buckshot"
			"Damage"	"5"
			"ShotCount"	"3"
		}
	}
	"SecondaryFire"
	{
		"Bullet" {
			"AmmoType"	"pistol"
			"Damage"	"14"
			"ShotCount"	"1"
		}
	}
}
 */
class SMOD_FileWeaponInfo_t : public FileWeaponInfo_t
{
public:
	DECLARE_CLASS_GAMEROOT( SMOD_FileWeaponInfo_t, FileWeaponInfo_t );
 
	void Parse( ::KeyValues* pKeyValuesData, const char* szWeaponName )
	{
		BaseClass::Parse( pKeyValuesData, szWeaponName );
		KeyValues *pWeaponSpec = pKeyValuesData->FindKey( "WeaponSpec" );
		if ( pWeaponSpec )
		{
			KeyValues *pPrimaryFire = pWeaponSpec->FindKey( "PrimaryFire" );
			if ( pPrimaryFire )
			{
				KeyValues *pBullet = pWeaponSpec->FindKey( "Bullet" );
				if ( pBullet )
				{
					m_sPrimaryDamage = pBullet->GetInt( "AmmoType", 0 );
					m_sPrimaryShotCount = pBullet->GetInt( "ShotCount", 0 );
				}
				else
				{
					m_sPrimaryDamage = 0;
					m_sSecondaryShotCount = 0;
				}
			}
			else
				m_sPrimaryBulletEnabled = false;
			KeyValues *pSecondaryFire = pWeaponSpec->FindKey( "SecondaryFire" );
			if ( pPrimaryFire )
			{
				KeyValues *pBullet = pWeaponSpec->FindKey( "Bullet" );
				if ( pBullet )
				{
					m_sSecondaryDamage = pBullet->GetInt( "AmmoType", 0 );
					m_sSecondaryShotCount = pBullet->GetInt( "ShotCount", 0 );
				}
				else
				{
					m_sSecondaryDamage = 0;
					m_sSecondaryShotCount = 0;
				}
			}
			else
				m_sSecondaryBulletEnabled = false;
		}
	}
 
	
	bool	m_sPrimaryBulletEnabled;
	char	m_sPrimaryAmmoType;
	int	m_sPrimaryDamage;
	int m_sPrimaryShotCount;

	bool	m_sSecondaryBulletEnabled;
	char	m_sSecondaryAmmoType;
	int	m_sSecondaryDamage;
	int m_sSecondaryShotCount;
};
 