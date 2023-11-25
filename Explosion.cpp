#include "Explosion.h"
#include "Ball.h"

EXPLOSION	Explosion[EXPLOSION_MAX];
BALL* e_ball;

unsigned	int	g_ExplosionSE;

void	EXPLOSION::Update()
{
	//変更==============================================================================================================
	if (use == true)
	{
		if (animationOver == true)
		{
			use = false;
		}
	}

}

void	EXPLOSION::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	animationOver = false;

	source = NONE;

	animTimer = 0.0f;
	animTimeMax = 13.0f;
	animOneFlameTime = 0.5f;

	animFlame_W = 5;
	animFlame_H = 3;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/explosion.png");				//	LoadTextureの戻り値を記録する変数

	pos = D3DXVECTOR2(-100, -100);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 3, BASE_SIZE * 3);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size * 1 / 2;				//	当たり判定のサイズ
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void	EXPLOSION::Reset()
{

}






//===============================================================================================================================================
//	グラウンド管理プログラム
//===============================================================================================================================================

/*==================================
	グラウンド初期化
====================================*/
void	InitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Init();
		Explosion[i].Prepare();
	}

	g_ExplosionSE = LoadSound((char*)"data/SE/explosion.wav");
}

/*==================================
	グラウンド終了処理
====================================*/
void	UninitExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Uninit();
	}
}

/*==================================
	グラウンド更新処理
====================================*/
void	UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Update();
	}
}

/*==================================
	グラウンド描画処理
====================================*/
void	DrawExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		Explosion[i].Draw();
	}


}

void SetExplosion(D3DXVECTOR2 new_pos, D3DXVECTOR2 new_size, EXPLOSION::SOURCE sourceValue)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (Explosion[i].GetUse() == false)
		{
			Explosion[i].SetUse(true);
			Explosion[i].SetSource(sourceValue);
			Explosion[i].SetPosi(new_pos);
			Explosion[i].SetSize(new_size);
			Explosion[i].SetCollisionSize(new_size * 3 / 4);
			Explosion[i].SetAnimation(true);
			Explosion[i].SetAnimTimer(0.0f);
			Explosion[i].SetAnimationOver(false);

			PlaySound(g_ExplosionSE, 0);

			return;
		}
	}
	

}


/*==================================
	グラウンド取得
====================================*/

EXPLOSION*	GetExplosion()
{
	return	&Explosion[0];
}