#include "Spring.h"
#include "Explosion.h"
#include "Ball.h"

SPRING	g_Spring[SPRING_MAX];
BALL* spring_ball;

void	SPRING::Update()
{
	if (use == true)
	{
		timer++;

		if (timer >= DeleteTime && !OnSpring)	use = false;

		if (OnSpring)
		{
			if (animation)
			{
				if (animationOver)
				{
					animation = false;
					animationNo_W = animTimeMax - 1;
				}
			}
			else
			{
				if (animationOver)
				{
					if (timer > 60 / 2)
					{
						use = false;
						animationOver = false;
						animation = false;
						OnSpring = false;

						animationNo_W = 0.0f;
						timer = 0;
					}
				}
				else
				{
					animation = true;
					timer = 0;
				}
			}
		}
	}
}

void	SPRING::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	animationOver = false;

	animTimer = 0.0f;
	animTimeMax = 3.0f;
	animOneFlameTime = 0.5f;

	timer = 0;

	animFlame_W = 3;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。

	texNo = LoadTexture((char*)"data/texture/springBox.png");				//	LoadTextureの戻り値を記録する変数
	g_SpringSE = LoadSound((char*)"data/SE/spring_SE.wav");

	pos = D3DXVECTOR2(-100, -100);					//	オブジェクトの現在地
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 3);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(BASE_SIZE, BASE_SIZE);				//	当たり判定のサイズ
	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	spring_ball = GetBall();
}

void	SPRING::Reset()
{

}






//===============================================================================================================================================
//	グラウンド管理プログラム
//===============================================================================================================================================

/*==================================
	グラウンド初期化
====================================*/
void	InitSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Init();
		g_Spring[i].Prepare();
	}
}

/*==================================
	グラウンド終了処理
====================================*/
void	UninitSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Uninit();
	}
}

/*==================================
	グラウンド更新処理
====================================*/
void	UpdateSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Update();
	}
}

/*==================================
	グラウンド描画処理
====================================*/
void	DrawSpring()
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		g_Spring[i].Draw();
	}


}

void	SetSpring(D3DXVECTOR2 new_pos)
{
	for (int i = 0; i < SPRING_MAX; i++)
	{
		if (g_Spring[i].GetUse() == false)
		{
			g_Spring[i].SetUse(true);
			g_Spring[i].SetOnSpring(false);
			g_Spring[i].SetAnimation(false);
			g_Spring[i].SetAnimationOver(false);
			g_Spring[i].SetPosi(new_pos);
			g_Spring[i].SetTimer(0);

			break;
		}
	}


}


/*==================================
	グラウンド取得
====================================*/

SPRING*	GetSpring()
{
	return	&g_Spring[0];
}