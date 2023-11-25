#pragma once

#ifndef EFFECT_H_

#define	EFFECT_H_

#include	"enemy.h"

#define	EFFECT_MAX	(100)


class EFFECT : public	BASE_OF_PERFORMER
{
public:
	enum EFFECT_TYPE
	{
		ABSORB_R,
		ABSORB_L,
		BLOOD,
		SHINE,
		effect_type_max
	};

private:
	EFFECT_TYPE	effect_type;

	ENEMY*	absorbed_enemy;

	unsigned	int	TexNums[effect_type_max];
	unsigned	int	SENums[effect_type_max];

	int	timer;

	const	int	ShiningTimeMax = 60 / 3;

public:
	void	Update();

	void	Prepare();
	void	Reset();

	void	SetEffect(const	D3DXVECTOR2 new_pos, const D3DXVECTOR2 new_size, const EFFECT::EFFECT_TYPE	new_type, ENEMY*	new_enemy);

	void	SetEffectType(const	EFFECT_TYPE	new_type) { effect_type = new_type; }
	EFFECT_TYPE	GetEffectType() { return	effect_type; }

	void	SetAbsorbedEnemy(ENEMY*	new_enemy) { absorbed_enemy = new_enemy; }
	ENEMY*	GetAbsorbedEnemy() { return	absorbed_enemy; }

};

void	InitEffect();		//	�G�t�F�N�g������
void	UninitEffect();		//	�G�t�F�N�g�I������
void	UpdateEffect();		//	�G�t�F�N�g�X�V����
void	DrawEffect();		//	�G�t�F�N�g�`�揈��

void	SetEffects(const	D3DXVECTOR2 new_pos,	const D3DXVECTOR2 new_size,	const EFFECT::EFFECT_TYPE	new_type,	ENEMY*	new_enemy);		//	�G�t�F�N�g�̃Z�b�g
EFFECT*	GetEffects();		//	�G�t�F�N�g�̎擾

#endif // !EFFECT_H_



