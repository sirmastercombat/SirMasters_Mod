
#ifndef	WEAPONCUSTOM_H
#define	WEAPONCUSTOM_H

#include "basehlcombatweapon.h"
#include "weapon_rpg.h"

class CWeaponCustom : public CHLSelectFireMachineGun
{
	DECLARE_DATADESC();
public:
	DECLARE_CLASS( CWeaponCustom, CHLSelectFireMachineGun );

	CWeaponCustom();

	DECLARE_SERVERCLASS();
	
	void	Precache( void );
	void	AddViewKick( void );
	void	ShootBullets( bool isPrimary = true, bool usePrimaryAmmo = true );
	void	ShootProjectile( bool isPrimary, bool usePrimaryAmmo );
	void	ItemPostFrame( void );
	void	PrimaryAttack( void );
	void	SecondaryAttack( void );

	int		GetMinBurst() { return 2; }
	int		GetMaxBurst() { return 5; }

	virtual void Equip( CBaseCombatCharacter *pOwner );
	bool	Reload( void );

	float	GetFireRate( void ) { return this->GetWpnData().m_sPrimaryFireRate; }	// 13.3hz
	int		CapabilitiesGet( void ) { return bits_CAP_WEAPON_RANGE_ATTACK1; }
	int		WeaponRangeAttack2Condition( float flDot, float flDist );
	Activity	GetPrimaryAttackActivity( void );

	virtual const Vector& GetBulletSpreadPrimary( void )
	{
		static const Vector cone = this->GetWpnData().m_vPrimarySpread;
		return cone;
	}

	virtual const Vector& GetBulletSpreadSecondary( void )
	{
		static const Vector cone = this->GetWpnData().m_vSecondarySpread;
		return cone;
	}
	bool IsPrimaryBullet( void ) {return this->GetWpnData().m_sPrimaryBulletEnabled;}

	bool IsSecondaryBullet( void ) {return this->GetWpnData().m_sSecondaryBulletEnabled;}

	const WeaponProficiencyInfo_t *GetProficiencyValues();

	void FireNPCPrimaryAttack( CBaseCombatCharacter *pOperator, Vector &vecShootOrigin, Vector &vecShootDir );
	void Operator_ForceNPCFire( CBaseCombatCharacter  *pOperator, bool bSecondary );
	void Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator );
	protected: //Why did I not put this in? I have no idea...
		CHandle<CMissile>	m_hMissile;
};

#define CustomWeaponAdd( num )										\
class CWeaponCustom##num : public CWeaponCustom						\
{																	\
	DECLARE_DATADESC();												\
	public:															\
	DECLARE_CLASS( CWeaponCustom##num, CWeaponCustom );				\
	CWeaponCustom##num() {};										\
	DECLARE_SERVERCLASS();											\
};																	\
IMPLEMENT_SERVERCLASS_ST(CWeaponCustom##num, DT_WeaponCustom##num)	\
END_SEND_TABLE()													\
BEGIN_DATADESC( CWeaponCustom##num )										\
END_DATADESC()														\
LINK_ENTITY_TO_CLASS( weapon_custom##num, CWeaponCustom##num );		\
PRECACHE_WEAPON_REGISTER(weapon_custom##num);

#define CustomWeaponNamedAdd( customname )										\
class CWeaponCustomNamed##customname : public CWeaponCustom						\
{																	\
	DECLARE_DATADESC();												\
	public:															\
	DECLARE_CLASS( CWeaponCustomNamed##customname, CWeaponCustom );				\
	CWeaponCustomNamed##customname() {};										\
	DECLARE_SERVERCLASS();											\
};																	\
IMPLEMENT_SERVERCLASS_ST(CWeaponCustomNamed##customname, DT_WeaponCustomNamed##customname)	\
END_SEND_TABLE()													\
BEGIN_DATADESC( CWeaponCustomNamed##customname )										\
END_DATADESC()														\
LINK_ENTITY_TO_CLASS( weapon_##customname, CWeaponCustomNamed##customname );		\
PRECACHE_WEAPON_REGISTER(weapon_##customname);
#endif	//WEAPONCUSTOM_H