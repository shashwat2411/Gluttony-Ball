

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
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = true;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	onGround = false;

	MoveX = true;
	MoveY = true;

	animTimeMax = 13;		//	animTimerがこの値を超えると0に戻る
	animOneFlameTime = 0.2f;			//	animTimerに加算し続ける変数

	animFlame_W = 1;
	animFlame_H = 3;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;
	animationNo_H = 0.0f;

	speed = 4.0f;
	gravityNum = 0.1f;

	texNo = LoadTexture((char*)"data/texture/Waivers.png");


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size / 3;				//	当たり判定のサイズ

	move = D3DXVECTOR2(0, 0);		//移動方向をセット

}

void WAIVER::Reset()
{
}

void	 WAIVER::SetWaiverAbirities(D3DXVECTOR2 new_pos, D3DXVECTOR2	new_way,
	const	BALL::ABILITY_ATTACK&			AbilityTypes_AT,
	const	BALL::ABILITY_MOVE_BALL&		AbilityTypes_MB,
	const	BALL::ABILITY_MOVE_PLAYER&		AbilityTypes_MP)
{
	use = true;		//使用フラグをtrueに
	active = true;
	pos = new_pos;	//座標をセット
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

