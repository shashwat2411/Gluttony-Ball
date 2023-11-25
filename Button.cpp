#include "Button.h"
#include "collision.h"
#include "Ball.h"
#include "InterlockArrangement.h"

BUTTON button[BUTTON_MAX];

BALL*	b_ball;
INTERLOCKARRANGEMENT*	b_inter;

static	D3DXCOLOR	ColorsType[10] = { D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 1.0f, 0.2f, 1.0f), D3DXCOLOR(1.0f, 0.2f, 1.0f, 1.0f), D3DXCOLOR(0.2f, 1.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 0.7f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 1.0f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f),
D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) };

void BUTTON::Update()
{
	if (use)
	{
		if (collisionBool)
		{
			if (On_OffSwitch && animationNo_W != 1)			animationNo_W = 1;
			else if (!On_OffSwitch && animationNo_W != 0)	animationNo_W = 0;
		}
		else
		{
			if (!GetCollision(pos + collisionLocalPos, pos_bef + collisionLocalPos, collisionSize, b_ball->GetPosi() + b_ball->GetCollisionPos(),
				b_ball->GetCollisionSize()))
			{
				collisionBool = true;
			}
		}
	}
}


void BUTTON::Prepare()
{
	use = false;						//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;					//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	MoveX = false;
	MoveY = false;
	ArrivePoint = false;

	SaveAble = false;

	texNo = LoadTexture((char*)"data/texture/laver_button.png");			//	LoadTextureの戻り値を記録する変数
	g_ButtonSE = LoadSound((char*)"data/SE/switchLaber_SE.wav");

	animFlame_W = 2;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	size = D3DXVECTOR2(BASE_SIZE*1, BASE_SIZE*1);						//	オブジェクトの描画範囲
	collisionLocalPos = D3DXVECTOR2(0, 0);								//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size;												//	当たり判定のサイズ

	On_OffSwitch = false;	//trueならスイッチがオンになりギミックが作動する

	b_ball = GetBall();
	b_inter = GetInterlockArrangement();
}

void BUTTON::Reset()
{

}

void BUTTON::SetButton(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off)
{
	use = true;		//使用フラグをtrueに
	SetPosi(pos);	//座標をセット

	gravity = false;			//重力を無効化
	onGround = false;
	BallCollide = false;
	collisionBool = true;
	On_OffSwitch = button_off;

	if (On_OffSwitch)	animationNo_W = 1;
	else				animationNo_W = 0;
}



//=============================================
//	ボタン管理プログラム
//=============================================

/*==================================
	ボタンブロック初期化
====================================*/
void	InitButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Init();
		button[i].Prepare();
	}
}

/*==================================
	ボタンブロック終了処理
====================================*/
void	UninitButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Uninit();
	}
}

/*==================================
	ボタンブロック更新処理
====================================*/
void	UpdateButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Update();
	}
}

/*==================================
	ボタンブロック描画処理
====================================*/
void	DrawButton()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		button[i].Draw();
	}
}

/*==================================
	ボタンブロックのセット
====================================*/
void	SetButtons(D3DXVECTOR2 pos, D3DXVECTOR2	size, const	bool	button_off, int index)	//	ボタンのセット
{
	if (index < BUTTON_MAX)
	{
		if (!button[index].GetUse())
		{
			button[index].SetButton(pos, size, button_off);
			button[index].SetColor(ColorsType[index]);

			b_inter[index].SetOn_Off_InterlockArrangement(button_off);
		}
	}
}
/*==================================
	ボタンブロック取得
====================================*/
BUTTON* GetButton()
{
	return	button;
}

