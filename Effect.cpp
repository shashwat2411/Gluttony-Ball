
#include	"effect.h"
#include	"Ball.h"

BALL*	ef_Ball;

void	EFFECT::Update()
{
	if (use)
	{
		if (effect_type == ABSORB_R || effect_type == ABSORB_L)
		{
			if (animTimer >= 15 && absorbed_enemy->GetUse())
			{
				animOneFlameTime = 0.1f;
				absorbed_enemy->SetUse(false);
				SetEffects(D3DXVECTOR2(pos.x, pos.y + BASE_SIZE * 3), absorbed_enemy->GetSize(), BLOOD, absorbed_enemy);

				PlaySound(SENums[ABSORB_R], 0);
			}

			if (animationOver)
			{
				use = false;
				ef_Ball->SetUse(true);
			}
		}
		else if (effect_type == BLOOD)
		{
			if (animationOver)
			{
				use = false;
			}
		}
		else if (effect_type == SHINE)
		{
			timer++;

			if (timer >= ShiningTimeMax)
			{
				timer = 0;

				use = false;
			}

			Move();
		}
	}
}

void	EFFECT::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = true;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	animationOver = false;

	animTimer = 0.0f;
	animTimeMax = 10.0f;
	animOneFlameTime = 0.1f;

	animFlame_W = 5;
	animFlame_H = 2;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	//collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	TexNums[ABSORB_R] = LoadTexture((char*)"data/texture/BallEatting_01.png");
	TexNums[ABSORB_L] = LoadTexture((char*)"data/texture/BallEatting_02.png");
	TexNums[BLOOD] = LoadTexture((char*)"data/texture/blood.png");
	TexNums[SHINE] = LoadTexture((char*)"data/texture/shine.png");

	texNo = TexNums[ABSORB_R];				//	LoadTextureの戻り値を記録する変数

	SENums[ABSORB_R] = LoadSound((char*)"data/SE/eatting_SE.wav");

	pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size * 1 / 2;				//	当たり判定のサイズ
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	ef_Ball = GetBall();
}

void	EFFECT::Reset()
{

}

void	EFFECT::SetEffect(const	D3DXVECTOR2 new_pos, const D3DXVECTOR2 new_size, const EFFECT::EFFECT_TYPE	new_type, ENEMY*	new_enemy)
{
	use = true;
	pos = new_pos;
	size = new_size;

	timer = 0;

	animTimer = 0.0f;

	active = false;
	animation = true;
	animationOver = false;

	MoveY = false;

	effect_type = new_type;

	absorbed_enemy = new_enemy;

	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (new_type == ABSORB_R)
	{
		animTimer = 0.0f;
		animTimeMax = 20.0f;
		animOneFlameTime = 0.4f;

		animFlame_W = 5;
		animFlame_H = 4;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		pos = new_pos;
		pos.x -= BASE_SIZE;
		pos.y -= BASE_SIZE * 2;
		size = D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 10);

		texNo = TexNums[ABSORB_R];
	}
	if (new_type == ABSORB_L)
	{
		animTimer = 0.0f;
		animTimeMax = 20.0f;
		animOneFlameTime = 0.4f;

		animFlame_W = 5;
		animFlame_H = 4;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		pos = new_pos;
		pos.x += BASE_SIZE;
		pos.y -= BASE_SIZE * 2;
		size = D3DXVECTOR2(BASE_SIZE * 6, BASE_SIZE * 10);

		texNo = TexNums[ABSORB_L];
	}
	if (new_type == BLOOD)
	{
		animTimer = 0.0f;
		animTimeMax = 8.0f;
		animOneFlameTime = 0.4f;

		animFlame_W = 2;
		animFlame_H = 4;

		texSize_W = 1.0f / animFlame_W;
		texSize_H = 1.0f / animFlame_H;

		size = D3DXVECTOR2(BASE_SIZE * 12, BASE_SIZE * 4);

		texNo = TexNums[BLOOD];
	}
	if (new_type == SHINE)
	{
		active = true;
		animation = false;
		MoveY = true;

		texSize_W = 1.0f;
		texSize_H = 1.0f;

		size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE * 2);

		texNo = TexNums[SHINE];

		color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f);

		move = D3DXVECTOR2(0, -1);

		if (ef_Ball->GetAbilityAttack() != BALL::NONE_ATTACK)	color.r = 1.0f;
		if (ef_Ball->GetAbilityMoveBall() != BALL::NONE_BALL)	color.g = 1.0f;
		if (ef_Ball->GetAbilityMovePlayer() != BALL::NONE_PLAYER)	color.b = 1.0f;
	}
}

//==================================================================================
//	エフェクト管理プログラム
EFFECT	effect[EFFECT_MAX];

void	InitEffect()		//	エフェクト初期化
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].Init();
		effect[i].Prepare();
	}
}

void	UninitEffect()		//	エフェクト終了処理
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].Uninit();
	}
}

void	UpdateEffect()		//	エフェクト更新処理
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].Update();
	}
}

void	DrawEffect()		//	エフェクト描画処理
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		effect[i].Draw();

		if (effect[i].GetAbsorbedEnemy() != nullptr)
		{
			effect[i].GetAbsorbedEnemy()->Draw();
		}
	}
}

void	SetEffects(const	D3DXVECTOR2 new_pos, const D3DXVECTOR2 new_size, const EFFECT::EFFECT_TYPE	new_type, ENEMY*	new_enemy)		//	エフェクトの取得
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (!effect[i].GetUse())
		{
			effect[i].SetEffect(new_pos, new_size, new_type, new_enemy);

			return;
		}
		else if (i == 0 && (new_type == EFFECT::ABSORB_L || new_type == EFFECT::ABSORB_R))
		{
			effect[i].SetEffect(new_pos, new_size, new_type, new_enemy);

			return;
		}
	}
}

EFFECT*	GetEffects()		//	エフェクトの取得
{
	return	effect;
}















