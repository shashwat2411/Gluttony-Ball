#include "InterlockArrangement.h"
#include "collision.h"
#include "Ball.h"
#include "Button.h"

INTERLOCKARRANGEMENT interlockarrangement[BUTTON_MAX];

static	D3DXCOLOR	ColorsType[10] = { D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f), D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f),
D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f) };

void INTERLOCKARRANGEMENT::Update()
{
	if (use)
	{
		if (On_OffSwitch && texNo != texture2)	texNo = texture2;//テクスチャを切り替える
		else if (!On_OffSwitch && texNo != texture1)	texNo = texture1;
	}
}

void INTERLOCKARRANGEMENT::Prepare()
{
	use = false;						//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = false;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = false;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = false;					//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する
	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	MoveX = false;
	MoveY = false;
	ArrivePoint = false;

	texture1 = LoadTexture((char*)"data/texture/SwitchBlock_close.png");			//	LoadTextureの戻り値を記録する変数
	texture2 = LoadTexture((char*)"data/texture/SwitchBlock_open.png");

	texNo = texture1;

	size = D3DXVECTOR2(BASE_SIZE * 1, BASE_SIZE * 1);					//	オブジェクトの描画範囲
	collisionLocalPos = D3DXVECTOR2(0, 0);								//	オブジェクトから見た当たり判定の中心座標
	collisionSize = size;												//	当たり判定のサイズ

	On_OffSwitch = false;												//trueならスイッチがオンになりギミックが作動する


}

void INTERLOCKARRANGEMENT::Reset()
{

}

void INTERLOCKARRANGEMENT::SetInterlockArrangement(D3DXVECTOR2 new_pos,D3DXVECTOR2 new_size)
{
	use = true;		//使用フラグをtrueに
	pos = new_pos;	//座標をセット
	size = new_size;

	gravity = false;			//重力を無効化
	onGround = false;
	collisionBool = true;
}


//=============================================
//	ボタンに連動して作動するもの管理プログラム
//=============================================
/*==================================
	ボタンに連動して作動するもの初期化
====================================*/
void	InitInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Init();
		interlockarrangement[i].Prepare();
	}
}

/*==================================
	ボタンに連動して作動するもの終了処理
====================================*/
void	UninitInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Uninit();
	}
}

/*==================================
	ボタンに連動して作動するもの更新処理
====================================*/
void	UpdateInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Update();
	}
}

/*==================================
	ボタンに連動して作動するもの描画処理
====================================*/
void	DrawInterlockArrangement()
{
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		interlockarrangement[i].Draw();
	}
}

/*==================================
	ボタンに連動して作動するもののセット
====================================*/
void	SetInterlockArrangements(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	if (index < BUTTON_MAX)
	{
		if (!interlockarrangement[index].GetUse())
		{
			interlockarrangement[index].SetInterlockArrangement(pos, size * BASE_SIZE);

			interlockarrangement[index].SetColor(ColorsType[index]);

			interlockarrangement[index].SetCollisionSize(size * BASE_SIZE);
			interlockarrangement[index].SetTexSizeWidth(size.x);
			interlockarrangement[index].SetTexSizeHeight(size.y);
		}
	}
}

/*==================================
	ボタンに連動して作動するもの取得
====================================*/
INTERLOCKARRANGEMENT* GetInterlockArrangement()
{
	return	interlockarrangement;
}

