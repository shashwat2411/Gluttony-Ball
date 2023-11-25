#include "StickyBomb.h"
#include "Explosion.h"

STICKYBOMB	g_StickyBomb[STICKYBOMB_MAX];

void	STICKYBOMB::Update()
{
	if (use)
	{
		//変更==============================================================================================================
		counter += 1;

		if (counter % ExplosionTimeMax == 0)
		{
			counter = 0;
			SetExplosion(pos, D3DXVECTOR2(size.x * 2, size.x * 2), EXPLOSION::PLAYER);
			use = false;
			follower = nullptr;
		}

		if (animation)
		{
			if (animationOver)	animationOver = false;
		}
		else
		{
			if (counter >= ExplosionTimeMax / 2)	animation = true;
		}

		if (follower != nullptr)
		{
			pos = follower->GetPosi();

			if (follower->GetPosi().x + size.x < 0 || follower->GetPosi().x - size.x > SCREEN_WIDTH ||
				follower->GetPosi().y + size.y < 0 || follower->GetPosi().y - size.y > SCREEN_HEIGHT)	use = false;

			if (!(follower->GetUse()))	use = false;
		}

	}
}

void	STICKYBOMB::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	animationOver = false;

	animTimer = 0.0f;
	animTimeMax = 2.0f;
	animOneFlameTime = 0.1f;

	animFlame_W = 2;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/sticky_bomb.png");				//	LoadTextureの戻り値を記録する変数


	pos = D3DXVECTOR2(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE * 2, BASE_SIZE);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(size.x, size.y);				//	当たり判定のサイズ

	follower = nullptr;

	counter = 0;

	//SetStickyBomb(pos, size);
}

void	STICKYBOMB::Reset()
{

}






//===============================================================================================================================================
//	グラウンド管理プログラム
//===============================================================================================================================================

/*==================================
	グラウンド初期化
====================================*/
void	InitStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		g_StickyBomb[i].Init();
		g_StickyBomb[i].Prepare();
	}
}

/*==================================
	グラウンド終了処理
====================================*/
void	UninitStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		g_StickyBomb[i].Uninit();
	}
}

/*==================================
	グラウンド更新処理
====================================*/
void	UpdateStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == true) { g_StickyBomb[i].Update(); }
	}
}

/*==================================
	グラウンド描画処理
====================================*/
void	DrawStickyBomb()
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == true) { g_StickyBomb[i].Draw(); }
	}


}

void	SetStickyBomb(D3DXVECTOR2 new_pos, ENEMY*	stickEnemy, float angle)
{
	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse())
		{
			if (g_StickyBomb[i].GetFollower() != nullptr)
			{
				if (g_StickyBomb[i].GetFollower() == stickEnemy)	return;
			}
		}
	}

	for (int i = 0; i < STICKYBOMB_MAX; i++)
	{
		if (g_StickyBomb[i].GetUse() == false)
		{
			g_StickyBomb[i].SetUse(true);
			g_StickyBomb[i].SetPosi(new_pos);
			g_StickyBomb[i].SetAngle(angle);
			g_StickyBomb[i].follower = stickEnemy;
			g_StickyBomb[i].SetCounter(0);
			g_StickyBomb[i].SetAnimation(false);
			g_StickyBomb[i].SetAnimationOver(false);

			return;
		}
	}
}


/*==================================
	グラウンド取得
====================================*/

STICKYBOMB*	GetStickyBomb()
{
	return	&g_StickyBomb[0];
}