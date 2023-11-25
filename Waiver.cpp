

#include "Waiver.h"
#include "ground.h"
#include "collision.h"


WAIVER	waiver[WAIVER_MAX];


void WAIVER::Update()
{
	if (use)
	{
		timer++;

		if (!onWall)	pos_bef.x = pos.x;
		if (!onGround)	pos_bef.y = pos.y;

		if (fabs(pos.x - actionFirstPos.x) >= BASE_SIZE)	collisionBool = true;

		if (onGround) { move.x *= frictionRate; }

		if (timer >= DeleteTimeMax / 2)
		{
			if (timer % 15 == 0)
			{
				if (color.a == 1.0f)	color.a = 0.2f;
				else color.a = 1.0f;
			}
		}

		if (timer >= DeleteTimeMax)
		{
			timer = 0;
			use = false;
		}

		Gravity();
		Move();
	}

}

void WAIVER::Prepare()
{
	use = false;							//	�I�u�W�F�N�g�̎g�p�Atrue:Update�ADraw���s����B	false:Update�ADraw�A�ǂ�����s���Ȃ�
	active = false;						//	�ړ��̉s�Atrue:move�ɒl������ꍇ�A�ړ��ł���B	false:move�ɒl�������Ă��A�ړ��ł��Ȃ�
	animation = false;					//	�A�j���[�V�����̉s�Atrue:�A�j���[�V�������s���B	false:�A�j���[�V�������s��Ȃ��A�A�j���[�V�������~�߂�
	gravity = true;						//	�d�̗͂L���Atrue:�d�͂������Afalse:�d�͂������Ȃ��A�󒆂ŐÎ~����

	collisionBool = true;				//	�R���W�����̗L���Atrue;�����蔻�肪�����B	false:�����蔻�肪�����Ȃ��B
	onGround = false;

	MoveX = true;
	MoveY = true;

	animTimeMax = 13;		//	animTimer�����̒l�𒴂����0�ɖ߂�
	animOneFlameTime = 0.2f;			//	animTimer�ɉ��Z��������ϐ�

	animFlame_W = 1;
	animFlame_H = 3;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;
	animationNo_H = 0.0f;

	speed = 4.0f;
	gravityNum = 0.1f;

	texNo = LoadTexture((char*)"data/texture/Waivers.png");


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	�I�u�W�F�N�g�̌��ݒn
	pos_bef = pos;
	r_pos = pos;					//	pos��Reset�l
	size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);					//	�I�u�W�F�N�g�̕`��͈�

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	�I�u�W�F�N�g���猩�������蔻��̒��S���W
	collisionSize = size / 3;				//	�����蔻��̃T�C�Y

	move = D3DXVECTOR2(0, 0);		//�ړ��������Z�b�g

}

void WAIVER::Reset()
{
}

void	 WAIVER::SetWaiverAbirities(D3DXVECTOR2 new_pos, D3DXVECTOR2	new_way,
	const	BALL::ABILITY_ATTACK&			AbilityTypes_AT,
	const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MB,
	const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MP)
{
	use = true;		//�g�p�t���O��true��
	active = true;
	pos = new_pos;	//���W���Z�b�g
	actionFirstPos = new_pos;
	D3DXVec2Normalize(&new_way, &new_way);

	move = new_way * speed;

	color.a = 1.0f;

	onGround = false;
	collisionBool = false;

	timer = 0;

	abilityType_at = AbilityTypes_AT;
	abilityType_mb = AbilityTypes_MB;
	abilityType_mp = AbilityTypes_MP;

	if (AbilityTypes_AT != BALL::NONE_ATTACK)
	{
		animationNo_H = 0;
	}
	if (AbilityTypes_MP != BALL::NONE_PLAYER)
	{
		animationNo_H = 1;
		move = new_way * speed * 1.2f;
	}
	if (AbilityTypes_MB != BALL::NONE_BALL)
	{
		animationNo_H = 2;
		move = new_way * speed * 1.4f;
	}

	/*switch (AbilityTypes_AT)
	{
	case	BALL::EXPLOSION:
		animationNo_H = 1;
		texSize_H = (1.0f / 7.0f);
		break;
	case	BALL::STICKY:
		animationNo_H = 2;
		texSize_H = (1.0f / 7.0f);
		break;
	default:
		break;
	}

	switch (AbilityTypes_MB)
	{
	case	BALL::HOMING:
		move = new_way * speed * 1.1f;
		animationNo_H = 3;
		texSize_H = (1.0f / 7.0f);
		break;
	case	BALL::BOUNCE:
		move = new_way * speed * 1.1f;
		animationNo_H = 4;
		texSize_H = (1.0f / 7.0f);
		break;
	}

	switch (AbilityTypes_MP)
	{
	case	BALL::SPRING:
		move = new_way * speed * 1.2f;
		animationNo_H = 5;
		texSize_H = (1.0f / 7.0f);
		break;
	case	BALL::TRACE:
		move = new_way * speed * 1.2f;
		animationNo_H = 6;
		texSize_H = (1.0f / 7.0f);
		break;

	default:
		break;
	}*/
}

void	InitWaiver()
{
	for (int i = 0; i < WAIVER_MAX; i++)
	{
		waiver[i].Init();
		waiver[i].Prepare();
	}
}

void	UninitWaiver()
{
	for (int i = 0; i < WAIVER_MAX; i++)
	{
		waiver[i].Uninit();
	}
}

void	UpdateWaiver()
{
	for (int i = 0; i < WAIVER_MAX; i++)
	{
		waiver[i].Update();
	}
}

void	DrawWaiver()
{
	for (int i = 0; i < WAIVER_MAX; i++)
	{
		waiver[i].Draw();
	}
}


void	SetWaiver(D3DXVECTOR2	wa_pos, D3DXVECTOR2	wa_way,
	const	BALL::ABILITY_ATTACK&			AbilityTypes_ATTACK,
	const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MOVE_BALL,
	const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MOVE_PLAYER)
{
	for (int i = 0; i < WAIVER_MAX; i++)
	{
		if (!waiver[i].GetUse())
		{
			waiver[i].SetWaiverAbirities(wa_pos, wa_way, AbilityTypes_ATTACK, AbilityTypes_MOVE_BALL, AbilityTypes_MOVE_PLAYER);
			break;
		}
	}
}

WAIVER* GetWaiver()
{
	return waiver;
}

