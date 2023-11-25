
#include	"knife.h"

void	KNIFE::Update()
{
	if (use)
	{
		if (!(pos.x > 0 && pos.x < SCREEN_WIDTH))	use = false;
		if (!(pos.y > 0 && pos.y < SCREEN_HEIGHT))	use = false;

		pos_bef = pos;

		Move();
	}
}

void	KNIFE::Prepare()
{
	use = false;							//	オブジェクトの使用、true:Update、Drawを行える。	false:Update、Draw、どちらも行えない
	active = true;						//	移動の可不可、true:moveに値がある場合、移動できる。	false:moveに値があっても、移動できない
	animation = true;					//	アニメーションの可不可、true:アニメーションを行う。	false:アニメーションを行わない、アニメーションを止める
	gravity = true;						//	重力の有無、true:重力が働く、false:重力が働かない、空中で静止する

	collisionBool = true;				//	コリジョンの有無、true;当たり判定が働く。	false:当たり判定が働かない。
	onGround = false;

	MoveX = true;
	MoveY = true;

	texNo = LoadTexture((char*)"data/texture/trace_knife.png");

	animTimeMax = 1;		//	animTimerがこの値を超えると0に戻る
	animOneFlameTime = 1.0f;			//	animTimerに加算し続ける変数

	animFlame_W = 1;
	animFlame_H = 1;

	texSize_W = 1.0f / animFlame_W;
	texSize_H = 1.0f / animFlame_H;

	speed = 5.0f;

	pos = D3DXVECTOR2(0, 0);					//	オブジェクトの現在地
	pos_bef = pos;
	r_pos = pos;					//	posのReset値
	size = D3DXVECTOR2(BASE_SIZE, BASE_SIZE * 2);					//	オブジェクトの描画範囲

	collisionLocalPos = D3DXVECTOR2(0, 0);		//	オブジェクトから見た当たり判定の中心座標
	collisionSize = D3DXVECTOR2(BASE_SIZE / 2, BASE_SIZE / 2);				//	当たり判定のサイズ
}

void	KNIFE::Reset()
{

}


//===================================================================================
//	ナイフ管理プログラム
//===================================================================================
KNIFE	knife[KNIFE_MAX];

void	InitKnife()	//	ナイフの初期化
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Init();
		knife[i].Prepare();
	}
}

void	UninitKnife()	//	ナイフの終了処理
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Uninit();
	}
}

void	UpdateKnife()	//	ナイフの更新処理
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Update();
	}
}

void	DrawKnife()	//	ナイフの描画処理
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		knife[i].Draw();
	}
}

void	SetKnife(const	D3DXVECTOR2	pos,	D3DXVECTOR2	way)	//	ナイフのセット
{
	for (int i = 0; i < KNIFE_MAX; i++)
	{
		if (!knife[i].GetUse())
		{
			knife[i].SetUse(true);
			knife[i].SetPosi(pos);

			D3DXVec2Normalize(&way, &way);
			knife[i].SetMove(way * knife[i].GetSpeed());

			knife[i].SetAngle(VecToAng(D3DXVECTOR2(0, -1), way) * 2);

			break;
		}
	}
}

KNIFE*	GetKnife()
{
	return	knife;
}




















