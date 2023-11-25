
#pragma once

#include "Ball.h"

#define		WAIVER_MAX (50)

class WAIVER :public	BASE_OF_PERFORMER
{
private:
	BALL::ABILITY_ATTACK	abilityType_at;
	BALL::ABILITY_MOVE_BALL	abilityType_mb;
	BALL::ABILITY_MOVE_PLAYER	abilityType_mp;

	int	timer;	//	���ł���܂ł̌v���J�E���^�[

	const	int	DeleteTimeMax = 60 * 6;

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetWaiverAbirities(D3DXVECTOR2 new_pos, D3DXVECTOR2	new_way,
		const	BALL::ABILITY_ATTACK&			AbilityTypes_AT,
		const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MB,
		const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MP);		//	�\�͕����̃Z�b�g

	const	BALL::ABILITY_ATTACK&			GetAbilityType_AT() { return	abilityType_at; }	//	�����A�r���e�B�̔\�̓^�C�v�擾
	const	BALL::ABILITY_MOVE_BALL&		GetAbilityType_MB() { return	abilityType_mb; }	//	�����A�r���e�B�̔\�̓^�C�v�擾
	const	BALL::ABILITY_MOVE_PLAYER&		GetAbilityType_MP() { return	abilityType_mp; }	//	�����A�r���e�B�̔\�̓^�C�v�擾
};


void	InitWaiver();		//	�\�͕���������
void	UninitWaiver();		//	�\�͕����I������
void	UpdateWaiver();		//	�\�͕����X�V����
void	DrawWaiver();		//	�\�͕����`�揈��


void	SetWaiver(D3DXVECTOR2	wa_pos, D3DXVECTOR2	wa_way,
	const	BALL::ABILITY_ATTACK&			AbilityTypes_ATTACK,
	const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MOVE_BALL,
	const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MOVE_PLAYER);	//	�\�͕����̃Z�b�g

WAIVER* GetWaiver();		//	�\�͕����擾