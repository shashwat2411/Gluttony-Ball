
#pragma once

#include "Ball.h"

#define		WAIVER_MAX (50)

class WAIVER :public	BASE_OF_PERFORMER
{
private:
	BALL::ABILITY_ATTACK	abilityType_at;
	BALL::ABILITY_MOVE_BALL	abilityType_mb;
	BALL::ABILITY_MOVE_PLAYER	abilityType_mp;

	int	timer;	//	消滅するまでの計測カウンター

	const	int	DeleteTimeMax = 60 * 6;

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetWaiverAbirities(D3DXVECTOR2 new_pos, D3DXVECTOR2	new_way,
		const	BALL::ABILITY_ATTACK&			AbilityTypes_AT,
		const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MB,
		const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MP);		//	能力放棄のセット

	const	BALL::ABILITY_ATTACK&			GetAbilityType_AT() { return	abilityType_at; }	//	放棄アビリティの能力タイプ取得
	const	BALL::ABILITY_MOVE_BALL&		GetAbilityType_MB() { return	abilityType_mb; }	//	放棄アビリティの能力タイプ取得
	const	BALL::ABILITY_MOVE_PLAYER&		GetAbilityType_MP() { return	abilityType_mp; }	//	放棄アビリティの能力タイプ取得
};


void	InitWaiver();		//	能力放棄初期化
void	UninitWaiver();		//	能力放棄終了処理
void	UpdateWaiver();		//	能力放棄更新処理
void	DrawWaiver();		//	能力放棄描画処理


void	SetWaiver(D3DXVECTOR2	wa_pos, D3DXVECTOR2	wa_way,
	const	BALL::ABILITY_ATTACK&			AbilityTypes_ATTACK,
	const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MOVE_BALL,
	const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MOVE_PLAYER);	//	能力放棄のセット

WAIVER* GetWaiver();		//	能力放棄取得